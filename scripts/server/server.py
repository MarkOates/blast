# server.py
from http.server import BaseHTTPRequestHandler, HTTPServer
import socket


# Notes on setting up virtual environment https://chatgpt.com/c/6839fa16-8b64-800f-9286-c0025778fc5f
# Step 1: Create a virtual environment
#   python3 -m venv venv
# Step 2: Activate the virtual environment
#   source venv/bin/activate
# Step 3: Install the requests package
#   pip install requests
#   python client.py <target_ip>
#   deactivate


def get_local_ip():
   try:
      # Connect to an external address to get the proper interface
      s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
      s.connect(("8.8.8.8", 80))
      ip = s.getsockname()[0]
      s.close()
      return ip
   except Exception:
      return "127.0.0.1"

class SimpleHandler(BaseHTTPRequestHandler):
   def do_POST(self):
      content_length = int(self.headers['Content-Length'])
      post_data = self.rfile.read(content_length)
      print(f"Received: {post_data.decode('utf-8')}")
      self.send_response(200)
      self.end_headers()

if __name__ == "__main__":
   local_ip = get_local_ip()
   port = 8000
   print(f"Server running at http://{local_ip}:{port}")
   server = HTTPServer(('0.0.0.0', port), SimpleHandler)
   server.serve_forever()

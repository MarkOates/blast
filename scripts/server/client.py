# client.py
# Run with "python3 client.py 192.168.1.10" (or passing in your friend's IP address here

import requests
import sys
import re

def is_valid_ip(ip_address):
   pattern = r'^(\d{1,3}\.){3}\d{1,3}$'
   if not re.match(pattern, ip_address):
      return False
   parts = ip_address.split('.')
   return all(0 <= int(part) <= 255 for part in parts)

if len(sys.argv) != 2:
   print("Usage: python3 client.py <target_ip>")
   sys.exit(1)

target_ip = sys.argv[1]

if not is_valid_ip(target_ip):
   print("Error: Invalid IP address format.")
   sys.exit(1)

url = f'http://{target_ip}:8000'
payload = 'Hello from your friend!'

try:
   response = requests.post(url, data=payload)
   print(f"Sent message, got status code: {response.status_code}")
except requests.exceptions.RequestException as e:
   print(f"Failed to send message: {e}")

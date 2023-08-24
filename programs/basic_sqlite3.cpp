#include <stdio.h>
#include <sqlite3.h> 


int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("test.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   sqlite3_close(db);
}


//void encode(std::string& data) {
    //std::string buffer;
    //buffer.reserve(data.size());
    //for(size_t pos = 0; pos != data.size(); ++pos) {
        //switch(data[pos]) {
            //case '&':  buffer.append("&amp;");       break;
            //case '\"': buffer.append("&quot;");      break;
            //case '\'': buffer.append("&apos;");      break;
            //case '<':  buffer.append("&lt;");        break;
            //case '>':  buffer.append("&gt;");        break;
            //default:   buffer.append(&data[pos], 1); break;
        //}
    //}
    //data.swap(buffer);
//}


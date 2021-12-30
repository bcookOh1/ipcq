
// g++ -Wall -std=c++17 -g -Id:/sw_libs/c++/boost_1_78_0 -o reader.exe reader.cpp IpcQueue.cpp IpcQueueReader.cpp
// g++ -Wall -std=c++17 -g -Id:/sw_libs/c++/boost_1_78_0 -o reader.exe reader.cpp -LD:/VscProjects/message_queue -lipcq

#include <iostream>
#include <string>
#include "IpcQueueReader.h"

using namespace std;

int main (){

   cout << "startup" << endl;

   IpcQueueReader reader(QueueName);
   reader.Open();

   size_t count = 0;
   int result  = reader.GetMsgCount(count);
   if(result == 0){
      do { 
         unsigned int cmd;
         string s;
         result = reader.Pop(cmd, s);
         if(result != 0){
            cout << "error: " << reader.GetErrorStr() << endl;
            break;
         }
         else {
            cout << "(" << cmd << " " << s << ")" << endl;
            result  = reader.GetMsgCount(count);
            if(result != 0){
               cout << "error: " << reader.GetErrorStr() << endl;
               break;
            } // end if 
         } // end if 

      } while(count > 0);
   } 
   else {
      cout << "error: " << reader.GetErrorStr() << endl;
   } // end if 

   return 0;
} // end main
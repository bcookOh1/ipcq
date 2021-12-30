
// g++ -Wall -std=c++17 -g -Id:/sw_libs/c++/boost_1_78_0 -o writer.exe writer.cpp IpcQueue.cpp IpcQueueWriter.cpp

#include <iostream>
#include <string>
#include "IpcQueueWriter.h"

using namespace std;

int main (){

   cout << "startup" << endl;

   IpcQueueWriter writer(QueueName);
   writer.Open();
   string s;
   s = "write string 1";
   writer.Push(10,s);
   s = "write string 2";
   writer.Push(9,s);
   s = "write string 3";
   writer.Push(8,s);
   s = "write string 4";
   writer.Push(7,s);

   cout << "error: " << writer.GetErrorStr() << endl;
   size_t count = 0;
   writer.GetMsgCount(count);
   cout << "count: " << count << endl;
   cout << "error: " << writer.GetErrorStr() << endl;

   return 0;
} // end main

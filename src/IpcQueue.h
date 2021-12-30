
#pragma once

#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost::interprocess;

const string QueueName = "TmQueue";
const size_t QueueSize = 5;
const size_t CvpValueLength = 256;

// the message, command value pair
struct Cvp {
   unsigned int cmd;
   char value[CvpValueLength];
}; // end struct

namespace ipcq {

class IpcQueue {
public:
   IpcQueue(const string &queueName);
   virtual ~IpcQueue();
   
   virtual int Open() = 0;
   int Clear();
   int Close();

   int GetMsgCount(size_t &count);
   string GetErrorStr(){return _errorStr;}

protected:

   string _queueName;
   unique_ptr<message_queue> _mq;
   string _errorStr;

   int StringToValue(const string &inStr, char outVal[]);
   int ValueToString(const char *inVal, string &outStr);
   
}; // end class

} // end namespace

#include "IpcQueue.h"

namespace ipcq {

IpcQueue::IpcQueue(const string &queueName){
   _mq = nullptr;
   _queueName = queueName;
} // end ctor 

IpcQueue::~IpcQueue(){
} // dtor 


int IpcQueue::Clear(){
   int ret = 0;

   if(_mq == nullptr) return -1;

   while(_mq->get_num_msg() != 0){

      unsigned int priority;
      message_queue::size_type recvd_size;
      Cvp cvp{0};

      _mq->receive(&cvp, sizeof(Cvp), recvd_size, priority);

   } // end while

   return ret;
} // end Clear


int IpcQueue::Close(){
   int ret = 0;
   _errorStr.clear();

   if(_mq != nullptr) {
      Clear();
      message_queue::remove(_queueName.c_str());
   }
   else {
      _errorStr = "message queue is not open";
      ret = -1;
   } // end if 
   
   return ret;
} // end Close

int IpcQueue::GetMsgCount(size_t &count) {
   int ret = 0;
   _errorStr.clear();

   if(_mq != nullptr) {
      count = static_cast<size_t>(_mq->get_num_msg());
   }
   else {
      count = 0;
      _errorStr = "message queue is not open";
      ret = -1;
   } // end if 
   
   return ret;
} // end GetMsgCount



int IpcQueue::StringToValue(const string &inStr, char outVal[]) {
   int ret = 0;
   _errorStr.clear();

   size_t length = inStr.length();
   size_t i = 0;

   // check if too long
   if(length < CvpValueLength) {
      for(char c : inStr) 
         outVal[i++] = c;
   }
   else {
      _errorStr = "inStr is too long";
      return -1;
   } // end if 

   return ret;
} // end StringToValue


int IpcQueue::ValueToString(const char *inVal, string &outStr) {
   int ret = 0;
   _errorStr.clear();
   
   // check if too long
   if(strlen(inVal) < CvpValueLength) {
      outStr.assign(inVal);
   }
   else {
      _errorStr = "inVal is too long";
      ret = -1;
   } // end if 

   return ret;
} // end ValueToString

} // end namespace
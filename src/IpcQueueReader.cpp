
#include "IpcQueueReader.h"

namespace ipcq {

IpcQueueReader::IpcQueueReader(const string &queueName) : 
   IpcQueue(queueName) {
} // end ctor 

IpcQueueReader::~IpcQueueReader(){
} // end dtor 


int IpcQueueReader::Open(){
   int ret = 0;
   
   BOOST_TRY {

      // boost interprocess is not copyable so the following actually moves the pointer
      _mq = unique_ptr<message_queue>(
         new message_queue(open_only, _queueName.c_str()));
   }
   BOOST_CATCH(interprocess_exception &ex){
      _errorStr = ex.what();
      ret = -1;
   } BOOST_CATCH_END

   return ret;
} // end Open

int IpcQueueReader::Pop(unsigned int &cmd, string &value){
   int ret = 0;

   if(_mq != nullptr) {

      unsigned int priority{0};
      message_queue::size_type recvd_size{0};
      Cvp cvp{0};

      bool result = _mq->try_receive(&cvp, sizeof(Cvp), recvd_size, priority);
      if(result != true){
         _errorStr = "message not available";
         ret = -1;
      }
      else {
         cmd = cvp.cmd;
         result = ValueToString(cvp.value, value);
         if(result != 0){
            // _errorStr set in ValueToString
            ret = -1;
         } // end if 
      } // end if 
      
   }
   else { 
      _errorStr = "message queue is not open";
      return -1;
   } // end if 

   return ret;
} // end Pop

} // end namespace
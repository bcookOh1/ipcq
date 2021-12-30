
#include "IpcQueueWriter.h"

namespace ipcq {

IpcQueueWriter::IpcQueueWriter(const string &queueName) : 
   IpcQueue(queueName) {
} // end ctor

IpcQueueWriter::~IpcQueueWriter() {
} // end dtor

int IpcQueueWriter::Open(){
   int ret = 0;
   _errorStr.clear();
      
   BOOST_TRY {
 
      message_queue::remove(_queueName.c_str());

      // boost interprocess is not copyable so the following actually moves the pointer
      _mq = unique_ptr<message_queue>(
         new message_queue(create_only, _queueName.c_str(), QueueSize, sizeof(Cvp))); 
   }
   BOOST_CATCH(interprocess_exception &ex){
      _errorStr = ex.what();
      ret = -1;
   } BOOST_CATCH_END

   return ret;
} // end open

int IpcQueueWriter::Push(unsigned int cmd, const string &value){
   int ret = 0;
   _errorStr.clear();

   if(_mq != nullptr) {
      Cvp cvp{0};
      cvp.cmd = cmd;

      int result = StringToValue(value, cvp.value);
      if(result == 0) {

         unsigned int priority{0};

         bool result = _mq->try_send(&cvp, sizeof(Cvp), priority);
         if(result != true){
            _errorStr = "message queue is not available";
            ret = -1;
         } // end if 
      
      }
      else {
         // _errorStr set in StringToValue()
         ret = -1;
      } // end if 

   }
   else { 
      _errorStr = "message queue is not open";
      ret = -1;
   } // end if 

   return ret;
} // end Push

} // end namespace


#include "IpcQueue.h"
#include <string>

using namespace std;

namespace ipcq {

class IpcQueueReader : public IpcQueue {
public:

   IpcQueueReader(const string &queueName);
   ~IpcQueueReader();

   virtual int Open() override;
   int Pop(unsigned int &cmd, string &value);

private:


}; // end class

} // end namespace 
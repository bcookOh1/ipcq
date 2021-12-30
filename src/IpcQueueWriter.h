

#include "IpcQueue.h"
#include <string>

using namespace std;

namespace ipcq {

class IpcQueueWriter : public IpcQueue {
public:

   IpcQueueWriter(const string &queueName);
   ~IpcQueueWriter();

   virtual int Open() override;
   int Push(unsigned int cmd, const string &value);

private:


}; // end class

} // end namespace
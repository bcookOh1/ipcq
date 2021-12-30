12-30-2021
this a library is used in the Turing Machine Simulator and show_diagram programs.
It is compiled with mingw64 with -std=c++17 (c++20 didn't work, seemed to be missing a dll at load?).
It uses Boost::interprocess::messsage_queue for the queue data structure. The memory mapped shared file is 
at C:\ProgramData\boost_interprocess.
  
The classes IpcQueueWriter and IpcQueueReader use std::string.  

The library is built like this:
g++ -Wall -std=c++17 -Id:/sw_libs/c++/boost_1_78_0 -c IpcQueue.cpp IpcQueueReader.cpp IpcQueueWriter.cpp
ar rcs libipcq.a IpcQueue.o IpcQueueReader.o IpcQueueWriter.o, the result is libipcq.a. 

the writer.exe and reader.exe (driver programs) are built like this in the src directory:
g++ -Wall -std=c++17 -g -Id:/sw_libs/c++/boost_1_78_0 -I./ -o reader.exe reader.cpp -L./ -lipcq
g++ -Wall -std=c++17 -g -Id:/sw_libs/c++/boost_1_78_0 -I./ -o writer.exe writer.cpp -L./ -lipcq
(note: g++ only wants "ipcq" for the library name) 

To use in the Turing Machine Simulator and show_diagram programs: 
For headers just just use /ipcq/include/ipcq.h which includes both IpcQueueWriter.h and IpcQueueReader.h. 
The library itself is /ipcq/lib/libipcq.a.

 



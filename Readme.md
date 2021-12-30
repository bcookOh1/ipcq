12-19-2021
this a library for use in the Turing Machine Simulator and state diagram display programs.
It is compiled with mingw64 with -std=c++17 (c++20 didn't work).
It uses Boost::interprocess::messsage_queue for the queue data structure.The memory mapped shared file is 
here: C:\ProgramData\boost_interprocess.
  
The classes IpcQueueWriter and IpcQueueReader use std::string.  

The library is built like this:
g++ -Wall -std=c++17 -Id:/sw_libs/c++/boost_1_77_0 -c IpcQueue.cpp IpcQueueReader.cpp IpcQueueWriter.cpp
ar rcs libipcq.a IpcQueue.o IpcQueueReader.o IpcQueueWriter.o

the result is libipcq.a. 

the reader.exe is built like this (in the source directory):
g++ -Wall -std=c++17 -g -Id:/sw_libs/c++/boost_1_77_0 -I./ -o reader.exe reader.cpp -L./ -lipcq
(note g++ only wants "ipcq" for the lib include 

for use in the Turing Machine Simulator and state diagram display programs use: 

for headers IpcQueueWriter.h and IpcQueueReader.h, 
note just use ipcq.h, it will include both of these headers

D:\sw_libs\c++\ipcq\include

for the library libipcq.a

D:\sw_libs\c++\ipcq\lib
 



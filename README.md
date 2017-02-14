# Operating-System-Assimilation
## This program handles the basic data structures (i.e. the devices and their queues All queues are FIFO) in an operating system

This program has two stages of operation:
### 1/"sys gen" section:
*	The system installer (me) specifies how many devices of each type (printers and disks) are in the system
*	Program asks user how much memory our system has (assume that there is only one CPU).
### 2/"running" section:
*	Handle system calls issued by the process currently controlling the CPU (lower case will indicate system calls).
*	Handle interrupts that signal various system events (Capital letters will be interrupts). All interrupts will be handled "atomically" (one can not interrupt an interrupt handling routine) and will return control to the interrupted process. ###### These calls and interrupts will actually be indicated by keyboard input

*->An "A" entered on the keyboard indicates the arrival of a process. 
*->System asks how much memory this process will need. 
*->Allocate this memory using "best-fit" approach.

#### The handling routine should:
1.	Create a PCB for this process, 
2.	Generate a PID,
3.	Enqueue the PCB into the Ready Queue. 
If the CPU is not occupied, 
->The first process in the Ready Queue should be passed to the CPU. 
->The process in the CPU can issue system calls. 
One of these is "t", which indicate that the process is terminating. 
-> The process currently in the CPU will request "printer 1" by issuing a "p1" on the keyboard, and Printer 1 will signal an interrupt indicating completion of the task at the head of its queue with a "P1" being entered at the keyboard. Similarly, "d3" to request disk 3 and "D3" to signal D3's completion. On such a "task completed" interrupt the PCB for that process should be moved to the back of the Ready Queue. After a system call (e.g. "p3") is made, you should prompt the process (that's me) for various parameters.
These should:
•	Include the filename, whether the requested action is a "read" or a "write" ("r" or "w" on the keyboard; You can only write to a printer, so no need to prompt it) and, if a write, what is the file size. The PCB for this process and the associated information should be enqueued to the appropriate device queue.

The OS should recycle the PCB (but not the PID), in other words reclaim the now unused memory.

ATT : Each non-CPU device has a "name" consisting of a letter and an integer. 


"S" on the keyboard indicates a "Snapshot" interrupt (simulating a Big Button on the Sys-op's console):
•	The handling routine should wait for the next keyboard input and, 
⎝	if "r":
o	Show the PIDs of the processes in the Ready Queue, 
⎝	if "p":
o	Show the PIDs of the processes in the printer queues.
o	Printer specific information: I/O queue, 
o	Name of the file that is currently printing
o	Its size
⎝	if "d":
o	Display I/O queue,  
o	Name of the file that is currently printing, 
o	Size
o	Type of operation ("read" or "write")). 
o	Be sure the contents of the queues don't scroll of a 24 line. screen. 
⎝	If "S" interrupt is followed by "m":
o	Show the current state of memory (show where each process is located in memory)




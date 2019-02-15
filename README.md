# OS Project
To run the program, type make all into the command line
A solution executable will appear. Type ./OS to run the executable.
You would be prompted to enter 2 numbers, first is the RAM capacity, and the second is how much hard disk you want for this simulation
The commands are
"A Number Number2" which creates a new process with priority of Number that requires Number2 bytes of memory
"t" will terminate the current running process and assign an new process to CPU
"d number file_name" Process currently using CPU will request hard disk number and wants to read of write the file_name
"D number" Process in Hard Disk number has finished and moves back to ready queue
"S r" shows process using CPU and all other process in Ready Queue
"S i" shows process using hard Disk and all other process in I/O queue
"S m" shows state of memory and the memory address of each process.
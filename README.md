# Some tasks using MPI
One of 6th semester tasks

This program includes two modes of work: 
time measuring wich measures work speed of four MPI functions(MPI_Bcast, MPI_Gather, MPI_Scatter, MPI_Reduce for MPI_SUM) 
and test mode which tests my implementation of these functions.
## Time measuring
This mode of operation measures the data transfer time a specified number of times for each of these functions 
(as well as for my implementations) and then calculates the average value. 
Measurements are carried out separately for the root process and for the rest. 
The size of the buffer for transmission and the number of iterations are set after the program starts. 
The default variable type is int.
## Test mode
If you select the test mode, the program will take the data for the buffers from the test1.txt file 
and after execution will compare the result with the result you gave in the same file.
>**Do not change the test1.txt file format for normal program execution.**

You can only change data.

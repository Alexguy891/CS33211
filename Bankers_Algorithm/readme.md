# Banker's Algorithm Sequence Calculator
For calculating safe or unsafe sequences using the banker's algorithm.

### What is banker's algorithm for?
Banker's algorithm is an algorithm used to avoid deadlock and allocate resource for programs. Simply put, the algorithm tests the satefy of allocating resources by testing all possible activities before allocating any resources to a process. The algorithm is used to ensure safe resource sharing for processes within an operating system.

### How does the algorithm work?
Banker's algorithm is easiest explained through the example that gives the algorithm its name. Considering a bank has `n` accounts and the sum of all money held in the accounts is `x`. If someone wants to loan `y` amount of money from the bank, the bank will check if `x - y > x` to determine if the loan will be given. This is to prevent any issues if all account holders decided to withdraw all their money at once. In other words, the total amount of money loaned off must always be less than the total amount of money in all accounts combined.

### How does this program work?
This program first takes an input from a `input.csv` file that is formatted in a specific way. The file data is read into 3 vectors, `all` for the allocated resources matrix, `max` for the maximum resources matrix, and `ava` for the available resources list. The program then generates the needed resource matrix called `nee` by subtracting the maximum resource values by the allocated resource values. The program will print all the resource matrices in console to be verified. The program then iterates through each process, determining whether or not there is a position in the sequence in which the process will finish and its needed resources will be met. This does so by continously looping from 0 to `n`, where `n` represents the number of processes, until it finds a position where the needed resource values are all less than the availble resources. This will continue until either all finishable processes are marked finished, though it is possible a process may not have a position in the sequence where it can finish. Then the program iterates through all points in the finish array, and checks if all processes were finished. If not, the program will print `Sequence is unsafe`, otherwise, the program prints the processes in order of the safe sequence.

### How to format your csv file
* Each row of the matrices must be delimited by a newline character.
* Each cell of the matrix must be delimited by a space character.
* To separate columns by matrix, they must be delimited by a `,`.
* The file must be named as `input.csv`

#### Example:
For an allocated resource matrix of:
```
2 3 2
1 2 3
1 2 4
5 1 3
2 0 0
```
an max resource matrix of:
```
6 7 4
2 3 3
2 2 4
6 2 5
2 3 3
```
and an availble resource list of 
```
10 5 6
```
your file must be formatted as
```
2 3 2, 6 7 4, 10 5 6
1 2 3, 2 3 3,
1 2 4, 2 2 4,
5 1 3, 6 2 5,
2 0 0, 2 3 3,
```
### How to use this program:
1. Download the source files into a directory.
2. Create or add your `input.csv` file into the same directory.
3. Open your terminal in the directory.
4. Compile the program first using
```
g++ bankers.cpp -o bankers
```
5. Then run the program using
``` 
./bankers
```
#### Example:
If my files are located in my Documents folder on Ubuntu and my .csv file is:
```
0 1 0,7 5 3,3 3 2
2 0 0,3 2 2,
3 0 2,9 0 2,
2 1 1,2 2 2,
0 0 2,4 3 3,
```
then my terminal would like like:
```
$ user@linxpc:~/Documents$ g++ bankers.cpp -o bankers
$ user@linxpc:~/Documents$ ./bankers
$
$ ***Alloc resource table***
$ 0 1 0 
$ 2 0 0 
$ 3 0 2 
$ 2 1 1 
$ 0 0 2 
$
$ ***Max resource table***
$ 7 5 3 
$ 3 2 2 
$ 9 0 2 
$ 2 2 2 
$ 4 3 3 
$
$ ***Available resource list***
$ 3 3 2 
$
$ ***Needed resource list***
$ 7 4 3 
$ 1 2 2 
$ 6 0 0 
$ 0 1 1 
$ 4 3 1 
$
$ Safe sequence is: 
$  P1 to P3 to P4 to P0 to P2
```

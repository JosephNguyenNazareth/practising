# MATRIX MULTIPLICATION
Note: At first, we copy the files matrix a and b to the folder containing the project. After running the program, we open file *.out to get the result.
## Matrix Iterative algorithm
#### a) Overview
By the common way, we use 3 loops to calculate the product c of two matrices a,b. It costs O(n^3).
#### b) Description
Like in Math, we will calculate sum of products row i in matrix a with every column j in matrix b. Every sum of product of row i and column j we have cell c[i][j] of matrix result c.
#### c) Implementation
This algorithm is implemented in C++, using package "chrono" to counting time with millisecond accuracy. We use 3 loops, loop i traverses row, loop j traverses column, loop k calculates sums of product and record the result of cell c[i][j].  Source code is in the attached file.
#### d) Instruction
For best result, algorithms will read the same data from file. We run source code by just using Visual Studio, add file .cpp corresponding with this algorithm, then choose menu Debug->Start debugging.
## Divide and Conquer algorithm
#### a) Overview
This algorithm relies on block partitioning to multiply two matrices. It makes heavy use of recursions to achieve the final product. However, the algorithm runs in O(n^3) time, the same as the traditional method.
### b) Description
Specifically, the algorithm only works with square matrices whose dimensions are powers of two. For the multiplication of two matrices A and B, we start first by dividing each matrix into four blocks of equal dimensions: A_11, A_12, A_21, A_22, B_11, B_12, B_21, B_22. We then proceed to multiply the blocks together using the traditional method. Finally, we put the product blocks C_11, C_12, C_21, C_22 back together to get the final result. There are 8 multiplications in total, plus 4 additions.
### c) Implementation
Divide & Conquer algorithm is measured in C++. We use <chrono> to compute the time necessary for the algorithm to run.
### d) Instruction
Divide and Conquer is coupled with the iterative Method (naive) inside the matrix.test.cpp file. Simply compile the file and then run the output file to see the results of the tests.
Divide & Conquer
## Cannon's algorithm
#### a) Overview
Naive algorithm costs O(n^3). Thanks to Cannon algorithm, we can reduce the complexity down (n^3)/p with: p is the number of block after partition.
#### b) Description
This algorithm is a parallel algorithm, so it is faster than normal algorithm. As we know, normal matrix multiplication algorithm is a sequential algorithm, it uses a process to run, but Cannon's algorithm uses many processes to execute. Tasks of this algorithm is: Shift left row, shift up column, calculate the product a[i][j]* b[i][j] after shift and store in c[i][j], add sum of temp matrix to create result. Example, we uses process 0 to add temp matrix and calculate a[i][j]*b[i][j], process 1 to Shift left row, process 2 to Shift up column. Those process also communicate (send or receive) information between them.
#### c) Implementation
Cannon algorithm is implemented on C++, using package "chrono" to counting time with millisecond accuracy.
#### d) Instruction
We will use source code in file attach, but this algorithm is implemented by sequential algorithm. Sorry, I will give you the parallel algorithm of it as soon as possible.
For best result, algorithms will read the same data from file. We run source code by just using Visual Studio, add file .cpp corresponding with this algorithm, then choose menu Debug->Start debugging. Wait for result...
## Sub-cubic Algorithm
### 1. Strassen's Algorithm
#### a) Overview
Naive algorithm costs O(n^3). Thanks to Strassen, we can reach to O(n^(2.8))
#### b) Description
Strassen algorithm has a special feature: Instead of doing multiplication by nxnxn as common is mathematics, this turn to a whole new method.
The base case is 2x2 matrix, which is usually be multiplied in style of 2x2x2 = 8 loops; on the other hand, Strassen uses his greedy to cut off one loop, which means, in his algorithm, there are only 7 loops!
The most interesting matter is how he can find and research in that way; however, we can save time for this innovation.
#### c) Implementation
Strassen algorithm is implemented in C++, using package "chrono" to counting time with millisecond accuracy.
#### d) Instruction
At first, type in source code the size of the matrix (must be 2 exponents), then compile the program.
For best result, algorithms will read the same data from file. We run source code by just using Visual Studio, add file .cpp corresponding with this algorithm, then choose menu Debug->Start debugging. Wait for result...
### 2. Coppersmith - Winograd algorithm
New technique and research give us better chance for completely computing multiplication as fast as have ever seen.
O(n^(2.3)) is the result of years or attempting.
However, as having been criticised by experts, this algorithm is not practical due to its complex code and description. This often applies in strong hardware computer for vast of inputs.
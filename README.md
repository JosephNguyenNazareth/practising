# MATRIX MULTIPLICATION

## Sub-cubic Algorithm
### 1. Strassen's Algorithm

#### a) Overview
Naive algorithm costs O(n^3). Thanks to Strassen, we can reach to O(n^(2.8))
#### b) Description
Strassen algorithm has a special feature: Instead of doing multiplication by nxnxn as common is mathematics, this turn to a whole new method.
The base case is 2x2 matrix, which is usually be multiplied in style of 2x2x2 = 8 loops; on the other hand, Strassen use his greedy to cut off one loop, which mean, in his algorithm, there are only 7 loops!
The most interesting matter is how he can find and research in that way; however, we can save time for this innovation.
#### c) Implementation
Strassen algorithm is implemented on C++, using package "chrono" to couting time with milisecond accuracy.
#### d) Instruction
At first, type in source code the size of the matrix (must be 2 exponent), then compile the programme.
For best result, algorithms will read the same data from file. At command line, type "SubCubic" "<" "*test data file"; the programme will load data and get ready to compute.
Waiting for result..



### 2. Coppersmith - Winograd algorithm

New technique and research give us better chance for completely computing multiplication as fast as have ever seen.
O($$n^(2.3)$$) is the result for years or attemping.
However, as having been criticised by experts, this algorithm is not practical due to its complex code and description. This often applies in strong hardware computer for vast of inputs.

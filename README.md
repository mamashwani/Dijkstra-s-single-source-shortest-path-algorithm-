# Dijkstra-s-single-source-shortest-path-algorithm-
Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation
# Assumptions:
- The input file is a text file; no need to handle binary files.
- The input will always be in order of x coordinate, y coordinate, and weight of distance between those two points
- The weight can be a double not just an integer, but the coordinates will always be ints.
- The path file will contain 2 numbers separated by a space, the first digit will always be the source, and the second digit will be the vertex that is the destination we want the shortest path to. 
- An input file can contain empty lines that should be ignored.
- If a source points to a destination that cannot be reached, the path is infinite, 
- If A source and destination are the same, then the shortest distance is 0.
- Characters are case sensitive.

# Notes
- The 9 "input8x.txt" files are the 9 input files that were used to test this code
- The 9 "output8x.txt" files are the files outputted by the program.
- The 9 "ans8x.txt" files are files containing the correct output that should occur from each corresponding input file, and are available
for comparison to the outputs files to ensure correct output. 
- The 9 "path8x.txt" files contain the command the code must parse through and execute.
- This code was tested on the University of Houston's Linux server and passed all the test cases.
- The "ArgumentManager.h" file parses arguments to sequentially open the 9 input files to automatically test the code on the server.
- The "test.sh" file is a SHELL script for automatically testing the input files on the Linux server.
- The "compile.sh" file is  SHELL script for automatically compiling the code on the Linux server before running the tests.

# Resources:

https://www.geeksforgeeks.org/data-structures/linked-list/

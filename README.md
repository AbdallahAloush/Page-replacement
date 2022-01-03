# Operating systems assignment 4 (Page replacement algorithms)
## Page replacement algorithms
- We are required to mimick page repalcement algorithms done in virtual memory  
- Some test files are included in the repo
- The best way to evaluate the correctness of our results is using:
```
gcc main.c -o main
cat inputfile.txt | ./main | diff outputfile.txt -
```
**Note: you can make the pages array that takes input from useer be dynamic in case that we know nothing about the size of the input but since the provided test case were of small size if left it as is (128)**

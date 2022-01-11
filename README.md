# Operating systems assignment 4 (Page replacement algorithms)
## Page replacement algorithms
- We are required to mimick page repalcement algorithms done in virtual memory  
- Some test cases are included in the repo
- pages array is dynamic **(Resizes to double the original size)**.
- The best way to evaluate the correctness of our results is using:
```
gcc main.c -o main
cat inputs/inputfile.txt | ./main | diff outputs/outputfile.txt -
```
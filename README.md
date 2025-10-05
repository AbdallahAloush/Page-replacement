# Page Replacement Algorithms Simulator

This project is a C implementation of four classic **page replacement algorithms** used in operating systems for memory management:

* **FIFO (First-In, First-Out)**
* **LRU (Least Recently Used)**
* **CLOCK**
* **OPTIMAL**

The program simulates how pages are loaded into frames and calculates the number of page faults.

---

## Features

* Implements 4 different replacement policies.
* Displays the frame content at each step.
* Marks page faults with `F` in the output.
* Dynamically resizes the input pages array if needed.
* Supports user input of any sequence length.

---

## Usage

### Compile

```bash
gcc main.c -o page_replacement
```

### Run

Provide:

1. Number of frames
2. Replacement algorithm (`FIFO`, `LRU`, `CLOCK`, or `OPTIMAL`)
3. A sequence of page numbers, ending with `-1`

Example:

```bash
./page_replacement
3 FIFO
7 0 1 2 0 3 0 4 -1
```

---

## Sample Output

The following is the output of running **FIFO** with 3 frames on the input sequence from `outputs/outputFIFO1.txt`:

```
Replacement Policy = FIFO
-------------------------------------
Page   Content of Frames
----   -----------------
02     02 
03     02 03 
02     02 03 
01     02 03 01 
05 F   05 03 01 
02 F   05 02 01 
04 F   05 02 04 
05     05 02 04 
03 F   03 02 04 
02     03 02 04 
05 F   03 05 04 
02 F   03 05 02 
-------------------------------------
Number of page faults = 6
```
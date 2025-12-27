# Survey Analyzer Part 2 (Course Project)
 
## Overview
This project builds upon Part 1 by utilizing dynamic memory management and compiling via a Makefile. The program reads a student survey from stdin and outputs a specified format of response statistics to stdout.
Information is pulled from the survey text file with line-based input parsing, tokenization with `strtok`, simple aggregation in 2D arrays, and Unix-style CLI usage.

## Features
- Reads:
  - Output format (first non-comment line)
  - Program list (comma-separated)
  - Residency list (comma-separated)
  - Survey questions/assertions (semicolon-separated)
  - Answer options (comma-separated)
  - Number of responses (int)
  - Respondent answer rows (comma-separated)
- Computes per-question:
  - **Option counts** using dynamically allocated table
  - **Program proportions**
  - **Residency proportions**
- Prints:
  - Output generated based on format code

## Tech Stack
- C (C11)
- GCC
- Make/Makefile
- stdio.h, string.h, stdlib.h
- Unix CLI

## Installation
Clone the repo and compile with make:

```bash
git clone https://github.com/atwoodg/dynamic-survey-analyzer.git

cd dynamic-survey-analyzer

make

#To remove build:
make clean
```

## How to use
Running the system:
```bash
cat tests/in01.txt | ./dyn_survey
cat tests/in02.txt | ./dyn_survey
cat tests/in03.txt | ./dyn_survey 
```

## Tests
To compare expected output and actual output:
```bash
cat tests/in01.txt | ./dyn_survey | diff tests/out01.txt -
cat tests/in02.txt | ./dyn_survey | diff tests/out02.txt -
cat tests/in03.txt | ./dyn_survey | diff tests/out03.txt - 
```

## Credits
- Contributors: Gabriel Atwood, Roberto Bittencourt
- Course: SENG 265 (Software Development Methods)


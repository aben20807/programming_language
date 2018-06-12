# Implemented by c++11

## Language

+ C++

## Environment

+ g++
```sh
$ g++ -g -Wall -fopenmp -o omptest omptest.cpp
```

## Usage

### Record time execution for each multiplication by using 12 methods

```sh
$ ./omptest < ../matrix_mul/test_case/t10.in
```

### Run all test cases (10 to 300 matrix) by using 10 methods

+ It will take within 30 minutes.

```sh
$ bash run.sh
```

## Data structure

+ matrix: two-dimensional vector.

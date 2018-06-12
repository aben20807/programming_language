# matrix\_mul

+ Matrix Multiplication

## Language

+ Rust

## Environment

+ rustc 1.26.0
+ cargo 1.26.0

## Usage

### Print answer by using 12 methods

```sh
$ cargo run --release answer < test_case/t10.in
```

### Record time execution for each multiplication by using 12 methods

```sh
$ mkdir test_output
$ cargo run --release analysis < test_case/t10.in
```

### Run all test cases (10 to 300 matrix) by using 10 methods

+ It will take within 10 minutes.

```sh
$ bash run.sh
```

## Data structure

+ matrix: two-dimensional vector.
+ matrix\_tr: two-dimensional vector, transform of matrix.
+ m11: a quarter matrix in the upper left corner of matrix.
+ m12: a quarter matrix in the upper right corner of matrix.
+ m21: a quarter matrix in the lower left corner of matrix.
+ m22: a quarter matrix in the lower right corner of matrix.

## Methods

### Usage

+ mul(): let c = a.mul(b), b need to be a reference of a matrix.

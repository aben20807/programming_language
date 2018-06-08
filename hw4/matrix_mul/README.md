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

### Function description

#### A. mul()

+ Triple nested for loop.

#### B. mul\_cache()

+ Triple nested for loop, but use matrix\_tr of b.

#### C. mul\_rw\_e()

+ Create threads for each element multiplication with read-write lock.

#### D. mul\_rw()

+ Create two threads to calculate upper and lower matrix with read-write lock.

#### E. mul\_2t()

+ Triple nested for loop, but use two threads to calculate upper and lower parts.

#### F. mul\_2t\_cache()

+ Use matrix\_tr of b.
+ Triple nested for loop, but use two threads to calculate upper and lower parts.

#### G. mul\_s()

+ Use Strassen algorithm.
+ Call mul() when calculating multiplication.

#### H. mul\_s\_2t()

+ Use Strassen algorithm.
+ Call mul\_2t() when calculating multiplication.

#### I. mul\_s\_2t\_split()

+ Use Strassen algorithm.
+ Use m11, m12, m21, m22 submatrix in struct.
+ Call mul\_2t() when calculating multiplication.

#### J. mul\_4t\_cache()

+ Use matrix\_tr of b.
+ Triple nested for loop, but use four threads to calculate four parts.

#### K. mul\_s\_4t\_split()

+ Use Strassen algorithm.
+ Use m11, m12, m21, m22 submatrix in struct.
+ Call mul\_4t() when calculating multiplication.

#### L. mul\_4t()

+ Triple nested for loop, but use four threads to calculate four parts.

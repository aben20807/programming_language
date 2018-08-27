# Matrix Multiplication

## member

+ 何中淼、鍾日超、洪瑞隆、黃柏瑄

## Subproject

+ cpp: matrix multiplication implemented by C++11.
+ java: matrix multiplication implemented by Java.
+ matlab: matrix multiplication implemented by Matlab.
+ matrix\_creator: create test case.
+ matrix\_mul: matrix multiplication implemented by Rust.
+ plot: plot analysis images.

## Methods

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

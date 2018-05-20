#[macro_use]
extern crate text_io;
extern crate crossbeam;
use std::fmt;
use std::sync::{Arc, RwLock};
use std::time::Instant;

#[derive(Clone)]
struct M {
    row: usize,
    col: usize,
    matrix: Vec<Vec<i32>>,
}

impl M {
    fn new(r: usize, c: usize) -> M {
        M {
            row: r,
            col: c,
            matrix: vec![vec![0i32; c]; r],
        }
    }

    fn input(&mut self) {
        for i in 0..self.row {
            for j in 0..self.col {
                let e: i32;
                scan!("{}", e);
                self.matrix[i][j] = e;
            }
        }
    }

    fn mul(&self, m2: &M) -> M {
        let mut ma = M::new(self.row, m2.col);
        let m1x = &self.matrix;
        let m2x = &m2.matrix;
        for i in 0..self.row {
            for j in 0..m2.col {
                for k in 0..self.col {
                    ma.matrix[i][j] += m1x[i][k] * m2x[k][j];
                }
            }
        }
        ma
    }

    fn mul_t(&self, m2: &M) -> M {
        let mut ma = M::new(self.row, m2.col);
        {
            let mid = self.row / 2;
            let (l, r) = ma.matrix.split_at_mut(mid);
            let m1x = &self.matrix;
            let m2x = &m2.matrix;
            crossbeam::scope(|scope| {
                scope.spawn(move || for i in 0..mid {
                                for j in 0..m2.col {
                                    for k in 0..self.col {
                                        l[i][j] += m1x[i][k] * m2x[k][j];
                                    }
                                }
                            });
                scope.spawn(move || for i in (mid - mid)..(self.row - mid) {
                                for j in 0..m2.col {
                                    for k in 0..self.col {
                                        r[i][j] += m1x[i][k] * m2x[k][j];
                                    }
                                }
                            });
            });
        }
        ma
    }

    fn mul_rw(&self, m2: &M) -> M {
        let ma = M::new(self.row, m2.col);
        let x = Arc::new(RwLock::new(ma));
        let m1x = &self.matrix;
        let m2x = &m2.matrix;
        crossbeam::scope(|scope| for i in 0..self.row {
                             for j in 0..m2.col {
                                 let x1 = x.clone();
                                 scope.spawn(move || for k in 0..self.col {
                                                 let tmp = m1x[i][k] * m2x[k][j];
                                                 let mut x1 = x1.write().unwrap();
                                                 x1.matrix[i][j] += tmp;
                                             });
                             }
                         });
        let x1 = (x.read().unwrap()).clone();
        x1
    }
}

impl fmt::Display for M {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        let mut s = String::new();
        for it in &self.matrix {
            for itt in it {
                s.push_str(&itt.to_string());
                s.push(' ');
            }
            s.pop();
            s.push('\n');
        }
        s.pop();
        write!(f, "{}", s)
    }
}

fn main() {
    // let array = [1, 2, 3];

    // crossbeam::scope(|scope| for i in &array {
    //                      scope.spawn(move || {
    //                                      println!("element: {}", i);
    //                                  });
    //                  });
    // let mut pool = ThreadPool::new(4);
    // let mut vec = vec![0, 1, 2, 3, 4, 5, 6, 7];
    // crossbeam::scope(|scope| for e in &mut vec {
    //                      scope.spawn(move || { *e += 1; });
    //                  });
    // println!("{:?}", vec);
    loop {
        let mut r: usize;
        let mut c: usize;
        let mut m1;
        {
            scan!("{} {}", r, c);
            print!("{}x{}", r, c);
            m1 = M::new(r, c);
            m1.input();
        }
        print!(" x ");
        let mut m2;
        {
            scan!("{} {}", r, c);
            println!("{}x{}", r, c);
            m2 = M::new(r, c);
            m2.input();
        }
        let start = Instant::now();
        let _ma = m1.mul(&m2);
        let duration = start.elapsed();
        println!("{:?}", duration);
        let start = Instant::now();
        let _ma = m1.mul_rw(&m2);
        let duration = start.elapsed();
        println!("{:?}", duration);
        let start = Instant::now();
        let _ma = m1.mul_t(&m2);
        let duration = start.elapsed();
        println!("{:?}", duration);
    }
}

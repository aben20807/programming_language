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

    fn tr(&self) -> M {
        let mut ma = M::new(self.col, self.row);
        for i in 0..self.row {
            for j in 0..self.col {
                ma.matrix[j][i] = self.matrix[i][j];
            }
        }
        ma
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

    fn mul_cache(&self, m2: &M) -> M {
        let mut ma = M::new(self.row, m2.row);
        let m1x = &(self.matrix);
        let m2x = &(m2.matrix);
        for i in 0..self.row {
            for j in 0..m2.row {
                for k in 0..self.col {
                    ma.matrix[i][j] += m1x[i][k] * m2x[j][k];
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
                                        r[i][j] += m1x[i + mid][k] * m2x[k][j];
                                    }
                                }
                            });
            });
        }
        ma
    }

    fn mul_t_cache(&self, m2: &M) -> M {
        let mut ma = M::new(self.row, m2.row);
        {
            let mid = self.row / 2;
            let (l, r) = ma.matrix.split_at_mut(mid);
            let m1x = &self.matrix;
            let m2x = &m2.matrix;
            crossbeam::scope(|scope| {
                scope.spawn(move || for i in 0..mid {
                                for j in 0..m2.row {
                                    for k in 0..self.col {
                                        l[i][j] += m1x[i][k] * m2x[j][k];
                                    }
                                }
                            });
                scope.spawn(move || for i in (mid - mid)..(self.row - mid) {
                                for j in 0..m2.row {
                                    for k in 0..self.col {
                                        r[i][j] += m1x[i + mid][k] * m2x[j][k];
                                    }
                                }
                            });
            });
        }
        ma
    }

    fn mul_rw_e(&self, m2: &M) -> M {
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

    fn mul_rw(&self, m2: &M) -> M {
        let mid = self.row / 2;
        let ma = M::new(self.row, m2.col);
        let x = Arc::new(RwLock::new(ma));
        let m1x = &self.matrix;
        let m2x = &m2.matrix;
        crossbeam::scope(|scope| {
            let x1 = x.clone();
            let x2 = x.clone();
            scope.spawn(move || for i in 0..mid {
                            for j in 0..m2.col {
                                for k in 0..self.col {
                                    let mut x1 = x1.write().unwrap();
                                    x1.matrix[i][j] += m1x[i][k] * m2x[k][j];
                                }
                            }
                        });
            scope.spawn(move || for i in (mid - mid)..(self.row - mid) {
                            for j in 0..m2.col {
                                for k in 0..self.col {
                                    let mut x2 = x2.write().unwrap();
                                    x2.matrix[i + mid][j] += m1x[i + mid][k] * m2x[k][j];
                                }
                            }
                        });
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
    loop {
        let mut r: usize;
        let mut c: usize;
        let mut m1;
        {
            scan!("{} {}", r, c);
            if r == 0 && c == 0 {
                break;
            }
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
        let print_result = false;
        {
            println!("single thread");
            let start = Instant::now();
            let _ma = m1.mul(&m2);
            let duration = start.elapsed();
            println!("= {} ns", duration.subsec_nanos() as f64);
            if print_result {
                println!("{}", _ma);
            }
        }
        {
            println!("single thread cache");
            let m2 = m2.tr();
            let start = Instant::now();
            let _ma = m1.mul_cache(&m2);
            let duration = start.elapsed();
            println!("= {} ns", duration.subsec_nanos() as f64);
            if print_result {
                println!("{}", _ma);
            }
        }
        {
            println!("rwlock many threads for every elements");
            let start = Instant::now();
            let _ma = m1.mul_rw_e(&m2);
            let duration = start.elapsed();
            println!("= {} ns", duration.subsec_nanos() as f64);
            if print_result {
                println!("{}", _ma);
            }
        }
        {
            println!("rwlock two threads");
            let start = Instant::now();
            let _ma = m1.mul_rw(&m2);
            let duration = start.elapsed();
            println!("= {} ns", duration.subsec_nanos() as f64);
            if print_result {
                println!("{}", _ma);
            }
        }
        {
            println!("split mut two threads");
            let start = Instant::now();
            let _ma = m1.mul_t(&m2);
            let duration = start.elapsed();
            println!("= {} ns", duration.subsec_nanos() as f64);
            if print_result {
                println!("{}", _ma);
            }
        }
        {
            println!("split mut two threads cache");
            let m2 = m2.tr();
            let start = Instant::now();
            let _ma = m1.mul_t_cache(&m2);
            let duration = start.elapsed();
            println!("= {} ns", duration.subsec_nanos() as f64);
            if print_result {
                println!("{}", _ma);
            }
        }
        println!("");
    }
}

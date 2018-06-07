#[macro_use]
extern crate text_io;
extern crate crossbeam;
use std::fmt;
use std::sync::{Arc, RwLock};
use std::time::Instant;
use std::ops::Add;
use std::ops::Sub;
use std::fs::OpenOptions;
use std::io::prelude::*;
use std::env;

#[derive(Clone)]
struct M {
    row: usize,
    col: usize,
    matrix: Vec<Vec<i32>>,
    matrix_tr: Vec<Vec<i32>>,
    print_split: bool,
    m11: Vec<Vec<i32>>,
    m12: Vec<Vec<i32>>,
    m21: Vec<Vec<i32>>,
    m22: Vec<Vec<i32>>,
}

#[allow(dead_code)]
impl M {
    fn new(r: usize, c: usize) -> M {
        M {
            row: r,
            col: c,
            matrix: vec![vec![0i32; c]; r],
            matrix_tr: vec![vec![0i32; c]; r],
            print_split: false,
            m11: vec![vec![0i32; c/2]; r/2],
            m12: vec![vec![0i32; c/2]; r/2],
            m21: vec![vec![0i32; c/2]; r/2],
            m22: vec![vec![0i32; c/2]; r/2],
        }
    }

    fn from(m: &Vec<Vec<i32>>, r: usize, c: usize) -> M {
        M {
            row: r,
            col: c,
            matrix: (*m).clone(),
            matrix_tr: vec![vec![0i32; c]; r],
            print_split: false,
            m11: vec![vec![0i32; c/2]; r/2],
            m12: vec![vec![0i32; c/2]; r/2],
            m21: vec![vec![0i32; c/2]; r/2],
            m22: vec![vec![0i32; c/2]; r/2],
        }
    }

    fn input(&mut self) {
        for i in 0..self.row {
            for j in 0..self.col {
                let e: i32;
                scan!("{}", e);
                self.matrix[i][j] = e;
                self.matrix_tr[j][i] = e;
                if i < self.row / 2 {
                    if j < self.col / 2 {
                        self.m11[i][j] = e;
                    } else {
                        self.m12[i][j - self.col / 2] = e;
                    }
                } else {
                    if j < self.col / 2 {
                        self.m21[i - self.row / 2][j] = e;
                    } else {
                        self.m22[i - self.row / 2][j - self.col / 2] = e;
                    }
                }
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

    fn sub(&self, [rb, re, cb, ce]: [usize; 4]) -> M {
        let mut ma = M::new(re - rb, ce - cb);
        for i in rb..re {
            for j in cb..ce {
                ma.matrix[i - rb][j - cb] = self.matrix[i][j];
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
        let m2x = &(m2.matrix_tr);
        for i in 0..self.row {
            for j in 0..m2.row {
                for k in 0..self.col {
                    ma.matrix[i][j] += m1x[i][k] * m2x[j][k];
                }
            }
        }
        ma
    }

    fn mul_s(&self, m2: &M) -> M {
        let a11 = self.sub([0, self.row / 2, 0, self.col / 2]);
        let a12 = self.sub([0, self.row / 2, self.col / 2, self.col]);
        let a21 = self.sub([self.row / 2, self.row, 0, self.col / 2]);
        let a22 = self.sub([self.row / 2, self.row, self.col / 2, self.col]);
        let b11 = m2.sub([0, m2.row / 2, 0, m2.col / 2]);
        let b12 = m2.sub([0, m2.row / 2, m2.col / 2, m2.col]);
        let b21 = m2.sub([m2.row / 2, m2.row, 0, m2.col / 2]);
        let b22 = m2.sub([m2.row / 2, m2.row, m2.col / 2, m2.col]);
        let p1 = (&a11 + &a22).mul(&(&b11 + &b22));
        let p2 = (&a21 + &a22).mul(&b11);
        let p3 = (&a11).mul(&(&b12 - &b22));
        let p4 = (&a22).mul(&(&b21 - &b11));
        let p5 = (&a11 + &a12).mul(&b22);
        let p6 = (&a21 - &a11).mul(&(&b11 + &b12));
        let p7 = (&a12 - &a22).mul(&(&b21 + &b22));
        let c11 = &(&(&p1 + &p4) - &p5) + &p7;
        let c12 = &p3 + &p5;
        let c21 = &p2 + &p4;
        let c22 = &(&(&p1 + &p3) - &p2) + &p6;
        let mut ma = M::new(self.row, m2.col);
        let mut mi = 0;
        for i in 0..c11.row {
            let mut mj = 0;
            for j in 0..c11.col {
                ma.matrix[mi][mj] = c11.matrix[i][j];
                mj += 1;
            }
            mi += 1;
        }
        let mut mi = 0;
        for i in 0..c12.row {
            let mut mj = ma.col / 2;
            for j in 0..c12.col {
                ma.matrix[mi][mj] = c12.matrix[i][j];
                mj += 1;
            }
            mi += 1;
        }
        let mut mi = ma.row / 2;
        for i in 0..c21.row {
            let mut mj = 0;
            for j in 0..c21.col {
                ma.matrix[mi][mj] = c21.matrix[i][j];
                mj += 1;
            }
            mi += 1;
        }
        let mut mi = ma.row / 2;
        for i in 0..c11.row {
            let mut mj = ma.col / 2;
            for j in 0..c11.col {
                ma.matrix[mi][mj] = c22.matrix[i][j];
                mj += 1;
            }
            mi += 1;
        }
        ma
    }

    fn mul_s_2t(&self, m2: &M) -> M {
        let a11 = self.sub([0, self.row / 2, 0, self.col / 2]);
        let a12 = self.sub([0, self.row / 2, self.col / 2, self.col]);
        let a21 = self.sub([self.row / 2, self.row, 0, self.col / 2]);
        let a22 = self.sub([self.row / 2, self.row, self.col / 2, self.col]);
        let b11 = m2.sub([0, m2.row / 2, 0, m2.col / 2]);
        let b12 = m2.sub([0, m2.row / 2, m2.col / 2, m2.col]);
        let b21 = m2.sub([m2.row / 2, m2.row, 0, m2.col / 2]);
        let b22 = m2.sub([m2.row / 2, m2.row, m2.col / 2, m2.col]);
        let p1 = (&a11 + &a22).mul_2t(&(&b11 + &b22));
        let p2 = (&a21 + &a22).mul_2t(&b11);
        let p3 = (&a11).mul_2t(&(&b12 - &b22));
        let p4 = (&a22).mul_2t(&(&b21 - &b11));
        let p5 = (&a11 + &a12).mul_2t(&b22);
        let p6 = (&a21 - &a11).mul_2t(&(&b11 + &b12));
        let p7 = (&a12 - &a22).mul_2t(&(&b21 + &b22));
        let c11 = &(&(&p1 + &p4) - &p5) + &p7;
        let c12 = &p3 + &p5;
        let c21 = &p2 + &p4;
        let c22 = &(&(&p1 + &p3) - &p2) + &p6;
        let mut ma = M::new(self.row, m2.col);
        let mut mi = 0;
        for i in 0..c11.row {
            let mut mj = 0;
            for j in 0..c11.col {
                ma.matrix[mi][mj] = c11.matrix[i][j];
                mj += 1;
            }
            mi += 1;
        }
        let mut mi = 0;
        for i in 0..c12.row {
            let mut mj = ma.col / 2;
            for j in 0..c12.col {
                ma.matrix[mi][mj] = c12.matrix[i][j];
                mj += 1;
            }
            mi += 1;
        }
        let mut mi = ma.row / 2;
        for i in 0..c21.row {
            let mut mj = 0;
            for j in 0..c21.col {
                ma.matrix[mi][mj] = c21.matrix[i][j];
                mj += 1;
            }
            mi += 1;
        }
        let mut mi = ma.row / 2;
        for i in 0..c11.row {
            let mut mj = ma.col / 2;
            for j in 0..c11.col {
                ma.matrix[mi][mj] = c22.matrix[i][j];
                mj += 1;
            }
            mi += 1;
        }
        ma
    }

    fn mul_s_2t_split(&self, m2: &M) -> M {
        let a11 = M::from(&self.m11, self.row / 2, self.col / 2);
        let a12 = M::from(&self.m12, self.row / 2, self.col / 2);
        let a21 = M::from(&self.m21, self.row / 2, self.col / 2);
        let a22 = M::from(&self.m22, self.row / 2, self.col / 2);
        let b11 = M::from(&m2.m11, m2.row / 2, m2.col / 2);
        let b12 = M::from(&m2.m12, m2.row / 2, m2.col / 2);
        let b21 = M::from(&m2.m21, m2.row / 2, m2.col / 2);
        let b22 = M::from(&m2.m22, m2.row / 2, m2.col / 2);
        let p1 = (&a11 + &a22).mul_2t(&(&b11 + &b22));
        let p2 = (&a21 + &a22).mul_2t(&b11);
        let p3 = (&a11).mul_2t(&(&b12 - &b22));
        let p4 = (&a22).mul_2t(&(&b21 - &b11));
        let p5 = (&a11 + &a12).mul_2t(&b22);
        let p6 = (&a21 - &a11).mul_2t(&(&b11 + &b12));
        let p7 = (&a12 - &a22).mul_2t(&(&b21 + &b22));
        let mut ma = M::new(self.row, m2.col);
        ma.print_split = true;
        ma.m11 = (&(&(&p1 + &p4) - &p5) + &p7).matrix;
        ma.m12 = (&p3 + &p5).matrix;
        ma.m21 = (&p2 + &p4).matrix;
        ma.m22 = (&(&(&p1 + &p3) - &p2) + &p6).matrix;
        ma
    }

    fn mul_s_4t_split(&self, m2: &M) -> M {
        let a11 = M::from(&self.m11, self.row / 2, self.col / 2);
        let a12 = M::from(&self.m12, self.row / 2, self.col / 2);
        let a21 = M::from(&self.m21, self.row / 2, self.col / 2);
        let a22 = M::from(&self.m22, self.row / 2, self.col / 2);
        let b11 = M::from(&m2.m11, m2.row / 2, m2.col / 2);
        let b12 = M::from(&m2.m12, m2.row / 2, m2.col / 2);
        let b21 = M::from(&m2.m21, m2.row / 2, m2.col / 2);
        let b22 = M::from(&m2.m22, m2.row / 2, m2.col / 2);
        let p1 = (&a11 + &a22).mul_4t(&(&b11 + &b22));
        let p2 = (&a21 + &a22).mul_4t(&b11);
        let p3 = (&a11).mul_4t(&(&b12 - &b22));
        let p4 = (&a22).mul_4t(&(&b21 - &b11));
        let p5 = (&a11 + &a12).mul_4t(&b22);
        let p6 = (&a21 - &a11).mul_4t(&(&b11 + &b12));
        let p7 = (&a12 - &a22).mul_4t(&(&b21 + &b22));
        let mut ma = M::new(self.row, m2.col);
        ma.print_split = true;
        ma.m11 = (&(&(&p1 + &p4) - &p5) + &p7).matrix;
        ma.m12 = (&p3 + &p5).matrix;
        ma.m21 = (&p2 + &p4).matrix;
        ma.m22 = (&(&(&p1 + &p3) - &p2) + &p6).matrix;
        ma
    }

    fn mul_2t(&self, m2: &M) -> M {
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

    fn mul_2t_cache(&self, m2: &M) -> M {
        let mut ma = M::new(self.row, m2.row);
        {
            let mid = self.row / 2;
            let (l, r) = ma.matrix.split_at_mut(mid);
            let m1x = &self.matrix;
            let m2x = &m2.matrix_tr;
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

    fn mul_4t(&self, m2: &M) -> M {
        let mut ma = M::new(self.row, m2.row);
        {
            let mid = self.row / 2;
            let (u, d) = ma.matrix.split_at_mut(mid);
            {
                let midd = mid / 2;
                let (u1, u2) = u.split_at_mut(midd);
                let (d1, d2) = d.split_at_mut(midd);
                let m1x = &self.matrix;
                let m2x = &m2.matrix;
                crossbeam::scope(|scope| {
                    scope.spawn(move || for i in 0..midd {
                                    for j in 0..m2.col {
                                        for k in 0..self.col {
                                            u1[i][j] += m1x[i][k] * m2x[k][j];
                                        }
                                    }
                                });
                    scope.spawn(move || for i in 0..(mid - midd) {
                                    for j in 0..m2.col {
                                        for k in 0..self.col {
                                            u2[i][j] += m1x[i + midd][k] * m2x[k][j];
                                        }
                                    }
                                });
                    scope.spawn(move || for i in 0..midd {
                                    for j in 0..m2.col {
                                        for k in 0..self.col {
                                            d1[i][j] += m1x[i + mid][k] * m2x[k][j];
                                        }
                                    }
                                });
                    scope.spawn(move || for i in 0..(self.row - mid - midd) {
                                    for j in 0..m2.col {
                                        for k in 0..self.col {
                                            d2[i][j] += m1x[i + mid + midd][k] * m2x[k][j];
                                        }
                                    }
                                });
                });
            }
        }
        ma
    }

    fn mul_4t_cache(&self, m2: &M) -> M {
        let mut ma = M::new(self.row, m2.row);
        {
            let mid = self.row / 2;
            let (u, d) = ma.matrix.split_at_mut(mid);
            {
                let midd = mid / 2;
                let (u1, u2) = u.split_at_mut(midd);
                let (d1, d2) = d.split_at_mut(midd);
                let m1x = &self.matrix;
                let m2x = &m2.matrix_tr;
                crossbeam::scope(|scope| {
                    scope.spawn(move || for i in 0..midd {
                                    for j in 0..m2.row {
                                        for k in 0..self.col {
                                            u1[i][j] += m1x[i][k] * m2x[j][k];
                                        }
                                    }
                                });
                    scope.spawn(move || for i in 0..(mid - midd) {
                                    for j in 0..m2.row {
                                        for k in 0..self.col {
                                            u2[i][j] += m1x[i + midd][k] * m2x[j][k];
                                        }
                                    }
                                });
                    scope.spawn(move || for i in 0..midd {
                                    for j in 0..m2.row {
                                        for k in 0..self.col {
                                            d1[i][j] += m1x[i + mid][k] * m2x[j][k];
                                        }
                                    }
                                });
                    scope.spawn(move || for i in 0..(self.row - mid - midd) {
                                    for j in 0..m2.row {
                                        for k in 0..self.col {
                                            d2[i][j] += m1x[i + mid + midd][k] * m2x[j][k];
                                        }
                                    }
                                });
                });
            }
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
        if self.print_split {
            for i in 0..self.row {
                for j in 0..self.col {
                    if i < self.row / 2 {
                        if j < self.col / 2 {
                            s.push_str(&self.m11[i][j].to_string());
                            s.push(' ');
                        } else {
                            s.push_str(&self.m12[i][j - self.col / 2].to_string());
                            s.push(' ');
                        }
                    } else {
                        if j < self.col / 2 {
                            s.push_str(&self.m21[i - self.row / 2][j].to_string());
                            s.push(' ');
                        } else {
                            s.push_str(&self.m22[i - self.row / 2][j - self.col / 2].to_string());
                            s.push(' ');
                        }
                    }
                }
                s.pop();
                s.push('\n');
            }
            s.pop();
        } else {
            for it in &self.matrix {
                for itt in it {
                    s.push_str(&itt.to_string());
                    s.push(' ');
                }
                s.pop();
                s.push('\n');
            }
            s.pop();
        }
        write!(f, "{}", s)
    }
}

impl<'a, 'b> Add<&'b M> for &'a M {
    type Output = M;
    fn add(self, m2: &'b M) -> M {
        let mut ma = M::new(self.row, self.col);
        let m1x = &self.matrix;
        let m2x = &m2.matrix;
        for i in 0..self.row {
            for j in 0..self.col {
                ma.matrix[i][j] = m1x[i][j] + m2x[i][j];
            }
        }
        ma
    }
}

impl<'a, 'b> Sub<&'b M> for &'a M {
    type Output = M;
    fn sub(self, m2: &'b M) -> M {
        let mut ma = M::new(self.row, self.col);
        let m1x = &self.matrix;
        let m2x = &m2.matrix;
        for i in 0..self.row {
            for j in 0..self.col {
                ma.matrix[i][j] = m1x[i][j] - m2x[i][j];
            }
        }
        ma
    }
}

fn test_mul(mul: &Fn(&M, &M) -> M, n: i32, m1: &M, m2: &M, filename: &str, print_result: bool) {
    let filename = format!("./test_output/{}.csv", filename);
    let print_file = !print_result;
    let mut file = OpenOptions::new()
        .write(true)
        .create(true)
        .append(true)
        .open(filename)
        .unwrap();
    let mut n = n;
    while n > 0 {
        let start = Instant::now();
        let _ma = mul(m1, m2);
        let duration = start.elapsed();
        if print_file {
            if let Err(e) = write!(file, "{}, ", duration.subsec_nanos() as f64) {
                eprintln!("Couldn't write to file: {}", e);
            }
        } else {
            println!("= {} ns", duration.subsec_nanos() as f64);
            println!("{}", _ma);
        }
        n -= 1;
    }
    if print_file {
        if let Err(e) = writeln!(file, "") {
            eprintln!("Couldn't write to file: {}", e);
        }
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let mode = &args[1];
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
    if mode == "answer" {
        test_mul(&M::mul, 1, &m1, &m2, "m1", true); // A
        test_mul(&M::mul_cache, 1, &m1, &m2, "m2", true); // B
        test_mul(&M::mul_rw_e, 1, &m1, &m2, "m3", true); // C
        test_mul(&M::mul_rw, 1, &m1, &m2, "m4", true); // D
        test_mul(&M::mul_2t, 1, &m1, &m2, "mm5", true); // E
        test_mul(&M::mul_2t_cache, 1, &m1, &m2, "mm6", true); // F
        test_mul(&M::mul_s, 1, &m1, &m2, "m7", true); // G
        test_mul(&M::mul_s_2t, 1, &m1, &m2, "mm8", true); // H
        test_mul(&M::mul_s_2t_split, 1, &m1, &m2, "m9", true); // I
        test_mul(&M::mul_4t_cache, 1, &m1, &m2, "mm10", true); // J
        test_mul(&M::mul_s_4t_split, 1, &m1, &m2, "mm11", true); // K
        test_mul(&M::mul_4t, 1, &m1, &m2, "mm12", true); // L
    } else if mode == "analysis" {
        test_mul(&M::mul, 100, &m1, &m2, "m1", false); // A
        test_mul(&M::mul_cache, 100, &m1, &m2, "m2", false); // B
        // test_mul(&M::mul_rw_e, 100, &m1, &m2, "m3", false); // C // too slow
        // test_mul(&M::mul_rw, 100, &m1, &m2, "m4", false); // D // too slow
        test_mul(&M::mul_2t, 100, &m1, &m2, "m5", false); // E
        test_mul(&M::mul_2t_cache, 100, &m1, &m2, "m6", false); // F
        test_mul(&M::mul_s, 100, &m1, &m2, "m7", false); // G
        test_mul(&M::mul_s_2t, 100, &m1, &m2, "m8", false); // H
        test_mul(&M::mul_s_2t_split, 100, &m1, &m2, "m9", false); // I
        test_mul(&M::mul_4t_cache, 100, &m1, &m2, "m10", false); // J
        test_mul(&M::mul_s_4t_split, 100, &m1, &m2, "m11", false); // K
        test_mul(&M::mul_4t, 100, &m1, &m2, "m12", false); // L
    }
}

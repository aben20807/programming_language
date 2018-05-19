#[macro_use]
extern crate text_io;
use std::fmt;

struct M {
    row: i32,
    col: i32,
    matrix: Vec<Vec<i32>>,
}

impl M {
    fn new(r: i32, c: i32) -> M {
        M {
            row: r,
            col: c,
            matrix: vec![vec![0i32; c as usize]; r as usize],
        }
    }

    fn input(&mut self) {
        for i in 0..self.row as usize {
            for j in 0..self.col as usize {
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
        for i in 0..self.row as usize {
            for j in 0..m2.col as usize {
                for k in 0..self.col as usize {
                    ma.matrix[i][j] += m1x[i][k] * m2x[k][j];
                }
            }
        }
        ma
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
    let mut r: i32;
    let mut c: i32;
    let mut m1;
    {
        scan!("{} {}", r, c);
        m1 = M::new(r, c);
    }
    println!("m1");
    m1.input();
    // println!("{}", m1);
    let mut m2;
    {
        scan!("{} {}", r, c);
        m2 = M::new(r, c);
    }
    println!("m2");
    m2.input();
    // println!("{}", m2);
    let ma = m1.mul(&m2);
    println!("{}", ma);

}

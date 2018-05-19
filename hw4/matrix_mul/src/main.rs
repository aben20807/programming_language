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

    fn mul(&self, m2: &M) {
        let m1 = &self.matrix;
        let m2 = &m2.matrix;
        for (i, it) in m1.iter().enumerate() {
            for (j, it) in it.iter().enumerate() {
                println!("({}, {}) {}", i, j, m1[i][j]);
            }
        }
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
        write!(f, "{}", s)
    }
}

fn main() {
    let r: i32;
    let c: i32;
    scan!("{} {}", r, c);
    let m1 = M::new(r, c);
    println!("{}", m1);
    let m2 = M::new(r, c);
    println!("{}", m2);
    m1.mul(&m2);
}

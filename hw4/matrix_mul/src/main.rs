#[macro_use]
extern crate text_io;
use std::fmt;

struct M {
    matrix: Vec<Vec<i32>>,
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
    let m1 = M { matrix: vec![vec![60i32; c as usize]; r as usize] };
    println!("{}", m1);
}

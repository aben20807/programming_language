extern crate rand;
use rand::Rng;
use std::fs::OpenOptions;
use std::io::prelude::*;

fn main() {
    let mut n: usize;
    for i in 1..31 {
        n = i * 10;
        ow(n);
        ow(n);
    }
}

fn ow(n: usize) {
    let filename = format!("t{}.in", n);
    let mut file = OpenOptions::new()
        .write(true)
        .create(true)
        .append(true)
        .open(filename)
        .unwrap();
    if let Err(e) = writeln!(file, "{} {}", n, n) {
        eprintln!("Couldn't write to file: {}", e);
    }
    for _ in 0..n {
        for j in 0..n {
            if j != 0 {
                if let Err(e) = write!(file, " ",) {
                    eprintln!("Couldn't write to file: {}", e);
                }
            }
            let num: i32 = rand::thread_rng().gen_range(1, 100);
            if let Err(e) = write!(file, "{}", num) {
                eprintln!("Couldn't write to file: {}", e);
            }
        }
        if let Err(e) = writeln!(file, "") {
            eprintln!("Couldn't write to file: {}", e);
        }
    }
}

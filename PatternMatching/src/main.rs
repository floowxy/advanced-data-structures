mod build_lps;
mod kmp_search;
// modules 

use kmp_search::kmp_search;
// use module

fn main() {
    let text = "ABABABAC";
    let pattern = "ABA";

    let matches = kmp_search(text, pattern);

    println!("Text: {}", text);
    println!("Pattern: {}", pattern);
    println!("Matches: {:?}", matches);
}
mod brute_force_search;

use brute_force_search::brute_force_search;

fn main() {
    let text = "ABABABAC";
    let pattern = "";

    match brute_force_search(text, pattern) {
        Ok(occurrences) => {
            if occurrences.is_empty() {
                println!("pattern not found");
            } else {
                println!("occurrences: {:?}", occurrences);
            }
        }

        Err(error) => {
            println!("Error:🐱 {}", error);
        }
    }
}
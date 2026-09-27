pub fn brute_force_search(text: &str,pattern: &str,) -> Result<Vec<usize>, &'static str> {

    let len_text = text.len();
    let len_pattern = pattern.len();

    if pattern.is_empty() {
        return Err("pattern cannot be empty");
    }

    let text_bytes = text.as_bytes();
    let pattern_bytes = pattern.as_bytes();

    let mut occurrences = Vec::new();

    if len_pattern > len_text {
        return Ok(occurrences);
    }

    for i in 0..=len_text - len_pattern {
        let mut j = 0;
        while j < len_pattern && text_bytes[i + j] == pattern_bytes[j]{
            j += 1;
        }

        if j == len_pattern {occurrences.push(i);}
    }

    Ok(occurrences)
}
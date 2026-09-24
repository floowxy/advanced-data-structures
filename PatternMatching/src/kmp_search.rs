use crate::build_lps::build_lps;
pub fn kmp_search(text : &str , pattern :&str) -> Vec<usize>{
    if pattern.is_empty() {
    return Vec::new();
    }

    let lps = build_lps(pattern);
    
    let text = text.as_bytes();
    let pattern = pattern.as_bytes();

    let len_text    = text.len();
    let len_pattern = pattern.len();

    let mut i: usize = 0;
    let mut j: usize = 0;

    let mut matches: Vec<usize> = Vec::new();

    while i < len_text {
        if text[i] == pattern[j]{
            i +=1;
            j +=1;
        }
        if j == len_pattern {
            matches.push(i-j);
            j = lps[j-1];
        }    
        else if i < len_text && text[i] != pattern[j]{
            if j > 0 {
                j = lps[j-1];
            }
            else {
                i = i+1;
            }
        }
    
    }
    matches
}
pub fn build_lps(pattern: &str) -> Vec<usize> {
    let pattern = pattern.as_bytes();
    /*
    pattern.as_bytes returns reference  &[u8] UTF-8
    Example : pattern = "ABABAC$"
    bytes > [65,66,65,66,65,67,36]

    pattern &str > pattern &[u8] 
    */
    let m = pattern.len(); //m type usize
    
    let mut lps = vec![0usize; m]; //  m positions initialized to 0

    let mut len: usize = 0; //len border
    let mut   i: usize = 1; // index pattern

    while i < m {
        if pattern[i] == pattern[len]{
            len += 1;
            lps[i]=len;
            i   += 1;
        }
        else if len > 0 {
            len = lps[len - 1];
        }
        else{
            lps[i] = 0;
            i     += 1;
        }
    }
    lps
}
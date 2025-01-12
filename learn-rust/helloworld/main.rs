
fn main() {
    let value: f64 = 3.141592;
    let decimal_width = 4;
    println!("Hello, world!");
    println!("I am learning Rust, this is 2024!!!");
    println!("Pi is {value:.decimal_width$}"); // Prints Pi is 3.1416

    //let x = 5;
    //x = 10; // This will throw an error because x is immutable
    let mut x = 5;
    println!("The value of x is: {}", x);
    x = 10; // This will work because x is mutable
    println!("The value of x is: {}", x);

    // Constants
    const INDIA_US_TIME_DIFFERENCE: f64 = 12.5;
    println!("print a float:{}", INDIA_US_TIME_DIFFERENCE);

    // Shadowing

    // Expressions vs statements
    //let y = (let x = 6); // This is not allowed as assignment doesn't retunr value
    let _y = { // this will resolve into expression and so it works.
        let x = 6;
        x + 5 //adding a semicolon will make it a statement. This is an expression
    };
    // only expression will return a value, statements doesn't return a value.

}

//One of my implementations for a merge-in place of two sorted arrays problems.
// Leetcode: merge 2-sorted arrays in place
pub fn merge(nums1: &mut Vec<i32>, m: i32, nums2: &mut Vec<i32>, n: i32) {
    let mut p1: i32 = m - 1;
    let mut p2: i32 = n - 1;
    //println!("Hello, world!");
    for p in (0..=m+n-1).rev() {
        //println!("We are here");
        if p2 < 0 {
            break;
        }

        if p1 >=0 && nums1[p1 as usize] > nums2[p2 as usize] {
    
            //std::mem::replace(&mut nums1[p as usize], nums1.get(p1 as usize)); // this had errors.
            if let Some(value) = nums1.get_mut(p1 as usize) {
                nums1[p as usize] = *value;
            }
            p1 -= 1;
        } else {
            if let Some(value) = nums2.get_mut(p2 as usize) {
                nums1[p as usize] = *value;
            }
            p2 -= 1;
        }
    }
}

// Leetcode: Remove duplicates in an array
pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
        
    if nums.is_empty() { return 0; }

    let mut insertindex: i32 = 1;
    for i in 1..nums.len() {
        if nums[i-1] != nums [i] {
            nums[insertindex as usize] = nums[i];
            insertindex += 1;
        }
    }
    insertindex
}

// Leetcode: Rotate array by k-elements to the right.
pub struct Solution {

}
impl Solution {
    pub fn rotate(nums: &mut Vec<i32>, mut k: i32) {
        k %= nums.len() as i32;
        let n:i32 = nums.len() as i32 - 1;
        Self::reverse(nums, 0, n);
        Self::reverse(nums, 0, k-1);
        Self::reverse(nums, k, n);        
    }

    fn reverse(nums: &mut Vec<i32>, mut start: i32, mut end: i32) {
        while start < end {
            let temp:i32 = nums[start as usize];
            nums[start as usize] = nums[end as usize];
            nums[end as usize] = temp;
            start += 1;
            end -= 1;
        }
    }
}
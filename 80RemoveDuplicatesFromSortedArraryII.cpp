/*
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new length.
*/
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        const int count = nums.size();
        const int repeated_times = 2; // This can be changed to adapt any times
        if ( count <= repeated_times ) {
            return count;
        }
        
        int index = repeated_times;
        for (int i = repeated_times; i < count; ++i) {
            if ( nums[i] != nums[index - repeated_times]) {
                nums[index++] = nums[i];
            }
        }
        return index;
    }
};

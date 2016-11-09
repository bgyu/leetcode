/*
https://leetcode.com/problems/search-in-rotated-sorted-array-ii/

81. Search in Rotated Sorted Array II
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/
// Like "Search in Rotated Sorted Array", there are other simpler solutions, but hard to understand the boundary
// Using an extra binary search function makes code easy to understand.
class Solution {
public:
    bool bs(vector<int>& nums, int first, int last, int target) {
        if (first >= nums.size() || last >= nums.size() || nums.size() == 0 )
        {
            return false;
        }
        
        while (first <= last)
        {
            int mid = (first + last) / 2;
            if ( nums[mid] == target )
                return true;
                
            if ( nums[mid] < target )
                first = mid + 1;
            else
                last = mid - 1;
        }
        
        return false;
    }
    
    bool search(vector<int>& nums, int target) {
        if ( nums.size() == 0 )
        {
            return false;
        }
        
        if ( nums.size() == 1 )
        {
            return nums[0] == target;
        }
        
        int first = 0;
        int last = nums.size() - 1;
        
        while ( first <= last )
        {
            int mid = (first + last) / 2;
            if ( nums[mid] == target )
                return true;
                
            if ( nums[first] < nums[mid] )
            {
                if ( nums[first] <= target && target <= nums[mid] )
                    return bs(nums, first, mid, target);
                else
                    first = mid + 1;
            }
            else if ( nums[first] > nums[mid] )
            {
                if ( nums[mid] <= target && target <= nums[last] )
                    return bs(nums, mid, last, target);
                else
                    last = mid - 1;
            }
            else // nums[first] == nums[mid]
            {
                ++first;
                if ( first < nums.size() && nums[first] == target)
                    return true;
            }
        }
        return false;
    }
};

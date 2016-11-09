/*
https://leetcode.com/problems/search-in-rotated-sorted-array/
33. Search in Rotated Sorted Array
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
*/
class Solution {
public:
    int bs(vector<int>& nums, int start, int end, int target) // binary search based on start and end index
	{
		if (start > end || start >= (int)nums.size() || end >= (int)nums.size())
			return -1;

		while (start <= end) {
			int mid = (start + end) / 2;
			if (nums[mid] == target)
				return mid;
			else if (nums[mid] > target) 
			{
				end = mid - 1;
			}
			else // nums[mid] < target
			{
				start = mid + 1;
			}
		}

		return -1;
	}

	int search(vector<int>& nums, int target) 
	{
		int first = 0;
		int last = nums.size() - 1;

		while (first <= last) 
		{
			const int mid = (first + last) / 2;
			
			if (nums[mid] == target)
				return mid;

			if (nums[first] <= nums[mid]) // The first half is sorted
			{
			    // target is in the first half which is sorted, we can use binary search to get the result
				if (nums[first] <= target && target <= nums[mid])
					return bs(nums, first, mid, target);
				else
					first = mid + 1;
			} 
			else  // nums[first] > nums[mid]
			{
			    // target is in the second half which is sorted, we can use binary search to get the result
				if (nums[mid] <= target && target <= nums[last])
					return bs(nums, mid, last, target);
				else
					last = mid - 1;
			}			
		}
		return -1;
	}
};

/*
// Other solution online, but the boundary is not easy to understand
class Solution {
public:
    int search(int A[], int n, int target) {
        int first = 0, last = n;
        while (first != last) {
            const int mid = (first + last) / 2;
            if (A[mid] == target)
                return mid;
            if (A[first] <= A[mid]) {
                if (A[first] <= target && target < A[mid])
                    last = mid;
                else
                    first = mid + 1;
            } else {
                if (A[mid] < target && target <= A[last-1])
                    first = mid + 1;
                else
                    last = mid;
            }
        }
        return -1;
    }
};
*/

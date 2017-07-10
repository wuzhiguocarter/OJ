// 414. Third Maximum Number
// Given a non-empty array of integers, 
// return the third maximum number in this array. If it does not exist, return the maximum number. The time complexity must be in O(n).

// Example 1:
// Input: [3, 2, 1]

// Output: 1

// Explanation: The third maximum is 1.
// Example 2:
// Input: [1, 2]

// Output: 2

// Explanation: The third maximum does not exist, 
// so the maximum (2) is returned instead.
// Example 3:
// Input: [2, 2, 3, 1]

// Output: 1

// Explanation: Note that the third maximum here 
// means the third maximum distinct number.
// Both numbers with value 2 are both considered as second maximum.
#include <stdio.h>

int thirdMax(int* nums, int numsSize);

int nums[2] = {1,2};

int main()
{
	int ret = -1;
	ret = thirdMax(nums, 2);
	printf("Result is %d\n", ret);
	return 0;
}
int thirdMax(int* nums, int numsSize) {
	// assert(!(numsSize >= 2));
    // step-1: sort array *nums in descending order
    // Bubble sorting
    for (int i = 0; i < numsSize; ++i)
    {
    	for (int j = numsSize-1; j > i; --j) //attention
    	{
    		int temp = *(nums + j);
    		if (temp >= *(nums + j-1))
    		{
    			*(nums + j) = *(nums + j-1);
    			*(nums + j-1) = temp;
    		}
    	}
    }

    for (int i = 0; i < numsSize; ++i)
    {
    	printf("%d,", *(nums + i));
    }
    printf("\n");
    // step-2: find the third maximum distinct number if it exist, or 
    // return the maximum (2)
    int index = 0;
    int i = 0;
    for (; i < numsSize-1; ++i)
    {
    	if (*(nums + i) != *(nums + i+1))
    	{
    		index ++;
    		if (index == 2)
    		{
    			return *(nums + i+1);
    		}
    	}
    }

    return *(nums + 0); // added after run 2nd time

}
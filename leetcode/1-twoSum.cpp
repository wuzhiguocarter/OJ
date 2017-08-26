// 1. Two Sum
// Given an array of integers, return indices of the two numbers 
// such that they add up to a specific target.

// You may assume that each input would have exactly one solution, 
// and you may not use the same element twice.

// Example:
// Given nums = [2, 7, 11, 15], target = 9,

// Because nums[0] + nums[1] = 2 + 7 = 9,
// return [0, 1].

class Solution {
public:
    // 暴力搜索，时间复杂度O(n^2)，空间复杂度O(1)
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ret(2);
        int size = nums.size();
        for(int i = 0; i < size; i++){
            int a = nums[i];
            for(int j = i+1; j < size; j++){
                int b = nums[j];
                if(target == a + b){
                    ret = {i,j};
                    return ret;
                }                    
            }
        }
        return ret;
    }
    // 用一个哈希表存储每个数对应的下标
    // 时间复杂度O(n),空间复杂度O(n)
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mapping;
        vector<int> result;
        // 遍历一遍数组，将数组的元素和索引映射到unordered_map的元素
        for(int i = 0; i < nums.size();i++){
            mapping[nums[i]] = i;
        }
        for(int i = 0; i < nums.size();i++){
            const int gap = target - nums[i];
            // 第一个条件测试是是否找到gap，第二个条件保证第二个数的索引大于第一个
            if(mapping.find(gap) != mapping.end() && mapping[gap] > i){
                result.push_back(i);
                result.push_back(mapping[gap]);
                break;
            }
        }
        return result;        
    }
};
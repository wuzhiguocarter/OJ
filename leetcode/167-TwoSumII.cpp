// 167. Two Sum II - Input array is sorted
// Given an array of integers that is already sorted in ascending order,
//  find two numbers such that they add up to a specific target number.

// The function twoSum should return indices of the two numbers such that
//  they add up to the target, where index1 must be less than index2. 
//  Please note that your returned answers (both index1 and index2) are not zero-based.

// You may assume that each input would have exactly one solution and 
// you may not use the same element twice.

// Input: numbers={2, 7, 11, 15}, target=9
// Output: index1=1, index2=2
class Solution {
public:
    // 采用hash table 两次遍历法
    // 时间复杂度O(n),空间复杂度O(n)
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ret;
        unordered_map<int, int> mapping;
        for(int i = 0; i < numbers.size(); i++){
            mapping[numbers[i]] = i;
        }
        for(int i = 0; i < numbers.size(); i++){
            const int gap = target - numbers[i];
            if(mapping.find(gap) != mapping.end() && mapping[gap] > i){
                ret.push_back(i+1);
                ret.push_back(mapping[gap]+1);
                break;
            }    
        }
        return ret;
    }
};

// 采用hash table 一次遍历法
// 时间复杂度O(n),空间复杂度O(n)
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ret;
        unordered_map<int, int> mapping;
        for(int i = 0; i < numbers.size(); i++){
            int gap = target - numbers[i];
            if(mapping.find(gap) != mapping.end() && mapping.find(gap)->second != i){
                return vector<int>({mapping[gap]+1, i+1});
            }
            mapping[numbers[i]] = i; // 思考为什么放在这里，而不是if前面
        }
        return ret;
    }
};

// 左右夹逼法
// 时间复杂度O(n),空间复杂度O(1)
vector<int> twoSum(vector<int>& numbers, int target) {   
    int l = 0;
    int r = numbers.size() -1;
    while(l < r){
        if(numbers[l] + numbers[r] == target){
            vector<int> res{l+1,r+1};
            return res;
        }
        else if(numbers[l] + numbers[r] > target){
            r--;
        }
        else{
            l++;
        }
    }
}

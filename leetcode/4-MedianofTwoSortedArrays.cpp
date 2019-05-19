// unique algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector

using namespace std;

    void printvec(std::vector<int> vec) {
        for (auto &elem : vec) {
            cout << elem << "\t";
        }
        cout << "\n";
    }
    
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        size_t sz = nums1.size()+nums2.size();
        
        vector<int> merged_nums(sz);
        std::copy(nums1.begin(),nums1.end(),merged_nums.begin());
        std::copy(nums2.begin(),nums2.end(),merged_nums.begin()+std::distance(nums1.begin(),nums1.end()));
        
        // printvec(merged_nums);
        _sort(merged_nums);
        // printvec(merged_nums);
        
        if(sz %2 == 0){
            return (merged_nums[(sz-1)/2]+merged_nums[(sz-1)/2+1])*0.5;
        } else {
            return merged_nums[sz/2];
        }
    }
private: 
    void _sort(vector<int>& arr) {
        if(arr.size() < 2)
            return;
        vector<int> arr_tmp(arr.size());
        merge_sort(arr, 0, arr.size()-1, arr_tmp);
    }
    void merge_sort(vector<int> &arr, int left, int right, vector<int> &arr_tmp) {
        if (left < right) {
            int mid = (left + right)/2;
            merge_sort(arr, left, mid, arr_tmp);
            merge_sort(arr, mid+1, right, arr_tmp);
            merge(arr,left,mid,right,arr_tmp);
        }
    }
    void merge(vector<int> &arr, int left, int mid, int right, vector<int> &arr_tmp) {
        int i = left;
        int j = mid + 1;
        int t = 0;
        // 左、右
        //while(!(i > mid || j > right)) {
        while(i <= mid && j <= right) {
            if (arr[i] < arr[j]) {
                arr_tmp[t++] = arr[i++];
            } else {
                arr_tmp[t++] = arr[j++];
            }
        }
        while (i <= mid) {
            arr_tmp[t++] = arr[i++];
        }
        while(j <= right){
            arr_tmp[t++] = arr[j++];
        }
        
        t = 0;
        for(;left <= right;){
            arr[left++] = arr_tmp[t++];
        }
    }
};


    
int main() {
    Solution sol;
    vector<int> nums1 = {3,4};
    vector<int> nums2 = {1,2};
	auto result = sol.findMedianSortedArrays(nums1, nums2);
	cout << result;
	return 0;
}

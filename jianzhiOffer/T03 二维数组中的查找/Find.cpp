#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool Find(int target, const vector<vector<int> > & array) {
    	// 输入检查
        if(array.size() == 0) return false;
        // 初始化状态标志为"未找到"
        bool isfind = false;

        // 从右上角开始查找
        size_t rows = array.size();
        size_t cols = array[0].size();
        size_t r_index = 0;
        size_t c_index = cols - 1;

        // 迭代的查找直到r_index,c_index超出范围（未查找到）
        // 或者查找到目标，返回true
		while(r_index < rows && c_index >= 0){
            int temp = array[r_index][c_index];
            if(temp == target) return true;// 若右上角的值等于目标值，返回true
            if(temp > target){// 若右上角的值大于目标值，舍弃当前列(以后不在遍历当前列的元素)
                c_index--;
            }
            if(temp < target){// 若右上角的值小于目标值，舍弃当前行(以后不在遍历当前行的元素)
                r_index++;
            }
        }
        return false;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int> > array = {{1,2,8,9},
                                  {2,4,9,12},
                                  {4,7,10,13},
                                  {6,8,11,15}};
    Solution s;
    int target = stoi(argv[1],NULL,10);
    bool isfind = s.Find(target,array);
    cout << "Result: " << isfind << endl;
    return 0;
}
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool Find(int target, const vector<vector<int> > & array) {
        if(array.size() == 0) return false;
        bool isfind = false;
        size_t rows = array.size();
        size_t cols = array[0].size();
        size_t r_index = 0;
        size_t c_index = cols - 1;
		while(r_index < rows && c_index >= 0){
            int temp = array[r_index][c_index];
            if(temp == target) return true;
            if(temp > target){
                c_index--;
            }
            if(temp < target){
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
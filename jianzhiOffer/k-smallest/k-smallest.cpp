#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int swap(vector<int> &a, int index_a, vector<int> &b, int index_b){
        if(index_a > (int)a.size() - 1 || index_b > (int)b.size() - 1){
            return 0;
        }
        cout << "Going to swap " << a[index_a] << " and " << b[index_b] << endl;
        int temp = a[index_a];
        a[index_a] = b[index_b];
        b[index_b] = temp;
         
        return 1;
    }
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        //if(k < input.size()) return vector<int> fail(1,-1);

        vector<int> ret(k,-1);
        for(int i = 0; i < k; i++){
            ret[i] = input[i];
            cout << "push: " << ret[i] << endl;
        }

        if((int)input.size()/k <= 1) return ret;
         
        for(int j =  1; j <= (int)input.size()/k - 1; j++){
            // 0:k-1
            for(int m = 0; m < k; m++){
            	cout << "\n\n" << "m = " << m << endl;
                for(int i = 0;i+j*k < (int)input.size() && i < k; i++){
                    int index = i + j*k;
                    cout << "index: " << index << endl;
                    if(ret[m] > input[index]){
                        swap(ret,m,input,index);
                    }
                }
            }
        }
         
        return ret;
    }
    void print_vector(vector<int> vec){
    	cout << "\nPrint vector:" << endl;
    	for (std::vector<int>::iterator i = vec.begin(); i != vec.end(); ++i)
    	{
    		cout << *i << endl;
    	}
    }
};

int main(){

	Solution s;
	vector<int> test{4,5,1,6,2,7,3,8};
	int k = 4;

	vector<int> ret;
	ret = s.GetLeastNumbers_Solution(test,k);
	s.print_vector(ret);

	return  0;
}
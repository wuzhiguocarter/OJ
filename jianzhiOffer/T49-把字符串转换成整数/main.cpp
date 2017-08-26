// #include <stdio.h>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int StrToInt(string str) {
        if(str.size() == 0) return 0;
        
        int sign = 1;
        stack<int> ret;
        
        for(int i = 0; i < str.size(); i++){
            if(str[i] == '-'){
                sign = -1;
                continue;
            }
            if(str[i] == '+'){
                sign = 1;
                continue;
            }
            
            if(str[i] > '9' || str[i] < '0'){
                return 0;
            }
            // cout << "push: " << str[i]-'0' << endl;
            ret.push(str[i]-'0');
            // cout << "push: " << ret.top() << endl;
        }

        // cout << "sign:\t" << sign << endl;
        cout << "ret.size()" << ret.size() << endl;

        int MY_INT_MAX = 0x7FFFFFFF;
        int MY_INT_MIN = 0x80000000;
        
        long res = 0;
        int base = 1;
        
        // cout << "stack:\t" << endl;
        if(ret.empty()) return 0;
        int size = ret.size();
        for(int i = 0; i < size; i++){
            if(res*sign > MY_INT_MAX || res*sign < MY_INT_MIN){
            	cout << "溢出错误！" << endl;
            	return 0;
            } 
            if(ret.empty()){
            	cout << "empty" << endl;
            	return (int)res;
            } 
            cout << "ret.top(): " << ret.top() << endl;
            res = res + base*ret.top();
            base = base*10;
            ret.pop();
            
        }
        cout << endl;
        return (int)res;
    }
};

int main(){

	Solution obj;
	// string str;
	// cin >> str;
	int res = obj.StrToInt("123");
	cout << "res:\t" << res << endl;

	return 0;
}
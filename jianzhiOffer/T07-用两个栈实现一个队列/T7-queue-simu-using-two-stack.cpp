class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
    	int ret;
    	if(!stack2.empty()){
    		ret = stack2.top();
    		stack2.pop();
    		return ret;
    	}
    	else{
    		if(!stack1.empty()){
    			while(!stack1.empty()){
    				int temp = stack1.top();
    				stack1.pop();
    				stack2.push(temp);
    			}
	    		ret = stack2.top();
	    		stack2.pop();
	    		return ret;
    		}
    		else{
    			return -1;
    		}
    	}
        
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
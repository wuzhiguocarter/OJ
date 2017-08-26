class Solution
{
public:
    void push(int node) {
        que1.push(node);
    }

    int pop() {
    	int ret;
    	if(!que1.empty()){
    		if(que1.size() == 1){
    			ret = que1.front();
    			que1.pop();
    			return ret;
    		}
    		else{
    			while(que1.size() != 1){
	    			int temp = que1.front();
	    			que1.pop();
	    			que2.push(temp);
	    		}
    			ret = que1.front();
    			que1.pop();
    			return ret;
    		}	
    	}
    	else{
	    	if(!que2.empty()){
	    		if(que2.size() == 1){
	    			ret = que2.front();
	    			que2.pop();
	    			return ret;
	    		}
	    		else{
	    			while(que2.size() != 1){
		    			int temp = que2.front();
		    			que2.pop();
		    			que1.push(temp);
		    		}
	    			ret = que2.front();
	    			que2.pop();
	    			return ret;
	    		}	
	    	}
    		else
    			return -1;
    	}
        
    }

private:
    queue<int> que1;
    queue<int> que2;
};
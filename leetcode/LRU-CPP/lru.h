#include <iostream>
#include <list>
#include <map>


using namespace std;

class LRUCache {
private:
    typedef int key_t;
    typedef int value_t;
    typedef struct{
        key_t key;
        value_t value;
    } Node_t;
    typedef list<Node_t> cacheList_t;
    typedef map<key_t,cacheList_t::iterator> map_t;
    
    int m_capacity;
    cacheList_t m_cacheList;
    map_t m_mp;
    
    
    
public:
    LRUCache(int capacity) : m_capacity(capacity){
        
    }
    
    int get(int key) {
        auto it = m_mp.find(key);
        // not cached
        if(it == m_mp.end()) return -1;
        // cached
        else{
            auto list_it = m_mp[key];
            Node_t node = {key,list_it->value};
            m_cacheList.erase(list_it);
            m_cacheList.push_front(node);
            m_mp[key] = m_cacheList.begin();
            return m_cacheList.begin()->value;
        }
    }
    
    void put(int key, int value) {
        auto it = m_mp.find(key);
        // cached
        if(it != m_mp.end()){
            auto listIt = m_mp[key];
            // delete the cached node, and then insert it to the list head
            Node_t node = {key, value};
            m_cacheList.erase(listIt);
            m_cacheList.push_front(node);
            m_mp[key] = m_cacheList.begin();
            
        }
        // not cached
        else{
            // cache is full
            if(m_cacheList.size() == m_capacity){
                m_mp.erase(m_cacheList.back().key);
                m_cacheList.pop_back();
            }
            // cache is not full
            Node_t node = {key,value};
            m_cacheList.push_front(node);
            m_mp[key] = m_cacheList.begin();
            
        }
        
    }

    void printCacheList() const{
    	cout << "cacheList:" << endl;
    	for(auto &node:m_cacheList){
    		cout << "key: " << node.key << "\tvalue: " << node.value << endl;
    	}
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
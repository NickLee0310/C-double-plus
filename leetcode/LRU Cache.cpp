/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

The cache is initialized with a positive capacity.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2 capacity)
*/
class LRUCache {    
public:
    LRUCache(int cap)
        :capacity(cap)
    {}
    int get(int key) 
    {
        if(data.find(key) == data.end())
            return -1;
        used(key);
        return data[key];
    }
    void put(int key, int value) 
    {
        used(key);
        data[key] = value;
    }
private:
    int capacity;
    unordered_map<int, int> data;
    unordered_map<int, list<int>::iterator> pos;
    list<int> recent;
    void used(int key)
    {
        if(pos.find(key) != pos.end())
        {
            recent.erase(pos[key]);
        }
        else if(pos.size() == capacity)
        {
            int old = recent.back();
            recent.pop_back();
            data.erase(old);
            pos.erase(old);
        }
        recent.push_front(key);
        pos[key] = recent.begin();
    }
};

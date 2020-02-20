/*
Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.
Example:

MyQueue queue = new MyQueue();

queue.push(1);
queue.push(2);  
queue.peek();  // returns 1
queue.pop();   // returns 1
queue.empty(); // returns false
*/

class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() 
        :data()
    {}
    
    /** Push element x to the back of queue. */
    void push(int x) 
    {
        stack<int> temp;
        while(!data.empty())
        {
            temp.push(data.top());
            data.pop();
        }
        data.push(x);    
        while(!temp.empty())
        {
            data.push(temp.top());
            temp.pop();
        }
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() 
    {
        int val = data.top();
        data.pop();    
        return val;
    }
    
    /** Get the front element. */
    int peek() 
    {
        return data.top();    
    }
    
    /** Returns whether the queue is empty. */
    bool empty() 
    {
        return data.empty();    
    }
private:
    stack<int> data;
};

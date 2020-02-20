/*
Implement the following operations of a stack using queues.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.
Example:

MyStack stack = new MyStack();

stack.push(1);
stack.push(2);  
stack.top();   // returns 2
stack.pop();   // returns 2
stack.empty(); // returns false
*/

class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack()
        :data()
    {}
    
    /** Push element x onto stack. */
    void push(int x) 
    {
        int origSize = data.size();
        data.push(x);
        for(int i=0; i<origSize; ++i)
        {
            data.push(data.front());
            data.pop();
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() 
    {
        int val = data.front();
        data.pop();    
        return val;
    }
    
    /** Get the top element. */
    int top() 
    {
        return data.front();    
    }
    
    /** Returns whether the stack is empty. */
    bool empty() 
    {
        return data.empty();    
    }
private:
    queue<int> data;
};

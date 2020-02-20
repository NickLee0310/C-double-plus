/*
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

*/
class BSTIterator {
public:
    BSTIterator(TreeNode* root)
        :itr(root), nodes()
    {
        while(itr)
        {
            nodes.push(itr);
            itr = itr->left;
        }
    }
    
    /** @return the next smallest number */
    int next() 
    {
        auto itr = nodes.top();
        nodes.pop();
        int val  = itr->val;
        auto itr2 = itr->right;
        while(itr2)
        {
            nodes.push(itr2);
            itr2 = itr2->left;
        }     
        return val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() 
    {
        return !nodes.empty();
    }
private:
    TreeNode* itr;   
    stack<TreeNode*> nodes;
};

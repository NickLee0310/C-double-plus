/*
Implement a trie with insert, search, and startsWith methods.

Example:

Trie trie = new Trie();

trie.insert("apple");
trie.search("apple");   // returns true
trie.search("app");     // returns false
trie.startsWith("app"); // returns true
trie.insert("app");   
trie.search("app");     // returns true
*/

class Trie {
public:
    /** Initialize your data structure here. */
    Trie()
        :root(make_unique<node>(0))
    {}
    
    /** Inserts a word into the trie. */
    void insert(string word) 
    {
        auto cur = root.get();
        for(auto ch: word)
        {
            if(!cur->nodes[ch - 'a'])
                cur->nodes[ch - 'a'] = make_unique<node>(ch - 'a');
            cur = cur->nodes[ch - 'a'].get();
        }
        cur-> isEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) 
    {
        auto cur = root.get();
        for(auto ch: word)
        {
            if(!cur->nodes[ch - 'a'])
                return false;
            cur = cur->nodes[ch - 'a'].get();
        }
        return cur->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) 
    {
        auto cur = root.get();
        for(auto ch: prefix)
        {
            if(!cur->nodes[ch - 'a'])
                return false;
            cur = cur->nodes[ch - 'a'].get();
        }
        return true;
    }
private:
    struct node
    {
        int val;
        bool isEnd;
        array<unique_ptr<node>, 26> nodes;
        node(int v)
            :val(v), 
             isEnd(false), 
             nodes()
        {};
    };
    unique_ptr<node> root;
};

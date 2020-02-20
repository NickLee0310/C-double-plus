/*
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

Example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
*/

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary()
        :root(make_unique<node>(0))
    {}
    
    /** Adds a word into the data structure. */
    void addWord(string word) 
    {
        auto cur = root.get();
        for(auto ch:word)
        {
            if(!cur->nodes[ch - 'a'])
                cur->nodes[ch - 'a'] = make_unique<node>(ch - 'a');
            cur = cur->nodes[ch - 'a'].get();
        }
        cur->isEnd = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) 
    {
        auto cur = root.get();
        bool find = false;
        searchByChar(word, cur, find, 0);
        return find;
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
    void searchByChar(const string& word,
                     node* cur,
                     bool& find,
                     int idx)
    {
        if(find) return;
        if(word.size() == idx)
        {
            if(cur->isEnd) 
                find = true;
            return;
        }
        if(word[idx] == '.')
        {
            for(auto& node:cur->nodes)
            {
                if(node)
                    searchByChar(word, node.get(), find, idx+1);
            }
        }
        else if(cur->nodes[word[idx] - 'a'])
        {
            cur = cur->nodes[word[idx] - 'a'].get();
            searchByChar(word, cur, find, idx+1);
        }
    }
};

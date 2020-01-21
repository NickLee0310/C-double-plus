/*
Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

Example 1:

Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
 

Example 2:

Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
*/

class Solution {
public:
    int countSubstrings(string s) 
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 1));
        int ans = n;
        for(int i=n-2; i>=0; --i)
            for(int j=i+1; j<n; ++j)
            {
                if(dp[i+1][j-1] && s[i] == s[j])
                    dp[i][j] = 1;
                else
                    dp[i][j] = 0;
                ans += dp[i][j];
            }
        return ans;
    }
};

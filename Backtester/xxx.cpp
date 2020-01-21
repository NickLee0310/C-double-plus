class Solution {
public:
    int stoneGameII(vector<int>& piles) 
    {
        int n = piles.size();
        auto dp = vector<vector<int>>(n+1,  vector<int>(n+1, 0));
        vector<int> subsum(n+1, 0);
        for(int i=n-1; i>=0; --i)
            subsum[i] = subsum[i+1] + piles[i];
        for(int i=n-1; i>=0; --i)
            for(int j=n-1; j>=1; --j)
                for(int X=1; X<=2*j && i+X <= n ; ++X)
                {
                    dp[i][j] = max(dp[i][j], subsum[i] - dp[i+X][max(j, X)]);
                }
        return dp[0][1];
    }
};

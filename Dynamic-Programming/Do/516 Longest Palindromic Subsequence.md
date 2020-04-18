// 516 Longest Palindromic Subsequence
中等  
```
class Solution {
public:
  // https://mp.weixin.qq.com/s/zNai1pzXHeB2tQE6AdOXTA
  int longestPalindromeSubseq(string s) {
    // 状态:  dp[i][j]表示s[i..j]之间回文子序列的长度，dp设为二维数组是因为判断回文子序列需要两头抓
    // 选择:  dp[i][j]可以由什么所代替：
    //  若s[i] == s[j]，则dp[i][j] = dp[i + 1][j - 1] + 2
    //  若s[i] != s[j]，则dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
    // Base Case：
    //  如果只有一个字符，显然最长回文子序列长度是 1，也就是dp[i][j] = 1,(i == j)
    //  因为i肯定小于等于j，所以对于那些i > j的位置，根本不存在什么子序列，应该初始化为 0。
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      dp[i][i] = 1;
    }
    for (int i = n - 1; i >= 0; i--) {
      for (int j = i + 1; j < n; j++) {
        if (s[i] == s[j])
          dp[i][j] = dp[i + 1][j - 1] + 2;
        else
          dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
      }
    }
    return dp[0][n - 1];
  }
};
```
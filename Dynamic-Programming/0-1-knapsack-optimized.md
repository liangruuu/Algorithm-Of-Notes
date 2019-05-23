```
0-1背包问题

时间复杂度：O(n*C)  优化程度非常小
空间复杂度：O(n*C)  还能进行优化

状态转移方程：
F(n, C) = 考虑 将n个物品放进容积为C的背包, 使得价值最大
F(i, c) = max(F(i-1, c), v(i)+F(i-1, c-w(i)))

对于上面的转移方程：
第i行元素只依赖于第i-1行元素。理论上，只需要保持两行元素, 而不需要保持一个n维数组, 空间复杂度：O(2 * C) = O(C): 2行,每行C个元素

[   i = 0   ]         [   i = 2   ]          [   i = 2   ]       [   i = 4   ] (偶数行)  
                -->                   -->                   --> 
[   i = 1   ]         [   i = 1   ]          [   i = 3   ]       [   i = 3   ] (奇数行)
``` 
```
/// 动态规划改进: 滚动数组
/// 时间复杂度: O(n * C) 其中n为物品个数; C为背包容积
/// 空间复杂度: O(C), 实际使用了2*C的额外空间
class Knapsack01 {

public:
  int knapsack01(const vector<int> &w, const vector<int> &v, int C) {
    assert(w.size() == v.size() && C >= 0);
    int n = w.size();
    if (n == 0 && C == 0)
      return 0;

    // 把n行改为2行
    vector<vector<int>> memo(2, vector<int>(C + 1, 0));

    for (int j = 0; j <= C; j++)
      memo[0][j] = (j >= w[0] ? v[0] : 0);

    for (int i = 1; i < n; i++)
      for (int j = 0; j <= C; j++) {
        memo[i % 2][j] = memo[(i - 1) % 2][j];
        if (j >= w[i])
          memo[i % 2][j] =
              max(memo[i % 2][j], v[i] + memo[(i - 1) % 2][j - w[i]]);
      }
    return memo[(n - 1) % 2][C];
  }
};
```
再进一步优化：只使用一行大小为C的数组完成动态规划  
二维数组中每个元素只由它上面的和左上角的元素构成,而跟它右上角的元素大小无关, 即可以只使用1行数组,每次更新物品个数时从右向左刷新原数组  
放入物品0：0    1    2    3    4    5  ->  放入物品1：0    1    2    3    4    5  
&emsp;&emsp;&emsp;&emsp;&emsp;0    6    6    6    6    6&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;0    6    10(6)    16(6)    16(6)    16(6)
```
/// 动态规划改进
/// 时间复杂度: O(n * C) 其中n为物品个数; C为背包容积
/// 空间复杂度: O(C), 只使用了C的额外空间
class Knapsack01 {

public:
  int knapsack01(const vector<int> &w, const vector<int> &v, int C) {
    assert(w.size() == v.size() && C >= 0);
    int n = w.size();
    if (n == 0 || C == 0)
      return 0;

    vector<int> memo(C + 1, 0);

    for (int j = 0; j <= C; j++)
      memo[j] = (j >= w[0] ? v[0] : 0);

    for (int i = 1; i < n; i++)
      for (int j = C; j >= w[i]; j--)
        memo[j] = max(memo[j], v[i] + memo[j - w[i]]);

    return memo[C];
  }
};
```
1. 用背包问题解法暴力求解
```
/// 背包问题
class Knapsack01 {

private:
  // 用 [0...index]的物品,填充容积为c的背包的最大价值(对编号为index的物品进行判断)
  int bestValue(const vector<int> &w, const vector<int> &v, int index, int c) {

    if (c <= 0 || index < 0)
      return 0;

    // 方法一：不考虑放入编号为index的物品所获得的的总价值
    int res = bestValue(w, v, index - 1, c);
    if (c >= w[index])
    // 方法二：v[index] + bestValue(w, v, index - 1, c - w[index])  将编号为index的物品放入获得的价值
      res = max(res, v[index] + bestValue(w, v, index - 1, c - w[index]));
    return res;
  }

public:
  int knapsack01(const vector<int> &w, const vector<int> &v, int C) {
    assert(w.size() == v.size() && C >= 0);
    int n = w.size();
    if (n == 0 || C == 0)
      return 0;

    return bestValue(w, v, n - 1, C);
  }
};

```
2. 因为index和c构成了一个数据对, 而这个数据对在求解过程中同样的数据对可能求解了多次, 使用记忆化搜索(自顶向下)
```
/// 记忆化搜索
/// 时间复杂度: O(n * C) 其中n为物品个数; C为背包容积
/// 空间复杂度: O(n * C)
class Knapsack01 {

private:
  // 因为背包问题有两个约束条件n, C; 每一个状态被两个变量定义, 所以开辟的记忆化空间应该是一个二维数组
  vector<vector<int>> memo;

  // 用 [0...index]的物品,填充容积为c的背包的最大价值(对编号为index的物品进行判断)
  int bestValue(const vector<int> &w, const vector<int> &v, int index, int c) {

    if (c <= 0 || index < 0)
      return 0;

    if (memo[index][c] != -1)
      return memo[index][c];

    // 方法一：不考虑放入编号为index的物品所获得的的总价值
    int res = bestValue(w, v, index - 1, c);
    if (c >= w[index])
    // 方法二：v[index] + bestValue(w, v, index - 1, c - w[index])  将编号为index的物品放入获得的价值
      res = max(res, v[index] + bestValue(w, v, index - 1, c - w[index]));
    memo[index][c] = res;
    return res;
  }

public:
  int knapsack01(const vector<int> &w, const vector<int> &v, int C) {
    assert(w.size() == v.size() && C >= 0);
    int n = w.size();
    if (n == 0 || C == 0)
      return 0;

    memo.clear();
    // 等价于memo = vector(n, <vector<int>>(C+1, -1))
    for (int i = 0; i < n; i++)
      memo.push_back(vector<int>(C + 1, -1));
    return bestValue(w, v, n - 1, C);
  }
};
```
3. 自底向上
```
id      0   1   2
weight  1   2   3       有一个容量为5的背包
value   6   10  12


      0      1      2      3      4      5   -容量
0     0      6      6      6      6      6
1     0      6      10(6)  16(6)  16(6)  16(6)
2     0      6      10     16(12) 18     22
|
物品编号


分析方法：
1. 当背包中只有物品0时,容量只有>=1时才能装下物品0,而且价值为6
2. 当背包中有物品0和1时
  * 当容积==1时, 不考虑物品1, 只考虑物品0时(也就是arr[0][1])价值为6;同时考虑物品1和物品0时,因为物品1的容积大于背包大小,所以最大只能够装下物品0,价值为6)->*先考虑当前物品, 再考虑之前的物品
  * 当容积==2时, 不考虑物品1, 只考虑物品0时(也就是arr[0][2])价值为6;同时考虑物品1和物品0时,装下物品1后留给物品0的容积为0,所以arr[1][2]=v(1)+arr[0][0]=10+0=10
  * 当容积==3时, 不考虑物品1, 只考虑物品0时(也就是arr[0][3])价值为6;同时考虑物品1和物品0时,装下物品1后留给物品0的容积为1,所以arr[1][2]=v(1)+arr[0][1]=10+6=16
  *同理...
3. 当背包中有物品0,1,2时
  * 当容积==1时, 不考虑物品2,只考虑物品0,1时(也就是arr[1][1])价值为6;同时考虑物品0,1,2时,因为物品2的容积大于背包大小,所以最大只能够装下物品0,价值为6->*先考虑当前物品, 再考虑之前的物品 
  * 当容积==1时, 不考虑物品2,只考虑物品0,1时(也就是arr[1][1])价值为6;同时考虑物品0,1,2时,因为物品2的容积大于背包大小,所以最大只能够装下物品0,价值为6->*先考虑当前物品, 再考虑之前的物品
  * 当容积==3时, 不考虑物品2, 只考虑物品0,1时(也就是arr[1][3])价值为16;同时考虑物品0,1,2时,装下物品2后留给物品0,1的容积为0,所以arr[2][3]=v(2)+arr[1][0]=12+0=12<16 
  * 当容积==4时, 不考虑物品2, 只考虑物品0,1时(也就是arr[1][4])价值为16;同时考虑物品0,1,2时,装下物品2后留给物品0,1的容积为1,所以arr[2][3]=v(2)+arr[1][1]=12+6=18
  * 当容积==5时, 不考虑物品2, 只考虑物品0,1时(也就是arr[1][5])价值为16;同时考虑物品0,1,2时,装下物品2后留给物品0,1的容积为2,所以arr[2][3]=v(2)+arr[1][2]=12+10=22

最终结果为二维数组右下角的元素大小
```
```
/// 动态规划
/// 时间复杂度: O(n * C) 其中n为物品个数; C为背包容积
/// 空间复杂度: O(n * C)
class Knapsack01 {

public:
  int knapsack01(const vector<int> &w, const vector<int> &v, int C) {
    assert(w.size() == v.size() && C >= 0);
    int n = w.size();
    if (n == 0 || C == 0)
      return 0;

    vector<vector<int>> memo(n, vector<int>(C + 1, 0));

    // 动态规划自底向上规划问题,先处理最基础的问题,即二维数组中第一行的数据
    for (int j = 0; j <= C; j++)
      memo[0][j] = (j >= w[0] ? v[0] : 0);

    for (int i = 1; i < n; i++)
      for (int j = 0; j <= C; j++) {
        // 策略一：不放入编号为i的物品
        memo[i][j] = memo[i - 1][j];
        // 策略二：放入编号为i的物品,先判断能否放入
        if (j >= w[i])
          memo[i][j] = max(memo[i][j], v[i] + memo[i - 1][j - w[i]]);
      }
    return memo[n - 1][C];
  }
};
```
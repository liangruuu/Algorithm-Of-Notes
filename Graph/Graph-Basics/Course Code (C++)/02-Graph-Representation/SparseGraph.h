//
// Created by liuyubobobo on 9/21/16.
//

#ifndef INC_02_GRAPH_REPRESENTATION_SPARSEGRAPH_H
#define INC_02_GRAPH_REPRESENTATION_SPARSEGRAPH_H

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// 稀疏图 - 邻接表
class SparseGraph {

private:
  int n, m;              // 节点数和边数
  bool directed;         // 是否为有向图
  vector<vector<int>> g; // 图的具体数据

public:
  // 构造函数
  SparseGraph(int n, bool directed) {
    assert(n >= 0);
    this->n = n;
    this->m = 0; // 初始化没有任何边
    this->directed = directed;
    // g初始化为n个空的vector, 表示每一个g[i]都为空, 即没有任和边
    g = vector<vector<int>>(n, vector<int>());
  }

  ~SparseGraph() {}

  int V() { return n; } // 返回节点个数
  int E() { return m; } // 返回边的个数

  // 向图中添加一个边
  void addEdge(int v, int w) {

    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    // 一般在邻接表中验证是否存在平行边的复杂度为O(N)
    // 比较耗时所以先不去管平行边

    g[v].push_back(w);
    // v != w(处理自环边)
    if (v != w && !directed)
      g[w].push_back(v);

    m++;
  }

  // 验证图中是否有从v到w的边, 防止平行边的存在
  bool hasEdge(int v, int w) {

    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    for (int i = 0; i < g[v].size(); i++)
      if (g[v][i] == w)
        return true;
    return false;
  }
};

#endif // INC_02_GRAPH_REPRESENTATION_SPARSEGRAPH_H

//
// Created by liuyubobobo on 9/21/16.
//

#ifndef INC_03_VERTEX_ADJACENT_ITERATOR_SPARSEGRAPH_H
#define INC_03_VERTEX_ADJACENT_ITERATOR_SPARSEGRAPH_H

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

    g[v].push_back(w);
    if (v != w && !directed)
      g[w].push_back(v);

    m++;
  }

  // 验证图中是否有从v到w的边
  bool hasEdge(int v, int w) {

    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    for (int i = 0; i < g[v].size(); i++)
      if (g[v][i] == w)
        return true;
    return false;
  }

  // 因为用户在遍历图的时候不小心改变图结构,所以创建一个私有的迭代器类
  // 邻边迭代器, 传入一个图和一个顶点,
  // 迭代在这个图中和这个顶点向连的所有顶点
  // 使用迭代器可以隐藏迭代的过程,按照一定的顺序访问容器的所有内容
  // 相应的可以对map,set...都可以创建迭代器, 从用户的角度和普通遍历是没区别的
  // 则用户在调用的时候只需要实现同一个接口就能分别调用邻接表和邻接矩阵的遍历
  class adjIterator {
  private:
    SparseGraph &G; // 图G的引用
    int v;
    int index;    // 当前迭代到哪里了

  public:
    // 构造函数
    // 因为G是一个引用,所以用构造列表的方式初始化它
    adjIterator(SparseGraph &graph, int v) : G(graph) {
      this->v = v;
      this->index = 0;
    }

    ~adjIterator() {}

    // 返回图G中与顶点v相连接的第一个顶点
    int begin() {
      index = 0;
      if (G.g[v].size())
        return G.g[v][index];
      // 若没有顶点和v相连接, 则返回-1
      return -1;
    }

    // 返回图G中与顶点v相连接的下一个顶点
    int next() {
      index++;
      if (index < G.g[v].size())
        return G.g[v][index];
      // 若没有顶点和v相连接, 则返回-1
      return -1;
    }

    // 查看是否已经迭代完了图G中与顶点v相连接的所有顶点
    bool end() { return index >= G.g[v].size(); }
  };
};

#endif // INC_03_VERTEX_ADJACENT_ITERATOR_SPARSEGRAPH_H

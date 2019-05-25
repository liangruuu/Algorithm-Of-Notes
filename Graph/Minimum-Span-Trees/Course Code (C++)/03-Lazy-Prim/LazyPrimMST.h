//
// Created by liuyubobobo on 9/24/16.
//

#ifndef INC_03_LAZY_PRIM_LAZYPRIMMST_H
#define INC_03_LAZY_PRIM_LAZYPRIMMST_H

#include "Edge.h"
#include "MinHeap.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// 使用Prim算法求图的最小生成树
template <typename Graph, typename Weight> class LazyPrimMST {

private:
  Graph &G;                 // 图的引用
  // 最小堆, 算法辅助数据结构(因为每次都需要选择权值最小的边,所以用最小堆实现,每次使用extractMin来获取最小边)
  MinHeap<Edge<Weight>> pq; 
  bool *marked; // 标记数组, 在算法运行过程中标记节点i是否被访问
  vector<Edge<Weight>> mst; // 最小生成树所包含的所有边
  Weight mstWeight;         // 最小生成树的权值

  // 访问节点v
  void visit(int v) {

    assert(!marked[v]);
    marked[v] = true;

    // 将和节点v相连接的所有未访问的边放入最小堆中
    typename Graph::adjIterator adj(G, v);
    for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
      if (!marked[e->other(v)])
        pq.insert(*e);
  }

public:
  // 构造函数, 使用Prim算法求图的最小生成树
  LazyPrimMST(Graph &graph) : G(graph), pq(MinHeap<Edge<Weight>>(graph.E())) {

    // 算法初始化
    marked = new bool[G.V()];
    for (int i = 0; i < G.V(); i++)
      marked[i] = false;
    mst.clear();

    // Lazy Prim
    // pq承载E(图的边)个元素
    // visit函数遍历节点的所有邻边,所有节点合在一起也是边数E这个级别的
    // 特别的邻接矩阵是V^2级别的, 但是邻接矩阵一般表示的都是稠密图, 对于稠密图来说E和V^2是近乎一个级别的
    // 在visit()过程中需要有个插入操作,相对于优先队列来说也是logE级别的
    // 所以Lazy Prim总共时间复杂度为O(ElogE)
    // 事实上我们可以通过优化把时间复杂度降至O(ElogV)
    visit(0);
    while (!pq.isEmpty()) {
      // 使用最小堆找出已经访问的边中权值最小的边
      Edge<Weight> e = pq.extractMin();
      // 如果这条边的两端都已经访问过了, 则扔掉这条边(不是横切边)
      if (marked[e.v()] == marked[e.w()])
        continue;
      // 否则, 这条边则应该存在在最小生成树中
      mst.push_back(e);

      // 访问和这条边连接的还没有被访问过的节点(判断两个点是红点还是蓝点, 蓝点才能visit)
      if (!marked[e.v()])
        visit(e.v());
      else
        visit(e.w());
    }

    // 计算最小生成树的权值
    mstWeight = mst[0].wt();
    for (int i = 1; i < mst.size(); i++)
      mstWeight += mst[i].wt();
  }

  // 析构函数
  ~LazyPrimMST() { delete[] marked; }

  // 返回最小生成树的所有边
  vector<Edge<Weight>> mstEdges() { return mst; };

  // 返回最小生成树的权值
  Weight result() { return mstWeight; };
};

#endif // INC_03_LAZY_PRIM_LAZYPRIMMST_H

//ShortestPath_Dij.h
#ifndef SHORTESTPATH_DIJ_H_
#define SHORTESTPATH_DIJ_H_
#include "Assistance.h"	
#include <iostream>
#include "AdjMatrixUndirGraph.h"
#include "LinkStack.h"

template<class ElemType>
void DisplayShortAB(const int v1, const int v2,AdjMatrixUndirGraph<ElemType> &g)
//显示A村到B村的最短路径
{
	int* path = new int[g.GetVexNum()];
	int* dist = new int[g.GetVexNum()];
	ShortestPathDij(v1, path, dist,g);
	LinkStack<int> ls;
	ls.Push(v2);
	for (int i = path[v2]; i != -1; i = path[i])
		ls.Push(i);
	int index;
	ls.Pop(index);
	ElemType e;
	g.GetElem(index,e);
	cout << e;
	for (ls.Pop(index); !ls.IsEmpty(); ls.Pop(index))
	{
		g.GetElem(index, e);
		cout << " -> " << e;
	}
	g.GetElem(v2, e);
	cout << " -> " << e;
	cout << "   最短路径长度为：" << dist[v2] << endl;
}


template<class ElemType>
void ShortestPathDij(int v0, int* path, int* dist,AdjMatrixUndirGraph<ElemType>& g)
//使用迪杰斯特拉算法找到从源点v0到其他各点的最短路径
{
	int v, u, MinVal;
	int num = g.GetVexNum();
	for (v = 0; v < num; v++)
	{
		dist[v] = g.GetWeight(v0,v);
		if (dist[v] == g.GetInfinity() || dist[v] == 0)   //v0与v之间没有直接路径
			path[v] = -1;
		else
		{
			path[v] = v0;
		}
		g.SetTag(v,UNVISITED);      //初始化所有顶点的tag为UNVISITED
	}
	g.SetTag(v0,VISITED);
	for (int i = 1; i < num; i++)      //找到当前距离的最小值
	{
		MinVal = 1000;
		u = v0;
		for (v = 0; v < num; v++)
		{
			if (g.GetTag(v) == UNVISITED && dist[v] < MinVal)
			{
				u = v;
				MinVal = dist[v];
			}
		}
		g.SetTag(u, VISITED);         //将u并入集合U中
		for (v = g.FirstAdjVex(u); v != -1; v = g.NextAdjVex(u, v))
		{
			if (g.GetTag(v) == UNVISITED && dist[v] > MinVal + g.GetWeight(u,v))
			{
				dist[v] = MinVal + g.GetWeight(u, v);
				path[v] = u;
			}
		}
	}
}



#endif


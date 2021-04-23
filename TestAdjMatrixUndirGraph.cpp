#include "AdjMatrixUndirGraph.h"		// 邻接矩阵无向图
#include <iostream>
#include <fstream>
#include "Kruskal.h"

using namespace std;
int main(void)
{
    try									// 用try封装可能出现异常的代码
	{
		int N,M;
		ifstream file("test1.txt",ios::in);
		if(!file)
        {
            cout<<"打开文件失败";
            return 0;
        }
		file>>N;
		char *vexs=new char[N];
		for(int i=0;i<N;i++) file>>vexs[i];
		file>>M;
		AdjMatrixUndirGraph<char> g(vexs, N, M);
		char c = '0', e, e1, e2;
		int v, v1, v2, w; //w表示权重，即公路长度
		for(int i=0;i<M;i++)
        {
            file>>e1;
            file>>e2;
            file>>w;
            v1 = g.GetOrder(e1);
            v2 = g.GetOrder(e2);
            g.InsertArc(v1, v2, w);
        }
        cout<<endl<<"乡村之间公路的邻接矩阵为："<<endl;
        if (g.IsEmpty()) cout << "该图为空。" << endl;
        else  g.Display();
	    while (c != '4')	{
            cout << endl << "1. 最少资金乡村通路方案";
            cout << endl << "2. 建造乡村医院的乡村";
            cout << endl << "3. 问路系统";
            cout << endl << "4. 退出";
		    cout << endl << "选择功能(0~4):";
		    cin >> c;
		    switch (c) 		{
			    case '1':
					MiniSpanTreeKruskal(g);
				    break;
			    case '2':
				    break;
			    case '3':
			        cout << endl << "输入查询乡村A和B";
			        cin>> e1 >> e2;
			        v1 = g.GetOrder(e1);
			        v2 = g.GetOrder(e2);
					g.DisplayShortAB(v1, v2);
			        break;
       	      }
         }
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}
/*
ID: wuzhigu1
LANG: C++
TASK: barn1
*/
#include <fstream>
#include <iostream>
#include <list>
#include <cstring>
using namespace std;
ifstream fin("barn1.in");
ofstream fout("barn1.out");
int main()
{
	int m,s,c;
	fin>>m>>s>>c;
	int ans;
		list<int> lis,lit;
	int x,y,i,dif;
	//将数据输入到lit中保存并排序*********************************
	for(i=0;i!=c;i++)
	{
		fin>>x;
		lit.push_back(x);
	}
	lit.sort();
	list<int>::iterator iter,itend=lit.begin();itend++;
	//for(iter=lit.begin();iter!=lit.end();++iter)
		//cout<<*iter<<" ";
	//求出lit中每组数据的前后之差，将差值保存进lis并排序************************
	for(iter=lit.begin();itend!=lit.end();iter++,itend++)
	{
		dif=*itend-*iter;
		lis.push_back(dif);
	}
	//for(iter=lis.begin();iter!=lis.end();++iter)
	//	cout<<*iter<<" ";
	//如果m>=c,也就是每个门可以用一块木板，则长度为c
	if(m>=c)
		{
			ans=c;
		}
	else
	{
	lis.sort();
	list<int>::iterator it=lis.end();
	int sum=0;
	//求出最大的m-1个差值的和
	for(i=0;i<m-1;i++)
	{
		sum+=*(--it);
	}
	iter=lit.begin();itend=lit.end();itend--;
	//cout<<*iter<<" "<<*itend<<" ";
	//计算结果
	ans=*itend-*iter-sum+m;
	}
	fout<<ans<<endl;
	return 0;
}
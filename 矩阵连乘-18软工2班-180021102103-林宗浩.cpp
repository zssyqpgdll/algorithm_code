#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
const int N=105;

//bool Judge(int ra, int ca, int rb, int cb)
//{
//	if(ca!=rb)
//		return false;
//	return true;
//}

//计算最优值,最少数乘次数 
void MatrixChain(int p[], int n, int m[][N], int s[][N])
{
	for(int i=1;i<=n;i++)
	{
		m[i][i]=0;//对角线 
	}
	for(int r=2;r<=n;r++)
	{//r为段长 
		for(int i=1;i<=n-r+1;i++)
		{//i为段起点 
			int j=i+r-1;//j为段终点
			m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];//先初始化,断点先断在i和i+1处 
			s[i][j]=i;//记录断点位置 
			for(int k=i+1;k<j;k++)
			{//k为断点位置 
				int t=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(t<m[i][j])
				{
					m[i][j]=t;//遇到数乘次数更少的 
					s[i][j]=k;//更新断点 
				}
			}
		}
	}
}

//计算最优解
void Traceback(int i, int j, int s[][N])
{
	if(i==j)
		return;
	Traceback(i,s[i][j],s);
	Traceback(s[i][j]+1,j,s);
	cout << "Multiply A " << i << "," << s[i][j];
	cout << " and A " << (s[i][j]+1) << ", " << j << endl;
}

//另一种打印方法
void Traceback1(int i, int j, int s[][N])
{
	if(i==j)
		cout << "A" << i;
	else
	{
		cout << "(";
		Traceback1(i,s[i][j],s);
		Traceback1(s[i][j]+1,j,s);
		cout << ")";
	}
}

int main()
{
	int p[N*10];//每个矩阵的列数,p[0]为第一个矩阵的行数 
	int m[N][N];//存储最优结果
	int s[N][N];//存储当前结构的最优断点
	cout << "请输入矩阵的个数：";
	int n;
	int flag=1;
	while(cin >> n)
	{
		memset(p,0,sizeof(p));
		memset(m,0,sizeof(m));
		memset(s,0,sizeof(s));
//		cout << "请按顺序依次输入每个矩阵的行数和最后一个矩阵的列数：" << endl; 
//		for(int i=0;i<=n;i++)
//		{
//			cin >> p[i];
//			if(i!=1)
//			{
//				if(!Judge(p[i-2],p[i-1],p[i-1],p[i]))
//				{
//					cout << "矩阵不可乘" << endl;
//					flag=0;
//					break;
//				}
//			}
//		}
		for(int i=1;i<=n;i++)
		{
			cout << "请输入第" << i << "个矩阵的行和列：";
			if(i==1)
			{
				cin >> p[0] >> p[1];//第一个矩阵的行和列 
			}
			else
			{
				int a,b;
				cin >> a >> b;
				if(a!=p[i-1])
				{
					cout << "矩阵不可乘" << endl;
					flag=0;
					break;
				}
				p[i]=b;
			}
		}
		if(flag)
		{
			MatrixChain(p,n,m,s);
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=n;j++)
				{
					if(i>j)
						cout << "\t";
					else
						cout << m[i][j] << "\t";
				}
				cout << endl;
			}
			cout << endl;
			cout << "矩阵相乘的最少数乘次数为：" << m[1][n] << endl;
			cout << endl << "最佳数乘方式顺序：" << endl;
			Traceback(1,n,s);
			cout << "或者：" << endl;
			Traceback1(1,n,s);
			cout << endl << endl;
		}
		cout << "请输入矩阵的个数：";
	}
	return 0;
}

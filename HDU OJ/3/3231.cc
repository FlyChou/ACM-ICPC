/*
差分约束退化成拓扑排序

由于此题中，成环必为负环，所以差分约束由最短路退化成拓扑排序求解

*/

//Result:2012-10-18 19:01:27	Accepted	3231	46MS	2036K	2508 B	C++	Wizmann
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define NODE 2048
#define EDGE 204800
#define INF 1<<28

struct node
{
	int dest,cost,next;
	node(){}
	node(int idest,int icost,int inext)
	{
		dest=idest;cost=icost;next=inext;
	}
};

struct command
{
	int type;
	int h1,h2;
	command(){}
	command(char itype,int ih1,int ih2)
	{
		if(itype=='I') type=-1;
		else if(itype=='X') type=0;
		else if(itype=='Y') type=1;
		else if(itype=='Z') type=2;
		h1=ih1;h2=ih2;
	}
};


int head[NODE];
node g[EDGE];
command cmd[EDGE];
int n,m,ind;

int dis[3][NODE];
int in[NODE];

inline void init()
{
	memset(head,-1,sizeof(head));
	ind=0;
	memset(in,0,sizeof(in));
}

inline void addEdge(int a,int b,int cost)
{
	g[ind]=node(b,cost,head[a]);
	head[a]=ind++;
	in[b]++;
}

void makeG(int x)
{
	//a*2 is big,a*2-1 is small;
	for(int i=1;i<=2*n;i++)
	{
		addEdge(0,i,1);
	}
	for(int i=1;i<=n;i++)
	{
		addEdge(i*2,i*2-1,-1);
	}
	for(int i=0;i<m;i++)
	{
		int a=cmd[i].h1;
		int b=cmd[i].h2;
		if(cmd[i].type==-1)
		{
			addEdge(a*2,b*2-1,-1);
			addEdge(b*2,a*2-1,-1);
		}
		else if(cmd[i].type==x)
		{
			addEdge(b*2-1,a*2,-1);
		}
	}
}

bool topsort(int *dd)
{
	queue<int> q;
	q.push(0);
	dd[0]=0;
	int ok=0;
	while(!q.empty())
	{
		int now=q.front();
		q.pop();

		for(int i=head[now];i!=-1;i=g[i].next)
		{
			int next=g[i].dest;
			int cost=g[i].cost;

			if(--in[next]==0)
			{
				dd[next]=dd[now]+cost;
				q.push(next);
				ok++;
			}
		}
	}
	if(ok!=n*2) return false;
	else return true;
}



bool slove(int x)
{
	init();
	makeG(x);
	if(topsort(dis[x])) return true;
	else return false;
}

void showAns()
{
	for(int i=1;i<=n;i++)
	{
		bool flag=true;
		for(int j=0;j<3;j++)
		{
			if(!flag) printf(" ");
			else flag=false;
			printf("%d",dis[j][i*2-1]);
		}
		for(int j=0;j<3;j++)
		{
			if(!flag) printf(" ");
			printf("%d",dis[j][i*2]);
		}
		puts("");
	}
}


int main()
{
	freopen("input.txt","r",stdin);
	char inc[10];
	int a,b,cas=1;
	while(input(n>>m) && n+m)
	{
		printf("Case %d: ",cas++);
		for(int i=0;i<m;i++)
		{
			scanf("%s%d%d",inc,&a,&b);
			cmd[i]=command(*inc,a,b);
		}
		if(slove(0)&&slove(1)&&slove(2))
		{
			puts("POSSIBLE");
			showAns();
		}
		else
		{
			puts("IMPOSSIBLE");
		}
		puts("");
	}
	return 0;
}


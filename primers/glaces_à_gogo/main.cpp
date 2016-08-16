#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

struct p
{
	int x,y,d;
	p (){};
	p(int _x,int _y,int _d = 0) : x(_x),y(_y),d(_d) {}
	set<pair<ld,int> > s;
};

const int MAX = 300,V = 30;
int n,m,v;
p t[MAX][MAX];
ld dist[MAX][MAX];
int hard[5][2] = {{94,0},{191,2},{299,1},{299,153},{266,299}};

int main()
{
	ios_base::sync_with_stdio(0);
	
	cin >> m >> n >> v;
	
	for(int i=0;i<n;i++)
		for(int j=i;j<m;j++)
			dist[i][j] = sqrt(i*i + j*j);
	for(int i=0;i<n;i++)
		for(int j=0;j<i;j++)
			dist[i][j] = dist[j][i];
	
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			int d;
			cin >> d;
			t[i][j] = p(i,j,d);
		}
	
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			cout << 50*(i+1) << ',' << 50*(j+1) << endl;
	
	for(int i=0;i<5;i++)
		cout << hard[i][1] << ',' << hard[i][0] << endl;
		
	
	
	return 0;
}
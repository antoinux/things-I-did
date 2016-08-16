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
	ld best = -1;
};

const int MAX = 300,V = 30;
const char sep = ',';
int n,m,v;
p t[MAX][MAX];
ld dist[MAX][MAX];

int main(int argc,char **argv)
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
			t[j][i] = p(i,j,d);
		}
	
	fstream file(argv[1],fstream::in);
	
	for(int i=0;i<v;i++)
	{
		int x,y;
		stringstream ss,conv;
		string s,nb;
		file >> s;
		ss << s;
		getline(ss,nb,c);
		conv << nb;
		conv >> x;
		ss >> y;
		
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				ld di = dist[abs(x-i)][abs(y-j)];
				t[i][j].best = t[i][j].best < 0 ? di : min(di,t[i][j].best);
			}
	}
	
	ld ans = 0.,tot = 0.;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			tot += t[i][j].d;
	
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
// 			cout << t[i][j].best << " " << tot << endl;
			ans += t[i][j].d*t[i][j].best;
		}
		
	cout << ans/tot << endl;
		
	return 0;
}
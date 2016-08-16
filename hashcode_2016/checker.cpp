#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

/*long long _();
 i *nt main() { _(); return 0; }
 #define main _
 #define int long long*/

using namespace std;

const int MAX = 1e4+2;

struct ware
{
	int a,b;
	int p[MAX];
};

struct order
{
	int a,b;
	int p[MAX];
};

struct drone
{
	int disp,a,b;
};

inline int dist(int x1,int y1,int x2,int y2)
{
	return ceil((ld)sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))) + 1;
}

int X,Y,D,T_MAX,L,P,t[MAX],W,C,Q;
ware w[MAX];
order o[MAX];
drone dr[MAX];

inline bool isempty(const order& o1)
{
	for(int i=0;i<P;++i)
		if(o1.p[i] > 0)
			return 0;
	return 1;
}

int main(int argc,char **argv)
{
// 	ios_base::sync_with_stdio(0);
	
	cin >> X >> Y >> D >> T_MAX >> L >> P;
	for(int i=0;i<P;++i)
		cin >> t[i];
	cin >> W;
	for(int i=0;i<W;i++)
	{
		cin >> w[i].a >> w[i].b;
		for(int j=0;j<P;++j)
			cin >> w[i].p[j];
	}
	cin >> C;
	for(int i=0;i<C;++i)
	{
		cin >> o[i].a >> o[i].b;
		int l;
		cin >> l;
		for(int j=0;j<l;++j)
		{
			int m;
			cin >> m;
			++o[i].p[m];
		}
// 		cout << l << endl;
	}
	
	fstream fis(argv[1],ios_base::in);
	fis >> Q;
	
	vector<int> ends;
	for(int i=0;i<Q;i++)
	{
		int a,b,d,e;
		char c;
		fis >> a >> c >> b >> d >> e;
// 		a : drone
// 		b : warehouse/command
// 		d : product
// 		e : number
		if(c == 'L')
		{
			dr[a].disp += dist(dr[a].a,dr[a].b,w[b].a,w[b].b);
			dr[a].a = w[b].a;
			dr[a].b = w[b].b;
		}
		else
		{
			dr[a].disp += dist(dr[a].a,dr[a].b,o[b].a,o[b].b);
			dr[a].a = o[b].a;
			dr[a].b = o[b].b;
			o[b].p[d] -= e;
			if(isempty(o[b]))
				ends.pb(dr[a].disp - 1);
		}
	}
	fis.close();
// 	cout << ends.size() << endl;
	int T = ends.back();
	ll score = 0;
	for(int x : ends)
		score += ceil((100.*(((ld)T-x)/T)));
	cout << score << endl;
	
	return 0;
}
#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

const int MAX = 1e4+2,dead = 1e6-1000;

struct ware
{
	int a,b;
	int p[MAX],p2[MAX];
	vector<int> close;
	int ptr;
	int tot_w;
};

struct order
{
	int a,b,id;
	int p[MAX];
	bool touched = 0;
	vector<int> close;
	int ptr;
	int tot_w;
};

struct drone
{
	int disp,last;
};

struct rep
{
	int a;
	char ty;
	int b,c,d;
	rep (int _a,char _ty,int _b,int _c,int _d):a(_a),ty(_ty),b(_b),c(_c),d(_d){}
};

inline int dist(const ware& o1,const ware& o2)
{
	return ceil((ld)(sqrt((o1.a - o2.a)*(o1.a - o2.a) + (o1.b - o2.b)*(o1.b - o2.b)))) + 1;
}

inline int dist(const order& o1,const ware& o2)
{
	return ceil((ld)(sqrt((o1.a - o2.a)*(o1.a - o2.a) + (o1.b - o2.b)*(o1.b - o2.b)))) + 1;
}

inline int dist(const order& o1,const order& o2)
{
	return ceil((ld)(sqrt((o1.a - o2.a)*(o1.a - o2.a) + (o1.b - o2.b)*(o1.b - o2.b)))) + 1;
}

inline int dists(const order& o1,const ware& o2)
{
	return (o1.a - o2.a)*(o1.a - o2.a) + (o1.b - o2.b)*(o1.b - o2.b);
}

int X,Y,D,T_MAX,L,P,t[MAX],W,C,comp,compO;
ware w[MAX];
order o[MAX];
drone d[30];

int compTo;

bool sort1(int x,int y)
{
// 	return dists(o[compTo],w[x]) < dists(o[compTo],w[y]);
	return w[x].tot_w < w[y].tot_w;
}

bool sort2(int x,int y)
{
// 	return dists(o[x],w[compTo]) < dists(o[y],w[compTo]);
	return o[x].tot_w < o[y].tot_w;
}

inline int dist(int a1)
{
	return ceil((ld)(sqrt(o[a1].a*o[a1].a + o[a1].b*o[a1].b))) + 1;
}

inline int dist(const order& o1)
{
	return ceil((ld)(sqrt(o1.a*o1.a + o1.b*o1.b))) + 1;
}

inline bool isempty(const ware& w1)
{
	for(int i=0;i<P;++i)
		if(w1.p[i] > 0)
			return 0;
	return 1;
}

inline bool f(const ware& w1,const order& o1)
{
	bool repo = 0;
	for(int i=0;i<P;++i)
		if(o1.p[i] > 0)
			repo = 1;
	if(!repo)
		return 0;
	if(o1.touched)
		return 1;
	for(int i=0;i<P;++i)
		if(w1.p2[i] < o1.p[i])
			return 0;
		
	return 1;
}

inline bool isempty(const order& o1)
{
	for(int i=0;i<P;++i)
		if(o1.p[i] > 0)
			return 0;
	return 1;
}

inline bool g(const order& o1,const ware& w1)
{
	for(int i=0;i<P;++i)
		if(o1.p[i] > 0 && w1.p[i] > 0)
			return 0;
	return 1;
}

bool operator<(const order& o1,const order& o2)
{
	return dist(o1) < dist(o2);
}

bool isAlive(ware& w1)
{
	while(w1.ptr < C && (g(o[w1.close[w1.ptr]],w1) || isempty(o[w1.close[w1.ptr]])))
		++w1.ptr;
	return (w1.ptr < C);
}

int main()
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
		{
			cin >> w[i].p[j];
			w[i].p2[j] = w[i].p[j];
			w[i].tot_w += w[i].p[j];
		}
	}
	cin >> C;
	for(int i=0;i<C;++i)
	{
		cin >> o[i].a >> o[i].b;
		o[i].close = vector<int>(W);
		iota(o[i].close.begin(),o[i].close.end(),0);
		sort(o[i].close.begin(),o[i].close.end(),sort1);
		int l;
		cin >> l;
		o[i].id = i;
		for(int j=0;j<l;++j)
		{
			int m;
			cin >> m;
			++o[i].p[m];
		}
		for(int j=0;j<P;++j)
			o[i].tot_w += o[i].p[j];
	}
	for(int i=0;i<W;++i)
	{
		w[i].close = vector<int>(C);
		iota(w[i].close.begin(),w[i].close.end(),0);
		compTo = i;
		sort(w[i].close.begin(),w[i].close.end(),sort2);
	}
	
// 	for(int i=0;i<10;++i)
// 		cout << dist(o[0],w[o[0].close[i]]) << endl;
// 	for(int i=0;i<10;++i)
// 		cout << dist(o[w[0].close[i]],w[0]) << endl;
	
	vector<rep> ans;
	vector<pair<int,int> > ends; // Pour calculer le score et voir comment il se répartit dans le temps.
	
	// Il faut rajouter un while dans cette for car il peut
	// y avoir des orders pour lesquels on ne peut rien faire.
	// genre while(on ne peut pas) ++ptr; done
	
	for(int i=0;i<D;++i)
	{
		while(isempty(o[w[0].close[w[0].ptr]]) || g(o[w[0].close[w[0].ptr]],w[0]))
			++w[0].ptr;
		int charge = 0;
		int x = w[0].close[w[0].ptr];
		int len = dist(o[x],w[0]);
		int si = 0;
		d[i].last = x;
		for(int j=0;j<P && charge <= L;++j)
		{
			int di = min((L-charge)/t[j],min(o[x].p[j],w[0].p[j]));
			if(di)
			{
				++si;
				charge += di*t[j];
				o[x].p[j] -= di;
				w[0].p[j] -= di;
				ans.pb(rep(i,'L',0,j,di));
				if(isempty(o[x]))
					ends.pb({len + 2*si,x});
			}
		}
		d[i].disp = len + 2*si;
		int tmp = ans.size();
		for(int j=tmp-si;j<tmp;++j)
			ans.pb(rep(i,'D',x,ans[j].c,ans[j].d));
	}
	
	bool stop = 0;
	for(int T=0;T<dead && !stop;++T)
	{
		for(int i=0;i<D;++i)
		{
			if(d[i].disp > T)
				continue;
			
			int la = d[i].last;
			
			while(o[la].ptr < W && !isAlive(w[o[la].close[o[la].ptr]]))
				++o[la].ptr;
			if(o[la].ptr == W)
			{
				stop = 1;
				break;
			}
			int y = o[la].close[o[la].ptr];
			
			int charge = 0;
			int x = w[y].close[w[y].ptr];
			int len = dist(o[x],w[y]);
			int si = 0;
			d[i].last = x;
			for(int j=0;j<P && charge <= L;++j)
			{
				int di = min((L-charge)/t[j],min(o[x].p[j],w[y].p[j]));
				if(di)
				{
					++si;
					charge += di*t[j];
					o[x].p[j] -= di;
					w[y].p[j] -= di;
					ans.pb(rep(i,'L',y,j,di));
					if(isempty(o[x]))
						ends.pb({T + len + 2*si + dist(o[la],w[x]),x});
				}
			}
			d[i].disp = T + len + 2*si + dist(o[la],w[x]);
			int tmp = ans.size();
			for(int j=tmp-si;j<tmp;++j)
				ans.pb(rep(i,'D',x,ans[j].c,ans[j].d));
		}
	}
	
	cout << ans.size() << endl;
	for(rep r : ans)
		cout << r.a << " " << r.ty << " " << r.b << " " << r.c << " " << r.d << endl;
// 	cout << ans.size() << endl;
// 	for(auto p : ends)
// 		cout << p.first << " ";
// 	cout << endl;
	
// 	int T = ends.back().first;
// 	ll score = 0;
// 	for(auto p : ends)
// 		score += ceil(100.*(T-p.first)/T);
// 	cout << ends.size() << endl;
// 	cout << "Score : " << score << endl;
	
	return 0;
}
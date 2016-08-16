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
	ld di[30];
	ld best = 1e18;
	ld old_best;
	ld old_x;
};

const int MAX = 300,V = 30,T = 200,a = 1;
const char sep = ',';
const ld INF = 1e18;
int n,m,v;
pair<int,int> cl[V];
p t[MAX][MAX];
ld dist[MAX][MAX];

int main(int argc,char **argv)
{
	// 	ios_base::sync_with_stdio(0);
	srand(time(0));
	cout << setprecision(7);
	
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
			
			for(int k=0;k<v;k++)
			{
				ld xd,yd;
				file >> xd >> yd;
				int x = round(xd),y = round(yd);
				// 				cout << x << ',' << y << endl;
				cl[k] = {x,y};
				
				for(int i=0;i<n;i++)
					for(int j=0;j<m;j++)
					{
						ld di = dist[abs(x-i)][abs(y-j)];
						t[i][j].di[k] = di;
						t[i][j].best = min(t[i][j].best,di);
					}
			}
			
			ld ans = 0.,tot = 0.;
			ld ld_ans = INF;
			vector<pair<int,int> > v_ans(30);
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
				{
					tot += t[i][j].d;
					ans += t[i][j].best*t[i][j].d;
				}
				
				cout << ans << " " << tot << endl;
			cout << ans/tot << endl;
			
			bool keep = 1;
			
			
			
			while(keep)
			{
				// 				cout << k << endl;
				// 				int x = rand()%v;
				keep = 0;
				for(int z=0;z<v;z++)
				{
					ld best = INF;
					int x = rand()%v;
					// 				cout << best << endl;
					int xbest = 0,ybest = 0;
					for(int i=-a;i<a+1;i++)
						for(int j=-a;j<a+1;j++)
						{
							int xb = cl[x].first+i,yb = cl[x].second+j;
							if((i != 0 || j != 0) && xb>=0 && xb<n && yb>=0 && yb<m)
							{
								ld n_best = 0.;
								for(int p=0;p<n;p++)
									for(int l=0;l<m;l++)
									{
										// 									t[p][l].old_best = t[p][l].best;
										// 									t[p][l].old_x = t[p][l].di[x];
										ld t_best = t[p][l].best;
										ld dis = dist[abs(p-xb)][abs(l-yb)];
										if(t[p][l].best == t[p][l].di[x] && dis > t[p][l].di[x])
										{
											// 										t[p][l].di[x] = dis;
											// 										t[p][l].best = INF;
											t_best = dis;
											for(int u=0;u<V;u++)
												if(u != x)
													t_best = min(t_best,t[p][l].di[u]);
										}
										else
											t_best = min(t_best,dis);
										// 									t[p][l].di[x] = dis;
										n_best += t_best*t[p][l].d;
									}
									if(n_best < best)
									{
										best = n_best;
										xbest = xb;
										ybest = yb;
									}
									// 							for(int p=0;p<n;p++)
									// 								for(int l=0;l<m;l++)
									// 								{
									// 									t[p][l].di[x] = t[p][l].old_x;
									// 									t[p][l].best = t[p][l].old_best;
									// 								}
							}
						}
						if(best < ans || (best/tot - ans/tot < 0.0002 && rand()%100 < 20))
						{
							keep = 1;
							ans = best;
							cl[x].first = xbest;
							cl[x].second = ybest;
							for(int i=0;i<n;i++)
								for(int j=0;j<m;j++)
								{
									ld dis = dist[abs(i-xbest)][abs(j-ybest)];
									if(t[i][j].best == t[i][j].di[x] && dis > t[i][j].di[x])
									{
										t[i][j].di[x] = dis;
										t[i][j].best = INF;
										for(int p=0;p<V;p++)
											t[i][j].best = min(t[i][j].best,t[i][j].di[p]);
									}
									else
									{
										t[i][j].di[x] = dis;
										t[i][j].best = min(t[i][j].best,dis);
									}	
								}
						}
						if(ans < ld_ans)
						{
							ld_ans = ans;
							for(int i=0;i<v;i++)
								v_ans[i] = cl[i];
							fstream lolz("sub2.txt",ios_base::out);
							for(int i=0;i<v;i++)
								lolz << v_ans[i].first << ',' << v_ans[i].second << endl;
							lolz.close();
							cout << ld_ans/tot << endl;
						}
				}
			}
			// 				for(int i=0;i<n;i++)
			// 					for(int j=0;j<m;j++)
			// 					{
			// 						// 			cout << t[i][j].best << " " << tot << endl;
			// 						ans += t[i][j].d*t[i][j].best;
			// 					}
			// 					
			// 					cout << ans/tot << endl;
			for(int i=0;i<v;i++)
				cout << v_ans[i].first << ' ' << v_ans[i].second << endl;
			cout << ld_ans << " " << tot << endl;
			cout << ld_ans/tot << endl;
			return 0;
}
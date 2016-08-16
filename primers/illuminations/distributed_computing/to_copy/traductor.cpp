#include<bits/stdc++.h>

#define ll long long
#define pb push_back
#define mk make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

const int MAX1 = 1e3,MAX2 = 3*1e2,MAX3 = 5;
ll s[MAX1][MAX3],sc[MAX1][MAX3];
bool d[MAX1],dt[MAX1],dt2[MAX1],v_ans[MAX2];
int n,m,p;

inline void pdt2(void)
{
	for(int i=0;i<n;i++)
	{
		dt2[i] = 0;
		for(int j=0;j<m;j++)
			dt2[i] ^= dt[j] && (s[i][j/64] & (1ll << j%64)) != 0;
	}
}

int main(int argc,char **argv)
{
	ios_base::sync_with_stdio(0);
	fstream fis(argv[1],fstream::in);
	
	int v;
	while(fis >> v)
		dt[v] = 1;
	fis.close();
	fis.open("/cal/homes/aturquetil/hashcode/in",ios_base::in);
	fis >> n >> m;
	p = m/64 + 1;
	for(int i=0;i<m;i++)
	{
		int z;
		fis >> z;
		for(int j=0;j<z;j++)
		{
			int y;
			fis >> y;
			s[y][i/64] ^= (1ll << (i%64));
		}
	}
	fis.close();
	pdt2();
	int ans = 0;
	for(int i=0;i<n;i++)
		ans += dt2[i];
	
	cout << ans << endl;
	
	return 0;
}

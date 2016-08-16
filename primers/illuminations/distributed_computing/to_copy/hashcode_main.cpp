#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;


int getBest(void)
{
	fstream fis("best.txt",ios_base::in);
	int best;
	fis >> best;
	fis.close();
	return best;
}

const int MAX1 = 1e3,MAX2 = 3*1e2,MAX3 = 5,NB_ITER=8e6;
ll s[MAX1][MAX3],sc[MAX1][MAX3];
bool d[MAX1],dt[MAX1],dt2[MAX1],v_ans[MAX2];
int n,m,p,m_max;

void printAns(int best)
{
	fstream fos("sub.txt",ios_base::out),fos2("best.txt",ios_base::out);
	for(int i=0;i<m;i++)
		if(dt[i])
			fos << i << endl;
		fos.close();
	fos2 << best;
	fos2.close();
}

inline void swapR(int i,int j)
{
	for(int k=0;k<p;k++)
	{
		ll tmp = sc[i][k];
		sc[i][k] = sc[j][k];
		sc[j][k] = tmp;
	}
	
	bool tmp = dt[i];
	dt[i] = dt[j];
	dt[j] = tmp;
}

inline void addR(int i,int j)
{
	for(int k=0;k<p;k++)
		sc[j][k] ^= sc[i][k];
	
	dt[j] ^= dt[i];
}

inline void pdt2(void)
{
	for(int i=0;i<n;i++)
	{
		dt2[i] = 0;
		for(int j=0;j<m;j++)
			dt2[i] ^= dt[j] && (s[i][j/64] & (1ll << j%64)) != 0;
	}
}

bool invert(void)
{
	// On élimine sous la diagonale.
	for(int i=0;i<m;i++)
	{
		int pivot = i,iq = i/64,ir = i%64;
		while(pivot < m && (sc[pivot][iq] & (1ll << ir)) == 0)
			++pivot;
		
		if(pivot == m)
			return 0;
		
		if(pivot != i)
			swapR(i,pivot);
		for(int j=i+1;j<m;j++)
			if((sc[j][iq] & (1ll << ir)) != 0)
				addR(i,j); // add row i to row j(using XOR).
	}
	
	// On élimine au-dessus de la diagonale.
	for(int i=m-1;i>=0;i--)
		for(int j=0;j<i;j++)
			if((sc[j][i/64] & (1ll << i%64)) != 0)
				addR(i,j);
			return 1;
}

int main()
{
	// 	ios_base::sync_with_stdio(0);
	random_device rd;
	cin >> n >> m;
	p = m/64 + 1;
	for(int i=0;i<m;i++)
	{
		int z;
		cin >> z;
		for(int j=0;j<z;j++)
		{
			int y;
			cin >> y;
			s[y][i/64] ^= (1ll << (i%64));
		}
	}
	// 	f(0,m);
	ll sumscore = 0;
	// 	srand(unsigned(time(0)));
	// 	int compteur = 0;
	for(int iter=0;iter<NB_ITER;++iter)
	{
		vector<bool> v(n,0);
		for(int i=0;i<m;i++)
			v[i] = 1;
		mt19937 g(rd());
		shuffle(v.begin(),v.end(),g);
		
		for(int i=0;i<n;i++)
			dt[i] = v[i];
		
		
		int cur = 0;
		for(int i=0;i<n;i++)
			for(int j=0;j<p;j++)
				sc[i][j] = s[i][j];
			
			for(int i=0;i<n;i++)
				if(v[i])
				{
					swapR(i,cur);
					++cur;
				}
				
				// 		for(int i=0;i<n;i++)
				// 			dt[i] = 1;
				if(!invert())
					continue;
				pdt2();
				// 				++compteur;
				
				int ans = 0;
				for(int i=0;i<n;i++)
					ans += dt2[i];
				sumscore += ans;
				// 				if(ans >= 720)
				// 					cout << "Score atteint : " << ans << " average : " << sumscore/compteur << " " << compteur << endl;
				
				if(ans > m_max)
				{
					m_max = ans;
					for(int i=0;i<m;i++)
						v_ans[i] = dt[i];
					if(ans > 729)
					{
						fstream fis("/cal/homes/aturquetil/hashcode/results/best_score",ios_base::in);
						int all_best;
						fis >> all_best;
						fis.close();
						if(all_best < ans)
						{
							fstream fos("/cal/homes/aturquetil/hashcode/results/best_score",ios_base::out);
							fos << ans;
							fos.close();
							fos.open("/cal/homes/aturquetil/hashcode/results/best");
							for(int i=0;i<m;i++)
								if(v_ans[i])
									cout << i << endl;
							fos.close();
						}
					}
				}
	}
	
	for(int i=0;i<m;i++)
		if(v_ans[i])
			cout << i << endl;
		
		return 0;
}

#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

const int MAX = 125,T = 1000000;
int t[MAX][MAX],g[MAX][MAX],ans[MAX],ians[MAX],n;

int getBest()
{
	fstream fis("best.txt",ios_base::in);
	int best = 0;
	fis >> best;
	fis.close();
	return best;
}

void printAns(int best)
{
	fstream fos("best.txt",ios_base::out);
	fos << best << endl;
	fos.close();
	fos.open("sub1.txt",ios_base::out);
	for(int i=0;i<n;i++)
		fos << ans[i] << endl;
	fos.close();
}

void loadFile(string path)
{
	fstream fis(path,ios_base::in);
	for(int i=0;i<n;i++)
		fis >> ans[i];
	fis.close();
}

void updateFiles(int best)
{
	if(best < getBest())
		printAns(best);
}

int getScore()
{
	int score = 0;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			score += t[i][j]*g[ans[i]][ans[j]];
	return score;
}

int main(int argc,char **argv)
{
// 	ios_base::sync_with_stdio(0);
	srand(time(0));
	
	cin >> n;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin >> t[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin >> g[i][j];
	
// 	for(int i=0;i<n;i++)
// 		ans[i] = i;
// 	random_shuffle(ans,ans+n);
// 	for(int i=0;i<n;i++)
// 		ians[ans[i]] = i;
	loadFile("sub1.txt");
	
	int best = getScore(),loc_best = best,last_change = 0;
	
	for(int i=0;i<T;i++)
	{
		vector<int> perm(MAX);
		for(int i=0;i<MAX;i++)
			perm[i] = i;
		random_shuffle(perm.begin(),perm.end());
		int x = rand()%n,y = rand()%n;
		while(y == x) y = rand()%n;
// 		swap(ans[x],ans[y]);
		int tmp = ans[perm[0]];
		for(int i=0;i<9;i++)
			ans[perm[i]] = ans[perm[i+1]];
		ans[perm[9]] = tmp;
		int score = getScore();
		cout << score << endl;
		if(score < loc_best || (score - loc_best < 5000 && rand()%20000 < 1))
		{
			cout << score << endl;
			if(score >= loc_best)
				cout << last_change << " ";
			last_change = 0;
			loc_best = score;
			if(score < best)
			{
				best = score;
				updateFiles(best);
				cout << best << endl;
			}
			cout << loc_best << endl;
		}
		else
		{
			++last_change;
// 			swap(ans[x],ans[y]);
			tmp = ans[perm[9]];
			for(int i=8;i>=0;i--)
				ans[perm[i+1]] = ans[perm[i]];
			ans[perm[0]] = tmp;
		}
	}
	cout << best << " " << last_change << endl;
	return 0;
}
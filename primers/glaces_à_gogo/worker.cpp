#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define PI 3.14159265359
#define endl '\n'

using namespace std;

ld getBest()
{
	fstream fis("best.txt",ios_base::in);
	ld x = 1e18;
	fis.precision(5);
	fis >> x;
	fis.close();
	return x;
}

ld getResult()
{
	fstream fis("part_result.txt",ios_base::in);
	ld x;
	fis.precision(5);
	fis >> x;
	fis.close();
	return x;
}

bool stop()
{
	fstream fis("stop.txt",ios_base::in);
	int x;
	fis >> x;
	fis.close();
	return x;
}

int main()
{
// 	ios_base::sync_with_stdio(0);
	
// 	cout << "yo" << endl;
// 	cout << system("python cluster.py >out.txt") << endl;
// 	cout << "yo" << endl;
	
	while(1)
	{
		if(stop())
			break;
		system("python cluster.py >out.txt && ./eval2 out.txt <in.txt >part_result.txt");
		ld x = getResult();
		cout << x << endl;
		if(x < getBest())
		{
			system("cp part_result.txt best.txt && cp out.txt result.txt");
		}
	}
	
	return 0;
}
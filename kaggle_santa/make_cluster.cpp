#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mk make_pair
#define PI 3.14159265359
#define PI2 atan2(1,0)
#define endl '\n'

using namespace std;

struct gift
{
	int id;
	ld lat,lon,w;
	gift (){}
	gift(int _id,ld _lat,ld _lon,ld _w):id(_id),lat(_lat),lon(_lon),w(_w) {}
};

bool operator<(gift const& g1,gift const& g2)
{
	if(abs(g1.lat) != abs(g2.lat))
		return abs(g1.lon) < abs(g2.lon);
	return g1.id < g2.id;
}

// Génère des clusters avec la stratégie naïve de trier les cadeaux par longitude.

ld eps = 1e-6;
const int MAX = 1e5;
gift t[MAX+1];

int main(int argc,char **argv)
{
	ios_base::sync_with_stdio(0);
	
// 	cout << "hello !" << endl;
	string s;
	stringstream ss;
	cin >> s;
	
	while(cin >> s)
	{
// 		cout << s << endl;
		int id;
		ld lat,lon,w;
		stringstream convert;
		ss << s;
		string number;
		
		for(int i=0;i<4;i++)
		{
			getline(ss,number,',');
			convert << number;
			if(i == 0)
				convert >> id;
			else if(i == 1)
				convert >> lat;
			else if(i == 2)
				convert >> lon;
			else
				convert >> w;
			convert.clear();
		}
		
		t[id] = gift(id,lat,lon,w);
		ss.clear();
	}
	
	cout << "GiftId,Latitude,Longitude,Weight,ClusterId" << endl;
	sort(t+1,t+MAX+1);
// 	for(gift x : t)
// 		cout << x.id << endl;
	int i=1,cur_cluster = 0;
	while(i < MAX+1)
	{
		vector<gift> v;
		ld cur_w = 10.;
// 		cout << i << " " << MAX+1 << " " << cur_w + t[i].w << " " < endl;
		while(i < MAX+1 && cur_w + t[i].w < 1e3 - eps)
		{
// 			cout << cur_w << " " << t[i].w << endl;
			cur_w += t[i].w;
			cout << t[i].id << ',' << t[i].lat << ',' << t[i].lon << ',' << t[i].w << ',' << cur_cluster << endl;
			++i;
		}
		++cur_cluster;
	}
	
	return 0;
}
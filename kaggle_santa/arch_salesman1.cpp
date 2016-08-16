#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mk make_pair
#define PI 2*atan2(1,0)
#define PI2 atan2(1,0)
#define endl '\n'

using namespace std;

struct gift
{
	int id;
	ld lat,lon,w;
	bool done;
	gift (){}
	gift(int _id,ld _lat,ld _lon,ld _w):id(_id),lat(_lat),lon(_lon),w(_w),done(0) {}
};

bool operator<(gift const& g1,gift const& g2)
{
	if(g1.w != g2.w)
		return g1.w > g2.w;
	else if(g1.lat != g2.lat)
		return g1.lat < g2.lat;
	else if(g1.lon != g2.lon)
		return g1.lon < g2.lon;
	else
		return g1.id < g2.id;
}

double np[2] = {90.,0.};
const int MAX = 2000,sleigh = 10,R = 6371;

vector<gift> g[MAX];

ld dist(ld lat1,ld lon1,ld lat2,ld lon2)
{
	ld dlat = lat2 - lat1,dlon = lon2 - lon1,sin1 = sin(dlat/2),sin2 = sin(dlon/2);
	ld a = sin1*sin1 + cos(lat1) * cos(lat2) * sin2*sin2;
	return 2 * atan2(sqrt(a), sqrt(1-a));
}

int main(int argc,char **argv)
{
	ios_base::sync_with_stdio(0);
	
	string s;
	cin >> s;
	int max_cluster = 0;
	
	while(cin >> s)
	{
		unsigned int cur = 0;
		int id,cluster;
		ld lat,lon,w;
		stringstream ss;
// 		cout << s << endl;
		for(int i=0;i<5;i++)
		{
			string t;
			while(cur < s.size() && s[cur] != ',')
			{
				t += s[cur];
				++cur;
			}
			++cur;
// 			cout << i << " " << t << endl;
			ss << t;
			if(i == 0)
				ss >> id;
			else if(i == 1)
				ss >> lat;
			else if(i == 2)
				ss >> lon;
			else if(i == 3)
				ss >> w;
			else
				ss >> cluster;
			ss.clear();
		}
// 		cout << cluster << " " << max_cluster << endl;
		max_cluster = max(max_cluster,cluster+1);
		g[cluster].pb(gift(id,lat,lon,w));
	}
	
	gift santa(0,PI/2,0.,0.);
	ld score = 0.;
	cout << "GiftId,TripId" << endl;
// 	for(int i=0;i<3;i++)
// 		cout << i << " " << g[i].size() << endl;
	
	for(int i=0;i<max_cluster;i++)
	{
		vector<gift>& v = g[i];
		ld total_w = 10;
// 		cout << i << " " << v.size() << endl;
		for(gift x : v)
			total_w += x.w;
		sort(v.begin(),v.end());
// 		for(gift x : v)
// 			cout << i << " " << x.id << " " << x.w << " gift" << endl;
		score += total_w*dist(PI2,0.,v[0].lat,v[0].lon);
		cerr << total_w*dist(PI2,0.,v[0].lat,v[0].lon) << endl;
		cout << v[0].id << "," << i << endl;
		total_w -= v[0].w;
		for(unsigned int j=1;j<v.size();j++)
		{
			score += total_w*dist(v[j-1].lat,v[j-1].lon,v[j].lat,v[j].lon);
			total_w -= v[j].w;
			cout << v[j].id << "," << i << endl;
		}
		score += total_w*dist(PI2,0.,v.back().lat,v.back().lon);
// 		cout << total_w << endl;
	}
	
	cerr << score << endl;
	return 0;
}
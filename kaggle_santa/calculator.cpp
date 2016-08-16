#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mk make_pair
#define PI 3.14159265359
#define PI2 atan2(1,0) // It's PI/2.
#define endl '\n'

using namespace std;

struct gift
{
	int id;
	ld lat,lon,w;
	gift (){}
	gift(int _id,ld _lat,ld _lon,ld _w):id(_id),lat(_lat),lon(_lon),w(_w) {}
};

ld dist(ld lat1,ld lon1,ld lat2,ld lon2)
{
	lat1 *= PI/180;lon1 *= PI/180;lat2 *= PI/180;lon2 *= PI/180;
	ld dlat = lat2 - lat1,dlon = lon2 - lon1,sin1 = sin(dlat/2),sin2 = sin(dlon/2);
	ld a = sin1*sin1 + cos(lat1) * cos(lat2) * sin2*sin2;
	return 2 * atan2(sqrt(a),sqrt(1-a));
}

ld dist(gift g1,gift g2)
{
	return dist(g1.lat,g1.lon,g2.lat,g2.lon);
}

// Pour checker qu'une solution est correcte et en donner sa valeur.
// argv[1] est le fichier d'input complet d'origine (gift.csv).
// argv[2] est le fichier de la solution proposée (prête à être uploadée sur kaggle.com).

const gift santa(-1,90.,0.,0.);
const int R = 6371,MAX = 1e5,N = 1e4;
gift t[MAX+1];
vector<pair<int,int> > trips[N];
int v[MAX+1];

int main(int argc,char **argv)
{
	ios_base::sync_with_stdio(0);
	
	fstream f(argv[1],fstream::in);
	string s;
	f >> s;
	stringstream ss;
	
	while(f >> s)
	{
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
	
	fstream ans(argv[2],fstream::in);
	ans >> s;
	
	while(ans >> s)
	{
		int id,trip;
		stringstream convert;
		ss << s;
		string number;
		
		for(int i=0;i<2;i++)
		{
			getline(ss,number,',');
			convert << number;
			if(i == 0)
				convert >> id;
			else
				convert >> trip;
			convert.clear();
		}
		
		trips[trip].pb({id,trip});
		ss.clear();
	}
	
	ld score = 0;
	int cmp_too_much = 0;
	
	for(auto g : trips)
		if(!g.empty())
		{
			ld tot_w = 10.;
			for(auto p : g)
				tot_w += t[p.first].w;
			cmp_too_much += (tot_w > 1e3);
			score += tot_w*dist(santa,t[g[0].first]);
			tot_w -= t[g[0].first].w;
			++v[g[0].first];
			for(unsigned int i=0;i<g.size()-1;i++)
			{
				++v[g[i+1].first];
				score += tot_w*dist(t[g[i].first],t[g[i+1].first]);
				tot_w -= t[g[i+1].first].w;
			}
			score += tot_w*dist(t[g.back().first],santa);
		}
	
	int cmp_trop_vu = 0,cmp_pas_vu = 0;
	for(int i=1;i<MAX+1;i++)
		if(!v[i])
			++cmp_pas_vu;
		else if(v[i] > 1)
			++cmp_trop_vu;
		
	if(cmp_too_much)
		cout << "Certains voyages sont trop chargés ! " << cmp_too_much << " au total." << endl;
	if(cmp_pas_vu)
		cout << "Certains cadeaux n'ont pas été livrés ! " << cmp_pas_vu << " au total." << endl;
	if(cmp_trop_vu)
		cout << "Certains cadeaux ont été livré plus d'une fois... " << cmp_trop_vu << " au total." << endl;
	
	cout << "Score : " << R*score << endl;
	
	return 0;
}
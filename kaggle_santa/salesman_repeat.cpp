#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mk make_pair
#define PI 3.14159265359
#define PI2 atan2(1,0)
#define endl '\n'

using namespace std;

// Ne s'applique que sur un cluster à la fois, et il faut arrêter le programme manuellement,
// il boucle à l'infini (l'intérêt est de pouvoir mettre un timer sur sa gueule et de le faire
// tourner plusieurs heures).

// argv[1] est le fichier sur lequel on envoie la réponse sous la forme d'un csv.
// argv[2] est le fichier sur lequel on envoir le meilleur score.

struct gift
{
	int id,loc_id;
	ld lat,lon,w;
	gift (){}
	gift(int _id,ld _lat,ld _lon,ld _w):id(_id),loc_id(0),lat(_lat),lon(_lon),w(_w) {}
};

double np[2] = {90.,0.};
const ld INF = 1e9,eps = 1e-6;
const int sleigh = 10,R = 6371,N = 200;
const gift santa(-1,90.,0.,0.);
int cluster;

// Deux changements locaux : FLIP (correspond à swap sur les arrêtes lent car il faut inverser le segment)
//  							  ou SWAP (rapide car seuleument un swap à faire mais étrangement finalement plus lent que FLIP).
// Deux méthodes de test : SCORE (calculer le score total, lent)
// 							ou DIST (on peut calculer localement le changement donc rapide).
const string method = "SCORE",change = "FLIP";

ld mat_dist[N+1][N+1];
vector<gift> v;

ld dist(ld lat1,ld lon1,ld lat2,ld lon2)
{
	lat1 *= PI/180;lon1 *= PI/180;lat2 *= PI/180;lon2 *= PI/180;
	ld dlat = lat2 - lat1,dlon = lon2 - lon1,sin1 = sin(dlat/2),sin2 = sin(dlon/2);
	ld a = sin1*sin1 + cos(lat1) * cos(lat2) * sin2*sin2;
	return 2 * atan2(sqrt(a), sqrt(1-a));
}

ld dist(gift g1,gift g2)
{
	return dist(g1.lat,g1.lon,g2.lat,g2.lon);
}

int get_santa_id(vector<gift>& v)
{
	for(unsigned int i=0;i<v.size();i++)
		if(v[i].id == -1)
			return i;
		return 0;
}

ld get_score(vector<gift>& v,ld tot_w)
{
	int santa_id = get_santa_id(v),n = v.size();
	
	ld score = 0;
	for(int i=santa_id;i!=(santa_id-1+n)%n;i=(i+1)%n)
	{
		int j = (i+1)%n;
		score += tot_w*mat_dist[v[i].loc_id][v[j].loc_id];
		tot_w -= v[j].w;
	}
	score += tot_w*mat_dist[v[(santa_id-1+n)%n].loc_id][v[santa_id].loc_id];
	
	return score;
}

ld get_score(vector<gift>& v)
{
	ld tot_w = 10;
	for(gift x : v)
		tot_w += x.w;
	return get_score(v,tot_w);
}

ld get_score_swap(vector<gift> v,int x,int y,ld tot_w)
{
	swap(v[x],v[y]);
	return get_score(v,tot_w);
}

ld get_dist(vector<gift>& v)
{
	int n = v.size();
	ld ans = 0;
	for(int i=0;i<n;i++)
	{
		int j = (i+1)%n;
		ans += mat_dist[v[i].loc_id][v[j].loc_id];
	}
	return ans;
}

void flip(vector<gift>& v,int x,int y)
{
	int n = v.size();
	int cur_x = (x+1)%n,cur_y = y;
	while(cur_x != cur_y && (cur_y+1)%n != cur_x)
	{
		swap(v[cur_x],v[cur_y]);
		cur_x = (cur_x+1)%n;
		cur_y = (cur_y-1+n)%n;
	}
}

ld diff_dist_flip(vector<gift>& v,int x,int y)
{
	int n = v.size();
	int ax = (x+1)%n,ay = (y+1)%n;
	ld before_dist = mat_dist[v[x].loc_id][v[ax].loc_id] + mat_dist[v[y].loc_id][v[ay].loc_id];
	ld after_dist = mat_dist[v[x].loc_id][v[y].loc_id] + mat_dist[v[ax].loc_id][v[ay].loc_id];
	return after_dist - before_dist;
}

ld diff_score_flip(vector<gift> v,int x,int y,ld tot_w)
{
	ld bscore = get_score(v,tot_w);
	flip(v,x,y);
	ld ascore = get_score(v,tot_w);
	return ascore - bscore;
}

ld diff_dist_swap(vector<gift>& v,int x,int y)
{
	int n = v.size();
	int bx = (x-1+n)%n,ax = (x+1)%n,by = (y-1+n)%n,ay = (y+1)%n;
	ld before_dist = mat_dist[v[bx].loc_id][v[x].loc_id] + mat_dist[v[x].loc_id][v[ax].loc_id] + mat_dist[v[by].loc_id][v[y].loc_id] + mat_dist[v[y].loc_id][v[ay].loc_id];
	swap(v[x],v[y]);
	ld after_dist = mat_dist[v[bx].loc_id][v[x].loc_id] + mat_dist[v[x].loc_id][v[ax].loc_id] + mat_dist[v[by].loc_id][v[y].loc_id] + mat_dist[v[y].loc_id][v[ay].loc_id];
	swap(v[x],v[y]);
	return after_dist - before_dist;
}

ld diff_score_swap(vector<gift> v,int x,int y,ld tot_w)
{
	ld bscore = get_score(v,tot_w);
	swap(v[x],v[y]);
	ld ascore = get_score(v,tot_w);
	return ascore - bscore;
}

void disp(vector<gift>& v,ld score,string best_path,string best_score)
{
	fstream f1(best_path,fstream::out),f2(best_score,fstream::out);
	f1 << "GiftId,TripId" << endl;
	for(gift x : v)
		f1 << x.id << ',' << cluster << endl;
	f1.close();
	
	f2 << score << endl;
}

void disp(vector<gift>& v,int trip)
{
	int n = v.size(),santa_id = get_santa_id(v);
	
	for(int i=(santa_id+1)%n;i!=santa_id;i=(i+1)%n)
		cout << v[i].id << ',' << trip << endl;
}

ld density(ld delta_e,ld T)
{
	if(delta_e < 0)
		return 2.;
	if(T == 0.)
		return -1;
	return pow(2.71,-delta_e/T);
}

ld density(ld e1,ld e2,ld T)
{
	return density(e2-e1,T);
}

int main(int argc,char **argv)
{
	ios_base::sync_with_stdio(0);
	bool b_method = (method[0] == 'S');
	bool b_change = (change[0] == 'F');
	string s;
	cin >> s;
	
	while(cin >> s)
	{
		int id;
		ld lat,lon,w;
		stringstream ss,convert;
		ss << s;
		string number;
		
		for(int i=0;i<5;i++)
		{
			getline(ss,number,',');
			convert << number;
			if(i == 0)
				convert >> id;
			else if(i == 1)
				convert >> lat;
			else if(i == 2)
				convert >> lon;
			else if(i == 3)
				convert >> w;
			else
				convert >> cluster;
			convert.clear();
		}
		
		v.pb(gift(id,lat,lon,w));
		ss.clear();
	}
	
	v.pb(santa);
	ld total_w = 10.;
	ld best_score = INF;
	vector<gift> best_path;
	for(unsigned int i=0;i<v.size();i++)
	{
		v[i].loc_id = i;
		total_w += v[i].w;
	}
	int n = v.size();
	
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			mat_dist[i][j] = dist(v[i],v[j]);
		
		random_shuffle(v.begin(),v.end());
	
	srand(time(NULL));
	int cmp = 0;
	while(1)
	{
		++cmp;
		int x = rand()%n,y = rand()%n;
		while((b_change && (y == x || y == (x-1+n)%n || y == (x+1)%n)) || (!b_change && y == x))
			y = rand()%n;
		ld diff;
		if(b_change)
			diff = b_method ? diff_score_flip(v,x,y,total_w) : diff_dist_flip(v,x,y);
		else
			diff = b_method ? diff_score_swap(v,x,y,total_w) : diff_dist_swap(v,x,y);
		if(diff < 0)
		{
			if(b_change)
				flip(v,x,y);
			else
				swap(v[x],v[y]);
			cmp = 0;
		}
		else if(cmp > 300)
		{
			bool b = 1;
			for(x=0;x<n && b;x++)
				for(y=(x+2)%n;y!=(x-1+n)%n && b;y=(y+1)%n)
				{
					if(b_change)
						diff = b_method ? diff_score_flip(v,x,y,total_w) : diff_dist_flip(v,x,y);
					else
						diff = b_method ? diff_score_swap(v,x,y,total_w) : diff_dist_swap(v,x,y);
					if(diff < 0)
					{
						if(b_change)
							flip(v,x,y);
						else
							swap(v[x],v[y]);
						b = 0;
					}
				}
				if(b)
				{
					ld cur_score = get_score(v,total_w);
					if(cur_score < best_score)
					{
						best_score = cur_score;
						best_path = v;
						disp(best_path,best_score,argv[1],argv[2]);
					}
					x = rand()%n,y = rand()%n;
					while((b_change && (y == x || y == (x-1+n)%n || y == (x+1)%n)) || (!b_change && y == x))
						y = rand()%n;
					
					if(b_change)
						flip(v,x,y);
					else
						swap(v[x],v[y]);
					cmp = 0;
				}
		}
	}
	
	return 0;
}
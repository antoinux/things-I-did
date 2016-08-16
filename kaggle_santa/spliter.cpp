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

const int MAX = 2000;
vector<gift> g[MAX];

// Passer le nombre de fichiers à engendrer en argument(argv[1]).
// Rediriger le fichier à spliter sur l'entrée standart.
// Penser à d'abord créer un dossier "split" dans le dossier courant, les fichiers y seront créés.

int main(int argc,char **argv)
{
	ios_base::sync_with_stdio(0);
	string s;
	cin >> s;
	
	stringstream ss;
	ss << argv[1];
	int nb_files;
	ss >> nb_files;
	ss.clear();
	
	int max_cluster = 0;
	
	while(cin >> s)
	{
		int id,cluster;
		ld lat,lon,w;
		stringstream convert;
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
		
		max_cluster = max(max_cluster,cluster+1);
		g[cluster].pb(gift(id,lat,lon,w));
		ss.clear();
	}
	
	int per_file = max_cluster/nb_files + 1;
	
	for(int i=0;i<nb_files;i++)
	{
		int start = i*per_file;
		int end = min((i+1)*per_file,max_cluster);
		string num_start,num_end;
		stringstream ss;
		
		ss << start;
		ss >> num_start;
		ss.clear();
		
		ss << end;
		ss >> num_end;
		ss.clear();
		
		cout << "split/"+num_start+"-"+num_end+".csv" << endl;
		fstream f("split/"+num_start+"-"+num_end+".csv",fstream::out);
		f << "GiftId,Latitude,Longitude,Weight,ClusterId" << endl;
		for(int i=start;i<end;i++)
			for(gift x : g[i])
				f << x.id << ',' << x.lat << ',' << x.lon << ',' << x.w << ',' << i << endl;
		f.close();
	}
	
	return 0;
}
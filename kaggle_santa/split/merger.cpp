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
	int cluster;
	gift (){}
	gift(int _id,ld _lat,ld _lon,ld _w,int _cluster):id(_id),lat(_lat),lon(_lon),w(_w),cluster(_cluster) {}
};

vector<gift> v;

// Passer le nombre de fichiers à merger en premier argument (argv[1]).
// Passer ensuite les n noms de fichier (argv[2..n+2]).
// Rediriger la sortie standart pour déterminer où envoyer le fichier mergé.

int main(int argc,char **argv)
{
	ios_base::sync_with_stdio(0);
	string s;
	
	stringstream ss;
	ss << argv[1];
	int nb_files;
	ss >> nb_files;
	ss.clear();
	
	for(int i=2;i<nb_files-2;i++)
	{
		fstream f(argv[2],fstream::in);
		f >> s;
		while(f >> s)
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
			v.pb(gift(id,lat,lon,w,cluster));
			ss.clear();
		}
		f.close();
	}
	
	cout << "GiftId,Latitude,Longitude,Weight,ClusterId" << endl;
	for(gift x : v)
		cout << x.id << ',' << x.lat << ',' << x.lon << ',' << x.w << ',' << x.cluster << endl;
	
	return 0;
}
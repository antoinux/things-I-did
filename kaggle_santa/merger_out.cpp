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
	int id,trip;
	gift (){}
	gift(int _id,int _trip):id(_id),trip(_trip) {}
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
	
	for(int i=2;i<nb_files+2;i++)
	{
		fstream f(argv[i],fstream::in);
		f >> s;
		while(f >> s)
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
			v.pb(gift(id,trip));
			ss.clear();
		}
		f.close();
	}
	
	cout << "GiftId,TripId" << endl;
	for(gift x : v)
		cout << x.id << ',' << x.trip<< endl;
	
	return 0;
}
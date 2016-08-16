#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define pb push_back
#define mk make_pair
#define PI 3.14159265359
#define PI2 atan2(1,0)
#define endl '\n'

using namespace std;

const int N = 70;

int main(int argc,char **argv)
{
	ios_base::sync_with_stdio(0);
	srand(time(NULL));
	
	cout << "GiftId,Latitude,Longitude,Weight,ClusterId" << endl;
	for(int i=0;i<N;i++)
	{
		ld range = 0.29*PI/38.;
		ll rd_lat = rand(),rd_lon = rand();
		ll q_lat = rd_lat/range,q_lon = rd_lon/(2*range);
		ld lat = (ld)rd_lat - range*(ld)q_lat;
		ld lon = (ld)rd_lon - (2*range)*(ld)q_lon;
// 		cout << lat << " " << lon << endl;
		
		int rd = rand()%3;
		ld w = 1.;
		if(rd)
		{
			ll rd_w = rand()%10000;
			w = (49./10000.)*rd_w + 2;
		}
		cout << i << ',' << lat << ',' << lon << ',' << w << ",0" << endl;
	}
	
	return 0;
}
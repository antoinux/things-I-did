#include<bits/stdc++.h>

using namespace std;

typedef mt19937 rng_type;
uniform_int_distribution<rng_type::result_type> udist(0, 7);

rng_type rng;

chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
auto duration = now.time_since_epoch();

typedef chrono::duration<int, ratio_multiply<chrono::hours::period, ratio<8>
>::type> Days;

int main()
{	
	auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration);
	srand(nanoseconds.count());
	cout << rand() << endl;
	return 0;
}
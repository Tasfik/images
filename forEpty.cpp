#include <bits/stdc++.h>
using namespace std;

#define IN freopen("Routemap_BikolpoBus_Tasfik.txt", "r", stdin);
#define OUT freopen("epty.txt", "w", stdout);
#define ll long long int
#define PII pair <int, int>
#define MX 100001

vector <string> v;

int main() 
{
	IN
	OUT

	for (int num = 1 ; ; num++) {
		string s;
		v.clear();
		int cnt = 0;

		while (cin >> s && s != "$") {
			if (s == "end")
				return 0;
			v.push_back(s);
		}

		cout << "LON,LAT" << endl << "Start" << num << ",Start" << num << num << endl;
		for (int i = 0; i < v.size(); i+=2)
			cout << v[i] << "," << v[i+1] << endl;;
		cout << "End" << num << ",End" << num << num<< endl;
	}
}
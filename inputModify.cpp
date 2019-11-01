#include <bits/stdc++.h>
using namespace std;

#define IN freopen("Routemap_UttaraBus_tasfik.txt", "r", stdin);
#define OUT freopen("Roadmap_UttaraBus.txt", "w", stdout);
#define ll long long int
#define PII pair <int, int>
#define MX 100001

vector <string> v;

int main() 
{
	IN
	OUT

	for ( ; ; ) {
		string s;
		v.clear();
		int cnt = 0;

		while (cin >> s && s != "$") {
			if (s == "end")
				return 0;
			v.push_back(s);
		}

		cout << v.size() << " ";
		for (int i = 0; i < v.size(); i++)
			cout << v[i] << " ";
		cout << endl;
	}
}
#include <bits/stdc++.h>
using namespace std;

#define IN freopen("Routemap_BikolpoBus.txt", "r", stdin);
#define OUT freopen("in.txt", "w", stdout);
#define ll long long int
#define PII pair <int, int>
#define MX 100001

vector <string> v;

int main() 
{
	IN
	OUT

	for (int i = 0; i < 17; i++) {
		string s;
		v.clear();
		int cnt = 0;

		while (cin >> s && s != "$")
			v.push_back(s);

		cout << v.size() << " ";
		for (int i = 0; i < v.size(); i++)
			cout << v[i] << " ";
		cout << endl;
	}
}
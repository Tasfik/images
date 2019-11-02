#include <bits/stdc++.h>
using namespace std;

#define IN freopen("in.txt", "r", stdin);
#define OUT freopen("out.txt", "w", stdout);
#define ll long long int
#define PII pair <int, int>
#define MX 100001

int main()
{
	int a = 12;
	int b = a/5, c = a%6;

	stringstream ss;
	string s1, s2;

	ss << b;
	ss >> s1;

	ss << c;
	ss >> s2;

	cout << "s1.length() = " << s1.length() << endl;		//ThisIsForDebuggingPurposes
	cout << "s2.length() = " << s2.length() << endl;		//ThisIsForDebuggingPurposes
	
	string res = s1 + " , " + s2;

	cout << res << endl;
}

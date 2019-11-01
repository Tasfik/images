#include <bits/stdc++.h>
using namespace std;

#define IN freopen("in.txt", "r", stdin);
#define OUT freopen("out.txt", "w", stdout);
#define ll long long int
#define PII pair <int, int>
#define MX 100001

int main() 
{
	double a = 90.1234356, b = 90.1234355;

	cout << "(a == b) = " << (a == b) << endl;		//ThisIsForDebuggingPurposes

	map <double, int> m;

	m[a] = 1;

	if (m.find(b) == m.end()) {
		cout << "not found" << endl;
	}
	else {
		cout << "found" << endl;
	}

	double d = __LONG_LONG_MAX__;
	cout << d << endl;
}
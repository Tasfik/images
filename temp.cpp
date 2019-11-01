#include <bits/stdc++.h>
using namespace std;

#define IN freopen("in.txt", "r", stdin);
#define OUT freopen("out.txt", "w", stdout);
#define ll long long int
#define PII pair <int, int>
#define MX 100001

int main() 
{
	freopen("in1.txt", "r", stdin);
	int n1, sum1 = 0;
	scanf("%d", &n1);
	for (int i = 0; i < n1; i++) {
		int x;
		scanf("%d", &x);
		sum1 += x;
	}

	cout << "sum1 = " << sum1 << endl;		//ThisIsForDebuggingPurposes

	freopen("in2.txt", "r", stdin);
	int n2, sum2 = 0;
	scanf("%d", &n2);
	for (int i = 0; i < n2; i++) {
		int x;
		scanf("%d", &x);
		sum2 += x;
	}

	cout << "sum2 = " << sum2 << endl;		//ThisIsForDebuggingPurposes
}


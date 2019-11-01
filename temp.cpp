#include <bits/stdc++.h>
using namespace std;

#define IN freopen("in.txt", "r", stdin);
#define OUT freopen("graph.txt", "w", stdout);
#define ll long long int
#define PII pair <ll, ll>
#define PDD pair <double, double>
#define DhakaRoadMX 49869
#define BikolpoBusRoadMX 17
#define UttaraBusRoadMX 19
#define MetroRailMX 14
#define NodeMX 1500
#define EdgeMX NodeMX * NodeMX
#define PI 2.0 * acos(0.0)
#define modify 1000000

const double typeCost[] = {1.0, 1.0, 1.0};

// car = 0
// metro = 1
// bikolpo bus = 2
//uttara bus = 2


vector <ll> g[NodeMX], type[NodeMX];
vector <double> cost[NodeMX];
map <PII, ll> road;
PII RoadList[NodeMX];
ll path[NodeMX], pathType[NodeMX];
double dist[NodeMX];

void Dijkstra(ll source) {
	map<double, ll> m;
	
	for (ll i = 1; i < NodeMX; i++)
	{
		dist[i] = __LONG_LONG_MAX__;
		path[i] = -1;
		pathType[i] = -1;
	}

	m[0.0] = source;
	dist[source] = 0.0;

	// cout << "cleared" << endl;
	while (!m.empty())
	{
		// cout << "m.size() = " << m.size() << endl;		//ThisIsForDebuggingPurposes
		map<double, ll>::iterator it = m.begin();

		ll u = it->second;
		m.erase(it);

		for (ll i = 0; i < g[u].size(); i++)
		{
			ll v = g[u][i];
			ll pathTP = type[u][i];
			double NewCost = dist[u] + cost[u][i];

			if (NewCost < dist[v])
			{
				path[v] = u;
				pathType[v] = pathTP;
				dist[v] = NewCost;
				m[NewCost] = v;
			}
		}
	}
}

void PrintPath(ll v) {
	if (v == -1)
		return;
	PrintPath(path[v]);
	cout << v << " ";
}

double deg2rad(double deg) {
	return deg * (PI / 180.0);
}

double square(double n) {
	return n * n;
}

ll error = 0;

PDD revertPII(PII a) {
	double x = (double)a.first / modify;
	double y = (double)a.second / modify;
	return PDD(x, y);
}

double distance(PII A, PII B) {
	PDD a = revertPII(A);
	PDD b = revertPII(B);

	double R = 6371.0;
	double dLat = deg2rad(a.first - b.first);
	double dLon = deg2rad(a.second - b.second);

	double c = square(sin(dLat / 2.0)) + cos(deg2rad(a.first)) * cos(deg2rad(b.first)) * square(sin(dLon / 2.0));
	double d = 2.0 * atan( sqrt(c) / sqrt(1.0 - c));

	if (A == B) {
		cout << "error : " << A.first << " " << B.first << " " << A.second << " " << B.second <<
		error++;
	}
	else if (d == 0.0) {
		cout << "zero : " << road[a] << " " << road[b] << endl; 
		cout << "c = " << c << endl;		//ThisIsForDebuggingPurposes
		cout << "d = " << d << endl;		//ThisIsForDebuggingPurposes
		cout << "dLat = " << dLat << endl;		//ThisIsForDebuggingPurposes
		cout << "dLon = " << dLon << endl;		//ThisIsForDebuggingPurposes
		cout << endl << endl << endl;		//ThisIsForDebuggingPurposes
	}
	

	return R * d;
}

ll err[3];
int work = 0;

ll str (string s) {
	ll res = 0;

	for (int i = 0; i <s.length(); i++) {
		
		if (s[i] == '.')
			continue;

		ll digit = s[i] - '0';

		res += digit;
		res *= 10;
	}

	for (int i = s.length(); i <= 12; i++) 
		res *= 10;

	return res;
}

ll scan (ll limit, ll vehicle, ll RoadNo) {
	for (ll i = 0; i < limit; i++) {
		int n;
		scanf("%d", &n);

		ll prevRoadNo = 0, curRoadNo = 0;
		ll preva, prevb;
		for (ll j = 0; j < n; j++){
			// double A, B;
			// scanf("%lf%lf", &A, &B);

			string A, B;
			cin >> A >> B;

			ll a = str(A);
			ll b = str(B);

			// cout << "a = " << a << endl;		//ThisIsForDebuggingPurposes
			// cout << "A = " << A << endl;		//ThisIsForDebuggingPurposes
			// cout << "str(A) = " << str(A) << endl;		//ThisIsForDebuggingPurposes
			// work += (a%10 > 0) + (b%10 > 0);

			// if (a%10 > 0)
			// 	cout << "work = " << A << " " << a << " " << endl;

			if (j && a == preva && b == prevb) {
				// cout << "vehicle = " << vehicle << endl;		//ThisIsForDebuggingPurposes
				// // cout << " = " <<  << endl;		//ThisIsForDebuggingPurposes
				err[vehicle]++;
			}

			if (road.find( PII(a, b) ) != road.end()) {
				curRoadNo = road[ PII(a, b) ];
			}
			else {
				road[ PII(a, b) ] = ++RoadNo;
				curRoadNo = RoadNo;
				RoadList[RoadNo] = PII(a, b);
			}

			if (j) {
				g[curRoadNo].push_back(prevRoadNo);
				g[prevRoadNo].push_back(curRoadNo);

				type[curRoadNo].push_back(vehicle);
				type[prevRoadNo].push_back(vehicle);

				double dist = distance(RoadList[curRoadNo], RoadList[prevRoadNo]) * typeCost[vehicle];
				// ll distLL = (ll)(dist * modify);
				cost[curRoadNo].push_back(dist);
				cost[prevRoadNo].push_back(dist);
			}
			prevRoadNo = curRoadNo;

			preva = a;	prevb = b;
		}
	}
	return RoadNo;
}

int main() {
	OUT

	ll RoadNo = 0;

	freopen("Roadmap_Dhaka.txt", "r", stdin);
	RoadNo = scan(DhakaRoadMX, 0, RoadNo);
	
	ll r1 = RoadNo;
	cout << "read dhaka road" << endl;
	cout << "RoadNo = " << RoadNo << endl;		//ThisIsForDebuggingPurposes

	freopen("Roadmap_DhakaMetroRail.txt", "r", stdin);
	RoadNo = scan(MetroRailMX, 1, RoadNo);

	ll r2 = RoadNo;
	cout << "read Metro Rail" << endl;
	cout << "RoadNo = " << r2 - r1 << endl;		//ThisIsForDebuggingPurposes

	freopen("Roadmap_BikolpoBus.txt", "r", stdin);
	RoadNo = scan(BikolpoBusRoadMX, 2, RoadNo);

	ll r3 = RoadNo;
	cout << "read Uttara Bus" << endl;
	cout << "RoadNo = " << r3 - r2 << endl;		//ThisIsForDebuggingPurposes

	freopen("Roadmap_UttaraBus.txt", "r", stdin);
	RoadNo = scan(UttaraBusRoadMX, 2, RoadNo);

	ll r4 = RoadNo;
	cout << "read Bikolpo Bus" << endl;
	cout << "RoadNo = " << r4 - r3 << endl;		//ThisIsForDebuggingPurposes

	cout << "error = " << error << endl;		//ThisIsForDebuggingPurposes

	cout << "err : " << err[0] << " " << err[1] << " " << err[2] << endl;

	cout << "work = " << work << endl;		//ThisIsForDebuggingPurposes

	
	for (ll i = 0 ; i < 50; i++) {
		for (ll j = 0; j < g[i].size(); j++) {
			cout << i << " " << j << " " << cost[i][j] << endl;
		}
	}

	// freopen("in.txt", "r", stdin);
	// double a, b, c, d;
	// scanf("%lf%lf %lf%lf", &a, &b, &c, &d);

	ll source = 2, destination = 19;

	cout << "before" << endl;
	Dijkstra(2);

	cout << "dist[19] = " << dist[19] << endl;		//ThisIsForDebuggingPurposes

	for (ll i = 0; i < 20; i++) {
		cout << "i = " << i << " dis = " << dist[i] << endl;
	}
	cout << endl << endl << endl;		//ThisIsForDebuggingPurposes

	for (ll i = 0; i < 20; i++) {
		cout << "i = " << i << " path = " << path[i] << endl;
	}
	
	cout << endl << endl << endl;		//ThisIsForDebuggingPurposes

	cout << "path : ";
	PrintPath(destination);
}
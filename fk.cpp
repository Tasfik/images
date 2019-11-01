#include <bits/stdc++.h>
using namespace std;

#define IN freopen("in.txt", "r", stdin);
#define OUT freopen("out.txt", "w", stdout);
#define ll long long int
#define PII pair <double, double>
#define DhakaRoadMX 50000
#define BikolpoBusRoadMX 20
#define UttaraBusRoadMX 20
#define MetroRailMX 15
#define NodeMX 5 * DhakaRoadMX
#define EdgeMX NodeMX * NodeMX
#define PI 2.0 * acos(0.0)
#define NodeMX 5 * 50000
#define PI 2.0 * acos(0.0)
#define EPS 1e-10

const double typeCost[] = {20.0, 5.0, 7.0};

// car = 0
// metro = 1
// bikolpo bus = 2
//uttara bus = 2


vector <int> g[NodeMX], type[NodeMX];
vector <ll>  cost[NodeMX];
map <PII, int> road;
PII RoadList[NodeMX];
int path[NodeMX], pathType[NodeMX];
ll dist[NodeMX];
map <ll, int> m;

void Dijkstra(ll source) {
	for (ll i = 1; i < NodeMX; i++)
	{
		dist[i] = LONG_LONG_MAX;
		path[i] = -1;
		pathType[i] = -1;
	}

	m[0] = source;
	dist[source] = 0;

	while (!m.empty()) {
		map<ll, int>::iterator it = m.begin();

		ll u = it->second;
		m.erase(it);

		for (ll i = 0; i < g[u].size(); i++)
		{
			ll v = g[u][i];
			ll pathTP = type[u][i];
			ll NewCost = dist[u] + cost[u][i];

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
	cout << RoadList[v].first << "," << RoadList[v].second<< "," << pathType[v] << endl;
}

double deg2rad(double deg) {
	return deg * (PI / 180.0);
}

double square(double n) {
	return n * n;
}

double distance(PII a, PII b) {
	double R = 6371.0;
	double dLat = deg2rad(a.first - b.first);
	double dLon = deg2rad(a.second - b.second);

	double c = square(sin(dLat / 2.0)) + cos(deg2rad(a.first)) * cos(deg2rad(b.first)) * square(sin(dLon / 2.0));
	double d = 2.0 * atan( sqrt(c) / sqrt(1.0 - c));
	return R * d;
}

ll check = 0;

ll scan (ll limit, ll vehicle, ll RoadNo) {
	for (ll i = 0; i < limit; i++) {
		ll n;
		scanf("%d", &n);

		ll prevRoadNo, curRoadNo;
		for (ll j = 0; j < n; j++){
			double a, b;
			scanf("%lf%lf", &a, &b);


			check += (floor(a/100) > 0) + (floor(b/100) > 0);

			if (road.find( PII(a, b) ) != road.end()) {
				curRoadNo = road[ PII(a, b) ];
			}
			else {
				road[ PII(a, b) ] = ++RoadNo;
				curRoadNo = RoadNo;
				RoadList[RoadNo] == PII(a, b);
			}

			if (j) {
				g[curRoadNo].push_back(prevRoadNo);
				g[prevRoadNo].push_back(curRoadNo);

				type[curRoadNo].push_back(vehicle);
				type[prevRoadNo].push_back(vehicle);

				double dist = distance(RoadList[curRoadNo], RoadList[prevRoadNo]) * typeCost[vehicle];
				cost[curRoadNo].push_back(dist);
				cost[prevRoadNo].push_back(dist);
			}
			prevRoadNo = RoadNo;
		}
	}
	return RoadNo;
}

int main() {
	// OUT

	ll RoadNo = 0;

	freopen("Roadmap_Dhaka.txt", "r", stdin);
	RoadNo = scan(DhakaRoadMX, 0, RoadNo);
	
	cout << "read dhaka road" << endl;
	cout << "RoadNo = " << RoadNo << endl;		//ThisIsForDebuggingPurposes

	freopen("Roadmap_DhakaMetroRail.txt", "r", stdin);
	RoadNo = scan(MetroRailMX, 1, RoadNo);

	cout << "read Metro Rail" << endl;
	cout << "RoadNo = " << RoadNo << endl;		//ThisIsForDebuggingPurposes

	freopen("Roadmap_BikolpoBus.txt", "r", stdin);
	RoadNo = scan(BikolpoBusRoadMX, 2, RoadNo);

	cout << "read Uttara Bus" << endl;
	cout << "RoadNo = " << RoadNo << endl;		//ThisIsForDebuggingPurposes

	freopen("Roadmap_UttaraBus.txt", "r", stdin);
	RoadNo = scan(UttaraBusRoadMX, 2, RoadNo);

	cout << "read Bikolpo Bus" << endl;
	cout << "RoadNo = " << RoadNo << endl;		//ThisIsForDebuggingPurposes

	cout << "check = " << check << endl;		//ThisIsForDebuggingPurposes

	freopen("graph.txt", "w", stdout);
	for (ll i = 0 ; i < 20; i++) {
		for (ll j = 0; j < g[i].size(); j++) {
			cout << i << " " << j << " " << cost[i][j] << endl;
		}
	}
	// freopen("in.txt", "r", stdin);
	// double a, b, c, d;
	// scanf("%lf%lf %lf%lf", &a, &b, &c, &d);

	// ll source = road[ PII(a, b) ], destination = road[ PII(c, d) ];

	// Dijkstra(source);

	// PrintPath(destination);
}
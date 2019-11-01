#include <bits/stdc++.h>
using namespace std;

#define IN freopen("in.txt", "r", stdin);
#define OUT freopen("out.txt", "w", stdout);
#define ll long long int
#define PII pair <double, double>
#define DhakaRoadMX 50000
#define NodeMX 5 * DhakaRoadMX
#define PI 2.0 * acos(0.0)
#define EPS 1e-10

const double typeCost[] = {20.0, 5.0};

// car = 0
// metro = 1


vector <int> g[NodeMX], type[NodeMX];
vector <ll>  cost[NodeMX];
map <PII, int> road;
PII RoadList[NodeMX];
int path[NodeMX], pathType[NodeMX];
ll dist[NodeMX];
map <ll, int> m;

void Dijkstra(int source) {
	for (int i = 1; i < NodeMX; i++)
	{
		dist[i] = LONG_LONG_MAX;
		path[i] = -1;
		pathType[i] = -1;
	}

	m[0] = source;
	dist[source] = 0;

	while (!m.empty()) {
		map<ll, int>::iterator it = m.begin();

		int u = it->second;
		m.erase(it);

		for (int i = 0; i < g[u].size(); i++)
		{
			int v = g[u][i];
			int pathTP = type[u][i];
			ll NewCost = (ll)(dist[u] + cost[u][i]);

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

void PrintPath(int v) {
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

int scan (int vehicle, int RoadNo) {
	int n;
	while (scanf("%d", &n)) {
		n /= 2;

		int prevRoadNo = -1, curRoadNo = -2;
		for (int j = 0; j < n; j++){
			double a, b;
			scanf("%lf%lf", &a, &b);

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
				cost[curRoadNo].push_back(dist);
				cost[prevRoadNo].push_back(dist);
			}
			prevRoadNo = curRoadNo;
		}
	}
	return RoadNo;
}

int main() {
	

	freopen("Roadmap_Dhaka.txt", "r", stdin);
	int RoadNo = scan(0, 0);

	freopen("Roadmap_DhakaMetroRail.txt", "r", stdin);
	RoadNo = scan(1, RoadNo);
	
	freopen("input.txt", "r", stdin);
	double a, b, c, d;
	scanf("%lf%lf %lf%lf", &a, &b, &c, &d);

	// double a = 90.364255;
	// double b = 23.828335;
	// double c = 90.36315;
	// double d = 23.804896;
	int source = road[ PII(a, b) ], destination = road[ PII(c, d) ];

	cout << "source = " << source << endl;		//ThisIsForDebuggingPurposes
	cout << "destination = " << destination << endl;		//ThisIsForDebuggingPurposes

	Dijkstra(source);

	freopen("output.txt", "w", stdout);
	PrintPath(destination);
}
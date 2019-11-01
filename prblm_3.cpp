#include <bits/stdc++.h>
using namespace std;

#define IN freopen("in.txt", "r", stdin);
#define OUT freopen("out.txt", "w", stdout);
#define ll long long int
#define PII pair <double, double>
#define DhakaRoadMX 49869
#define BikolpoBusRoadMX 17
#define UttaraBusRoadMX 19
#define MetroRailMX 14
#define NodeMX 1500
#define EdgeMX NodeMX * NodeMX
#define PI 2.0 * acos(0.0)

const double typeCost[] = {20.0, 5.0, 7.0};

// car = 0
// metro = 1
// bikolpo bus = 2
//uttara bus = 2


vector <int> DhakaRoad[NodeMX], g[NodeMX], cost[NodeMX], type[NodeMX];
map <PII, int> road;
PII RoadList[NodeMX];
int dist[NodeMX], path[NodeMX], pathType[NodeMX];

void Dijkstra(int source) {
	map<int, int> m;
	
	for (int i = 1; i < DhakaRoadMX; i++)
	{
		dist[i] = INT_MAX;
		path[i] = -1;
		pathType[i] = -1;
	}

	m[0] = source;
	dist[source] = 0;

	while (!m.empty())
	{
		map<int, int>::iterator it = m.begin();

		int u = it->second;
		m.erase(it);

		for (int i = 0; i < g[u].size(); i++)
		{
			int v = g[u][i];
			int pathTP = type[u][i];
			int NewCost = dist[u] + cost[u][i];

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
	cout << RoadList[v].first << "," << RoadList[v].second<< "," <<pathType[v] << endl;
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

int scan (int limit, int vehicle, int RoadNo) {
	for (int i = 0; i < limit; i++) {
		int n;
		scanf("%d", &n);

		int prevRoadNo, curRoadNo;
		for (int j = 0; j < n; j++){
			double a, b;
			scanf("%lf%lf", &a, &b);

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

	int RoadNo = 0;

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

	// freopen("in.txt", "r", stdin);
	// double a, b, c, d;
	// scanf("%lf%lf %lf%lf", &a, &b, &c, &d);

	// int source = road[ PII(a, b) ], destination = road[ PII(c, d) ];

	// Dijkstra(source);

	// PrintPath(destination);
}
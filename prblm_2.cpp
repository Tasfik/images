#include <bits/stdc++.h>
using namespace std;

#define IN freopen("in.txt", "r", stdin);
#define OUT freopen("out.txt", "w", stdout);
#define ll long long int
#define PII pair <double, double>
#define DhakaRoadMX 49869
#define DhakaRoadNodeMX 260
#define PI 2.0 * acos(0.0)

const double costCar = 20.0;
const double costMetro = 5.0;

// struct node {
// 	double latitude, longitude, cost;
// 	int type;	//car = 0, metro  = 1, bus = 2;

// 	node (double lat = 0.0, double lon = 0.0, double cst = 0.0, int tp = 0) {
// 		latitude = lat;
// 		longitude = lon;
// 		cost = cst;
// 		type = tp;
// 	}
// };

vector <int> DhakaRoad[DhakaRoadMX], g[DhakaRoadNodeMX], cost[DhakaRoadNodeMX], type[DhakaRoadNodeMX];
map <PII, int> road;
PII RoadList[DhakaRoadMX];
int dist[DhakaRoadNodeMX], path[DhakaRoadNodeMX];

void Dijkstra(int source)
{
	map<int, int> m;
	
	for (int i = 1; i < DhakaRoadMX; i++)
	{
		dist[i] = INT_MAX;
		path[i] = -1;
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
			int NewCost = dist[u] + cost[u][i];

			if (NewCost < dist[v])
			{
				path[v] = u;
				dist[v] = NewCost;
				m[NewCost] = v;
			}
		}
	}
}

void PrintPath(int v)
{
	if (v == -1)
		return;
	PrintPath(path[v]);
	cout << RoadList[v].first << " " << RoadList[v].second << endl;
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

int main() 
{
	OUT

	freopen("Roadmap_Dhaka.txt", "r", stdin);
	int RoadNo = 0;
	for (int i = 0; i < DhakaRoadMX; i++) {
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

				type[curRoadNo].push_back(0);
				type[prevRoadNo].push_back(0);

				double dist = distance(RoadList[curRoadNo], RoadList[prevRoadNo]) * costCar;
				cost[curRoadNo].push_back(dist);
				cost[prevRoadNo].push_back(dist);

			}
			prevRoadNo = RoadNo;
		}
	}

	for (int i = 0; i < DhakaRoadMX; i++) {
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

				type[curRoadNo].push_back(0);
				type[prevRoadNo].push_back(0);

				double dist = distance(RoadList[curRoadNo], RoadList[prevRoadNo]) * costCar;
				cost[curRoadNo].push_back(dist);
				cost[prevRoadNo].push_back(dist);

			}
			prevRoadNo = RoadNo;
		}
	}

	cout << "RoadNo = " << RoadNo << endl;		//ThisIsForDebuggingPurposes

	double a, b, c, d;
	scanf("%lf%lf %lf%lf", &a, &b, &c, &d);

	int source = road[ PII(a, b) ], destination = road[ PII(c, d) ];

	Dijkstra(source);

	PrintPath(destination);
}
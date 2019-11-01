#include <bits/stdc++.h>
using namespace std;

#define IN freopen("Roadmap_Dhaka.txt", "r", stdin);
#define OUT freopen("out.txt", "w", stdout);
#define ll long long int
#define PII pair <double, double>
#define DhakaRoadMX 50000
#define NodeMX 5 * 50000
#define PI 2.0 * acos(0.0)
#define EPS 1e-8

vector <int> g[NodeMX];
vector <double> cost[NodeMX];
map <PII, int> road;
PII RoadList[5 * DhakaRoadMX];
int path[NodeMX];
double dist[NodeMX];
map<double, int> m;

void Dijkstra(int source) {
	
	m.clear();
	for (int i = 1; i < NodeMX; i++)
	{
		dist[i] = __LONG_LONG_MAX__;
		path[i] = -1;
	}

	m[0.0] = source;
	dist[source] = 0.0;

	while (!m.empty())
	{
		map<double, int>::iterator it = m.begin();

		cout << "it = " << it->first << ", " << it->second << endl;

		int u = it->second;
		m.erase(it);

		for (int i = 0; i < g[u].size(); i++)
		{
			int v = g[u][i];
			double NewCost = dist[u] + cost[u][i];

			cout << "v = " << v << endl;		//ThisIsForDebuggingPurposes
			cout << "NewCost = " << NewCost << endl;		//ThisIsForDebuggingPurposes

			if (NewCost - dist[v] > EPS)
			{
				path[v] = u;
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
	// printf("%lf,%lf\n", RoadList[v].first, RoadList[v].second);
	cout << v << " ";
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

	if (d == 0.0) {
		// cout << "zero" << endl;

		// cout << a.first << " " << a.second << " " << (a == b) << endl;
		
	}

	return R * d;
}

int scan (int RoadNo) {
	int n;
	while (scanf("%d", &n) != EOF) {
		
		// scanf("%d", &n);
		// cout << "i = " << i << endl;		//ThisIsForDebuggingPurposes
		// cout << endl << "n = " << n << " : " ;		//ThisIsForDebuggingPurposes
		n /= 2;

		int prevRoadNo = -1, curRoadNo = -2;
		for (int j = 0; j < n; j++){
			double a, b;
			scanf("%lf%lf", &a, &b);

			// cout << "RoadNo = " << RoadNo xed << a << " " << setprecision(9) << fixed << b << " ";

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

				double dist = distance(RoadList[curRoadNo], RoadList[prevRoadNo]);

				if (curRoadNo == prevRoadNo) {
					// cout << "i = " << i << " ";		//ThisIsForDebuggingPurposes
					// cout << "j = " << j << endl;		//ThisIsForDebuggingPurposes
				}
				cost[curRoadNo].push_back(dist);
				cost[prevRoadNo].push_back(dist);
			}

			prevRoadNo = curRoadNo;
		}
	}

	return RoadNo;
}
int main() {
	freopen("Roadmap_DhakaMetroRail.txt", "r", stdin);
	// OUT
	int RoadNo = 0;
	RoadNo = scan(0);

	freopen("Roadmap_UttaraBus.txt", "r", stdin);
	RoadNo = scan(RoadNo);

	freopen("Roadmap_BikolpoBus.txt", "r", stdin);
	RoadNo = scan(RoadNo);



	freopen("graph.txt", "w", stdout);
	// for (int i = 0 ; i < 20; i++) {
	// 	for (int j = 0; j < g[i].size(); j++) {
	// 		int temp = floor(cost[i][j] * 1000);
	// 		cout << i << " " << g[i][j] << " " << temp % 10000 << endl;
	// 	}
	// }

	// cout << "RoadNo = " << RoadNo << endl;		//ThisIsForDebuggingPurposes

	// double a, b, c, d;
	// scanf("%lf%lf %lf%lf", &a, &b, &c, &d);

	double a = 90.364255;
	double b = 23.828335;
	double c = 90.36315;
	double d = 23.804896;

	int source = road[ PII(a, b) ], destination = road[ PII(c, d) ];

	cout << "source = " << source << endl;		//ThisIsForDebuggingPurposes
	cout << "destination = " << destination << endl;		//ThisIsForDebuggingPurposes

	Dijkstra(source);

	for (int i = 0; i < 20; i++) {
		cout << "i = " << i << " ";		//ThisIsForDebuggingPurposes
		cout << "dist[i] = " << dist[i] << endl;		//ThisIsForDebuggingPurposes
	}
	cout << endl << endl << endl;		//ThisIsForDebuggingPurposes

	for (int i = 0; i < 20; i++){
		cout << "i = " << i << " ";		//ThisIsForDebuggingPurposes
		cout << "path[i] = " << path[i] << endl;		//ThisIsForDebuggingPurposes
	}
	cout << endl << endl << endl;		//ThisIsForDebuggingPurposes

	// printf("LON,LAT\n");
	PrintPath(destination);
}
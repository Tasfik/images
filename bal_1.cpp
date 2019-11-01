#include <bits/stdc++.h>
using namespace std;

#define IN freopen("Roadmap_Dhaka.txt", "r", stdin);
#define OUT freopen("out.txt", "w", stdout);
#define ll long long int
#define PII pair <ll, ll>
#define DhakaRoadMX 50000
#define NodeMX 5 * 50000
#define PI 2.0 * acos(0.0)
#define EPS 1e-10

const double multiply = 10000000000.0;
const ll bigNum = 10000000000;

vector <int> g[NodeMX];
vector <ll> cost[NodeMX];
map <PII, int> road;
PII RoadList[5 * DhakaRoadMX];
int path[NodeMX];
ll dist[NodeMX];
map<ll, int> m;

void Dijkstra(int source) {
	
	m.clear();
	for (int i = 1; i < NodeMX; i++)
	{
		dist[i] = __LONG_LONG_MAX__;
		path[i] = -1;
	}

	m[0] = source;
	dist[source] = 0;

	while (!m.empty())
	{
		map<ll, int>::iterator it = m.begin();

		cout << endl << "it = " << it->first << ", " << it->second << endl;

		int u = it->second;
		m.erase(it);

		for (int i = 0; i < g[u].size(); i++)
		{
			int v = g[u][i];
			ll NewCost = (ll)((dist[u] + cost[u][i]));

			cout << "v = " << v << endl;		//ThisIsForDebuggingPurposes
			cout << "NewCost = " << NewCost << endl;		//ThisIsForDebuggingPurposes

			if (NewCost - dist[v] > EPS)
			{
				path[v] = u;
				dist[v] = NewCost;
				cout << "m.size() = " << m.size() << endl;		//ThisIsForDebuggingPurposes
				m[NewCost] = v;
				cout << "m.size() = " << m.size() << endl;		//ThisIsForDebuggingPurposes
			}

			cout << "m.size() = " << m.size() << endl;		//ThisIsForDebuggingPurposes
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
	double d = 2.0 * atan( sqrt(c) / sqrt(1.0 - c)) * multiply;

	if (d <= EPS) {
		cout << "zero" << endl;

		cout << setprecision(9) << fixed << a.first << " " << setprecision(9) << fixed << a.second << " " << (a == b) << endl;
		cout << setprecision(9) << fixed << b.first << " " << setprecision(9) << fixed << b.second << " " << (a == b) << endl;
		
	}

	return R * d;
}

int lent[NodeMX];
int visited[NodeMX]; //use disjoint set find() to print path
vector <int> level[400];
int maxi = 0;

void BFS(int source, int destination = -1)
{
	queue<int> Q;

	for (int i = 0; i < NodeMX; i++)
		visited[i] = 0;

	Q.push(source);

	lent[source] = 0;
	visited[source] = 1;
	level[0].push_back(source);

	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();

		for (int i = 0; i < g[u].size(); i++)
		{
			int v = g[u][i];

			if (!visited[v])
			{
				lent[v] = lent[u] + 1;
				visited[v] = 1;
				Q.push(v);
				maxi = max(maxi, lent[v]);
				level[ lent[v] ].push_back(v);
			}
		}
	}
}

int main() {
	freopen("Roadmap_BikolpoBus.txt", "r", stdin);
	OUT
	int RoadNo = 0, n, i = -1;
	while (scanf("%d", &n) != EOF) {
		i++;
		// scanf("%d", &n);
		// cout << "i = " << i << endl;		//ThisIsForDebuggingPurposes
		// cout << endl << "n = " << n << " : " ;		//ThisIsForDebuggingPurposes
		n /= 2;

		int prevRoadNo = -1, curRoadNo = -2;
		for (int j = 0; j < n; j++){
			double a, b;
			scanf("%lf%lf", &a, &b);

			// if (a == 90.36315 && b == 23.804896) {
			// 	cout << "destination found" << endl;
			// }
			// cout << "RoadNo = " << RoadNo xed << a << " " << setprecision(9) << fixed << b << " ";

			if (road.find( PII(a, b) ) != road.end()) {
				curRoadNo = road[ PII(a, b) ];
			}
			else {
				road[ PII(a, b) ] = ++RoadNo;
				curRoadNo = RoadNo;
				RoadList[RoadNo] = PII(a, b);
			}

			if (curRoadNo == prevRoadNo)
				continue;

			// cout << "i = " << i << " ";		//ThisIsForDebuggingPurposes
			// cout << "j = " << j << endl;		//ThisIsForDebuggingPurposes
			// cout << "a = " << setprecision(9) << fixed << a << " ";		//ThisIsForDebuggingPurposes
			// cout << "b = " << setprecision(9) << fixed << b << endl;		//ThisIsForDebuggingPurposes
			// cout << "curRoadNo = " << curRoadNo << endl;		//ThisIsForDebuggingPurposes
			// cout << "prevRoadNo = " << prevRoadNo << endl;		//ThisIsForDebuggingPurposes
			

			if (j) {
				g[curRoadNo].push_back(prevRoadNo);
				g[prevRoadNo].push_back(curRoadNo);

				double dist = distance(RoadList[curRoadNo], RoadList[prevRoadNo]);

				if (dist <= EPS) {
					cout << "dist is zero" << endl;
					cout << "curRoadNo = " << curRoadNo << endl;		//ThisIsForDebuggingPurposes
					cout << "prevRoadNo = " << prevRoadNo << endl;		//ThisIsForDebuggingPurposes
				}

				// if (curRoadNo == prevRoadNo) {
				// 	cout << "i = " << i << " ";		//ThisIsForDebuggingPurposes
				// 	cout << "j = " << j << endl;		//ThisIsForDebuggingPurposes
				// }
				cost[curRoadNo].push_back((ll)dist);
				cost[prevRoadNo].push_back((ll)dist);
			}

			prevRoadNo = curRoadNo;
		}

		// cout << " >> " << endl;
		// cout << " >> " << endl;
		// cout << " >> " << endl;
		// cout << " >> " << endl;
	}

	freopen("graph.txt", "w", stdout);

	cout << "RoadNo = " << RoadNo << endl;		//ThisIsForDebuggingPurposes
	// for (int i = 0 ; i < RoadNo; i++) {
	// 	cout << i << " : ";
	// 	for (int j = 0; j < g[i].size(); j++) {
	// 		int temp = floor(cost[i][j] * 1000);
	// 		cout << g[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	// cout << "RoadNo = " << RoadNo << endl;		//ThisIsForDebuggingPurposes

	// double a, b, c, d;
	// scanf("%lf%lf %lf%lf", &a, &b, &c, &d);

	double a = 90.364255;
	double b = 23.828335;
	double c = 90.36315;
	double d = 23.804896;
	int source = road[ PII(a, b) ], destination = road[ PII(c, d) ];
	// BFS(source, destination);

	// for (int i = 1 ; i <= 114; i++) {
	// 	cout << "i = " << i << " ";		//ThisIsForDebuggingPurposes
	// 	cout << "lent[i] = " << lent[i] << endl;		//ThisIsForDebuggingPurposes
	// }
	// cout << "level : " << endl;
	// for (int i = 0; i <= 85; i++) {
	// 	for (int j = 0; j < level[i].size(); j++) {
	// 		cout << level[i][j] << " ";
	// 	}
	// 	printf(">\n");
	// }

	cout << "source = " << source << endl;		//ThisIsForDebuggingPurposes
	cout << "destination = " << destination << endl;		//ThisIsForDebuggingPurposes

	Dijkstra(source);
	
	PrintPath(destination);

	cout << endl << endl << "dist " << endl;
	for (int i = 0; i <= destination; i++) {
		cout << "i = " << i << " ";		//ThisIsForDebuggingPurposes
		cout << "dist[i] = " << dist[i] << endl;		//ThisIsForDebuggingPurposes
	}
	cout << endl << endl << endl;		//ThisIsForDebuggingPurposes

	cout << endl << endl << "path " << endl;
	for (int i = 0; i < destination; i++){
		cout << "i = " << i << " ";		//ThisIsForDebuggingPurposes
		cout << "path[i] = " << path[i] << endl;		//ThisIsForDebuggingPurposes
	}
	cout << endl << endl << endl;		//ThisIsForDebuggingPurposes

	// // printf("LON,LAT\n");
}
#include <bits/stdc++.h>
using namespace std;

#define IN freopen("in.txt", "r", stdin);
#define OUT freopen("out.txt", "w", stdout);
#define ll long long int
#define PII pair <double, double>
#define DhakaRoadMX 49869

vector <int> DhakaRoad[DhakaRoadMX], g[5*DhakaRoadMX], cost[5*DhakaRoadMX];
map <PII, int> road;
PII RoadList[DhakaRoadMX];
int dist[5*DhakaRoadMX], path[5*DhakaRoadMX];

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

double square(double n) {
	return n * n;
}

double distance(PII a, PII b) {
	return sqrt(square(a.first - b.first) + square(a.second - b.second));
}

int main() 
{
	IN
	OUT
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
				double dist = distance(RoadList[curRoadNo], RoadList[prevRoadNo]);
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
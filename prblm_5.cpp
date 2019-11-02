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

const double typeCost[] = {20.0, 5.0, 7.0};
const double multiply = 1000000.0;
const double speed = 10.0;
const int interval = 15;

// car = 0
// metro = 1
// bikolpo bus = 2
//uttara bus = 2
// walk = 3
//wait = 4


int flag[2];
int wait[NodeMX];
vector <int> g[NodeMX], type[NodeMX];
vector <PII> points;
vector <ll>  cost[NodeMX];
map <PII, int> road;
PII RoadList[NodeMX];
int path[NodeMX], pathType[NodeMX];
ll dist[NodeMX];
map <ll, int> m;

int getTime (int hour, int minute, int type) {
	return ((hour % 12) * 60 + minute) + (type * 12 * 60);
}

string getFormattedTime(int time) {
	time = floor(time / multiply);
	
	string tp, s1, s2;

	// cout << "time = " << time << endl;		//ThisIsForDebuggingPurposes
	if (time >= 12 * 60) {
		time -= 12 * 60;
		tp = "PM";
	}
	else
		tp = "AM";

	int h = floor(time / 60);

	h -= (h >= 12) * 12;

	stringstream ss;
	ss << h;
	ss >> s1;

	ss << (time % 60);
	ss >> s2;

	if (s1.length() == 0)
		s1 += '0';
	
	if (s2.length() == 0)
		s2 += '0';
	
	string res = " " +  s1 + " : " + s2 + " " + tp;

	// cout << "res = " << res << endl;		//ThisIsForDebuggingPurposes

	return res;
}

int startingTime = getTime(5, 43, 0);

void Dijkstra(int source) {
	for (int i = 1; i < NodeMX; i++)
	{
		dist[i] = LONG_LONG_MAX;
		path[i] = -1;
		pathType[i] = -1;
	}

	m[startingTime] = source;
	dist[source] = startingTime;


	while (!m.empty()) {
		map<ll, int>::iterator it = m.begin();

		int u = it->second;
		m.erase(it);

		for (int i = 0; i < g[u].size(); i++)
		{
			int v = g[u][i];
			int pathTP = type[u][i];
			ll NewCost = (ll)(dist[u] + cost[u][i]);
			
			if (dist[u] < 6 * 12) {
				NewCost += 6 * 12 - dist[u];
			}
			else if (dist[u] > 23 * 12) {
				NewCost = LONG_LONG_MAX;
			}

			if (type[u][i] == 1 || type[u][i] == 2) {
				NewCost += (interval - (dist[u] % interval)) % interval;
			}

			if (NewCost < dist[v])
			{
				path[v] = u;
				pathType[v] = pathTP;
				dist[v] = NewCost;
				m[NewCost] = v;
				wait[v] = (interval - (dist[u] % interval)) % interval;
			}
		}
	}
}

int PrintPath(int v) {
	if (v == -1)
		return 1;
	
	int val = PrintPath(path[v]);

	if (val == 2)
		cout << pathType[v] << endl;
	
	if (wait[v] > 0)
		cout << "wait " << getFormattedTime(wait[v]) << " minutes" << endl;

	cout << setprecision(7) << fixed << RoadList[v].first << "," << setprecision(7) << fixed << RoadList[v].second << "," << getFormattedTime(dist[v]) << endl;

	if (val == 1)
		return 2;
	else
		cout << pathType[v] << endl;
		

	return 0;
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
	return R * d * multiply;
}

int scan (int vehicle, int RoadNo) {
	int n;
	while (scanf("%d", &n) != EOF) {
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
				points.push_back( PII(a, b) );
				RoadList[RoadNo] = PII(a, b);
			}

			if (j) {
				g[curRoadNo].push_back(prevRoadNo);
				g[prevRoadNo].push_back(curRoadNo);

				type[curRoadNo].push_back(vehicle);
				type[prevRoadNo].push_back(vehicle);

				double dist = distance(RoadList[curRoadNo], RoadList[prevRoadNo]);
				cost[curRoadNo].push_back(dist);
				cost[prevRoadNo].push_back(dist);
			}
			prevRoadNo = curRoadNo;
		}
	}
	return RoadNo;
}

PII cmpPair;
bool cmp(PII a, PII b) {
	double d1 = distance (a, cmpPair) * multiply;
	double d2 = distance (b, cmpPair) * multiply;

	return (d1 - d2 <= EPS);
}

int findPoint(PII p, int n) {
	if (road.find(p) != road.end())
		return road[p];

	flag[n] = 0;
	cmpPair = p;
	sort(points.begin(), points.end(), cmp);
	startingTime += distance(points[0], p) * speed;
	return road[ points[0] ];
}

int main() {
	

	freopen("Roadmap_Dhaka.txt", "r", stdin);
	int RoadNo = scan(0, 0);

	freopen("Roadmap_DhakaMetroRail.txt", "r", stdin);
	RoadNo = scan(1, RoadNo);

	freopen("Roadmap_BikolpoBus.txt", "r", stdin);
	RoadNo = scan(2, RoadNo);

	freopen("Roadmap_UttaraBus.txt", "r", stdin);
	RoadNo = scan(2, RoadNo);
	
	freopen("input.txt", "r", stdin);
	double a, b, c, d;
	int h, m;
	string s;
	scanf("%lf%lf %lf%lf", &a, &b, &c, &d);
	cin >> h >> m;
	
	getchar();
	cin >> s;

	startingTime = getTime(a, b, (s == "PM"));
	// double a = 90.364255;
	// double b = 23.828335;
	// double c = 90.36315;
	// double d = 23.804896;
	flag[0] = flag[1] = 1;
	int source = findPoint(PII(a, b), 0), destination = findPoint(PII(c, d), 1);
	
	cout << "source = " << source << endl;		//ThisIsForDebuggingPurposes
	cout << "destination = " << destination << endl;		//ThisIsForDebuggingPurposes

	Dijkstra(source);

	
	freopen("output.txt", "w", stdout);

	if (!flag[0])
		cout << setprecision(7) << fixed << a << "," << setprecision(7) << fixed << b 
			<< getFormattedTime(startingTime) << ",3" << endl;
	
	PrintPath(destination);

	if (!flag[1])
		cout << setprecision(7) << fixed << c << "," << setprecision(7) << fixed << d <<","
			<< getFormattedTime(distance(RoadList[destination], PII(c, d))) << ",3" << endl;
}
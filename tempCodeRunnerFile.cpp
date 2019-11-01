
PII cmpPair;
bool cmp(PII a, PII b) {
	double d1 = distance (a, cmpPair) * multiply;
	double d2 = distance (b, cmpPair) * multiply;

	return (d1 - d2 <= EPS);
}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <set>

using namespace std;

void printArray(int a[], int n) {
	for (int* i = a; i < a + n; i++) {
		if (i != a) {
			printf(" ");
		}
		printf("%d", *i);
	}
	printf("\n");
}

int n, m, a, b, solncount;
pair<int, int> pieces[20], pfirst, plast, piecelist[20];
bool remaining[20];

void backtrack(pair<int, int> piecelist[20], int idx, bool remaining[20], int lastval) {
	if (idx == n && (plast.first == lastval)) {
		solncount += 1;
		//printf("soln: ");
		//for (int i = 0; i < idx; i++) {
		//	printf("%d %d ", piecelist[i].first, piecelist[i].second);
		//}
		//printf("end\n");
		return;
	}
	for (int i = 0; i < m; i++) {
		if (remaining[i]) {
			pair<int, int> currdomino = pieces[i];

			if (currdomino.first == lastval) {
				piecelist[idx] = currdomino;
				remaining[i] = false;
				backtrack(piecelist, idx + 1, remaining, currdomino.second);
			}
			if (currdomino.second == lastval) {
				piecelist[idx] = currdomino;
				remaining[i] = false;
				backtrack(piecelist, idx + 1, remaining, currdomino.first);
			}
			remaining[i] = true;
		}
	}
}
int main() {
	while (true) {
		scanf("%d", &n);
		if (n == 0)break;
		scanf("%d", &m);
		scanf("%d %d", &a, &b);
		pfirst = make_pair(a, b);
		scanf("%d %d", &a, &b);
		plast = make_pair(a, b);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			pieces[i] = make_pair(a, b);
		}
		solncount = 0;
		memset(remaining, true, sizeof(remaining));
		backtrack(piecelist, 0, remaining, pfirst.second);
		solncount > 0 ? printf("YES\n") : printf("NO\n");
	}
}
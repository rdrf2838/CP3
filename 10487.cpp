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

using namespace std;

void printArray(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i];
	}
	cout << endl;
}
int main() {
	std::ios::sync_with_stdio(false);
	int caseno = 0;
	while (true) {
		caseno += 1;
		int n, m, a[1001], goal; memset(a, 0, sizeof(a));
		cin >> n;
		if (n == 0) break;
		cout << "Case " << caseno << ":\n";
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		cin >> m;
		while (m--) {
			cin >> goal;
			int mindiff = 99999999;
			int currsum = 0;
			for (int i = 0; i < n - 1; i++) {
				int num1 = a[i];
				for (int j = i + 1; j < n; j++) {
					int num2 = a[j];
					int sum = num1 + num2;
					int diff = abs(goal - sum);
					if (diff < mindiff) {
						mindiff = diff;
						currsum = sum;
					}
				}
			}
			cout << "Closest sum to " << goal << " is " << currsum << ".\n";
		}
	}
}
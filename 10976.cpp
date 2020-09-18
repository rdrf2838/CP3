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
	int k, min, max, x, y, kd, ctr = 0;
	while (cin >> k) {
		min = k + 1;
		max = k * 2 + 1;
		for (int i = min; i < max; i++) {
			y = i;
			kd = k;
			if ((y * k) % (y - k) == 0) {
				ctr += 1;
			}

		}
		cout << ctr << "\n";
		for (int i = min; i < max; i++) {
			y = i;
			kd = k;
			if ((y * k) % (y - k) == 0) {
				x = (y * k) / (y - k);
				cout << "1/" << k << " = 1/" << x << " + " << "1/" << y << "\n";
			}

		}
		ctr = 0;
	}
}
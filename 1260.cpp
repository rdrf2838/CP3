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
	int t, n;
	cin >> t;
	while (t--) {
		int a[1001], b=0;  memset(a, 0, sizeof(a)); 
		cin >> n;
		for (int k = 0; k < n; k++) {
			cin >> a[k];
			}
		for (int i = 1; i < n; i++) {
			int currval = a[i];
			for (int j = 0; j < i; j++) {
				int compval = a[j];
				if (currval >= compval) {
					b += 1;
				}
			}
		}
		cout << b << "\n";
	}
}
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
	for (int i = 0; i < n; i++) {
		cout << a[i] << ",";
	}
	cout << endl;
}
int main(){
	int ctr = 0, max = 2000000000;
	long i, j, k, l, m = 1000000, top, btm;
	for (int a = 1; a < 2001; a++) {
		if (pow(a, 4) > max)break;
		for (int b = a; b < 2001; b++) {
			if (a * pow(b, 3) > max)break;
			for (int c = b; c < 2001; c++) {
				if (a * b * pow(c, 2) > max)break;
				i = a; j = b; k = c;
				btm = (i * j * k - m);
				if (btm <= 0)continue;
				top = m * (i + j + k);
				if (top % btm != 0)continue;
				l = top / btm;
				if (l < k)continue;
				if (i + j + k + l > 2000)continue;
				ctr += 1;
				printf("%.2lf %.2lf %.2lf %.2lf\n", i/ 100.0, j/ 100.0, k / 100.0, l/ 100.0);

			}
		}
	}
}
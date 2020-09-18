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
unsigned int bitcount(unsigned int n)
{
	unsigned int count = 0;
	while (n) {
		count += n & 1;
		n >>= 1;
	}
	return count;
}
int main() {
	int n, b, caseno = 0;
	while (true) {
		caseno += 1;
		if (caseno > 1) {
			std::printf("\n");
		}
		scanf("%d %d\n", &n, &b);
		if ((n == 0) && (b == 0)) {
			break;
		}
		std::printf("Case Number %d\n", caseno);
		int sz[21], m, mlist[11], mcus[11], sharecount, temp, tempsum;
		for (int i = 0; i < n; i++) {
			scanf("%d", &sz[i]);
		}
		scanf("%d\n", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d", &sharecount);
			tempsum = 0;
			for (int j = 0; j < sharecount; j++) {
				scanf("%d", &temp);
				tempsum = tempsum | (1 << (temp - 1));
			}
			mlist[i] = tempsum;
			scanf("%d", &mcus[i]);
		}
		int maxtotal = 0, bi;
		for (int i = 0; i < ((1 << n) - 1); i++) {
			if (bitcount(i) == b) {
				//if there are b set bits - valid choice
				int total = 0;
				for (int j = 0; j < n; j++) {
					if (i & (1 << j)) {
						total += sz[j];
					}
				}
				for (int a = 0; a < m; a++) {
					int mbits = mlist[a];
					int bc = bitcount(i & mbits);
					if (bc > 1) {
						if (bc % 2 == 0) {
							total -= mcus[a];
						}
						else if (bc % 2 == 1) {
							total += mcus[a];
						}
					}

				}
				if (total > maxtotal) {
					maxtotal = total;
					bi = i;
				}
			}
		}
		std::printf("Number of Customers: %d\n", maxtotal);
		std::printf("Locations recommended : ");
		for (int i = 0; i < n; i++) {
			if (((1 << i) & bi)) {
				std::printf("%d ", i + 1);
			}
		}
		std::printf("\n");

	}

	//for (i = 0; i < (1 << n); i++) { // for each subset, O(2^n)
	//	sum = 0;
	//	for (int j = 0; j < n; j++) // check membership, O(n)
	//		if (i & (1 << j)) // test if bit ‘j’ is turned on in subset ‘i’?
	//			sum += l[j]; // if yes, process ‘j’
	//	if (sum == X) break; // the answer is found: bitmask ‘i’
	//}
}
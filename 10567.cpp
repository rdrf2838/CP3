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
#include <fstream>

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
void printVector(vector<int> vec) {
	for (int ci : vec) {
		printf("%d ", ci);
	}
	printf("\n");
}

int bs(vector<int> vec, int l, int r, int x) {
	if (r > l) {
		int midl = (l + r) / 2; int midr = midl + 1;
		if (vec[midl] == x)return midl;
		if (vec[midr] == x)return midr;
		if (vec[midl] < x && x < vec[midr])return midr;
		if (x < vec[midl])return bs(vec, l, midl, x);
		if (vec[midr] < x)return bs(vec, midr, r, x);
	}
	else if (l == 0) return 0;
	return -1;
}
int ascii2int(char c) {
	int asciival = int(c);
	if (asciival <= 90) return asciival - 65;
	if (asciival >= 97) return asciival - 97 + 26;
}
vector<int> arrvi[52];

int main() {
	char temp[1000000];
	string s;
	scanf("%s", &temp);
	s = temp;
	int i = 0;
	for (char c : s) {
		arrvi[ascii2int(c)].push_back(i);
		i++;
	}
	int q;
	scanf("%d", &q);
	while (q--) {
		char ss[101]; int ctrpos = 0, arrctrpos[101], ctr = 0; string sss; bool issuccess = true;
		scanf("%s", &ss);
		sss = ss;
		for (char c : sss) {
			int val = ascii2int(c);
			vector<int> currvec = arrvi[val];
			int res = bs(currvec, 0, currvec.size() - 1, ctrpos);
			if (res == -1) {
				printf("Not matched\n");
				issuccess = false;
				break;
			}
			arrctrpos[ctr] = currvec[res];
			ctrpos = currvec[res] + 1;
			ctr += 1;
		}
		if (issuccess) {
			printf("Matched %d %d\n", arrctrpos[0], arrctrpos[ctr - 1]);
		}
	}
}
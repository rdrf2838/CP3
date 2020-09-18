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

int t, k;
char arr1[5][6], arr2[5][6], word[6];

string nextPerm(char arr[5][6], int ctr) {
	char test[6];
	int d[5], hack[5] = { 1296, 216,36,6,1 }, temp = ctr;
	for (int i = 0; i < 5; i++) {
		int currbase = hack[i];
		d[i] = temp >= currbase ? temp / currbase : 0;
		temp = temp % currbase;
	}
	for (int i = 0; i < 5; i++) {
		test[i] = arr[i][d[i]];
	}
	test[5] = '\0';
	string temp2 = "";
	for (int i = 0; i < 6; i++) {
		temp2 = temp2 + test[i];
	}
	return temp2;
}
string strcpybl(string s1) {
	string s2 = "";
	for (char c : s1) {
		s2 += c;
	}
	return s2;
}

void comparer(char arr1[5][6], char arr2[5][6], int count) {
	int ctr = 0, ctr1 = 0, ctr2 = 0;
	string s1, s2;
	vector<string> sprevlist;
	while (ctr < count) {
		if (ctr1 == 7776 || ctr2 == 7776) {
			printf("NO\n");
			return;
		}

		s1 = nextPerm(arr1, ctr1);
		s2 = nextPerm(arr2, ctr2);

		if (s1 == s2) {
			bool foundb4 = false;
			for (string word : sprevlist) {
				if (word == s1) {
					foundb4 = true;
				}
			}
			if (foundb4) { ctr -= 1; }
			else {
				string sprev = strcpybl(s1);
				sprevlist.push_back(sprev);
			}
			ctr += 1; ctr1 += 1; ctr2 += 1;
		}
		else if (s1 > s2) {
			ctr2 += 1;
		}
		else if (s1 < s2) {
			ctr1 += 1;
		}
	}
	printf("%s\n", s1.c_str());
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &k);
		for (int i = 0; i < 6; i++) {
			scanf("%s", word);
			for (int j = 0; j < 5; j++) {
				arr1[j][i] = word[j];
			}
		}
		for (int i = 0; i < 6; i++) {
			scanf("%s", word);
			for (int j = 0; j < 5; j++) {
				arr2[j][i] = word[j];
			}
		}
		for (int i = 0; i < 5; i++) {
			sort(arr1[i], arr1[i] + 6);
			sort(arr2[i], arr2[i] + 6);
		}
		comparer(arr1, arr2, k);
	}
}
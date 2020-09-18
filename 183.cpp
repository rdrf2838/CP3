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
void printArray(bool a[], int n) {
	for (bool* i = a; i < a + n; i++) {
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
char temp;
int r, c, n, listctr;

int checker(bool arr[201][201], int rowleft, int rowright, int colleft, int colright) {
	bool isallfalse = true;
	bool isalltrue = true;
	for (int i = rowleft; i <= rowright; i++) {
		for (int j = colleft; j <= colright; j++) {
			if (arr[i][j] == true) isallfalse = false;
			else isalltrue = false;
			if ((!isallfalse) && (!isalltrue))return -1;
		}
	}
	if (isallfalse)return 0;
	else return 1;
}

void quartenarysearch(bool arr[201][201], int rowleft, int rowright, int colleft, int colright) {
	if (rowright >= rowleft && colright >= colleft) {
		int res = checker(arr, rowleft, rowright, colleft, colright);
		if (res != -1) {
			printf("%d", res);
			return;
		}
		int rowcurr = (rowleft + rowright) / 2;
		int colcurr = (colleft + colright) / 2;
		printf("D");

		quartenarysearch(arr, rowleft, rowcurr, colleft, colcurr);
		quartenarysearch(arr, rowleft, rowcurr, colcurr + 1, colright);
		quartenarysearch(arr, rowcurr + 1, rowright, colleft, colcurr);
		quartenarysearch(arr, rowcurr + 1, rowright, colcurr + 1, colright);
	}
}
void fill(bool arr[201][201], int rowleft, int rowright, int colleft, int colright, char currchar) {
	for (int i = rowleft; i <= rowright; i++) {
		for (int j = colleft; j <= colright; j++) {
			arr[i][j] = currchar == '1' ? true : false;
		}
	}
}
void quartenaryfiller(bool arr[201][201], int rowleft, int rowright, int colleft, int colright, char list[]) {
	//printf("%d %d %d %d %d", rowleft, rowright, colleft, colright, listctr);
	if (listctr >= n)return;
	if (rowright >= rowleft && colright >= colleft) {
		char currchar = list[listctr];
		if (currchar == '1' || currchar == '0') {
			//printf(" filled: %c\n", currchar);
			listctr += 1;
			fill(arr, rowleft, rowright, colleft, colright, currchar);
			return;
		}
		if (currchar = 'D') {
			//printf(" divided\n");

			listctr += 1;
			int rowcurr = (rowleft + rowright) / 2;
			int colcurr = (colleft + colright) / 2;
			quartenaryfiller(arr, rowleft, rowcurr, colleft, colcurr, list);
			quartenaryfiller(arr, rowleft, rowcurr, colcurr + 1, colright, list);
			quartenaryfiller(arr, rowcurr + 1, rowright, colleft, colcurr, list);
			quartenaryfiller(arr, rowcurr + 1, rowright, colcurr + 1, colright, list);
		}
	}
}

bool arr[201][201];
int main() {
	while (true) {
		scanf("%c", &temp);
		scanf("%d %d", &r, &c);
		if (temp == '#')break;
		else if (temp == 'B') {
			for (int i = 0; i < r; i++) {
				for (int j = 0; j < c; j++) {
					scanf("%1d", &arr[i][j]);
				}
			}
			printf("D%4d%4d\n", r, c);
			quartenarysearch(arr, 0, r - 1, 0, c - 1);
			printf("\n");
		}
		else if (temp == 'D') {
			listctr = 0;
			char charlist[51];
			scanf("%s", &charlist);
			string charlisttemp = charlist;
			n = charlisttemp.length();
			printf("B%4d%4d\n", r, c);
			quartenaryfiller(arr, 0, r - 1, 0, c - 1, charlist);
			for (int i = 0; i < r; i++) {
				for (int j = 0; j < c; j++) {
					printf("%d", arr[i][j]);
				}
			}
			printf("\n");

		}
	}
}
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
#include <queue>

using namespace std;

int main() {
	ifstream inputFile;
	ofstream outputFile;
	string line;
	string header = "C:\\Users\\leeji\\Music\\";
	
	int fileCount = 3;
	string inputArr[] = {
		"C:\\Users\\leeji\\Music\\.Playlists (Phone)\\Filter.m3u8",
		"C:\\Users\\leeji\\Music\\.Playlists (Phone)\\Normal.m3u8" ,
		"C:\\Users\\leeji\\Music\\.Playlists (Phone)\\Tier 1.m3u8" };
	string outputArr[] = {
		"C:\\Users\\leeji\\Music\\.Playlists (Computer)\\Filter.m3u8",
		"C:\\Users\\leeji\\Music\\.Playlists (Computer)\\Normal.m3u8" ,
		"C:\\Users\\leeji\\Music\\.Playlists (Computer)\\Tier 1.m3u8" };

	for (int i = 0; i < fileCount; i++) {
		inputFile.open(inputArr[i]);
		outputFile.open(outputArr[i]);
		if (inputFile.is_open())
		{
			while (getline(inputFile, line))
			{
				line = header + line.substr(26);
				outputFile << line << '\n';
			}
			inputFile.close();
			outputFile.close();
		}
		else cout << "Unable to open file";
	}
	cout << "Complete";
	

}

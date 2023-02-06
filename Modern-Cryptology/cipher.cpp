// THIS PROGRAM WAS INTENDED AS ROUGH WORK. HOWEVER, COMMENTS HAVE BEEN INCLUDED TO MAKE THINGS AS CLEAR AS POSSIBLE

#include <bits/stdc++.h>
using namespace std;

int main() {
	string msg = "Mewa wa mey twsam iepjoys gt mey ipbya. Pa xgn iph ayy, meysy wa hgmewhr gt whmysyam wh mey iepjoys. Agjy gt mey kpmys iepjoysa vwkk oy jgsy whmysyamwhr meph mewa ghy! Mey iguy nayu tgs mewa jyaapry wa p awjfky anoamwmnmwgh iwfeys wh vewie uwrwma epby oyyh aewtmyu ox 8 fkpiya. Mey fpaavgsu wa mxSrN03uwdd vwmegnm mey dngmya.";
	
	transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
	
	string test = "";
	
	unordered_map<char, int> charFreq;
	multimap<int, char, greater<int>> table;
	map<char, char> subs;
	
	// count frequency of each occuring character
	for(char c: msg) {
		if(charFreq.find(c) == charFreq.end()) charFreq[c] = 1;
		else charFreq[c]++;
	}
	
	// shift the data to a multimap with frequency as key (decreasing order)
	for(auto& it: charFreq) {
		table.insert({it.second, it.first});
	}
	
	cout << "character frequency table: " << endl;
	for(auto& it: table) {
		cout << "(" << it.first << ": " << it.second << "), ";
	}
	cout << endl;
	
	cout << endl;
	cout << "ciphertext space: " << endl;
	for(auto& it: table) {
		cout << it.second << ", ";
	}
	cout << endl << endl;
	
	// made a substitution mapping to figure out the changes. It consists of only the letters that were enough to solve the cipher
	subs = {{'y', 'e'},{'a', 's'},{'m', 't'},{'e', 'h'},{'w', 'i'},{'t', 'f'},{'s', 'r'},{'i', 'c'},{'p', 'a'},{'j', 'm'},{'o', 'b'},{'g', 'o'},{'b', 'v'},{'x', 'y'},{'n', 'u'},{'d', 'q'},{'f', 'p'},{'u', 'd'},{'v', 'w'},{'k', 'l'},{'r', 'g'},{'h', 'n'},{'8', '6'},{'0', '6'},{'3', '9'}};
	
	/** POSSIBLE VALUES AFTER DIGIT SHIFTS:
		tyRgU03diqq
		tyRgU92diqq
		tyRgU81diqq
		tyRgU70diqq
		tyRgU69diqq
		tyRgU58diqq
		tyRgU47diqq
		tyRgU36diqq
		tyRgU25diqq
		tyRgU14diqq
	**/
	
	for(char c: msg) {
		if(subs.find(c) != subs.end()) {
			//test += "(";
			test += subs[c];
			//test += ")";
		} else {
			test += c;
		}
	}
	
	cout << "substituted message: " << endl << test << endl;
	
	return 0;
}

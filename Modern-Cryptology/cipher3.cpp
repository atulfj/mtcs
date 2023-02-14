#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

int main() {
	// The ciphertext
	string ctxt = "qmnjvsa nv wewc flct vprj tj tvvplvl fv xja vqildhc xmlnvc nacyclpa fc gyt vfvw. fv wgqyp, pqq pqcs y wsq rx qmnjvafy cgv tlvhf cw tyl aeuq fv xja tkbv cqnsqs.  lhf avawnc cv eas fuqb qvq tc yllrqr xxwa cfy. psdc uqf avrqc gefq pyat trac xwv taa wwd dv eas flcbq. vd trawm vupq quw x decgqcwt, yq yafl vlqs yqklhq! snafq vml lhvqpawr nqg_vfusr_ec_wawy qp fn wgawdgf.";
		
	cout << "Ciphertext: \n" << ctxt << "\n\n";
	     
	// Maps for freq analysis
	unordered_map<char, int> charFreq, subs;
	multimap<int, char, greater<int>> sortedByFreq;
	
	// Remove non-alphabet characters (underscore, period, quotes) and populate freq map
	string temp = "";
	for(int i = 0; i < ctxt.size(); i++) {
		if(ctxt[i] >= 'a' && ctxt[i] <= 'z') {
			temp += ctxt[i];
			charFreq[ctxt[i]]++;
		}
	}
	
	string blocked = "";
	for(int i = 0; i < temp.size(); i++) {
		if((i)%5 == 0) {
			blocked += " ";
			blocked += temp[i];
		} else {
			blocked += temp[i];
		}
	}
	
	cout << "Block of 5: \n" << blocked << "\n\n";
	
	subs = {{'l', 's'}, {'a', 't'}, {'v', 'e'}, {'h', 'p'}, {'r', 'w'}, {'q', 'a'}, {'m', 'k'}, {'p', 'd'}, {'f', 'h'}, {'w', 'o'}, {'n', 'r'}, {'j', 'b'}, {'s', 'f'}, {'c', 'i'}, {'e', 'c'}, {'c', 'i'}, {'t', 'l'}, {'x', 'y'}, {'i', 'q'}, {'d', 'u'}, {'y', 'n'}, {'u', 'm'}, {'b', 'v'}};
	
	string permuted = "";
	for(int i = 0; i < floor(temp.size()/5); i++) {
		permuted += temp[i*5+3];
		permuted += temp[i*5+2];
		permuted += temp[i*5+4];
		permuted += temp[i*5];
		permuted += temp[i*5+1];
		permuted += " ";
	}
	
	cout << "permuted: \n" << permuted << "\n\n";
	
	string test = "";
	for(char c: permuted) {
		if(subs.find(c) != subs.end()) {
			//test += "(";
			test += subs[c];
			//test += ")";
		} else {
			test += c;
		}
	}
	
	cout << "substituted message: " << endl << test << endl;
	
}

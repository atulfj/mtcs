#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

// Decryption function 
string decrypt(string ciphertxt, string key) {
	string plaintxt = "";
	
	// Extend the key to the same length as ciphertxt
	int len = ciphertxt.size();
	while(key.size() < len) {
		key += key;
	}
	key.resize(len);
	
	for(int i = 0; i < len; i++) {
		plaintxt += ((ciphertxt[i] - key[i] + 26) % 26) + 'a';
	}
	
	return plaintxt;
}

int main() {
	// The ciphertext
	string ctxt = "Kg fcwd qh vin pnzy hjcocnt, cjjwg ku wnth nnyvng kxa cjjwg. Urfjm xwy yjg rbbufqwi 'vjg_djxn_ofs_dg_rmncbgi' yq iq uqtxwlm. Oca zxw qcaj vjg tctnplyj hqs cjn pjcv ejbvdnt. Yt hkpe cjn gcnv, aqv okauy bknn ongm vt zvvgs vcpkh bqtft cjntj.";
	
	string key, ptxt;
	
	cout << "Ciphertext: \n" << ctxt << "\n\n";
	     
	// Maps for freq analysis
	unordered_map<char, int> charFreq;
	multimap<int, char, greater<int>> sortedByFreq;
	
	// Convert to lowercase
	transform(ctxt.begin(), ctxt.end(), ctxt.begin(), ::tolower);
	
	// Remove non-alphabet characters (underscore, period, quotes) and populate freq map
	string temp = "";
	for(char c: ctxt) {
		if(c >= 'a' && c <= 'z') {
			temp += c;
			charFreq[c]++;
		}
	}
	ctxt = temp;
	cout << "Raw ciphertext: \n" << ctxt << "\n\n";
	
	// Arrange characters in decreasing order of their freq
	for(auto const& [c, f] : charFreq) {
		sortedByFreq.insert({f, c});
	}
	cout << "Character frequencies: \n";
	for(auto const& [f, c]: sortedByFreq) {
		cout << c << " : " << f << "\t";
	}
	cout << "\n\n";
	
	// Suspected key: 9292552221
	// Convert key to string before passing to function
	long keynum = 9292552221;
	
	while(keynum) {
		key += char(keynum%10)+'a';
		keynum /= 10;
	}
	reverse(key.begin(), key.end());
	
	cout << "Key: " << key << "\n\n";
	
	// Calling decrypt function
	ptxt = decrypt(ctxt, key);
	
	cout << "Plaintext: \n" << ptxt << "\n\n";
}

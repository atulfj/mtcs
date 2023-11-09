#pragma GCC optimize("Ofast")
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <vector>

using namespace std;

#define min(x,y) ({ __typeof__(x) __var0 = x; __typeof__(y) __var1 = y; __var0 < __var1 ? __var0 : __var1; })
#define max(x,y) ({ __typeof__(x) __var0 = x; __typeof__(y) __var1 = y; __var0 < __var1 ? __var1 : __var0; })

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define iter(it, x) for(auto it = (x).begin(); it != (x).end(); it++)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define debug(arr) trav(a, arr) cout << a << " "; cout << endl
#define see(x) cout << x << endl
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef priority_queue<pll, vector<pll>, greater<pll>> pq_minll;
typedef priority_queue<pll> pq_maxll;
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound
#define mod 1000000007

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("../inputf.in", "r", stdin);
    freopen("../outputf.out", "w", stdout);

    int tc;
    cin >> tc;
    while(tc--) {
        string row1, row2;
        cin >> row1 >> row2;

        int res = 0;

        int n = sz(row1);

        bool ok = true;

        /* fill the ones where we dont have a choice */
        rep(i, 0, n) {
            if(row1[i] == '?' && row2[i] != '?') {
                row1[i] = (row2[i] == 'R' ? 'W' : 'R'); 
                res++;
            } else if(row2[i] == '?' && row1[i] != '?') {
                row2[i] = (row1[i] == 'R' ? 'W' : 'R'); 
                res++;
            } else if(row1[i] != '?' && row1[i] == row2[i]) {
                ok = false;
                break;
            }
        }

        if(!ok) {
            see(-1);
            continue;
        }

        map<char, int> mp1 = {{'R', 0}, {'W', 0}, {'?', 0}}, mp2 = {{'R', 0}, {'W', 0}, {'?', 0}};
        trav(ch, row1) mp1[ch]++;
        trav(ch, row2) mp2[ch]++;

        int need1 = abs(mp1['R']-mp1['W']), need2 = abs(mp2['R']-mp2['W']);

        if(need1 > 0 && need1 > mp1['?']) {
            see(-1);
            continue;
        } 

        if(need2 > 0 && need2 > mp2['?']) {
            see(-1);
            continue;
        }

        res += 2 * abs(mp1['W'] - mp2['W']);

        see(res);
    }

    return 0;
}    
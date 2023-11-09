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

bool isPossible(string& str, int mid, vi& c) {
    set<char> seen;
    int n = sz(str);
    
    vi breaks(c.begin(), c.begin()+mid);
    sort(all(breaks));
    
    int j = 0;
    rep(i, 0, n) {
        if(j < sz(breaks) && i == breaks[j]) {
            seen.clear();
            j++;
        }
        if(seen.find(str[i]) != seen.end()) return false;
        seen.insert(str[i]);
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("../inputf.in", "r", stdin);
    freopen("../outputf.out", "w", stdout);

    int tc;
    cin >> tc;
    while(tc--) {
        string str;
        cin >> str;
        int m;
        cin >> m;
        vi pos(m);
        trav(p, pos) cin >> p;

        /* solve */
        int low = 0, high = m, mid;

        while(low <= high) {
            mid = (low + high)/2;
            if(isPossible(str, mid, pos)) high = mid-1;
            else low = mid+1;
        }

        see((low <= m ? low : -1));
    }

    return 0;
}    
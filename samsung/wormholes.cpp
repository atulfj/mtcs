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
#define see(x) cout << (x) << endl
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

int res = INT_MAX;

int calculateDist(pii a, pii b) {
    return abs(a.f - b.f) + abs(a.s - b.s);
}

void minimizeCost(pii src, pii dest, vi& used, vvi& wormhole, int cost) {
    res = min(res, calculateDist(src, dest) + cost);
    rep(i, 0, sz(wormhole)) {
        if(!used[i]) {
            used[i] = 1;
            /* end 1 */
            int newCost = calculateDist(src, mp(wormhole[i][0], wormhole[i][1])) + wormhole[i][4] + cost;
            minimizeCost(mp(wormhole[i][2], wormhole[i][3]), dest, used, wormhole, newCost);
            /* end 2*/
            newCost = calculateDist(src, mp(wormhole[i][2], wormhole[i][3])) + wormhole[i][4] + cost;
            minimizeCost(mp(wormhole[i][0], wormhole[i][1]), dest, used, wormhole, newCost);
            used[i] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("inputf.in", "r", stdin);
    freopen("outputf.out", "w", stdout);

    int tc;
    cin >> tc;
    while(tc--) {
        int n;
        cin >> n;
        pii src, dest;
        cin >> src.f >> src.s >> dest.f >> dest.s;
        vvi wormhole(n, vi(5, 0));
        trav(r, wormhole) {
            trav(a, r) {
                cin >> a;
            }
        }
        vi used(n, 0);
        minimizeCost(src, dest, used, wormhole, 0);
        see(res);
    }

    return 0;
}    
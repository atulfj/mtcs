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

int res = 0;
int spCpu;
int spChips;

class Config {
public:
    int cpus;
    int chips;
    int boards;
    int sp;

    Config() : cpus(0), chips(0), boards(0), sp(0) {}
};

void solve(vector<Config>& configs, int i, int curSp, int nDist, int nCPU, int nChips, int nBoards) {
    if(i == sz(configs) || nDist == 3) {
        curSp += nCPU * spCpu + nChips * spChips;
        res = max(res, curSp);
        return;
    }
    solve(configs, i+1, curSp, nDist, nCPU, nChips, nBoards);
    int maxProd = max(nCPU/configs[i].cpus, max(nChips/configs[i].chips, nBoards/configs[i].boards));
    rep(k, 1, maxProd+1) {
        int leftCPU = nCPU - configs[i].cpus * k;
        int leftChips = nChips - configs[i].chips * k;
        int leftBoards = nBoards - configs[i].boards * k;
        int newSp = curSp + configs[i].sp * k;
        solve(configs, i+1, newSp, nDist+1, leftCPU, leftChips, leftBoards);
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
        int nCPU, nChips, nBoards;
        cin >> nCPU >> nChips >> nBoards >> spCpu >> spChips;
        int n;
        cin >> n;
        vector<Config> configs(n);
        trav(c, configs) {
            cin >> c.cpus >> c.chips >> c.boards >> c.sp;
        }
        solve(configs, 0, 0, 0, nCPU, nChips, nBoards);
        see(res);
    }

    return 0;
}    
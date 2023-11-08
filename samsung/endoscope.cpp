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

int dirs[5] = {-1,0,1,0,-1};

vector<pii> getNextCoords(int r, int c, int pipe) {
    vector<pii> res;

    if(pipe == 1) {
        rep(i, 0, 4) {
            res.pb(mp(r + dirs[i], c + dirs[i+1]));
        }
    } else if(pipe == 2) {
        res.pb(mp(r - 1, c));
        res.pb(mp(r + 1, c));
    } else if(pipe == 3) {
        res.pb(mp(r, c - 1));
        res.pb(mp(r, c + 1));
    } else if(pipe == 4) {
        res.pb(mp(r - 1, c));
        res.pb(mp(r, c + 1));
    } else if(pipe == 5) {
        res.pb(mp(r, c + 1));
        res.pb(mp(r + 1, c));
    } else if(pipe == 6) {
        res.pb(mp(r, c - 1));
        res.pb(mp(r + 1, c));
    } else if(pipe == 7) {
        res.pb(mp(r - 1, c));
        res.pb(mp(r, c - 1));
    }

    return res;
}

bool canGo(vvi& grid, pii prev, pii& next) {
    int r = prev.f, c = prev.s, nr = next.f, nc = next.s;
    int p = grid[nr][nc];
    trav(coord, getNextCoords(nr, nc, p)) {
        if(coord == prev) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("inputf.in", "r", stdin);
    freopen("outputf.out", "w", stdout);

    int tc;
    cin >> tc;

    while(tc--) {
        int n, m, r, c, l;
        cin >> n >> m >> r >> c >> l;
        vvi grid(n, vi(m, 0));
        trav(r, grid) {
            trav(a, r) cin >> a;
        }

        set<pii> seen;
        queue<vi> q;

        seen.insert(mp(r, c));
        q.push({r, c, l-1});

        while(!q.empty()) {
            auto v = q.front();
            q.pop();
            int r = v[0], c = v[1], curLen = v[2];
            if(curLen <= 0) continue;
            /* choose between several pipe types */
            int pipe = grid[r][c];
            trav(p, getNextCoords(r, c, pipe)) {
                int nr  = p.f, nc = p.s;
                if(nr >= 0 && nr < n && nc >= 0 && nc < m && seen.find(p) == seen.end() && grid[nr][nc] != 0 && canGo(grid, mp(r, c), p)) {
                    seen.insert(p);
                    q.push({nr, nc, curLen - 1});
                }
            }
        }

        see(sz(seen));
    }  

    return 0;
}    
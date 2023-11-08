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

int res = 100;

void dfs(vvi& mat, int r, int c, int curMax) {
    //see(r << " " << c);
    int val = mat[r][c];
    if(val == 3) {
        res = min(res, curMax);
        return;
    }
    mat[r][c] = -1;

    /* horizontal */
    if(c-1 >= 0 && mat[r][c-1] != -1 && mat[r][c-1] != 0) {
        dfs(mat, r, c-1, curMax);
    }
    if(c+1 < sz(mat[0]) && mat[r][c+1] != -1 && mat[r][c+1] != 0) {
        dfs(mat, r, c+1, curMax);
    }
    
    /* vertical up */
    int h = r-1;
    while(h >= 0 && mat[h][c] != 1 && mat[h][c] != 3) {
        h--;
    }
    //see("h " << h);
    if(h != r && h >= 0) {
        dfs(mat, h, c, max(curMax, r-h));
    }

    /* vertical down */
    h = r+1;
    while(h < sz(mat) && mat[h][c] != 1 && mat[h][c] != 3) {
        h++;
    }
    //see("h " << h);
    if(h != r && h < sz(mat)) {
        dfs(mat, h, c, max(curMax, h-r));
    }

    mat[r][c] = val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("inputf.in", "r", stdin);
    freopen("outputf.out", "w", stdout);

    int tc = 1;
    //cin >> tc;

    while(tc--) {
        int n, m;
        cin >> n >> m;
        vvi mat(n, vi(m, 0));
        trav(r, mat) {
            trav(a, r) {
                cin >> a;
            }
        }
        dfs(mat, n-1, 0, 0);
        see(res);
    }  

    return 0;
}    
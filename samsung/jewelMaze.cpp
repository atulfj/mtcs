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

int dirs[5] = {-1,0,1,0,-1};
int res = 0;

void dfs(vvi& mat, int n, int r, int c, int curJewels) {
    //see(curJewels);
    if(r == n-1 && c == n-1) {
        res = max(res, curJewels);
        return;
    }
    int val = mat[r][c];
    mat[r][c] = -1;
    rep(i, 0, 4) {
        int nr = r + dirs[i], nc = c + dirs[i+1];
        if(nr >= 0 && nr < n && nc >= 0 && nc < n && mat[nr][nc] != -1 && mat[nr][nc] != 1) {
            if(mat[nr][nc] == 2) {
                dfs(mat, n, nr, nc, curJewels+1);
            } else {
                dfs(mat, n, nr, nc, curJewels);
            }
        }
    }
    mat[r][c] = val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("inputf.in", "r", stdin);
    freopen("outputf.out", "w", stdout);

    int tc = 1;
    cin >> tc;

    while(tc--) {
        int n;
        cin >> n;
        vvi mat(n, vi(n, 0));
        trav(r, mat) {
            trav(a, r) {
                cin >> a;
            }
        }
        int val = mat[0][0];
        mat[0][0] = -1;
        dfs(mat, n, 0, 0, (val == 2 ? 1 : 0));
        see(res);
        res = 0;
    }  

    return 0;
}    
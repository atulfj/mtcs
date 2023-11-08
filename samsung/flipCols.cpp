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

int countOneRows(vvi& mat) {
    int n = sz(mat), m = sz(mat[0]), rows = 0;
    trav(r, mat) {
        if(m == accumulate(all(r), 0)) {
            rows++;
        }
    }
    return rows;
}

void toggle(vvi& mat, int col) {
    int n = sz(mat);
    rep(i, 0, n) {
        mat[i][col] = 1 - mat[i][col];
    }
}

void backtrack(vvi& mat, int k) {
    int m = sz(mat[0]);
    if(k <= 0) {
        res = max(res, countOneRows(mat));
        return;
    }
    rep(i, 0, m) {
        toggle(mat, i);
        // trav(r, mat) {
        //     debug(r);
        // }
        // see(endl);
        backtrack(mat, k-1);
        toggle(mat, i);
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("inputf.in", "r", stdin);
    freopen("outputf.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;
    vvi mat(n, vi(m, 0));
    trav(r, mat) {
        trav(a, r) {
            cin >> a;
        }
    }

    /* BACKTRACKING */

    backtrack(mat, k);

    see(res);

    return 0;
}    
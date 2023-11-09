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

int solve(vll& arr, int i, int j, ll val, vvll& t) {
    if(i >= j) return 0;
    
    if(t[i][j] != -1) return t[i][j];

    ll remFirstTwo = 0, remFirstLast = 0, remLastTwo = 0;

    /* remove first two */
    if(arr[i] + arr[i+1] == val) {
        remFirstTwo = 1 + solve(arr, i+2, j, val, t);
    } 
    /* remove last two */
    if(arr[j] + arr[j-1] == val) {
        remLastTwo = 1 + solve(arr, i, j-2, val, t);
    }
    /* remove first and last */
    if(arr[i] + arr[j] == val) {
        remFirstLast = 1 + solve(arr, i+1, j-1, val, t);
    }
    
    return t[i][j] = max(remFirstLast, max(remFirstTwo, remLastTwo));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("../inputf.in", "r", stdin);
    freopen("../outputf.out", "w", stdout);

    int tc;
    cin >> tc;
    while(tc--) {
        int n;
        cin >> n;
        vll arr(n);
        trav(a, arr) cin >> a;

        /** solve */
        //see("arr: "); debug(arr);
        if(n < 2) {
            see(0);
            continue;
        }

        vvll memo;

        memo = vvll(n, vll(n, -1));
        ll a = 1 + solve(arr, 2, n-1, arr[0]+arr[1], memo);

        memo = vvll(n, vll(n, -1));
        ll b = 1 + solve(arr, 0, n-3, arr[n-1]+arr[n-2], memo);

        memo = vvll(n, vll(n, -1));
        ll c = 1 + solve(arr, 1, n-2, arr[0]+arr[n-1], memo);

        see(max(a, max(b, c)));
    }

    return 0;
}    
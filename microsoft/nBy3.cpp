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
        int n, k;
        cin >> n >> k;
        vll arr(n);
        trav(a, arr) cin >> a;

        priority_queue<ll, vector<ll>, greater<ll>> minHeap;
        priority_queue<ll> maxHeap;

        sort(all(arr));
        rep(i, 0, n/3) {
            maxHeap.push(arr[i]);
            minHeap.push(arr[n-i-1]);
        }

        ll res = LLONG_MIN;
        while(k > 0) {
            ll max1 = maxHeap.top(); maxHeap.pop();
            ll max2 = maxHeap.top(); 
            ll min1 = minHeap.top(); minHeap.pop();
            ll min2 = minHeap.top(); 
            ll diffMax = max1 - max2, diffMin = min2 - min1;
            ll maxDiff = max(1, (max(diffMax, diffMin)));
            if(diffMax >= diffMin) {
                maxHeap.push(max1 - min(maxDiff, k));
                minHeap.push(min1);
            } else {
                minHeap.push(min1 + min(maxDiff, k));
                maxHeap.push(max1);
            }
            k -= maxDiff;
            res = max(res, minHeap.top()-maxHeap.top());
        }

        see(res);
    }

    return 0;
}    
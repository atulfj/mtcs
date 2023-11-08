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

void getMinTouches(int target, map<int,int> output, int curLevel, vi& working, int k, vi& signs) {
    int n = sz(working);

    if(n == 0) return;

    rep(i, 0, n) {
        int cur = working[i];
        working.erase(working.begin()+i);
        map<int,int> newOutput;

        newOutput[cur] = 1; /* {element, touches needed to make it} */
        trav(it, output) {
            int val = it.first, touches = it.second;

            /* operations */
            if(signs[0] == 1) {
                int newAdd = cur + val;
                int newTouches = touches + 3;
                if(newOutput.find(newAdd) == newOutput.end()) {
                    newOutput[newAdd] = newTouches;
                } else {
                    newOutput[newAdd] = min(newAdd, newOutput[newAdd]);
                }
                if(newAdd == target && newTouches <= k) {
                    res = min(res, newTouches);
                }
            } 

            if(signs[1] == 1) {
                if(cur >= val) {
                    int newSub = cur - val;
                    int newTouches = touches + 3;
                    if(newOutput.find(newSub) == newOutput.end()) {
                        newOutput[newSub] = newTouches;
                    } else {
                        newOutput[newSub] = min(newTouches, newOutput[newSub]);
                    }
                    if(newSub == target && newTouches <= k) {
                        res = min(res, newTouches);
                    }
                }
            }

            if(signs[2] == 1) {
                int newMul = cur * val;
                int newTouches = touches + 3;
                if(newOutput.find(newMul) == newOutput.end()) {
                    newOutput[newMul] = newTouches;
                } else {
                    newOutput[newMul] = min(newTouches, newOutput[newMul]);
                }
                if(newMul == target && newTouches <= k) {
                    res = min(res, newTouches);
                }
            }

            if(signs[3] == 1) {
                if((cur != 0) && (val % cur) == 0) {
                    int newDiv = val / cur;
                    int newTouches = touches + 3;
                    if(newOutput.find(newDiv) == newOutput.end()) {
                        newOutput[newDiv] = newTouches;
                    } else {
                        newOutput[newDiv] = min(newTouches, newOutput[newDiv]);
                    }
                    if(newDiv == target && newTouches <= k) {
                        res = min(res, newTouches);
                    }
                }
            }

            /* effect of concatenation */
            string one = to_string(cur);
            string two = to_string(val);
            //see(21);
            string onetwo = one + two;
            int newElem = stoi(onetwo);
            //see(22);
            int newTouches = touches + 1;
            if(newOutput.find(newElem) == newOutput.end()) {
                newOutput[newElem] = newTouches;
            } else {
                newOutput[newElem] = min(newTouches, newOutput[newElem]);
            }
            if(newElem == target && newTouches <= k) {
                res = min(res, newTouches);
            }
        }

        trav(it, output) {
            int val = it.first, touches = it.second;
            if(newOutput.find(val) == newOutput.end()) {
                newOutput[val] = touches;
            } else {
                newOutput[val] = min(touches, newOutput[val]);
            }
        }

        getMinTouches(target, newOutput, curLevel+1, working, k, signs);
        working.insert(working.begin()+i, cur);
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
        see("hi");
        int n, m, k;
        cin >> n >> m >> k;
        vi working(n);
        trav(a, working) cin >> a;
        vi signs(4);
        rep(i, 0, m) {
            int op;
            cin >> op;
            op--;
            signs[op] = 1;
        }
        int target;
        cin >> target;
        getMinTouches(target, {}, 1, working, k, signs);
        cout << tc << ": ";
        see(res);
    }  

    return 0;
}   
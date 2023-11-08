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

set<int> combs;

void getCombs(int nset, int nbits, int curMask, int curBit) {
    int setBits = __builtin_popcount(curMask);
    if(setBits > nset) return;
    if(setBits == nset) {
        combs.insert(curMask);
        return;
    }
    rep(i, curBit, nbits) {
        curMask |= (1 << i);
        getCombs(nset, nbits, curMask, i+1);
        curMask ^= (1 << i);
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
        vvi adjMat(n, vi(n, 0));
        trav(r, adjMat) {
            trav(a, r) {
                cin >> a;
            }
        }

        int nStates = (1 << n);

        vvi t(n, vi(nStates, 1e9));

        int src = 0, state = 1;

        rep(i, 1, n) {
            t[i][state | (1 << i)] = adjMat[src][i];
        }

        //see("here");

        rep(i, 3, n+1) {
            combs.clear();
            //see(3);
            getCombs(i, n, 0, 0);
            //see(4);
            trav(nextState, combs) {
                rep(nextEnd, 0, n) {
                    if((nextEnd^src) && ((nextState >> nextEnd)&1)) {
                        rep(prevEnd, 0, n) {
                            if((prevEnd^nextEnd) && (prevEnd^src) && ((nextState >> prevEnd)&1)) {
                                int prevState = (nextState) ^ (1 << nextEnd);
                                //see(1);
                                t[nextEnd][nextState] = min(t[prevEnd][prevState] + adjMat[prevEnd][nextEnd], t[nextEnd][nextState]);
                                //see(2);
                            }
                        }
                    }
                }
            }
        }

        int END_STATE = (1<<n)-1;
        rep(i, 1, n) {
            t[0][END_STATE] = min(t[0][END_STATE], t[i][END_STATE] + adjMat[i][0]);
        }

        see(t[0][END_STATE]);
    }

    return 0;
}    
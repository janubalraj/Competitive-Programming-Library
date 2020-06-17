#include "bits/stdc++.h"
using namespace std;
#ifndef LOCAL
#define endl '\n'
#endif

#define fr(i, a, b) for(int i = a; i <= b; i++)
#define rf(i, a, b) for(int i = a; i >= b; i--)
#define pf push_front
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define lb lower_bound
#define ub upper_bound

typedef long long ll;
typedef long double f80;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

int pct(int x) { return __builtin_popcount(x); }
int pct(ll x) { return __builtin_popcountll(x); }
int bt(int x) { return 31 - __builtin_clz(x); } // floor(log2(x))
int bt(ll x) { return 63 - __builtin_clzll(x); } // floor(log2(x))
int cdiv(int a, int b) { return a / b + !(a < 0 || a % b == 0); }
ll cdiv(ll a, ll b) { return a / b + !(a < 0 || a % b == 0); }
int nxt_C(int x) { int c = x & -x, r = x + c; return (((r ^ x) >> 2) / c) | r; }
ll nxt_C(ll x) { ll c = x & -x, r = x + c; return (((r ^ x) >> 2) / c) | r; }

vector<int> get_bits(int mask) {
	vector<int> bb;
	while(mask) { int b = bt(mask); bb.pb(b); mask ^= (1 << b); }
	reverse(all(bb));
	return bb;
}

int get_mask(vector<int> v) {
	int mask = 0;
	for(int x : v) { mask ^= (1 << x); }
	return mask;
}

template<typename T>
void uniq(vector<T> &v) { sort(all(v)); v.resize(unique(all(v)) - v.begin()); }

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll rand(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

void sc() {}

template <typename Head, typename... Tail>
void sc(Head &H, Tail &... T) { cin >> H; sc(T...); }

#ifdef LOCAL
#define debug(...) cerr << "[L:" << __LINE__ << "][" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

// #ifndef LOCAL
// string to_string(__int128 x) {
// 	string s = "";
// 	bool neg = 0;
// 	if(x < 0) { s += "-"; neg = 1; x = -x; }
// 	if(!x) s += '0';
// 	while(x) {
// 		int rem = x % 10;
// 		s += to_string(rem);
// 		x /= 10;
// 	}
// 	reverse(s.begin() + neg, s.end());
// 	return s;
// }
// #endif

const int mod = 1e9 + 7; // 998244353;

int pwr(int a,ll b) {
	int ans = 1;
	while(b) {
		if(b & 1) ans = (ans * 1LL * a) % mod;
		a = (a * 1LL * a) % mod;
		b >>= 1;
	}
	return ans;
}

/*
	Lookout for overflows!!
	Check array sizes!!
	Clear before test cases!!
	Use the correct modulo!!
	Check for corner cases!!
	Are you forgetting something?!
	Read problem statement carefully!!!
*/

const int N = 1e5 + 5;
ll a[N], b[N];

ll dp[N][2], pdp[N][2];
vector<int> g[N], g1[N];

void pre(int u, int p) {
    for(int v : g1[u]) {
        if(v != p) {
            g[u].pb(v);
            pre(v, u);
        }
    }
}

void dfs(int u) {
    dp[u][0] = -1e18, dp[u][1] = 1e18;
    for(int v : g[u]) {
        dfs(v);
        dp[u][0] = max(dp[u][0], a[u] - b[u] + dp[v][1]);
        dp[u][1] = min(dp[u][1], a[u] - b[u] + dp[v][0]);
    }
    if(!sz(g[u])) {
        dp[u][0] = dp[u][1] = a[u] - b[u];
    }
    debug(u, dp[u][0], dp[u][1]);
}

void dfs1(int u) {
    vector<ll> p0, s0, p1, s1;
    ll val0 = 1e18, val1 = -1e18;
    fr(i, 0, sz(g[u]) - 1) {
        int v = g[u][i];
        val0 = min(val0, dp[v][0]);
        val1 = max(val1, dp[v][1]);
        p0.pb(val0);
        p1.pb(val1);
    }
    val0 = 1e18, val1 = -1e18;
    rf(i, sz(g[u]) - 1, 0) {
        int v = g[u][i];
        val0 = min(val0, dp[v][0]);
        val1 = max(val1, dp[v][1]);
        s0.pb(val0);
        s1.pb(val1);
    }
    reverse(all(s0));
    reverse(all(s1));
    fr(i, 0, sz(g[u]) - 1) {
        int v = g[u][i];
        ll val0 = 1e18, val1 = -1e18;
        if(i > 0) {
            val0 = min(val0, p0[i - 1]);
            val1 = max(val1, p1[i - 1]);
        }
        if(i + 1 < sz(s0)) {
            val0 = min(val0, s0[i + 1]);
            val1 = max(val1, s1[i + 1]);
        }
        if(u != 1) {
            val0 = min(val0, pdp[u][0]);
            val1 = max(val1, pdp[u][1]);
        }
        if(val0 == 1e18) {
            val0 = 0;
            val1 = 0;
        }
        pdp[v][0] = val1 + a[u] - b[u];
        pdp[v][1] = val0 + a[u] - b[u];
        dfs1(v);
    }
}

void solve() {
	int n;
    sc(n);
    fr(i ,1, n) {
        g[i].clear();
        g1[i].clear();
        sc(a[i]);
    }
    fr(i, 1, n) {
        sc(b[i]);
    }
    fr(i, 1, n - 1) {
        int u, v;
        sc(u, v);
        g1[u].pb(v);
        g1[v].pb(u);
    }
    pre(1, 0);
    dfs(1);
    dfs1(1);
    ll ans = -1e18;
    fr(i, 1, n) {
        ll val = dp[i][1];
        if(i > 1) {
            val = min(val, a[i] - b[i] + pdp[i][0]);
        }
        if(!sz(g[i])) {
            val = a[i] - b[i] + pdp[i][0];
        }
        ans = max(ans, val);
        debug(i, val);
    }
    cout << ans << endl;
}

int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	cin >> t;
	for(int tt = 1; tt <= t; tt++) {
		solve();
	}
	return 0;
}

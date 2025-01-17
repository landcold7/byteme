/* created   : 2020-11-22 20:55:46
 * accepted  : 2021-06-27 10:21:53
 */
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
using ll = long long;

struct TarjanScc {
  vector<vector<int>> g;
  vector<int> scc;
  // Pre order sequence
  vector<int> pre;
  // Low link value
  vector<int> low;
  vector<int> stk;
  int scc_cnt;
  int order;
  int n;
  int m;

  TarjanScc(int n_) : n(n_) {
    g.resize(n);
    scc.resize(n);
    low.resize(n);
    pre.resize(n, -1);
    scc_cnt = 0;
    order = 0;
  }

  void add_edge(int u, int v) {
    g[u].push_back(v);
    m++;
  }

  void dfs(int u) {
    pre[u] = order++;
    low[u] = pre[u];
    stk.push_back(u);
    for (int v : g[u]) {
      if (pre[v] == -1) {
        // Forward edge
        dfs(v);
        low[u] = min(low[u], low[v]);
      }
      else {
        // Back edge or cross edge
        low[u] = min(low[u], pre[v]);
      }
    }
    if (low[u] == pre[u]) {
      // Root node of a scc
      scc[u] = scc_cnt;
      while (true) {
        int v = stk.back();
        stk.pop_back();
        scc[v] = scc_cnt;
        // NOTE: ignore the cross edge
        // r -> u, r -> v, v -> u
        //        r
        //     /     \
        //    u <---- v
        //
        // When processing node v, the edge v -> u will be a cross edge,
        // even though it reaches u, but it does not effect the low link
        // value that v can escape.
        //
        pre[v] = m;
        if (v == u) break;
      }
      scc_cnt++;
    }
  }

  void do_dfs() {
    for (int i = 0; i < n; i++) {
      if (pre[i] == -1) {
        dfs(i);
      }
    }
    assert(stk.empty());
  }

  vector<vector<int>> scc_group() {
    vector<vector<int>> ans(scc_cnt);
    for (int i = 0; i < n; i++) {
      assert(0 <= scc[i] && scc[i] < scc_cnt);
      ans[scc[i]].push_back(i);
    }
    return ans;
  }

  vector<vector<int>> meta_graph() {
    vector<set<int>> mg(scc_cnt);
    vector<vector<int>> ans(scc_cnt);
    for (int u = 0; u < n; u++) {
      for (int v : g[u]) {
        int su = scc[u];
        int sv = scc[v];
        if (su != sv) {
          if (!mg[su].count(sv)) {
            mg[su].insert(sv);
            ans[su].push_back(sv);
          }
        }
      }
    }
    return ans;
  }
};

void solve() {
  int N, M; cin >> N >> M;
  vector<int> coin(N);
  for (int i = 0; i < N; i++) {
    cin >> coin[i];
  }
  TarjanScc g(N);
  for (int i = 0; i < M; i++) {
    int u, v; cin >> u >> v;
    u--, v--;
    g.add_edge(u, v);
  }
  g.do_dfs();
  vector<vector<int>> group = g.scc_group();
  int cnt = g.scc_cnt;
  vector<vector<int>> cg = g.meta_graph();
  vector<ll> coins(cnt);
  for (int i = 0; i < cnt; i++) {
    ll s = 0;
    for (int u : group[i]) {
      s += coin[u];
    }
    coins[i] = s;
  }
  vector<int> vis(cnt);
  vector<ll> f(all(coins));
  std::function<void(int)> dfs = [&](int u) {
    vis[u] = 1;
    for (int v : cg[u]) {
      assert(vis[v] != 1);
      if (vis[v] == 0) {
        dfs(v);
      }
      f[u] = max(f[u], f[v] + coins[u]);
    }
    vis[u] = 2;
  };
  for (int i = 0; i < cnt; i++) {
    if (!vis[i]) {
      dfs(i);
    }
  }
  trace(f);
  cout << *max_element(all(f)) << "\n";
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  solve();
  return 0;
}

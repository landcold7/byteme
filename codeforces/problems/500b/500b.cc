/* created   : 2019-11-03 15:35:16
 * accepted  : 2019-11-03 16:16:09
 * author    : landcold7
 */
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mt make_tuple
#ifndef LOCAL
#define trace(...)
#endif
typedef long long ll;

struct dsu {
  int n;
  int m; // the number of groups after applying join.
  int gid;
  vector<int> e;
  vector<int> root_hash;
  vector<int> gid_hash;

  dsu(int n_) : n(n_) {
    m = n;
    gid = 0;
    e.resize(n, -1);
    root_hash.resize(n, -1);
    gid_hash.resize(n, -1);
  }

  int size(int x) {
    return -e[find(x)];
  }

  int find(int x) {
    return e[x] < 0 ? x : e[x] = find(e[x]);
  }

  bool join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) {
      return false;
    }
    if (e[a] > e[b]) {
      swap(a, b);
    }
    e[a] += e[b];
    e[b] = a;
    m--;
    return true;
  }

  // Given a gid, finds the root of that group
  int get_groot(int ix) {
    assert(0 <= ix && ix < n);
    assert(root_hash[ix] != -1);
    return root_hash[ix];
  }

  // Give a root, finds the gid.
  int get_gid(int root) {
    assert(0 <= root && root < n);
    if (gid_hash[root] == -1) {
      gid_hash[root] = gid;
      root_hash[gid] = root;
      gid++;
    }
    return gid_hash[root];
  }

  vector<vector<int>> groups() {
    vector<vector<int>> ret(m);
    // Note: 0-based.
    for (int i = 0; i < n; i++) {
      int root = find(i);
      ret[get_gid(root)].push_back(i);
    }
    return ret;
  }
};

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<string> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  dsu ds(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (b[i][j] == '1') {
        ds.join(i, j);
      }
    }
  }
  vector<vector<int>> g = ds.groups();
  vector<vector<int>> z(ds.m);
  for (int i = 0; i < ds.m; i++) {
    for (auto v : g[i]) {
      z[i].push_back(a[v]);
    }
    sort(z[i].begin(), z[i].end());
  }
  vector<int> cnt(ds.m);
  for (int i = 0; i < n; i++) {
    int gid = ds.get_gid(ds.find(i));
    cout << z[gid][cnt[gid]++] << (i == n - 1 ? '\n' : ' ');
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  solve();
  return 0;
}

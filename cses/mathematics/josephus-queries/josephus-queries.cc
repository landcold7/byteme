/* created   : 2021-02-16 17:40:37
 * accepted  : $ACCEPTED
 */
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
using ll = long long;

int solve(int n, int k) {
  if (n == 1) return 1;
  // n=7: 1 2 3 4 5 6 7
  // n=3: 3 5 7
  // n=1: 7

  // n=8: 1 2 3 4 5 6 7 8
  // n=4: 1 3 5 7
  // n=2: 1 5
  // n=1: 1

  if (k <= (n + 1) / 2) {
    // 1 2 3 4 5 6 7
    return 2 * k % n;
  }
  else {
    int c = solve(n >> 1, k - (n + 1) / 2);
    return (n & 1) ? (2 * c + 1) : (2 * c - 1);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while (t--) {
    int N, K; cin >> N >> K;
    cout << solve(N, K) << "\n";
  }
  return 0;
}

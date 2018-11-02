#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define mst(x, y) memset(x, y, sizeof(x))
#define outret(val) cout << (val) << endl
#define fora(e, c) for (auto &e : c)
#define fori(i, a, b) for (int i = (a); i < (b); ++i)
#define ford(i, a, b) for (int i = (a); i > (b); --i)
#define pvi(x) fora(a, x) cout << a << " "; cout << endl
#define par(x, n) fori(a, 0, n) cout << x[a] << " "; cout << endl
#define output(ix, val) cout << "Case #" << (ix) << ": " << (val) << endl

#define trace(...) _f(#__VA_ARGS__, __VA_ARGS__)
template <typename T>
void _f(const char* name, T&& arg) {
  cout << name << ": " << arg << endl;
}

template <typename T, typename... Args>
void _f(const char* names, T&& arg, Args&&... args) {
  const char* split = strchr(names + 1, ',');
  cout.write(names, split - names) << ": " << arg << " |";
  _f(split, args...);
}

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<vector<string>> vvs;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

// #define LOCAL_FILE
// TODO
bool prime(int inp) {
  if (((!(inp & 1)) && inp != 2 ) || (inp < 2) || (inp % 3 == 0 && inp != 3))
    return false;

    for (int k = 1; 36 * k * k - 12 * k < inp; ++k) {
      if ((inp % (6 * k + 1) == 0) || (inp % (6 * k - 1) == 0))
        return false;   
    }
  return true;
}

int main(int argc, char** argv) {
#ifdef LOCAL_FILE
  // freopen("230b-input.txt", "rt", stdin);
  clock_t begin = clock();
#endif

  int n; cin >> n >> ws;
  fori (i, 1, n + 1) {
    ll inp; cin >> inp;
    ll a = sqrt(inp);
    if (a * a == inp && prime(a)) outret("YES");
    else outret("NO");
  }

#ifdef LOCAL_FILE
  clock_t end = clock();
  double elapsed = double(end - begin) / CLOCKS_PER_SEC;
  cout << "elapsed(s): " << elapsed << endl;
#endif

  return 0;
}

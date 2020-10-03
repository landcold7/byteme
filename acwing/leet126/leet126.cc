/* created   : 2020-09-23 08:40:07
 * accepted  : 2020-09-23 23:38:48
 */
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define ll long long
#define ull unsigned long long

struct HashString {
  static const int base = 131;

  static ull get(const string& s) {
    ull ans = 1;
    for (char c : s) {
      ans = ans * base + c - 'a';
    }
    return ans;
  }
};

class Solution {
 public:
  vector<vector<string>> findLadders(string B, string E, vector<string>& W) {
    W.push_back(B);
    int n = W.size();
    auto check = [](const string& a, const string& b) {
      int cnt = 0;
      for (int k = 0; k < a.size(); k++) {
        cnt += (a[k] != b[k]);
        if (cnt > 1) return false;
      }
      return cnt == 1;
    };
    vector<vector<int>> g(n);
    int dst = -1;
    for (int i = 0; i < n; i++) {
      if (W[i] == E) {
        dst = i;
      }
      for (int j = i + 1; j < n; j++) {
        if (check(W[i], W[j])) {
          g[i].push_back(j);
          g[j].push_back(i);
        }
      }
    }
    if (dst == -1) {
      return {};
    }
    int src = n - 1;
    deque<int> qu;
    vector<int> dist(n, 1e9);
    vector<vector<int>> parent(n);
    qu.push_back(src);
    dist[src] = 0;
    parent[src] = {-1};
    bool ok = false;
    while (qu.size()) {
      int u = qu.front(); qu.pop_front();
      if (u == dst) {
        ok = true;
      }
      // 1    2
      // |    |
      // 3 ----
      for (int v : g[u]) {
        if (dist[v] > dist[u] + 1) {
          dist[v] = dist[u] + 1;
          assert(parent[v].empty());
          parent[v].push_back(u);
          qu.push_back(v);
        }
        else if (dist[v] == dist[u] + 1) {
          parent[v].push_back(u);
        }
      }
    }
    if (!ok) return {};
    vector<vector<string>> ans;
    std::function<void(int, vector<string>&)> dfs = [&](int u,
                                                        vector<string>& path) {
      if (u == -1) {
        ans.push_back(path);
        reverse(all(ans.back()));
        return;
      }
      // trace(u, parent[u]);
      path.push_back(W[u]);
      for (int p : parent[u]) {
        dfs(p, path);
      }
      path.pop_back();
    };
    vector<string> path;
    dfs(dst, path);
    return ans;
  }
};

#define EXPECT_TRUE(a) assert(a)
#define EXPECT_FALSE(a) assert(!a)
#define EXPECT(a, b) assert(a == b)

void test(const string& B, const string& E, vector<string> W) {
  Solution sol;
  auto ans = sol.findLadders(B, E, W);
  trace(ans);
}

void solve() {
  test("hit", "cog", vector<string>({"hot", "dot", "dog", "lot", "log", "cog"}));

  test("cet", "ism", vector<string>({"kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob"}));
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  solve();
  return 0;
}
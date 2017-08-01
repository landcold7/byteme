#include <cstdio>  
#include <cmath>
#include <climits>
#include <cstdlib>
#include <ctype.h> // <cctype> isalpha isdigit
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>   // std:string std:stoi
#include <queue>
#include <deque>

using namespace std;

void printVector(vector<int>& v) {
    cout << "[ ";
    for (auto x:v)
        cout << x << " ";
    cout <<"] " << endl;
}

// hashmap approch
int singleNumber(vector<int>& nums) {
    unordered_map<int, int> mp;
    for (auto x: nums) 
        mp[x]++;
    
    for (auto it=mp.begin(); it!=mp.end(); ++it)
        if (it->second != 3)
            return it->first;
    return -1;
}

// more understandable approch besed on bit manipulation
// bit manipulation ( & | ~ ^ << >> )
int singleNumber(vector<int>& nums) {
    int res = 0;
    for (int i=0; i<32; ++i) {
        int sum = 0;
        for (auto x: nums) {
            sum += (x >> i) & 1;
            sum %= 3;
        }
        if (sum == 1) 
            res |= 1 << i;
    }
    return res;
}

// more harder get approach 
//      two, one
//       (0,   0)
// (0, 0) --> (0, 1) --> (1, 0) --> (0, 0)
int singleNumber(vector<int>& nums) { 
    int two=0, one=0;
    for (auto x: nums) {
        one = (one ^ x) & ~two;
        two = (two ^ x) & ~one;
    }
    return one;
}

int main(int argc, char** argv) {
    return 0;
}

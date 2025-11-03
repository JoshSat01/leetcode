
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minCost(string c, vector<int>& t) {

        int _E = 0;

        int n = c.size();
        for(int i = 0 ; i < n ; i++){
            if(i+1 < n && c[i+1] != c[i]) continue;
            int _  = t[i];
            int __ = t[i];
            while(i+1 < n && c[i+1] == c[i]){
                _ += t[i+1];
                __ = max(__ , t[i+1]);
                i++;
            }

            _E += (_-__);
        }

        return _E;
    }
};
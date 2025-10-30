#include<vector>
#include<map>

using namespace std;

class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        //_ 🪼☑️
        int _Res = 0;
        int __   = 0;
        int _Prev = 0;

        std::map<int , vector<int>> _;

        for(int i = 0 ; i < target.size() ; i++){
            _[target[i]].push_back(i);
        }

        //consecutive made elements skip , 
        target.push_back(1);
        target.push_back(0);
        target[0] = 0;
        for(auto _J : _){
            int val = _J.first;
            auto points = _J.second;
            int __C = 0;
            for(int i = 0 ; i < points.size() ; i++){
                int pos = points[i]+1;
                target[pos] = 0;
                //two side reduce one     
                if(target[pos-1] == 0 && target[pos+1] == 0) __C--;
                //no side increment __ 
                else if(target[pos-1] != 0 && target[pos+1] != 0) __C++;
            }

            _Res += ( (max(0 ,__)+1) * ( val - _Prev ) );
            _Prev = val;
            __ += __C;

        }

        return _Res;

    }
};
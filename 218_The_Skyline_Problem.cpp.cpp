#include <vector>
#include <set>
using namespace std;


//just put _ as the pattern search


struct Comparator{
    //allows compiler to treat this struct as callable also , __
    bool operator()(const vector<int>& a , const vector<int>& b) const {
        if(a[0] == b[0]) {
            if(a[1] == b[1]) return a[2] > b[2];
            return a[1] > b[1]; 
        }
        return a[0] < b[0];
    }
};

struct Comparator2{
    //allows compiler to treat this struct as callable also , __
    bool operator()(const vector<int>& a , const vector<int>& b) const {
        return a[1] > b[1];
    }
};

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& b) {
        //!@#$%^&* _ ✅🪼
        //

        //_! ❎
        std::multiset< std::vector<int> , Comparator > _b;
        std::multiset< std::vector<int> , Comparator2 > _;
        std::vector<std::vector<int>> res;
        int n = b.size();
        int _Point = -1 , end = -1;

        for(int i = 0 ; i < n ; i++){
            _b.insert({b[i][0] , b[i][2] , b[i][1]});
            _b.insert({b[i][1] , b[i][2] , -b[i][0]});//- representing this is end
        }

        for(auto b : _b){
            int s = b[0] , 
                e = b[2] ,
                h = b[1];

            //start of building
            if(e > 0) {
                _.insert(b);
                auto building = *_.begin();
                if(building[1] == h) {
                    if(res.size() && res[res.size()-1][1] == h)continue;
                    res.push_back({s,h});
                }
            }
            //end of building
            else {
                if(_.empty()) continue;
                auto building = *_.begin();
                _Point = building[2];
                _.erase(_.find({abs(e) , h , s}));
                h = 0;
                if(!_.empty()){
                    auto building = *_.begin();
                    e = abs(building[2]);
                    h = building[1];
                }
                if(_.empty() || (_Point < e && (res.size() && res[res.size()-1][1] != h) ) ) res.push_back({_Point , h});


            }
        }

        return res;
    }
};

#include <vector>
#include <stack>    

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        //🪼

        int res = 0;
        int prev = -1;
        nums.push_back(0);
        int n = nums.size();

        std::stack<int>_;//if minimmum comes after big one it will break;
        for(int i = 0 ; i < n ; i++){
            int _1 = nums[i];
            if(_1 == prev) continue;
            while( _.size() && _.top() > _1 ) {
                res++;
                _.pop();
            }
            if( _1 && ( _.empty() || (_.size() && _.top() != _1)) ) _.push(_1);
            prev = _1;//making continues same as single unit 
        }

        return res;
    }
};

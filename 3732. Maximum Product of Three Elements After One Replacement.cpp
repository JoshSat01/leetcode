

#include <vector>
using namespace std;    


#define ll long long

class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        int min1 = 100006 , min2 = 100006 ,  max1 = -100006 , max2 = -100006;

        for(int i = 0 ; i < nums.size() ; i++){
            if(nums[i] < min1) {
                min2 = min1;
                min1 = nums[i];
            }
            
            else  {
                min2 = std::min(min2 , nums[i]);
            }
        }

        for(int i = 0 ; i < nums.size() ; i++){
            if(nums[i] > max1) {
                max2 = max1;
                max1 = nums[i];
            }
            
            else  {
                max2 = std::max(max2 , nums[i]);
            }
        }
        
        // which is big
        int n = nums.size();
         vector<long long> _ = 
        {
            (ll)min1*(ll)min2,
            (ll)min1*(ll)max1,
            (ll)max1*(ll)max2
        };
        long long res = 0;
        for(int i = 0 ; i < 3 ; i++){
            long long val = (_[i] * (100000));
            res = std::max(res , val);
            res = std::max(res , -1*val);
        }

        return res;
    }
};



/*

if the element is not zero it does not allow to cross that point , like to cross opposite side should have equal number of zeros , one corner case is one less than of one side will also work like 2 , 0 , 3 here 

just come up with that that time 

*/


#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        // ☑️✅❌❎✅
        // >>!@#$%^&* ~ _  ✅ 

        /*
            here direction is changed when met not zero 
            if non zero is there , cant cross that point 
        */
        int n = nums.size() , _ = 0;
        vector<int>_1(n) , _2(n);
        _1[0] = nums[0];
        _2[n-1] = nums[n-1];
        for(int i = 1 , j = n-2 ; i < n ; i++ , j--){
            _1[i] = nums[i]+_1[i-1];
            _2[j] = nums[j]+_2[j+1];
        }

        for(int i = 0 ; i < n ; i++){
            if(nums[i] == 0 ){ 
                if(_1[i] == _2[i]) _+=2;
                else if(abs(_1[i] - _2[i]) == 1) _+=1;
            }
        }


        return _;

    }
};
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include<unordered_map>
#include<vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        std::unordered_map<int,int> _;
        ListNode* __ = head , *res = new ListNode() , *res1 = res;
        int n = nums.size();

        for(int i = 0 ; i < n ; i++){
            _[nums[i]] = 0;
        }

        while( __ != nullptr ){
            if(_.find(__->val) != _.end() ){
                res1 -> next = nullptr;
            }
            else {
                res1 -> next = __;
                res1 = __;
            }
            __ = __ -> next;
        }

        return res -> next;
    }
};
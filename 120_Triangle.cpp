//observation
/*

path could be anything here because values are not sorted , and every current row value depend only on next rows two values

just found minimum then add to current element , there part is over so no need them for other operations.

*/


class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int>fromBottom(triangle[n-1]);

        for(int i = n-2 ; i >= 0 ; i--){
            for(int j = 0 ; j < triangle[i].size() ; j++){
                int v = min(fromBottom[j] , fromBottom[j+1]);
                fromBottom[j] = v + triangle[i][j];
            }
        }

        return fromBottom[0];

    }
};

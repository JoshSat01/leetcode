
/*

2125. Number of Laser Beams in a Bank
Solved
Medium
Topics
premium lock icon
Companies
Hint
Anti-theft security devices are activated inside a bank. You are given a 0-indexed binary string array bank representing the floor plan of the bank, which is an m x n 2D matrix. bank[i] represents the ith row, consisting of '0's and '1's. '0' means the cell is empty, while'1' means the cell has a security device.

There is one laser beam between any two security devices if both conditions are met:

The two devices are located on two different rows: r1 and r2, where r1 < r2.
For each row i where r1 < i < r2, there are no security devices in the ith row.
Laser beams are independent, i.e., one beam does not interfere nor join with another.

Return the total number of laser beams in the bank.

*/


/*

jelly🪼:

Approach: here going with every device pointing to one direction, so if one row has devices 
then this will be give beams to next available devices , 
then if there any then that becomes next device that will give beam to next ,....

here prev as zero because initially no device to give beam

*/

#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int res = 0;
        int n = bank.size();
        int prev = 0;

        for(int i = 0 ; i < n ; i++){
            int cnt = 0;
            for(int j = 0 ; j < bank[i].size() ; j++){
                if(bank[i][j] == '1') cnt++;
            }

            res += (cnt * prev);
            if(cnt != 0) prev = cnt;
        }   

        return res;
    }
};
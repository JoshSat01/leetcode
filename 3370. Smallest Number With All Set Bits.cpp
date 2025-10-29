
//just find the jelly🪼

class Solution {
public:
    int smallestNumber(int n) {
        int res = 1;
        while(n > 0) {
            res = (res << 1) | 1;
            n = (n >> 1);
        }

        return res>>1;
    }
};
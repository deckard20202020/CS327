class Solution {
public:
    int trap(vector<int>& height) {

        //I have seen this problem int a lot of interviews.  I have written this one a bunch of times
        //but always good to practice again.
        int left = 0; 
        int right = height.size() - 1;

        int ans = 0;
        int lMax = 0; 
        int rMax = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                height[left] >= lMax ? (lMax = height[left]) : ans += (lMax - height[left]);
                ++left;
            } else {
                height[right] >= rMax ? (rMax = height[right]) : ans += (rMax - height[right]);
                --right;
            }
        }
        
        return ans;
    }
};
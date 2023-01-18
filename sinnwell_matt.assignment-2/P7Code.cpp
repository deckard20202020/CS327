class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        
                //idea-put all the numbers in a priority queue
        //or maybe just sort them
        //go through the array and if the next number is 1 higher increment the current streak
        //if not, update the longest streak and set the current streak back to 1

        //base case checks
        if (nums.size() == 0) {
            return 0;
        }

        if (nums.size() == 1) {
            return 1;
        }

        //now we know the length is at least 2
        sort(nums.begin(), nums.end());
        int longestStreak = 1;
        int tempStreak = 1;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i-1]) {
                if (nums[i] == nums[i -1] + 1) {
                    tempStreak++;
                } else {
                    longestStreak = max(longestStreak, tempStreak);
                    tempStreak = 1;
                }
            }

        }

        return max(longestStreak, tempStreak);
    }
};
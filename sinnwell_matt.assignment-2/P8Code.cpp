class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

        vector<int> answer;

        if (k == 0) {
            return answer;
        } 
        priority_queue<pair<int, int>> pq;

        for (int i = 0, n = (int)nums.size(); i < n; i++) {
            while (!pq.empty() && pq.top().second <= i-k) {
                pq.pop();
            }

            pq.push(make_pair(nums[i],i));

            if (i >= k-1) {
                answer.push_back(pq.top().first);
            }

        }

        return answer;

    }
};
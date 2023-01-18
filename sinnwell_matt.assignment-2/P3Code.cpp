class Solution {
public:
    vector<long long> minimumCosts(vector<int>& regular, vector<int>& express, int expressCost) {
        
        int n = regular.size();
        long currentMinCostRegular = 0L;
        long currentMinCostExpress = expressCost;
        
        vector<long long> res(n);
        for(int i = 0; i < n ; i++) {
            
            res[i] = min(regular[i] +currentMinCostRegular , express[i] + currentMinCostExpress);
            long nextMinCostRegular = min(currentMinCostRegular + regular[i], currentMinCostExpress + express[i]);
            long nextMinCostExpress = min(nextMinCostRegular + expressCost, currentMinCostExpress + express[i]);
            
            currentMinCostRegular = nextMinCostRegular;
            currentMinCostExpress = nextMinCostExpress;

            
        }
        return res;
        
    }
};
class Solution {
public:
    int maxProfit(vector<int>& prices) {

        if (prices.size() < 2) {
            return 0;
        }
        
        int buyPrice = prices[0];
        int profit = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            //set possible profit
            int temp = prices[i] - buyPrice;
            
            //if we have found a greater profit
            if (temp > profit) {
                //update the profit
                profit = temp;
            }
            
            //if the sell price is lower than the buy price
            //we know we have a smaller buy price so move the
            //buy price along.
            if (prices[i] < buyPrice) {
                buyPrice = prices[i];
            }
        }
        
        return profit;
    }
};
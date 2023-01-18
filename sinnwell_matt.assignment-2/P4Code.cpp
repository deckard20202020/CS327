class Solution {
public:
    string longestPalindrome(string s) {

        //base case checks
        if (s.empty()) {
            return "";
        } 
        if (s.size() == 1) {
            return s;
        } 

        int start = 0;
        //We will always have a length of at least 1
        int maxLen = 1;
        int i = 0;

        //iterate over the string
        while (i < s.size()) {

            //check
            if (s.size() - i <= maxLen / 2) {
                break;
            }

            int j = i; 
            int k = i;

            //Here we will skip characters that are the same.
            while (k < s.size() - 1 && s[k+1] == s[k]) {
                ++k; 
            }

            i = k + 1;

            //Here we increase the size of our palindrome
            while (k < s.size()-1 && j > 0 && s[k + 1] == s[j - 1]) {
                 ++k; --j; 
            }

            int currLen = k - j + 1;

            if (currLen > maxLen) { 
                start = j; maxLen = currLen; 
            }
        }

        return s.substr(start, maxLen);

    }
};
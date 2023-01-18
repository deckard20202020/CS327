//P1 Code

class Solution {
public:
    bool halvesAreAlike(string s) {

        int len = s.length() / 2;
        
        int leftSideCount = 0;
        int rightSideCount = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (i < len && (s[i] =='a' || s[i] =='e' || s[i] =='i'|| s[i] =='o' || s[i] =='u'
                           || s[i] =='A' || s[i] =='E' || s[i] =='I'|| s[i] == 'O' || s[i] =='U')) {
                leftSideCount++;
            }
                
            if (i >= len && (s[i] =='a' || s[i] =='e' || s[i] =='i'|| s[i] =='o' || s[i] =='u'
                           || s[i] =='A' || s[i] =='E' || s[i] =='I'|| s[i] =='O' || s[i] =='U')) {
                rightSideCount++;
            }
            
        }
        
        return leftSideCount == rightSideCount;
    }
        
};
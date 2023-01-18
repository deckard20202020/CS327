class Solution {
public:
    bool isValid(string s) {
                
        //we will always have a non empty string
        //string will only contain ()[]{}
        
        //idea
        //iterate through the string
        //if opening parenthesis put in a stack
        //if closing paranthesis
            //pop the stack and make sure it is the correct parenthesis
                //if not return false
        //when we are done check to make sure the stack is empty
        //if so return true
            //else return false
        stack<char> stack;
        
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c);
            } else {
                //check to see that the stack isn't empty
                if (stack.size() == 0) {
                    return false;
                }
                char popped = stack.top();
                if (c == ')' && popped == '(') {
                    stack.pop();
                    continue;
                } else if (c == ']' && popped == '[') {
                    stack.pop();
                    continue;
                } else if (c == '}' && popped == '{') {
                    stack.pop();
                    continue;
                } else return false;
            }
        }
        
        if (stack.size() == 0) {
            return true;
        } else {
            return false;
        }
    }
        
};
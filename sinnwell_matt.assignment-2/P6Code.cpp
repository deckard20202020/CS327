class Solution {
public:
    int evalRPN(vector<string>& tokens) {
                //base case
        if (tokens.size() == 1) {
            return stoi(tokens[0]);
        }

        //idea
        //if it's a number, put it in a stack
        //if it's an operator, pop two numbers and operate on them

        stack<int> stack;

        int answer = 0;

        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] != "+" && tokens[i] != "-" && tokens[i] != "*" && tokens[i] != "/") {
                stack.push(stoi(tokens[i]));
            } else {
                int first = stack.top();
                stack.pop();
                int second = stack.top();
                stack.pop();
                if (tokens[i] == "+") {
                    answer = second + first;
                    stack.push(answer);
                }
                if (tokens[i] == "-") {
                    answer = second - first;
                    stack.push(answer);
                }
                if (tokens[i] == "*") {
                    answer = (long) second * first;
                    stack.push(answer);
                }
                if (tokens[i] == "/") {
                    answer = second / first;
                    stack.push(answer);
                }
            }
        }

        return answer;
    }
};
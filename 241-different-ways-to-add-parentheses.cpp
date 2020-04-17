class Solution {
public:
    // tokens copy can be optimized since they are static, could use start/end index
    // time complexity O(op#^2) every op calculates other (op#-1)s
    // space complexity O(2*op#^2) every calculation produce 2 ints
    vector<int> build(vector<string> tokens) {
        vector<int> res;
        for (int i = 1, n = tokens.size(); i < n; i+=2) {
            vector<string> leftTks = {tokens.begin(), tokens.begin()+i};
            vector<int> left;
            if (leftTks.size() == 1) {
                left = {stoi(leftTks.front())};
            } else {
                left = build(leftTks);
            }
            
            const string& op = tokens[i];
            
            vector<string> rightTks = {tokens.begin()+i+1, tokens.end()};
            vector<int> right;
            if (rightTks.size() == 1) {
                right = {stoi(rightTks.front())};
            } else {
                right = build(rightTks);
            }
            
            if (op == "+") {
                for (int l : left) for (int r : right) res.push_back(l+r);
            } else if (op == "-") {
                for (int l : left) for (int r : right) res.push_back(l-r);
            } else if (op == "*") {
                for (int l : left) for (int r : right) res.push_back(l*r);
            }
        }
        return res;
    }
    
    vector<int> diffWaysToCompute(string input) {
        size_t head = 0;
        size_t tail = input.find_first_of("+-*");
        vector<string> tokens;
        while (tail != string::npos) {
            tokens.push_back(input.substr(head, tail-head));
            tokens.push_back(input.substr(tail,1));
            head = tail+1;
            tail = input.find_first_of("+-*", head);
        }
        tokens.push_back(input.substr(head));
        
        if (tokens.size() == 1) return {stoi(tokens.front())};
        return build(tokens);
    }
};

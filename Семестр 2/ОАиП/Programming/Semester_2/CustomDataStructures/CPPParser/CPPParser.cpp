#include <iostream>
#include <string>
#include <vector>

// recursively reverse the string

#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
	static int lengthOfLongestSubstring(string s) {
        int left = 0;
        int right;
        set<char> symbols;
        for (right = s.size() - 1; right > left; right--) {
            int oldSize = symbols.size();
            symbols.insert(s[right]);
            if (symbols.size() == oldSize) {
                symbols.clear();
                right = s.size();
                left++;
            }
        }
        return left - right;
	}

};

int main() {
	std::cout << Solution::lengthOfLongestSubstring("dvdf");
}
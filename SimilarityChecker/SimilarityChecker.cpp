#include <iostream>
#include <algorithm>
#include <set>

using std::string;
using std::set;

class SimilarityChecker {
public:
    static constexpr double MAX_LENGTH_SCORE = 60.0;
    static constexpr double MAX_ALPHA_SCORE = 40.0;
    static constexpr double ZERO_SCORE = 0.0;

	double getScore(const string& param1, const string& param2) const {
        if (!(isValidInput(param1) && isValidInput(param2))) {
            return ZERO_SCORE;
        }

        return getLengthScore(param1, param2) + getAlphaScore(param1, param2);
	}

private:
    bool isValidInput(const string& param) const {
        if (!param.size()) {
            return false;
        }
        for (char c : param) {
            if (!isupper((unsigned char)c)) {
                return false;
            }
        }

        return true;
    }

    double getLengthScore(const string& param1, const string& param2) const {
        size_t len1 = param1.length();
        size_t len2 = param2.length();

        size_t longLen = std::max(len1, len2);
        size_t shortLen = std::min(len1, len2);

        if (longLen >= shortLen * 2)
            return 0;

        size_t gap = longLen - shortLen;
        return (1.0 - (double)gap / shortLen) * MAX_LENGTH_SCORE;
    }

    double getAlphaScore(const string& param1, const string& param2) const {
        set<char> set1(param1.begin(), param1.end());
        set<char> set2(param2.begin(), param2.end());

        set<char> unionSet = set1;
        for (char c : set2) {
            unionSet.insert(c);
        }

        set<char> interSet;
        for (char c : set1) {
            if (set2.count(c)) {
                interSet.insert(c);
            }
        }

        size_t totalCnt = unionSet.size();
        size_t sameCnt = interSet.size();

        return ((double)sameCnt / totalCnt) * MAX_ALPHA_SCORE;
    }
};
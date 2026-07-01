#include <iostream>
#include <algorithm>

using std::string;

class SimilarityChecker {
public:
    static constexpr double MAX_LENGTH_SCORE = 60.0;
    static constexpr double ZERO_SCORE = 0.0;

	double getScore(string param1, string param2) {
        if (!(isValidInput(param1) && isValidInput(param2))) {
            return ZERO_SCORE;
        }

        return getLengthScore(param1, param2) + getCharacterScore(param1, param2);
	}

private:
    bool isValidInput(const string& param) const {
        if (!param.size()) {
            return false;
        }
        for (char c : param) {
            if (!isupper(c)) {
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

    double getCharacterScore(const string& param1, const string& param2) {
        return ZERO_SCORE;
    }
};
#include "gmock/gmock.h"
#include "SimilarityChecker.cpp"

using namespace testing;

class SimilarityCheckerFixture : public Test {
public:
	SimilarityChecker checker;
protected:
	double getFullScore(const string& param1, const string& param2) {
		return checker.getScore(param1, param2);
	}

	const double MAX_LEN_SCORE = SimilarityChecker::MAX_LENGTH_SCORE;
	const double MAX_ALAPH_SCORE = SimilarityChecker::MAX_ALPHA_SCORE;
};

TEST_F(SimilarityCheckerFixture, WrongInputCase1_1)
{
	double actual = getFullScore("AAA", "AB0");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, WrongInputCase1_2)
{
	double actual = getFullScore("AB0", "AAA");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, WrongInputCase2_1)
{
	double actual = getFullScore("AAAa", "ABC");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, WrongInputCase2_2)
{
	double actual = getFullScore("ABCd", "AAA");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, WrongInputCase3_1)
{
	double actual = getFullScore("", "ABC");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, WrongInputCase3_2)
{
	double actual = getFullScore("ABC", "");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckOnly1)
{
	double actual = getFullScore("AAA", "BBB");
	EXPECT_EQ(MAX_LEN_SCORE, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckOnly2)
{
	double actual = getFullScore("AAAAAAA", "BCDEFGH");
	EXPECT_EQ(MAX_LEN_SCORE, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckHalf1)
{
	string param1 = "AAAAAA";
	string param2 = "BBBB";
	double ratio = 1.0 - ((double)param1.size() - (double)param2.size()) / (double)param2.size();

	double actual = getFullScore(param1, param2);
	EXPECT_EQ(MAX_LEN_SCORE * ratio, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckHalf2)
{
	string param1 = "AAAA";
	string param2 = "BBBBB";
	double ratio = 1.0 - ((double)param2.size() - (double)param1.size()) / (double)param1.size();

	double actual = getFullScore(param1, param2);
	EXPECT_EQ(MAX_LEN_SCORE * ratio, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckDoubleCase)
{
	double actual = getFullScore("AAA", "BCDEFG");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckDoubleCase2)
{
	double actual = getFullScore("AAA", "BCDEFGHIJ");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, AlphaCheck1)
{
	double actual = getFullScore("AAAAAAAA", "A");
	EXPECT_EQ(MAX_ALAPH_SCORE, actual);
}

TEST_F(SimilarityCheckerFixture, AlphaCheck2)
{
	double actual = getFullScore("AAABAAAA", "A");
	EXPECT_EQ(MAX_ALAPH_SCORE/2, actual);
}

TEST_F(SimilarityCheckerFixture, AlphaCheck3)
{
	double actual = getFullScore("AAABAAAA", "AB");
	EXPECT_EQ(MAX_ALAPH_SCORE, actual);
}

TEST_F(SimilarityCheckerFixture, AlphaCheck4)
{
	double actual = getFullScore("AAAAAA", "ABCDABCDABCD");
	EXPECT_EQ(MAX_ALAPH_SCORE/4.0, actual);
}

TEST_F(SimilarityCheckerFixture, FullCheckSimilar1)
{
	double actual = getFullScore("ABCD", "DCBA");
	EXPECT_EQ(MAX_LEN_SCORE+MAX_ALAPH_SCORE, actual);
}

TEST_F(SimilarityCheckerFixture, FullCheckSimilar2)
{
	double actual = getFullScore("ABCD", "DCBA");
	EXPECT_EQ(MAX_LEN_SCORE + MAX_ALAPH_SCORE, actual);
}

TEST_F(SimilarityCheckerFixture, FullCheckHalf_DiffLength)
{
	double actual = getFullScore("ABCDAB", "DCBA");
	EXPECT_EQ(MAX_LEN_SCORE/2.0 + MAX_ALAPH_SCORE, actual);
}

TEST_F(SimilarityCheckerFixture, FullCheckHalf_DiffChar)
{
	double actual = getFullScore("ABCD", "AABB");
	EXPECT_EQ(MAX_LEN_SCORE + MAX_ALAPH_SCORE / 2.0, actual);
}
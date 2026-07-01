#include "gmock/gmock.h"
#include "SimilarityChecker.cpp"

using namespace testing;

class SimilarityCheckerFixture : public Test {
public:
	SimilarityChecker checker;
protected:
	const double MAX_LEN_SCORE = SimilarityChecker::MAX_LENGTH_SCORE;
};

TEST_F(SimilarityCheckerFixture, WrongInputCase1_1)
{
	double actual = checker.getScore("AAA", "AB0");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, WrongInputCase1_2)
{
	double actual = checker.getScore("AB0", "AAA");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, WrongInputCase2_1)
{
	double actual = checker.getScore("AAAa", "ABC");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, WrongInputCase2_2)
{
	double actual = checker.getScore("ABCd", "AAA");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, WrongInputCase3_1)
{
	double actual = checker.getScore("", "ABC");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, WrongInputCase3_2)
{
	double actual = checker.getScore("ABC", "");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckOnly1)
{
	double actual = checker.getScore("AAA", "BBB");
	EXPECT_EQ(MAX_LEN_SCORE, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckOnly2)
{
	double actual = checker.getScore("AAAAAAA", "BCDEFGH");
	EXPECT_EQ(MAX_LEN_SCORE, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckHalf1)
{
	string param1 = "AAAAAA";
	string param2 = "BBBB";
	double ratio = 0.5;

	double actual = checker.getScore(param1, param2);
	EXPECT_EQ(MAX_LEN_SCORE * ratio, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckHalf2)
{
	string param1 = "AAAA";
	string param2 = "BBBBB";
	double ratio = 0.75;

	double actual = checker.getScore(param1, param2);
	EXPECT_EQ(MAX_LEN_SCORE * ratio, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckDoubleCase)
{
	double actual = checker.getScore("AAA", "BCDEFG");
	EXPECT_EQ(0, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckDoubleCase2)
{
	double actual = checker.getScore("AAA", "BCDEFGHIJ");
	EXPECT_EQ(0, actual);
}
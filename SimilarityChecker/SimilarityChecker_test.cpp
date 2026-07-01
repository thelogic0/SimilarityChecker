#include "gmock/gmock.h"
#include "SimilarityChecker.cpp"

using namespace testing;

class SimilarityCheckerFixture : public Test {
public:
	SimilarityChecker checker;
};

TEST_F(SimilarityCheckerFixture, LengthCheckOnly1)
{
	double actual = checker.getScore("AAA", "BBB");
	EXPECT_EQ(SimilarityChecker::MAX_LENGTH_SCORE, actual);
}

TEST_F(SimilarityCheckerFixture, LengthCheckOnly2)
{
	double actual = checker.getScore("AAAAAAA", "BCDEFGH");
	EXPECT_EQ(SimilarityChecker::MAX_LENGTH_SCORE, actual);
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
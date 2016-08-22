#include "calc.h"
#include <gtest/gtest.h>
#include <string.h>
using namespace std;

TEST(calcRPNAndGetRPN, first_example) {
	char str[41] = "-1+5-3";
	str[6]='\0';
	Queue<char*>* rpn;
	getRPN(str,rpn);
	double actual = calcRPN(rpn);
	cout<<actual;
	EXPECT_EQ(1,actual );
}

TEST(calcRPNAndGetRPN, second_example) {
	char str[41] = "-10 + (8 * 2.5) - (3 / 1,5)";
	str[27]='\0';
	Queue<char*>* rpn;
	getRPN(str,rpn);
	double actual = calcRPN(rpn);
	EXPECT_EQ(8.0,actual );
}

TEST(calcRPNAndGetRPN, third_example) {
	char str[41] = "1 + (2 * (2.5 + 2.5 + (3- 2)))-(3 / 1.5)";
	str[40]='\0';
	Queue<char*>* rpn;
	getRPN(str,rpn);
	double actual = calcRPN(rpn);
	EXPECT_EQ(11.0,actual );
}

TEST(getRPN, fourth_example) {
	char str[41] = "1.1 + 2.1 + abc";
	str[40]='\0';
	Queue<char*>* rpn;
	int actual=getRPN(str,rpn);
	EXPECT_EQ(12,actual );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

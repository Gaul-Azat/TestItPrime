#include "calc.h"
#include <gtest/gtest.h>
#include <string.h>
using namespace std;

TEST(calcPRN, divisionByZero){
	char str[4]="6/0";
	str[3]='\0';
	Queue<char*>* rpn;
	getRPN(str,rpn);
	try {
		double actual = calcRPN(rpn);
	}catch(char const* msg)
	{
		ASSERT_STRCASEEQ("Деление на '0' невозможно", msg);
	}
}


TEST(calcRPNAndGetRPN, first_example) {
	char str[20] = "3 + 4 * 2 / (1 - 5)";
	str[19]='\0';
	Queue<char*>* rpn;
	getRPN(str,rpn);
	double actual = calcRPN(rpn);
	EXPECT_EQ(1.0,actual );
}



TEST(calcRPNAndGetRPN, second_example) {
	char str[41] = "-10 + (8 * 2.5) - (3 / 1,5)";
	str[27]='\0';
	Queue<char*>* rpn;
	getRPN(str,rpn);
	double actual = calcRPN(rpn);
	EXPECT_EQ(8.0,actual );
}



TEST(calcRPNAndGetRPN, second_example) {
	char str[41] = "-10 + (8 * 2.5) - (3 / 1,5)";
	str[27]='\0';
	Queue<char*>* rpn;
	getRPN(str,rpn);
	double actual = calcRPN(rpn);
	EXPECT_EQ(8.0,actual );
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

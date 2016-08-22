#include "calc.h"
#include <gtest/gtest.h>
#include <string.h>
using namespace std;

TEST(getRPN, emptyString){
	char str[1];
	str[0]='\0';
	Queue<char*>* rpn;
	int actual=getRPN(str,rpn);	
	EXPECT_EQ(-2,actual );
}

TEST(getRPN, oneNumber){
	char str[2];
	str[0]='1';
	str[1]='\0';
	Queue<char*>* rpn;
	getRPN(str,rpn);
	char *t=pop(rpn);
	double actual=atof(t);	
	EXPECT_EQ(1,actual );
}

TEST(getRPN, wrongFirstSymbol){
	char str[2];
	str[0]='+';
	str[1]='\0';
	Queue<char*>* rpn;
	int actual=getRPN(str,rpn);	
	EXPECT_EQ(0,actual );
}

TEST(getRPN, notClosedParentheses){
	char str[9]="(1+3-4+6";
	str[8]='\0';
	Queue<char*>* rpn;
	int actual=getRPN(str,rpn);	
	EXPECT_EQ(-2,actual );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

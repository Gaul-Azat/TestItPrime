#include"calc.h"
#include<stdlib.h>
#include<cstring>
using namespace std;

//Чтение числа или открывающей скобки
int readNumber(char* str, int pos, Stack<char*> *&signs, Queue<char*> *&rpn) {
	if (str[pos] == ' ')
	{
		return readNumber(str, pos + 1, signs, rpn);
	}
	if (str[pos] == '(')
	{	
		char *s=new char[2];
		s[0]='(';
		s[1]='\0';
		if (!pushSigns(signs,rpn, s))
			return pos;
		return readNumber(str, pos + 1, signs, rpn);
	}
	if (str[pos] == '\0' || str[pos]=='\n') {
		return -2;
	}
	char *number = new char[10];
	int oldPos=pos;
	int i = 0;
	if (str[pos] == '-') {
		number[0] = '-';
		i++;
		pos++;
	}
	while ((str[pos] >= '0'&& str[pos] <= '9') || str[pos] == ',' || str[pos] == '.'){
		if (str[pos] == ',') {
			number[i] = '.';
		}
		else {
			number[i] = str[pos];
		}			
			i++;
			pos++;
	}
	if (i == 0)
		return (oldPos);
	number[i] = '\0';
	push(rpn, number);
	return readSign(str,pos,signs,rpn);
}
//чтение знака операции или закрывающей скобки
int readSign(char* str, int pos, Stack<char*> *&signs, Queue<char*> *&rpn) {
	if (str[pos] == ' ')
	{
		return readSign(str, pos + 1, signs, rpn);
	}
	if (str[pos] == '+' || str[pos] == '-' || str[pos] == '*' || str[pos] == '/') {
		char *s=new char[2];
		s[0]=str[pos];
		s[1]='\0';
		if (!pushSigns(signs, rpn, s))
			return pos;
		return readNumber(str, pos + 1, signs, rpn);
	}
	switch (str[pos])
	{
	case ')':
	{
		char *s=new char[2];
		s[0]=')';
		s[1]='\0';
		if (!pushSigns(signs, rpn, s))
			return pos;
		return readSign(str, pos + 1, signs, rpn);
	}
	case '\n':
	{
		char * t = pop(signs);
		while (t != NULL) {
			if (t[0] == '(') {
				return -2;
			}
			char *s=new char[2];
			s[0]=t[0];
			s[1]='\0';
			push(rpn, s);
			t = pop(signs);
		}
		return -1;
	}
		
	case '\0':
	{
		char * t = pop(signs);
		while (t != NULL) {
			if (t[0] == '(') {
				return -2;
			}
			char *s=new char[2];
			s[0]=t[0];
			s[1]='\0';
			push(rpn, s);
			t = pop(signs);
		}
		return -1;
	}
	default:
		return pos;
	}
}


//Преобразование выражения в форму Обратной польской записи (RPN)
int getRPN(char *str, Queue<char*> * &answer) {
	Stack<char*> *signs = NULL;
	Queue<char*> *rpn = NULL;
	int t=readNumber(str, 0, signs, rpn);
	if (t==-1)
	{
		answer=rpn;
		return -1;
	}	
	//cout<<"Error on position:  "<<t<<endl;
	answer=NULL;
	return t;
}

//Вычисление значения выражения из формы Обратной польской записи (RPN)
double calcRPN(Queue<char*> *&rpn) {
	Stack<double> *stack = NULL;
	char* t = pop(rpn);
	while (t != NULL) {
		if ((t[0] >= '0' && t[0] <= '9') || (t[0] == '-'&&t[1] >= '0' && t[1] <= '9')) {
			//cout << atof(t)<<endl;
			push(stack, atof(t));
		}
		else {
			switch (t[0])
			{
			case'+':
			{
				double res = pop(stack) + pop(stack);
				//cout << res<<endl;
				push(stack, res);
				break;
			}
			case'-':
			{
				double second = pop(stack);
				double first = pop(stack);
				//cout << first-second<<endl;
				push(stack, first - second);
				break;
			}
			case'*':
			{
				double res = pop(stack) * pop(stack);
				//cout << res<<endl;
				push(stack, res);
				break;
			}
			case'/':
			{
				double second = pop(stack);
				double first = pop(stack);
				if (first == 0)
				{
					throw "Деление на '0' невозможно";
				}
				//cout << first / second << endl;
				push(stack, first / second);
				break;
			}
			default:
				break;
			}
		}
		//очищение памяти
		delete[] t;
		t = pop(rpn);
	}
	return pop(stack);
}

//Получение подстроки с ошибкой
char* getWrongSymbols(char* str, int startPos){
	size_t len =strlen(str);
	char *t=new char[len];
	int i=startPos;
	int j=0;
	while(str[i]!=' '){
		t[j]=str[i];
		j++;
		i++;
	}
	t[j]='\0';
	return t;
}

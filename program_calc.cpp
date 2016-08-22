#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<stdio.h>
#include <cmath>
using namespace std;

//Структура для реализации стека
template <typename T>
struct Stack
{
	T x;
	Stack<T> *next;
};

//Структура для реализации очереди
template <typename T>
struct Queue {
	T x;
	Queue<T> *next;
};

//Проталкивание элемента в конец очереди
template <typename T>
void push(Queue<T>* &start, const T val) {
	Queue<T> *el=new Queue<T>;
	el->x = val;
	el->next = NULL;
	if (start == NULL) {
		start = el;
		return;
	}
	Queue<T> *t = start;
	while (t->next != NULL) {
		t = t->next;
	}
	t->next = el;
}

//Проталкивание элемента в начало стека
template <typename T>
void push(Stack<T>* &start, const T val) {
	Stack<T> *temp = new Stack<T>;
	temp->x = val;
	temp->next = start;
	start = temp;
}

//Проталкивание знака операции в стек, соблюдая приоритет операций
template <typename T>
bool pushSigns(Stack<T>* &start, Queue<T> *&qstart, const T val) {
	switch (val[0])
	{
		case '+':
		{	
			T t = pop(start);
			while (t != NULL && (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/')) {
				char *s=new char[2];
				s[0]=t[0];
				s[1]='\0';
				push(qstart, s);
				t = pop(start);
			}
			if (t != NULL) {
				push(start, t);
			}
			char *s=new char[2];
			s[0]='+';
			s[1]='\0';
			push(start, s);
			return true;
		}
		case '-':
		{
			T t = pop(start);
			while (t != NULL && (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/')) {
				char *s=new char[2];
				s[0]=t[0];
				s[1]='\0';
				push(qstart, s);
				t = pop(start);
			}
			if (t != NULL) {
				push(start, t);
			}
			char *s=new char[2];
			s[0]='-';
			s[1]='\0';
			push(start, s);
			return true;
		}
		case '*':
		{
			T t = pop(start);
			while (t != NULL && (t[0] == '*' || t[0] == '/')) {
				char *s=new char[2];
				s[0]=t[0];
				s[1]='\0';
				push(qstart, s);
				t = pop(start);
			}
			if (t != NULL) {
				push(start, t);
			}
			char *s=new char[2];
			s[0]='*';
			s[1]='\0';
			push(start, s);
			return true;
		}
		case '/':
		{
			T t = pop(start);
			while (t != NULL && (t[0] == '*' || t[0] == '/')) {
				char *s=new char[2];
				s[0]=t[0];
				s[1]='\0';
				push(qstart, s);
				t = pop(start);
			}
			if (t != NULL) {
				push(start, t);
			}
			char *s=new char[2];
			s[0]='/';
			s[1]='\0';
			push(start, s);
			return true;
		}
		case '(':
		{
			char *s=new char[2];
			s[0]='(';
			s[1]='\0';
			push(start, s);
			return true;
		}
		case ')':
		{
			T t = pop(start);
			while (t != NULL && t[0] != '(') {
				char *s=new char[2];
				s[0]=t[0];
				s[1]='\0';
				push(qstart, s);
				t = pop(start);
			}
			if (t == NULL) {
				return false;
			}

			return true;
		}
		default:
			return false;
		}
}

//выталкивание элемента из стека
template <typename T>
T pop(Stack<T>* &start) {
	if (start == NULL) {
		return 0;
	}
	T val = start->x;
	Stack<T> *t = start;
	start = start->next;
	delete t;
	return val;
}
//выталкивание элемента из очереди
template <typename T>
T pop(Queue<T>* &start) {
	if (start == NULL) {
		return 0;
	}
	T val = start->x;
	Queue<T> *t = start;
	start = start->next;
	delete t;
	return val;
}

int readSign(char* str, int pos, Stack<char*> *&signs, Queue<char*> *&rpn);

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

const int MAX_SIZE = 265;

int main() {
	char *str = new char[MAX_SIZE];
	cout<<"Введите выражение:"<<endl;
	fgets(str, MAX_SIZE, stdin);
	Queue<char*> * rpn=NULL;
	int t=getRPN(str,rpn);
	if (t==-1){
		try{
			double answer=calcRPN(rpn);
			answer=round(answer*100)/100.0;
			cout <<"Результат:  " << answer <<endl;	
		}catch(char const* msg)
		{
			cout << msg << endl;
		}
	}
	else if (t==-2){
		cout<<"Некорректный конец выражения"<<endl; 
	}
	else {
		cout<<"Некорректный ввод, строка содержит недопустимое выражение на позиции  "<<t+1<<": " << getWrongSymbols(str, t)<<endl;
	}
	cout<<"Нажмите <Enter>";
	cin.get();
}

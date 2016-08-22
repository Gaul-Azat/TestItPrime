#pragma once
#include<iostream>
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
//чтение знака операции или закрывающей скобки
int readSign(char* str, int pos, Stack<char*> *&signs, Queue<char*> *&rpn);

//Чтение числа или открывающей скобки
int readNumber(char* str, int pos, Stack<char*> *&signs, Queue<char*> *&rpn);

//Преобразование выражения в форму Обратной польской записи (RPN)
int getRPN(char *str, Queue<char*> *&rpn);

//Вычисление значения выражения из формы Обратной польской записи (RPN)
double calcRPN(Queue<char*> *&rpn);

//Получение подстроки с ошибкой
char* getWrongSymbols(char* str, int startPos);

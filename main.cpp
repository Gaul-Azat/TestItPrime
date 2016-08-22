#include "calc.h"
#include<stdio.h>
#include <iostream>
#include <cmath>
const int MAX_SIZE = 265;
using namespace std;
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

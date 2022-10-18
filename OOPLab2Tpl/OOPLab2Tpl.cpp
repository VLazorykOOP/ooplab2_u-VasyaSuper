#include <iostream>
#include "Tasks.h"
#include "Examples.h"

using namespace std;

int main(){
    char ch = '5';

    system("chcp 1251");

    cout << "OOP - Лабораторна робота #2 \n";
    do {
        system("cls");
        MenuTask();
        cout << "====================================================================================================================================\n\n";
        cout << "    Виберіть завдання: ";
        ch = cin.get();
        
        cin.get();

        switch (ch) {
        case '1': task1(); break;
        case '2': task2(); break;
        case '3': task3(); break;
        case '4': task4(); break;
		case '5': return 0;
	    }
        cout << " Press any key and enter\n";
        ch = cin.get();
    } while (ch != '5');

    return 0;
}


#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>

using namespace std;

int dialogue;
char decision;

void dialogues(){
	if(dialogue == 0){
		cout << "(You hear very loud noises at the top of the hill)" << endl;
		cout << "Type '1' to investigate" << endl;
		cout << "Type any other key to ignore it and keep playing Tetris in a stolen Gameboy" << endl;
		cin >> decision;
		switch(decision){
		default :
			cout << "You ignore it completely. THE END." << endl;
			_getch();
			exit(0);
			break;
		case '1' : ;
		}
		cout << "You: WHAT THE HECK IS HAPPENING HERE?" << endl;
		_getch();
		cout << "Hippie: WOOOOOOOOOO WAAAAAAAAAA WOOOOOOOOOOO" << endl;
		_getch();
	}
}
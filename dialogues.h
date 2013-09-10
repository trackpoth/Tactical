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
		cout << "You don't see nothing else than fields around you" << endl;
		_getch();
	}
	if(dialogue == 1){
		cout << "(You hear very loud noises at the top of the hill)" << endl;
		cout << "[1] Investigate" << endl;
		cout << "[Any other key] Ignore it and keep playing Teetrix in a stolen Game Box" << endl;
		cin >> decision;
		switch(decision){
		default :
			cout << endl << "You ignore it completely. THE END." << endl;
			_getch();
			exit(0);
			break;
		case '1' : ;
		}
		cout << endl << "You: WHAT THE HECK IS HAPPENING HERE?" << endl;
		_getch();
		cout << "Hippie: WOOOOOOOOOO WAAAAAAAAAA WOOOOOOOOOOO" << endl;
		_getch();
	}
	if(dialogue == 2){
		cout << "(You hear someone running after you)" << endl;
		_getch();
		cout << "???: QUIERO MI BOCADILLO!" << endl;
		_getch();
		cout << "You: W-what? Sorry, I don't speak spanish" << endl;
		_getch();
		cout << "???: QUIERO MI BOCADILLO!!" << endl;
		_getch();
	}
}
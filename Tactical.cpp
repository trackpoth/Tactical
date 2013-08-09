#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>
#include "player.h"

using namespace std;

	//Inicialización de objetos
player mainplayer;

void clear(){
	HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hndl, &csbi);
	DWORD written;
	DWORD n = csbi.dwSize.X * csbi.dwCursorPosition.Y + csbi.dwCursorPosition.X + 1;	
	COORD curhome = {0,0};
	FillConsoleOutputCharacter(hndl, ' ', n, curhome, &written);
	csbi.srWindow.Bottom -= csbi.srWindow.Top;
	csbi.srWindow.Top = 0;
	SetConsoleWindowInfo(hndl, TRUE, &csbi.srWindow);
	SetConsoleCursorPosition(hndl, curhome);
}

void defeat(){
	if(playerlife <= 0){
		clear();
		cout << playername;
		cout << " has lost!\a" << endl;
		battlechecker = false;
		_getch();
		exit(0);
	}
}

void victory(){
	if(enemylife <= 0){
		clear();
		cout << playername;
		cout << " won the battle!\a" << endl;
		battlechecker = false;
		_getch();
		exit(0);
	}
}

void escapebattle(){
	if(runawayfrombattle == true){
		clear();
		cout << playername;
		cout << " ran away!\a" << endl;
		battlechecker = false;
		_getch();
		exit(0);
	}
}

void itemmenu(){
	printf("You have %d Small Health Pill(s) (+%d life)\n",smallhealthpill,smallhealthpillvalue);
	printf("You have %d Damage Pill(s) (+10 attack until the end of the battle)\n",damagepill);
	printf("\nType '1' to use a Small Health Pill\n");
	printf("Type '2' to use a Damage Pill\n");
	printf("Type any other key to go back to the main menu and skip the turn\n");
	cin >> movement;
	clear();
	switch(movement){
	case '1' : 
		if(smallhealthpill > 0){
			smallhealthpill--;
			playerlife += smallhealthpillvalue;
			mainplayer.limitplayerlife();
			printf("Used a Small Health Pill and life was restored by %d points! %d remaining\n",smallhealthpillvalue,smallhealthpill);
		}
		else{
			printf("You haven't any Small Health Pills left!\n");
		}
		break;
	case '2' : 
		if(damagepill > 0){
			damagepill--;
			damagepilleffect = true;
			printf("Used a Damage Pill and attack was increased by 10 points! %d remaining\n",damagepill);
		}
		else{
			cout << "You haven't any Damage Pills left!" << endl;
		}
		break;
	default : cout << "Closed the item bag without using items" << endl;
	}
}

void battlemenu(){
	cout << "Grass Common Bandit" << endl;
	if(piercingeyeeffect == false){
		printf("Life = %d\n",enemylife);
	}
	else{
		printf("Life = %d/%d\n",enemylife,enemymaxlife);
		printf("Attack = %d\n",enemyattack);
	}
	if(piercingeyeeffect == true){
		cout << "Weak to: ";
		if(enemytype == 1){
			cout << "Fire (x2)" << endl;
		}
		else{
			clear();
			cout << "CRITICAL ERROR: 'ENEMY TYPE CORRUPT'" << endl;
			_getch();
			exit(1);
		}
		cout << "Resistant to: ";
		if(enemytype == 1){
			cout << "Nothing" << endl;
		}
		else{
			clear();
			cout << "CRITICAL ERROR: 'ENEMY TYPE CORRUPT'" << endl;
			_getch();
			exit(1);
		}
	}
	printf("Effects = ");
	if(piercingeyeeffect == true){
		cout << "Piercing Eye (Infinite turns remaining)\n" << endl;
	}
	if(piercingeyeeffect == false){
		cout << "None\n" << endl;
	}
	cout << playername;
    printf("'s life = %d/",playerlife);
	mainplayer.saymaxlife();
	cout << endl;
	cout << playername;
    printf("'s SP = %d/%d\n",playersp,playermaxsp);
	cout << playername;
    printf("'s MP = %d/%d\n",playermp,playermaxmp);
	cout << playername;
	printf("'s attack");
	if(damagepilleffect == true){
		cout << " = ";
		mainplayer.sayattack();
		cout << " (Damage Pill +10 attack)" << endl;
	}
	if(damagepilleffect == false){
		cout << " = ";
		mainplayer.sayattack();
		cout << endl;
	}
	cout << playername;
	printf("'s magic attack = %d\n",playermagicattack);
	printf("Distance from the enemy: ");
	if(distanceenemy == 1){
		cout << "Very short" << endl;
	}
	if(distanceenemy == 2){
		cout << "Short" << endl;
	}
	if(distanceenemy == 3){
		cout << "Medium" << endl;
	}
	if(distanceenemy == 4){
		cout << "Far" << endl;
	}
	if(distanceenemy == 5){
		cout << "Very far" << endl;
	}
	printf("\nType '1' to attack the enemy\n");
	printf("Type '2' to open the item bag\n");
	printf("Type '3' to show the special moves list\n");
	printf("Type '4' to show the magic learned\n");
	printf("Type '5' to get closer to the enemy\n");
	if(distanceenemy == 5){
		printf("Type '6' to run away from the battle\n");
	}
	else{
		printf("Type '6' to move away from the enemy\n");
	}
	printf("Type any other key to skip the turn\n");
}


void battle(){
	while(battlechecker == true){

		STARTBATTLE:

		mainplayer.determinecriticalpower();

		t = clock();
		if(t >= 10000){
			t-=9999;
		}
		srand(seed);

		// Comprueba si has ganado o perdido la batalla
		escapebattle();
		victory();
		defeat();

		// Muestra el menú con parte de los parámetros y sus explicaciones, junto con las acciones que puede hacer el jugador
		battlemenu();

		// Comprueba si la distancia frente al enemigo es lo suficientemente corta como para realizar un ataque físico
		if(distanceenemy == 1 || distanceenemy == 2){
			successfulhit = true;
			successfulhit2 = true;
		}
		if(distanceenemy == 3 || distanceenemy == 4 || distanceenemy == 5){
			successfulhit = false;
			successfulhit2 = false;
		}

		// Se ejecuta el turno del jugador
		cin >> movement;
		clear();

		switch(movement){
		case '1':
			seed = t;
			subcriticalcheckerone = rand() % 100;
			if(successfulhit == true){
				mainplayer.attackenemy();
			}
			else{
				cout << "You are too far from the enemy to perform that move!" << endl;
			}
			break;
		case '2':
			itemmenu();break;
		case '3': 	
			printf("List of Special moves:\n\n");
			printf("Piercing eye [2 SP]['1' to use]\n");
			printf("-- Unveils more detailed stats of the enemy\n");
			printf("Quick eye [5 SP]['2' to use]\n");
			printf("-- Unveils more detailed stats of the enemy without finishing the current turn\n");
			printf("\nType any other key to go back to the main menu\n");
			cin >> movement;
			clear();
			switch(movement){
			case '1' : 
				if(playersp >= 2){
					playersp--;
					playersp--;
					piercingeyeeffect = true;
					cout << "Used Piercing Eye!" << endl;
				}
				else{
					cout << "You haven't enough SP left to perform this move!" << endl;
				}
				break;
			case '2' :
				if(playersp >= 5){
					playersp = (playersp - 5);
					piercingeyeeffect = true;
					cout << "Used Quick Eye!\n" << endl; 
					goto STARTBATTLE;
					break;
				}
				else{
					cout << "You haven't enough SP left to perform this move!" << endl;
				}
				break;
			default : goto STARTBATTLE;
				}
			break;
		case '5' : 
			if(distanceenemy == 1){
				cout << "You can't get closer to the enemy!" << endl;
			}
			else{
				distanceenemy--;
				cout << "Got closer to the enemy" << endl;
			}
			break;
		case '6' : 
			if(distanceenemy == 5){
				runawayfrombattle = true;
				goto STARTBATTLE;
			}
			else{
				distanceenemy++;
				cout << "Moved a bit away from the enemy" << endl;
			}
			break;
		case '4' :
			printf("List of Magic learned:\n\n");
			printf("Meditate [6 MP]['1' to use]\n");
			printf("-- Heals the player by 60 life points\n");
			printf("Fire [4 MP]['2' to use]\n");
			printf("-- Harms the enemy using the Fire Element\n");
			printf("\nType any other key to go back to the main menu\n");
			cin >> movement;
			clear();
			switch(movement){
			case '1' : 
				if(playermp >= 6){
					playermp -= 6;
					playerlife += 60;
					mainplayer.limitplayerlife();
					cout << "Used Meditate and life was restored by 60 points!" << endl;
				}
				else{
					cout << "You haven't enough MP left to perform this move!" << endl;
				}
				break;
			case '2' : 
				if(playermp >= 4){
					playermp -= 4;
					if(enemytype == 1){
						enemylife = (enemylife - playermagicattack * 2);
						printf("You dealt %d damage to the enemy by using Fire! It was very effective!\n",playermagicattack * 2);
					}
					else{
						enemylife -= playermagicattack;
						printf("You dealt %d damage to the enemy by using Fire!\n",playermagicattack);
					}
				}
				else{
					cout << "You haven't enough MP left to perform this move!" << endl;
				}
				break;
			default : 
				goto STARTBATTLE;
			}
			break;

		default: cout << "Skipped the turn" << endl;break;
		}

		// Comprueba de nuevo si la distancia frente al enemigo es lo suficientemente corta como para realizar un ataque físico
		if(distanceenemy == 1 || distanceenemy == 2){
			successfulhit = true;
			successfulhit2 = true;
		}
		if(distanceenemy == 3 || distanceenemy == 4 || distanceenemy == 5){
			successfulhit = false;
			successfulhit2 = false;
		}

		 // El enemigo ejecuta su turno
		seed = t;
		subcriticalcheckertwo = rand() % 100;
		if(successfulhit2 == true){
			if(subcriticalcheckertwo <= enemycriticalchecker){
				playerlife -= enemycriticalpower;
				printf("The enemy made a critical hit!\n\n");
			}
			else{
				playerlife -= enemyattack;
				printf("The enemy inflicted %d damage\n\n",enemyattack);
			}
		}
		else{
			cout << "The enemy got closer to " << playername << endl << endl;
			distanceenemy--;
		}
	}
}


int main(){
	// Inicio del programa, se le pregunta al jugador el nombre del main character
	while(1){
		cout << "Welcome to CutreRPG Alpha 0.3.4.3!" << endl;
		cout << "What will be the main character's name?" << endl;
		cin >> playername;
		clear();
		if(playername == "Trackpoth"){
			cout << "Will it be our god and savior's name, Trackpoth?\n\a" << endl;
		}
		if(playername == "COCOS"){
			cout << "COCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\a\n" << endl;
		}
		if(playername != "Trackpoth"){
			if(playername != "COCOS"){
				cout << "Will it be ";
				cout << playername;
				cout << "?\a\n\n";
			}
		}
		cout << "Type '1' to say yes" << endl;
		cout << "Type any other key to input a different name" << endl;
		cin >> movement;
		switch (movement){
		case '1' : 
			clear();
			cout << "Name applied correctly" << endl;
			printf("You found an enemy!\n\n");
			battle();
			break;
		}
		clear();
	}
	return 0;
}
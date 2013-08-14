#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>
#include "player.h"
#include "dialogues.h"

using namespace std;

	//Inicialización de objetos
warrior attack;

bool start;

void defeat(){
	mainplayer.defeatchecker();
}

void victory(){
	commonenemy.victorychecker();
}

void escapebattle(){
	if(runawayfrombattle == true){
		clear();
		cout << playername;
		cout << " ran away!\a" << endl;
		_getch();
		exit(0);
	}
}

void itemmenu(){
	printf("You have %d Small Health Pill(s) (+%d life)\n",mainplayer.saysmallhealthpill(),mainplayer.saysmallhealthpillvalue());
	printf("You have %d Damage Pill(s) (+10 attack until the end of the battle)\n",mainplayer.saydamagepill());
	printf("\nType '1' to use a Small Health Pill\n");
	printf("Type '2' to use a Damage Pill\n");
	printf("Type any other key to go back to the main menu and skip the turn\n");
	cin >> movement;
	clear();
	switch(movement){
	case '1' :
		if(mainplayer.saysmallhealthpill() > 0){
			mainplayer.smallhealthpilltaken();
			mainplayer.limitplayerlife();
		}
		else{
			printf("You haven't any Small Health Pills left!\n");
		}
		break;
	case '2' :
		if(mainplayer.saydamagepill() > 0){
			mainplayer.damagepilltaken();
		}
		else{
			cout << "You haven't any Damage Pills left!" << endl;
		}
		break;
	default : cout << "Closed the item bag without using items" << endl;
	}
}

void battlemenu(){
	cout << "Grass Human" << endl;
	if(piercingeyeeffect == false){
		cout << "Life = ";
		cout << commonenemy.saylife();
		cout << endl;
	}
	else{
		cout << "Life = " << commonenemy.saylife() << "/" << commonenemy.saymaxlife() << endl;
		printf("Attack = %d\n",commonenemy.sayattack());
	}
	if(piercingeyeeffect == true){
		cout << "Weak to: ";
		if(commonenemy.saytype() == 1){
			cout << "Fire (x2)" << endl;
		}
		else{
			clear();
			cout << "CRITICAL ERROR: 'ENEMY TYPE CORRUPT'" << endl;
			_getch();
			exit(1);
		}
		cout << "Resistant to: ";
		if(commonenemy.saytype() == 1){
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
	cout << "'s life = ";
	cout << mainplayer.saylife();
	cout << "/";
	cout << mainplayer.saymaxlife();
	cout << endl;
	cout << playername;
	cout << "'s SP = " << mainplayer.saysp() << "/";
	cout << mainplayer.saymaxsp();
	cout << endl;
	cout << playername;
	cout << "'s MP = " << mainplayer.saymp() << "/";
	cout << mainplayer.saymaxmp();
	cout << endl;
	cout << playername;
	printf("'s attack");
	if(damagepilleffect == true){
		cout << " = ";
		cout << mainplayer.attackparameter();
		cout << " (Damage Pill +10 attack)" << endl;
	}
	if(damagepilleffect == false){
		cout << " = ";
		cout << mainplayer.attackparameter();
		cout << endl;
	}
	cout << playername;
	cout << "'s magic attack = ";
	cout << mainplayer.saymagicattack();
	cout << endl;
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
	clear();
	if(start == true){
		cout << "Name applied correctly" << endl;
		start = false;
	}
	cout << "Press always any key to show the next lines of text" << endl << endl;
	dialogue = 0;
	dialogues();
	clear();

	while(1){

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
				commonenemy.enemyattacked();
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
				if(mainplayer.saysp() >= 2){
					mainplayer.decreaseplayersp();
					mainplayer.decreaseplayersp();
					piercingeyeeffect = true;
					cout << "Used Piercing Eye!" << endl;
				}
				else{
					cout << "You haven't enough SP left to perform this move!" << endl;
				}
				break;
			case '2' :
				if(mainplayer.saysp() >= 5){
					mainplayer.decreaseplayersp();
					mainplayer.decreaseplayersp();
					mainplayer.decreaseplayersp();
					mainplayer.decreaseplayersp();
					mainplayer.decreaseplayersp();
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
				if(mainplayer.saymp() >= 6){
					mainplayer.meditateused();
					mainplayer.limitplayerlife();
				}
				else{
					cout << "You haven't enough MP left to perform this move!" << endl;
				}
				break;
			case '2' :
				if(mainplayer.saymp() >= 4){
					commonenemy.fireattacked();
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
			mainplayer.playerattacked();
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
		cout << "Welcome to Tactical Alpha 1.0!" << endl;
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
			start = true;
			battle();
			break;
		}
		clear();
	}
	return 0;
}

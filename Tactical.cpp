#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>
#include "player.h"
#include "dialogues.h"
#include "weapons.h"

using namespace std;

bool start;

void enemy::enemyattacked(){
	if(damagepilleffect == false){
		if(subcriticalcheckerone <= mainplayer.saycriticalchecker()){
			cout << "\a";
			enemylife -= mainplayer.saycriticalpower();
			enemylife -= weapons.sayattack();
			cout << playername;
			printf(" made a critical hit, causing %d damage!\n",mainplayer.saycriticalpower() + weapons.sayattack());
		}
		else{
			enemylife -= mainplayer.attackparameter();
			enemylife -= weapons.sayattack();
			cout << playername;
			cout << " inflicted ";
			cout << mainplayer.attackparameter() + weapons.sayattack();
			cout << " to the enemy" << endl;
		}
	}
	if(damagepilleffect == true){
		if(subcriticalcheckerone <= mainplayer.saycriticalchecker()){
			cout << "\a";
			enemylife -= mainplayer.saycriticalpower();
			enemylife -= weapons.sayattack();
			cout << playername;
			printf(" made a critical hit, causing %d damage!\n",mainplayer.saycriticalpower() + weapons.sayattack());
		}
		else{
			enemylife -= mainplayer.attackparameter() + weapons.sayattack();
			enemylife -= 10;
			cout << playername;
			printf(" inflicted %d damage to the enemy\n",mainplayer.attackparameter() + weapons.sayattack() + 10);
		}
	}
}

void randomseed(){
	t = clock();
	if(t >= 10000){
		t-=9999;
	}
	seed = t;
	srand(seed);
}

void enemy::randomizetype(){
	enemytype = rand() % 7 + 1;
}

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

void equipment(){
	cout << "Melee weapon: ";
	if(weapons.sayattack1equipped() == 1){
		cout << "Tennis Racket [3 AT]" << endl;
	}
	cout << endl << "Type any key to go back to the battle menu" << endl;
	cin >> movement;
	switch(movement){
	default:;
	}
}

void battlemenu(){
	if(commonenemy.saytype() == 1){
		cout << "Grass ";
	}
	if(commonenemy.saytype() == 2){
		cout << "Normal ";
	}
	if(commonenemy.saytype() == 3){
		cout << "Dark ";
	}
	if(commonenemy.saytype() == 4){
		cout << "Light ";
	}
	if(commonenemy.saytype() == 5){
		cout << "Fire ";
	}
	if(commonenemy.saytype() == 6){
		cout << "Water ";
	}
	if(commonenemy.saytype() == 7){
		cout << "Ice ";
	}
	cout << "Human" << endl;
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
			cout << "[Darkness (x1.5)] [Fire (x1.5)] [Ice (x1.5)] " << endl;
		}
		if(commonenemy.saytype() == 2){
			cout << "[Darkness (x1.5)] [Fire (x1.5)]" << endl;
		}
		if(commonenemy.saytype() == 3){
			cout << "[Light (x1.5)] [Fire (x1.5)]" << endl;
		}
		if(commonenemy.saytype() == 4){
			cout << "[Darkness (x1.5)] [Water (x1.5)] [Grass (x1.5)]" << endl;
		}
		if(commonenemy.saytype() == 5){
			cout << "[Darkness (x1.5)] [Water (x2)]" << endl;
		}
		if(commonenemy.saytype() == 6){
			cout << "[Ice (x1.5)] [Grass (x2)]" << endl;
		}
		if(commonenemy.saytype() == 7){
			cout << "[Water (x1.5)] [Fire (x1.5)]" << endl;
		}
	}
	printf("Effects = ");
	if(piercingeyeeffect == true){
		cout << "Piercing Eye\n" << endl;
	}
	if(piercingeyeeffect == false){
		cout << "None\n" << endl;
	}
	cout << playername << endl;
	cout << "Life = " << mainplayer.saylife() << "/" << mainplayer.saymaxlife();
	cout << " | SP = " << mainplayer.saysp() << "/" << mainplayer.saymaxsp();
	cout << " | MP = " << mainplayer.saymp() << "/" << mainplayer.saymaxmp() << endl;
	cout << "Attack = " << mainplayer.attackparameter() << " + " << weapons.sayattack();
	cout << " | ";
	cout << "Magic attack = " << mainplayer.saymagicattack();
	cout << " | Ranged attack = " << mainplayer.sayrangedattack();
	cout << " | Defense = " << mainplayer.saydefense() << endl;
	cout << "Resistance = " << mainplayer.sayresistance() << "/" << mainplayer.saymaxresistance() << endl;
	cout << "Ultra meter = " << mainplayer.sayultra() << endl;
	cout << "Effects = ";
	if(damagepilleffect == true){
		cout << "[Damage Pill] " << endl;
	}
	else{
		cout << "None" << endl;
	}
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
	printf("\n[1] Attack\n");
	printf("[2] Items\n");
	printf("[3] Special\n");
	printf("[4] Magic\n");
	printf("[5] Move\n");
	printf("[6] Rest\n");
	if(mainplayer.sayultra() >= 100){
		cout << "[7] ULTRA" << endl;
	}
	printf("[p] Equipment & Options\n");
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
	randomseed();
	commonenemy.randomizetype();
	while(1){

STARTBATTLE:

		mainplayer.determinecriticalpower();
		commonenemy.determinecriticalpower();
		weapons.determineattack();

		randomseed();

		escapebattle();
		victory();
		defeat();

		battlemenu();

		if(distanceenemy == 1 || distanceenemy == 2){
			successfulhit = true;
			successfulhit2 = true;
		}
		if(distanceenemy == 3 || distanceenemy == 4 || distanceenemy == 5){
			successfulhit = false;
			successfulhit2 = false;
		}

		cin >> movement;

		switch(movement){
		case '5':
		case '1':
			break;
		default :
			clear();
			break;
		}

		switch(movement){
		case '1':
			subcriticalcheckerone = rand() % 100;
			cout << "Do you want to use your melee weapon [1] or your ranged weapon? [2]" << endl;
			cin >> movement;
			clear();
			switch(movement){
			case '1' :
				if(successfulhit == true && mainplayer.sayresistance() >= 2){
					commonenemy.enemyattacked();
					mainplayer.decreaseresistance();
					mainplayer.decreaseresistance();
					mainplayer.increaseultrar();
				}
				else{
					if(mainplayer.sayresistance() < 2){
						cout << "You are too tired to perform that move!" << endl;
					}
					else{
						cout << "You are too far from the enemy to perform that move!" << endl;
					}
				}
				break;
			case '2' :
				if(mainplayer.sayresistance() >= 1){
					commonenemy.rangedattacked();
					mainplayer.decreaseresistance();
					mainplayer.increaseultra();
				}
				else{
					cout << "You are too tired to perform that move!" << endl;
				}
				break;
			default : goto STARTBATTLE;break;
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
				if(mainplayer.saysp() >= 2 && mainplayer.sayresistance() >= 3){
					mainplayer.decreaseplayersp();
					mainplayer.decreaseplayersp();
					mainplayer.decreaseresistance();
					mainplayer.decreaseresistance();
					mainplayer.decreaseresistance();
					piercingeyeeffect = true;
					cout << "Used Piercing Eye!" << endl;
				}
				else{
					if(mainplayer.sayresistance() < 3){
						cout << "You are too tired to perform that move!" << endl;
					}
					else{
						cout << "You haven't enough SP left to perform this move!" << endl;
					}
				}
				break;
			case '2' :
				if(mainplayer.saysp() >= 5 && mainplayer.sayresistance() >= 3){
					mainplayer.decreaseplayersp();
					mainplayer.decreaseplayersp();
					mainplayer.decreaseplayersp();
					mainplayer.decreaseplayersp();
					mainplayer.decreaseplayersp();
					mainplayer.decreaseresistance();
					mainplayer.decreaseresistance();
					mainplayer.decreaseresistance();
					piercingeyeeffect = true;
					cout << "Used Quick Eye!\n" << endl;
					goto STARTBATTLE;
					break;
				}
				else{
					if(mainplayer.sayresistance() < 3){
						cout << "You are too tired to perform that move!" << endl;
					}
					else{
						cout << "You haven't enough SP left to perform this move!" << endl;
					}
				}
				break;
			default : goto STARTBATTLE;
				}
			break;
		case '5' :
			cout << "Do you want to move towards the enemy [1] or away from the enemy? [2]" << endl;
			cin >> movement;
			clear();
			switch(movement){
			case '1' :
				if(distanceenemy == 1){
					cout << "You can't get closer to the enemy!" << endl;
				}
				else{
					if(mainplayer.sayresistance() >= 3){
						distanceenemy--;
						cout << "Got closer to the enemy" << endl;
						mainplayer.decreaseresistance();
						mainplayer.decreaseresistance();
						mainplayer.decreaseresistance();
					}
					else{
						cout << "You are too tired to move!" << endl;
					}
				}
				break;
			case '2' :
				if(distanceenemy == 5 && mainplayer.sayresistance() >= 3){
					runawayfrombattle = true;
					mainplayer.decreaseresistance();
					mainplayer.decreaseresistance();
					mainplayer.decreaseresistance();
					goto STARTBATTLE;
				}
				if(distanceenemy == 5 && mainplayer.sayresistance() < 3){
					cout << "You are too tired to escape!" << endl;
				}
				if(distanceenemy < 5 && mainplayer.sayresistance() < 3){
					cout << "You are too tired to move!" << endl;
				}
				if(distanceenemy < 5 && mainplayer.sayresistance() >= 3){
					distanceenemy++;
					cout << "Moved a bit away from the enemy" << endl;
					mainplayer.decreaseresistance();
					mainplayer.decreaseresistance();
					mainplayer.decreaseresistance();
				}
				break;
			default : goto STARTBATTLE;break;
			}
			break;
		case '4' :
			printf("List of Magic learned:\n\n");
			printf("Meditate [6 MP]['1' to use]\n");
			printf("-- Heals the player by 60 life points\n");
			printf("Ice [3 MP]['2' to use]\n");
			printf("-- Harms the enemy using the Ice Element\n");
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
				if(mainplayer.saymp() >= 3){
					commonenemy.iceattacked();
				}
				else{
					cout << "You haven't enough MP left to perform this move!" << endl;
				}
				break;
			default :
				goto STARTBATTLE;
			}
			break;
		case '6' :
			mainplayer.increaseresistance();
			mainplayer.increaseresistance();
			mainplayer.increaseresistance();
			mainplayer.limitresistance();
			cout << "That was a good rest! Resistance +3 points" << endl;
			break;
		case '7' :
			if(mainplayer.sayultra() >= 100){
				cout << "List of Ultra Attacks:" << endl << endl;
				cout << "-Ultra kick in the nuts [WEAK][100 Ultra | 20 Resistance]['1' to use]" << endl << endl;
				cout << "Type any other key to go back to the battle menu" << endl;
				cin >> movement;
				clear();
				switch(movement){
					case '1' :
						if(mainplayer.sayresistance() >= 20){
							commonenemy.receivedultra();
							mainplayer.decreasetenresistance();
							mainplayer.decreasetenresistance();
						}
						else{
							cout << "You are too tired to perform that ultra!" << endl;
						}
						break;
					default :
						goto STARTBATTLE;
				}
			}
			else{
				cout << "Skipped the turn" << endl;
			}
			break;
		case 'p' : equipment();goto STARTBATTLE;break;
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
		subcriticalcheckertwo = rand() % 100;
		if(successfulhit2 == true){
			mainplayer.playerattacked();
		}
		else{
			cout << "The enemy got closer to " << playername << endl << endl;
			distanceenemy--;
		}

		mainplayer.increaseultra();
		mainplayer.limitultra();
	}
}


int main(){
	// Inicio del programa, se le pregunta al jugador el nombre del main character
	randomseed();
	while(1){
		cout << "Welcome to Tactical Alpha 1.2!" << endl;
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

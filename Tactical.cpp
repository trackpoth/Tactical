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

int eventtype;
int eventgenerator;

int shoptype;
int shopsubtype;
float shopvalue;
int shopitema;
int shopitemb;
int shopitemc;
int shopitemd;

void enemy::enemyattacked(){
	if(damagepilleffect == false){
		if(subcriticalcheckerone <= mainplayer.saycriticalchecker()){
			cout << "\a";
			enemylife -= mainplayer.saycriticalpower();
			enemylife -= weapons.sayrealattack();
			enemylife += enemydefense;
			cout << playername;
			printf(" made a critical hit, causing %d damage!\n",mainplayer.saycriticalpower() + weapons.sayrealattack() - enemydefense);
		}
		else{
			enemylife -= mainplayer.attackparameter();
			enemylife -= weapons.sayrealattack();
			enemylife += enemydefense;
			cout << playername;
			cout << " inflicted ";
			printf("%d",mainplayer.attackparameter() + weapons.sayrealattack() - enemydefense);
			cout << " to the enemy" << endl;
		}
	}
	if(damagepilleffect == true){
		if(subcriticalcheckerone <= mainplayer.saycriticalchecker()){
			cout << "\a";
			enemylife -= mainplayer.saycriticalpower();
			enemylife -= weapons.sayrealattack();
			enemylife += enemydefense;
			cout << playername;
			printf(" made a critical hit, causing %d damage!\n",mainplayer.saycriticalpower() + weapons.sayrealattack() - enemydefense);
		}
		else{
			enemylife -= mainplayer.attackparameter();
			enemylife -= weapons.sayrealattack();
			enemylife += enemydefense;
			enemylife -= 10;
			cout << playername;
			printf(" inflicted %d damage to the enemy\n",mainplayer.attackparameter() + weapons.sayrealattack() + 10 - enemydefense);
		}
	}
}

void enemy::rangedattacked(){
	if(damagepilleffect == false){
		if(subcriticalcheckerone <= mainplayer.saycriticalchecker()){
			cout << "\a";
			enemylife -= mainplayer.sayrangedattack();
			enemylife -= rangedweapon.sayrealattack();
			enemylife -= 10;
			enemylife += enemydefense;
			cout << playername;
			printf(" made a critical hit, causing %d damage!\n",mainplayer.sayrangedattack() + rangedweapon.sayrealattack() + 10 - enemydefense);
		}
		else{
			enemylife -= mainplayer.sayrangedattack();
			enemylife -= rangedweapon.sayrealattack();
			enemylife += enemydefense;
			cout << playername;
			cout << " inflicted ";
			cout << mainplayer.sayrangedattack() + rangedweapon.sayrealattack() - enemydefense;
			cout << " to the enemy" << endl;
		}
	}
	if(damagepilleffect == true){
		if(subcriticalcheckerone <= mainplayer.saycriticalchecker()){
			cout << "\a";
			enemylife -= mainplayer.sayrangedattack();
			enemylife -= rangedweapon.sayrealattack();
			enemylife += enemydefense;
			enemylife -= 10;
			enemylife -= 10;
			cout << playername;
			printf(" made a critical hit, causing %d damage!\n",mainplayer.sayrangedattack() + rangedweapon.sayrealattack() + 20 - enemydefense);
		}
		else{
			enemylife -= mainplayer.sayrangedattack();
			enemylife -= rangedweapon.sayrealattack();
			enemylife += enemydefense;
			enemylife -= 10;
			cout << playername;
			printf(" inflicted %d damage to the enemy\n",mainplayer.sayrangedattack() + rangedweapon.sayrealattack() + 10 - enemydefense);
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

void player::shop(){
	cout << "You see a shop near you" << endl;
	_getch();
	randomseed();
	cout << "It's a Small Item Shop!" << endl;
	shopsubtype = 1;
	if(shopsubtype = 1){
		shopvalue = 1.5;
	}
	_getch();
	randomseed();
	clear();
SHOP:
	cout << "Small Item Shop" << endl;
	cout << "Squares = " << squares << endl << endl;
	cout << "Small Health Pill" << endl;
	cout << "-" << smallhealthpillworth * shopvalue << " Squares/ud | In your pocket: " << smallhealthpill << endl;
	cout << "--Heals " << smallhealthpillvalue << " life points" << endl << endl;
	cout << "Damage Pill" << endl;
	cout << "-" << damagepillworth * shopvalue << " Squares/ud | In your pocket: " << damagepill << endl;
	cout << "--Adds 10 AT / MAT until the end of the battle" << endl;
	cout << endl << "Type '1' to buy item 1" << endl;
	cout << "Type '2' to buy item 2" << endl;
	cout << "Type any other key to leave the shop" << endl;
	cin >> movement;
	clear();
	switch(movement){
	case '1' :
		if(squares >= smallhealthpillworth * shopvalue){
			squares -= smallhealthpillworth * shopvalue;
			smallhealthpill++;
			goto SHOP;
		}
		else{
			cout << "You haven't enough squares to buy that item!" << endl << endl;
			goto SHOP;
		}
		break;
	case '2' :
		if(squares >= damagepillworth * shopvalue){
			squares -= damagepillworth * shopvalue;
			damagepill++;
			goto SHOP;
		}
		else{
			cout << "You haven't enough squares to buy that item!" << endl << endl;
			goto SHOP;
		}
		break;
	default :
		cout << "Exit the shop? [1] Yes [Any other key] No" << endl;
		cin >> movement;
		clear();
		switch(movement){
			case '1' : break;
			default : goto SHOP;
		}
	}
}

void enemy::randomizetype(){
	enemytype = rand() % 7 + 1;
}

void enemy::randomizeparameters(){
	enemymaxlife += rand() % 35 + 2;
	enemyattack += rand() % 3 + 1;
	enemydefense += rand() % 3;
	enemylife = enemymaxlife;
}

void weapon::determinerealattack(){
	realattack = (attack * mainplayer.attackparameter());
}

void ranged::determinerealattack(){
	realattack = (attack * mainplayer.sayrangedattack());
}

void player::determinemaxsp(){
	playermaxsp = (playermaxspbase + rangedweapon.saysp1());
}

void defeat(){
	mainplayer.defeatchecker();
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
	if(mainplayer.saysmallhealthpill() > 0){
		printf("Small Health Pill x%d [1 to use]\n",mainplayer.saysmallhealthpill());
		cout << "-Heals " << mainplayer.saysmallhealthpillvalue() << " life points" << endl;
	}
	if(mainplayer.saydamagepill() > 0){
		printf("Damage Pill x%d [2 to use]\n",mainplayer.saydamagepill());
		cout << "-Adds 10 AT / MAT until the end of the battle" << endl;
	}
	if(mainplayer.saysmallhealthpill() <= 0 && mainplayer.saydamagepill() <= 0){
		cout << "No items in the bag!" << endl;
	}
	printf("\nType any other key to go back to the main menu and skip the turn\n");
	cin >> movement;
	clear();
	switch(movement){
	case '1' :
		if(mainplayer.saysmallhealthpill() > 0){
			mainplayer.smallhealthpilltaken();
			mainplayer.limitplayerlife();
		}
		else{
			printf("Closed the item bag without using items\n");
		}
		break;
	case '2' :
		if(mainplayer.saydamagepill() > 0){
			mainplayer.damagepilltaken();
		}
		else{
			cout << "Closed the item bag without using items" << endl;
		}
		break;
	default : cout << "Closed the item bag without using items" << endl;
	}
}

void equipment(){
	cout << "Melee weapon: ";
	if(weapons.sayattack1equipped() == 1){
		cout << "Tennis Racket [2% +AT]" << endl;
	}
	cout << "Ranged weapon: ";
	if(rangedweapon.sayattack1equipped() == 1){
		cout << "Bullshot [2% +RAT][+1 SP]" << endl;
	}
	cout << endl << "Sector = " << section << endl;
	cout << "Zone = " << zone << endl;
	cout << endl << "Squares = " << mainplayer.saysquares() << endl;
	cout << endl << "Type 't' to enter the parameter upgrading center" << endl;
	cout << "Type any key to go back to the menu" << endl;
	cin >> movement;
	clear();
	switch(movement){
	case 't' :
		mainplayer.upgrading();
	default:;
	}
}

void traveling(){
TRAVELING:
	clear();
	randomseed();
	cout << "Where do you want to go? Northwest [1], North [2] or Northeast? [3]" << endl;
	// northwest = most efficient while searching safe places & shops, but also bosses can be found more often
	// north = default, everything can happen
	// northeast = most efficient while searching enemies and bosses, better loot
	cout << "[4] Equipment & stats" << endl;
	cin >> movement;
	clear();
	zone++;
	if(zone > 10){
		section++;
		zone = 1;
	}
	switch(movement){
	case '1' :
		cout << "Heading west..." << endl;
		Sleep(1000);
		eventgenerator = 1;
		break;
	case '2' :
		cout << "Heading north..." << endl;
		Sleep(1000);
		eventgenerator = 2;
		break;
	case '3' :
		cout << "Heading east..." << endl;
		Sleep(1000);
		eventgenerator = 3;
		break;
	case '4' :
		equipment();
		goto TRAVELING;
	default : clear();goto TRAVELING;
	}
	randomseed();
	travel = rand() % 101;
	if(eventgenerator == 1){
		if(travel >= 0 && travel <= 65){
			eventtype = 1;
		}
		if(travel >= 66 && travel <= 100){
			eventtype = 2;
		}
	}
	if(eventgenerator == 2){
		if(travel >= 0 && travel <= 85){
			eventtype = 1;
		}
		if(travel >= 86 && travel <= 100){
			eventtype = 2;
		}
	}
	if(eventgenerator == 3){
		if(travel >= 0 && travel <= 90){
			eventtype = 1;
		}
		if(travel >= 91 && travel <= 100){
			eventtype = 2;
		}
	}
	// eventype 1 = battle
	// eventype 2 = shop
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
		printf("AT = %d | DEF = %d\n",commonenemy.sayattack(),commonenemy.saydefense());
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
	cout << "AT = " << mainplayer.attackparameter() << " + " << weapons.sayattack() * 100 << "%";
	cout << " | ";
	cout << "MAT = " << mainplayer.saymagicattack();
	cout << " | RAT = " << mainplayer.sayrangedattack() << " + " << rangedweapon.sayattack() * 100 << "%";
	cout << " | DEF = " << mainplayer.saydefense() << endl;
	cout << "Resistance = " << mainplayer.sayresistance() << "/" << mainplayer.saymaxresistance() << " | ";
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
	printf("[p] Other\n");
}

void enemy::victorychecker(){
	if(enemylife <= 0){
		damagepilleffect = false;
		piercingeyeeffect = false;
		randomseed();
		clear();
		if(firstbattle == false){
			cout << playername;
			cout << " won the battle!\a" << endl;
		}
		if(firstbattle == true){
			cout << "Hippie: Wow, that did hurt!" << endl;
			_getch();
			cout << "You: What in the heavens were you doing?" << endl;
			_getch();
			cout << "Hippie: I was looking for my Hypercube" << endl;
			_getch();
			cout << "You: Your what!?" << endl;
			_getch();
			cout << "Hippie: You don't know what's an Hypercube, don't you?" << endl;
			_getch();
			cout << "Hippie: It's a cube with 4 dimensions, but I think someone stole it" << endl;
			_getch();
			cout << "You: (...)" << endl;
			_getch();
			cout << "Hippie: Can you find the thief?" << endl;
			_getch();
			cout << "You: Yeah, why not. I'll look for the imaginary cube of a guy I've just met" << endl;
			_getch();
			cout << "Hippie: Thank you! I think he went that way!" << endl;
			_getch();
			cout << "You: Oh my god..." << endl;
			_getch();
			cout << endl << "(As he finishes and goes down the hill, you start thinking)" << endl;
			_getch();
			cout << "You: Maybe... if the Hypercube is real...  and if I find it... " << endl;
			_getch();
			cout << "You: I would be able to go to the fourth dimension..." << endl;
			_getch();
			cout << "You: In the fourth dimension everything should be one dimension higher..." << endl;
			_getch();
			cout << "You: So if I bring my Game Box... I would be able to play teetrix in 3D!" << endl;
			_getch();
			cout << "You: Wow! That would be AWESOME!" << endl;
			_getch();
			cout << "You: Okay! I'll do it! Hypercube, I'll find you!" << endl;
			_getch();
			cout << "You: But where do I go?" << endl;
			_getch();
			firstbattle = false;
		}
		_getch();
		randomseed();
		mainplayer.randomtpincrease();
		cout << endl << playername << "'s Train Points were increased by " << mainplayer.saytpincrease() << "!" << endl;
		cout << playername << "'s Squares were increased by " << mainplayer.saysquaresincrease() << "!" << endl;
		_getch();
		clear();
		traveling();
	}
}

void battle(){
EVENT:
	clear();
	if(start == true){
		cout << "Name applied correctly" << endl;
	}
	cout << "Press always any key to show the next lines of text" << endl << endl;
	if(start == true){
		dialogue = 1;
		dialogues();
		clear();
		randomseed();
		commonenemy.randomizetype();
		commonenemy.randomizeparameters();
		start = false;
	}
	else{

		if(eventtype == 1){
			dialogue = 0;
			dialogues();
		}
		if(eventtype == 2){
			mainplayer.shop();
			traveling();
			goto EVENT;
		}
		clear();
		if(dialogue == 0){
			randomseed();
			commonenemy.randomizetype();
			commonenemy.randomizeparameters();
			commonenemy.restoreparameters();
		}
	}
	while(1){

STARTBATTLE:

		mainplayer.determinecriticalpower();
		commonenemy.determinecriticalpower();
		weapons.determineattack();
		weapons.determinerealattack();
		rangedweapon.determineattack();
		rangedweapon.determinerealattack();
		mainplayer.determinemaxsp();

		randomseed();

		escapebattle();
		defeat();
		commonenemy.victorychecker();
		if(commonenemy.saylife() <= 0){
			goto EVENT;
		}

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
			printf("Quick eye [4 SP]['2' to use]\n");
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
				if(mainplayer.saysp() >= 4 && mainplayer.sayresistance() >= 3){
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
			printf("Meditate [5 MP]['1' to use]\n");
			printf("-- Heals the player by 60 life points\n");
			printf("Ice [3 MP]['2' to use]\n");
			printf("-- Harms the enemy using the Ice Element\n");
			printf("\nType any other key to go back to the main menu\n");
			cin >> movement;
			clear();
			switch(movement){
			case '1' :
				if(mainplayer.saymp() >= 5){
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
			mainplayer.increaseresistance();
			mainplayer.increaseresistance();
			mainplayer.increaseresistance();
			mainplayer.increaseplayersp();
			cout << "That was a good rest! Stats recovered a little bit" << endl;
			break;
		case '7' :
			if(mainplayer.sayultra() >= 100){
				cout << "List of Ultra Attacks:" << endl << endl;
				cout << "-Ultra kick in the nuts [WEAK][100 Ultra | 10 Resistance]['1' to use]" << endl;
				cout << "--Causes relatively high damage with low ultra and resistance requirements" << endl;
				cout << endl << "Type any other key to go back to the battle menu" << endl;
				cin >> movement;
				clear();
				switch(movement){
					case '1' :
						if(mainplayer.sayresistance() >= 10){
							commonenemy.receivedultra();
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
		mainplayer.limitresistance();
		mainplayer.limitplayerlife();
		mainplayer.limitsp();
		commonenemy.limitlife();
	}
}


int main(){
	// Inicio del programa, se le pregunta al jugador el nombre del main character
	randomseed();
	while(1){
		cout << "Welcome to Tactical Alpha 1.4!" << endl;
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

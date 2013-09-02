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

// Funciones de alta importancia que pueden ser llamadas desde cualquier parte del programa

void gotoxy( int column, int line )
{
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

void randomseed(){
	t = clock();
	if(t >= 10000){
		t-=9999;
	}
	seed = t;
	srand(seed);
}

void itemmenu(){
	cout << playername << "'s life: " << mainplayer.saylife() << "/" << mainplayer.saymaxlife() << endl << endl;
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
	cout << "Shields: ";
	if(playershields.sayshield1equipped() == 1){
		cout << "Full Cracked Shield [10 SH][2 RT]" << endl;
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
	cout << "Where do you want to go? Northwest [1], North [2] or Northeast? [3]" << endl << endl;
	cout << "Northwest = More shops, more bosses" << endl;
	cout << "North     = Anything can happen" << endl;
	cout << "Northeast = More enemies" << endl;
	cout << endl << "[4] Equipment & stats" << endl;
	cout << "[5] Item bag" << endl;
	cin >> movement;
	clear();
	switch(movement){
	case '1' :
		cout << "Heading northwest..." << endl;
		Sleep(1000);
		eventgenerator = 1;
		break;
	case '2' :
		cout << "Heading north..." << endl;
		Sleep(1000);
		eventgenerator = 2;
		break;
	case '3' :
		cout << "Heading northeast..." << endl;
		Sleep(1000);
		eventgenerator = 3;
		break;
	case '4' :
		equipment();
		goto TRAVELING;
	case '5' :
		itemmenu();
		goto TRAVELING;
	default : clear();goto TRAVELING;
	}
	zone++;
	if(zone > 10){
		section++;
		zone = 1;
	}
	randomseed();
	travel = rand() % 101;
	if(eventgenerator == 1){

		// 1: 55%  2: 35%  3: 10%
		if(travel >= 0 && travel <= 55){
			eventtype = 1;
		}
		if(travel >= 56 && travel <= 90){
			eventtype = 2;
		}
		if(travel >= 91 && travel <= 100){
			eventtype = 3;
		}
	}
	if(eventgenerator == 2){

		// 1: 75%  2: 20%  3: 5%
		if(travel >= 0 && travel <= 75){
			eventtype = 1;
		}
		if(travel >= 76 && travel <= 95){
			eventtype = 2;
		}
		if(travel >= 96 && travel <= 100){
			eventtype = 3;
		}
	}
	if(eventgenerator == 3){

		// 1: 75%  2: 5%  3: 20%
		if(travel >= 0 && travel <= 75){
			eventtype = 1;
		}
		if(travel >= 76 && travel <= 80){
			eventtype = 2;
		}
		if(travel >= 81 && travel <= 100){
			eventtype = 3;
		}
	}
	// eventype 1 = battle
	// eventype 2 = shop
	// eventype 3 = boss
}



// Funciones procedentes de clases

void player::determinemaxshields(){
	if(playershields.sayshield1equipped() == true){
		maxshields = playershields.saymaxshield1();
		rechargerate = playershields.sayrecharge1();
	}
}

void player::playerattacked(){

	movementint = rand() % 101;

	// 1: 50%  2: 45%  3: 5%
	if(commonenemy.sayint() == 1){
		if(movementint >= 0 && movementint <= 50){
			movementfinal = 1;
		}
		if(movementint >= 51 && movementint <= 95){
			movementfinal = 2;
		}
		if(movementint >= 96 && movementint <= 100){
			movementfinal = 3;
		}
	}

	// 1: 35%  2: 55%  3: 10%
	if(commonenemy.sayint() == 2){
		if(movementint >= 0 && movementint <= 35){
			movementfinal = 1;
		}
		if(movementint >= 36 && movementint <= 90){
			movementfinal = 2;
		}
		if(movementint >= 91 && movementint <= 100){
			movementfinal = 3;
		}
	}

	// 1: 15%  2: 65%  3: 20%
	if(commonenemy.sayint() == 3){
		if(movementint >= 0 && movementint <= 15){
			movementfinal = 1;
		}
		if(movementint >= 16 && movementint <= 80){
			movementfinal = 2;
		}
		if(movementint >= 81 && movementint <= 100){
			movementfinal = 3;
		}
	}

	// 1: 5%  2: 55%  3: 40%
	if(commonenemy.sayint() == 4){
		if(movementint >= 0 && movementint <= 5){
			movementfinal = 1;
		}
		if(movementint >= 6 && movementint <= 60){
			movementfinal = 2;
		}
		if(movementint >= 61 && movementint <= 100){
			movementfinal = 3;
		}
	}

	// 2: 25%  3: 75%
	if(commonenemy.sayint() == 5){
		if(movementint >= 0 && movementint <= 25){
			movementfinal = 2;
		}
		if(movementint >= 26 && movementint <= 100){
			movementfinal = 3;
		}
	}

	// movementfinal == 1: No hace nada
	// movementfinal == 2: Ataca físicamente acercándose si está muy lejos
	// movementfinal == 3: Mira su vida actual y si es demasiado baja usa un objeto curativo, si no es así tiene el mismo efecto que movementfinal 2.
ATTACK:
	if(movementfinal == 1){
		cout << "The enemy doesn't do anything!" << endl << endl;
	}

	if(movementfinal == 2){
		if(successfulhit2 == true){
			subcriticalcheckertwo = rand() % 101;

			// El enemigo ejecuta un ataque físico

			if(subcriticalcheckertwo <= commonenemy.saycriticalchecker()){

				// Crítico defensa superior a ataque
				if(playerdefense >= commonenemy.saycriticalpower()){
					if(shields > 0){
						shields -= 1;
					}
					else{
						playerlife -= 1;
					}
					printf("You only took 1 damage because of your high defense!\n\n");
				}

				// Crítico defensa inferior a ataque
				else{
					if(shields > 0){
						shields -= commonenemy.saycriticalpower();
						shields += playerdefense;
						if(shields <= 0){
							playerlife += shields;
							shields = 0;
						}
					}
					else{
						playerlife -= commonenemy.saycriticalpower();
						playerlife += playerdefense;
					}
					printf("The enemy made a critical hit, causing %d damage!\n\n",commonenemy.saycriticalpower() - mainplayer.saydefense());
				}
			}
			else{

				// Normal defensa superior a ataque
				if(playerdefense >= commonenemy.sayattack()){
					if(shields > 0){
						shields -= 1;
					}
					else{
						playerlife -= 1;
					}
					printf("You only took 1 damage because of your high defense!\n\n");
				}

				// Normal defensa inferior a ataque
				else{
					if(shields > 0){
						shields -= commonenemy.sayattack();
						shields += playerdefense;
						if(shields <= 0){
							playerlife += shields;
							shields = 0;
						}
					}
					else{
						playerlife -= (commonenemy.sayattack() - playerdefense);
					}
					printf("The enemy inflicted %d damage\n\n",commonenemy.sayattack() - mainplayer.saydefense());
				}
			}
		}
		else{
			cout << "The enemy got closer to " << playername << endl << endl;
			distanceenemy--;
		}
	}

	if(movementfinal == 3){
		if(commonenemy.saylife() <= commonenemy.saymaxlife() * 0.3 && commonenemy.sayhealthdrink() == true){
			commonenemy.healthdrinktaken();
			cout << "The enemy used a Health Drink!" << endl << endl;
		}
		else{
			movementfinal = 2;
			goto ATTACK;
		}
	}
}

void player::playerattackedboss(){

	movementint = rand() % 101;

	// 1: 50%  2: 45%  3: 5%
	if(boss.sayint() == 1){
		if(movementint >= 0 && movementint <= 50){
			movementfinal = 1;
		}
		if(movementint >= 51 && movementint <= 95){
			movementfinal = 2;
		}
		if(movementint >= 96 && movementint <= 100){
			movementfinal = 3;
		}
	}

	// 1: 35%  2: 55%  3: 10%
	if(boss.sayint() == 2){
		if(movementint >= 0 && movementint <= 35){
			movementfinal = 1;
		}
		if(movementint >= 36 && movementint <= 90){
			movementfinal = 2;
		}
		if(movementint >= 91 && movementint <= 100){
			movementfinal = 3;
		}
	}

	// 1: 15%  2: 65%  3: 20%
	if(boss.sayint() == 3){
		if(movementint >= 0 && movementint <= 15){
			movementfinal = 1;
		}
		if(movementint >= 16 && movementint <= 80){
			movementfinal = 2;
		}
		if(movementint >= 81 && movementint <= 100){
			movementfinal = 3;
		}
	}

	// 1: 5%  2: 55%  3: 40%
	if(boss.sayint() == 4){
		if(movementint >= 0 && movementint <= 5){
			movementfinal = 1;
		}
		if(movementint >= 6 && movementint <= 60){
			movementfinal = 2;
		}
		if(movementint >= 61 && movementint <= 100){
			movementfinal = 3;
		}
	}

	// 2: 25%  3: 75%
	if(boss.sayint() == 5){
		if(movementint >= 0 && movementint <= 25){
			movementfinal = 2;
		}
		if(movementint >= 26 && movementint <= 100){
			movementfinal = 3;
		}
	}

	// movementfinal == 1: No hace nada
	// movementfinal == 2: Ataca físicamente acercándose si está muy lejos
	// movementfinal == 3: Mira su vida actual y si es demasiado baja usa un objeto curativo, si no es así tiene el mismo efecto que movementfinal 2.
ATTACK:
	if(movementfinal == 1){
		cout << "The enemy doesn't do anything!" << endl << endl;
	}

	if(movementfinal == 2){
		if(successfulhit2 == true){
			subcriticalcheckertwo = rand() % 101;

			// El enemigo ejecuta un ataque físico

			if(subcriticalcheckertwo <= boss.saycriticalchecker()){

				// Crítico defensa superior a ataque
				if(playerdefense >= boss.saycriticalpower()){
					if(shields > 0){
						shields -= 1;
					}
					else{
						playerlife -= 1;
					}
					printf("You only took 1 damage because of your high defense!\n\n");
				}

				// Crítico defensa inferior a ataque
				else{
					if(shields > 0){
						shields -= boss.saycriticalpower();
						shields += playerdefense;
						if(shields <= 0){
							playerlife += shields;
							shields = 0;
						}
					}
					else{
						playerlife -= boss.saycriticalpower();
						playerlife += playerdefense;
					}
					printf("The enemy made a critical hit, causing %d damage!\n\n",boss.saycriticalpower() - mainplayer.saydefense());
				}
			}
			else{

				// Normal defensa superior a ataque
				if(playerdefense >= boss.sayattack()){
					if(shields > 0){
						shields -= 1;
					}
					else{
						playerlife -= 1;
					}
					printf("You only took 1 damage because of your high defense!\n\n");
				}

				// Normal defensa inferior a ataque
				else{
					if(shields > 0){
						shields -= boss.sayattack();
						shields += playerdefense;
						if(shields <= 0){
							playerlife += shields;
							shields = 0;
						}
					}
					else{
						playerlife -= (boss.sayattack() - playerdefense);
					}
					printf("The enemy inflicted %d damage\n\n",boss.sayattack() - mainplayer.saydefense());
				}
			}
		}
		else{
			cout << "The enemy got closer to " << playername << endl << endl;
			distanceenemy--;
		}
	}

	if(movementfinal == 3){
		if(boss.saylife() <= boss.saymaxlife() * 0.3 && boss.sayhealthdrink() == true){
			boss.healthdrinktaken();
			cout << "The enemy used a Health Drink!" << endl << endl;
		}
		else{
			movementfinal = 2;
			goto ATTACK;
		}
	}
}

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
	enemyint = rand() % 3 + 1;
	healthdrink = rand() % 1;
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

void enemy::victorychecker(){
	if(enemylife <= 0 || runawayfrombattle == true){
		damagepilleffect = false;
		piercingeyeeffect = false;
		mainplayer.restoreshields();
		randomseed();
		clear();
		if(firstbattle == false && runawayfrombattle == false){
			cout << playername;
			cout << " won the battle!\a" << endl;
		}
		if(firstbattle == false && runawayfrombattle == true){
			cout << playername << " ran away!" << endl;
		}
		if(firstbattle == true && runawayfrombattle == false){
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
		if(firstbattle == true && runawayfrombattle == true){
			cout << "You run away as quickly as you can" << endl;
			_getch();
			cout << "THE END" << endl;
			_getch();
			cout << "(Maybe you shouldn't escape this battle...)" << endl;
			_getch();
			exit(0);
		}
		_getch();
		randomseed();
		if(runawayfrombattle == false){
			if(battletype == 1){
				mainplayer.randomtpincrease();
				cout << endl << playername << "'s Train Points were increased by " << mainplayer.saytpincrease() << "!" << endl;
				cout << playername << "'s Squares were increased by " << mainplayer.saysquaresincrease() << "!" << endl;
				_getch();
			}
			if(battletype == 2){
				mainplayer.randomtpincreaseboss();
				cout << endl << playername << "'s Train Points were increased by " << mainplayer.saytpincrease() << "!" << endl;
				cout << playername << "'s Squares were increased by " << mainplayer.saysquaresincrease() << "!" << endl;
				_getch();
				battletype = 1;
			}
		}
		clear();
		traveling();
	}
}



// Funciones normales

void defeat(){
	mainplayer.defeatchecker();
}

void escapebattle(){
	if(runawayfrombattle == true){
		damagepilleffect = false;
		piercingeyeeffect = false;
		runawayfrombattle = false;
		randomseed();
		clear();
		cout << playername;
		cout << " ran away!\a" << endl;
		_getch();
		clear();
		traveling();
	}
}

void battlemenu(){
	if(battletype == 1){
		commonenemy.saystats();
	}
	if(battletype == 2){
		boss.saystats();
	}
	cout << playername << endl;
	cout << "Life = " << mainplayer.saylife() << "/" << mainplayer.saymaxlife();
	if(mainplayer.sayshields() <= 0){
		mainplayer.increaserecharge();
		if(mainplayer.sayrechargemeter() >= 100){
			mainplayer.restoreshields();
		}
	}
	if(mainplayer.sayshields() <= 0){
		cout << " | Shields = Recharge: " << mainplayer.sayrechargemeter() << "%";
	}
	else{
		cout << " | Shields = " << mainplayer.sayshields() << "/" << mainplayer.saymaxshields();
	}
	cout << " | SP = " << mainplayer.saysp() << "/" << mainplayer.saymaxsp();
	cout << " | MP = " << mainplayer.saymp() << "/" << mainplayer.saymaxmp() << endl;
	cout << "AT = " << mainplayer.attackparameter() << " + " << weapons.sayattack() * 100 << "%";
	cout << " | ";
	cout << "MAT = " << mainplayer.saymagicattack();
	cout << " | RAT = " << mainplayer.sayrangedattack() << " + " << rangedweapon.sayattack() * 100 << "%";
	cout << " | DEF = " << mainplayer.saydefense() << endl;
	cout << "Resistance = " << mainplayer.sayresistance() << "/" << mainplayer.saymaxresistance() << " | ";
	cout << "Ultra meter = " << mainplayer.sayultra() <<  " | Distance = ";
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
	cout << "Effects = ";
	if(damagepilleffect == true){
		cout << "[Damage Pill] " << endl;
	}
	else{
		cout << "None" << endl;
	}
	printf("\n[q] Meelee attack [w] Ranged attack [e] Magic attack\n");
	printf("[2] Items         [3] Special       [4] Magic\n");
	printf("[5] Move          [6] Rest");
	if(mainplayer.sayultra() >= 100){
		cout << "          [7] Ultra";
	}
	printf("\n[p] Other\n");
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
		mainplayer.determinemaxshields();
		mainplayer.restoreshields();
		battletype = 1;
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
		if(eventtype == 3){
			dialogue = 2;
			dialogues();
		}
		clear();
		if(dialogue == 0){
			randomseed();
			commonenemy.randomizetype();
			commonenemy.randomizeparameters();
			commonenemy.restoreparameters();
			battletype = 1;
		}
		if(dialogue == 2){
			randomseed();
			boss.randomizeboss();
			battletype = 2;
		}
	}

if(battletype == 1){
	while(1){

STARTBATTLE:

		mainplayer.determinecriticalpower();
		commonenemy.determinecriticalpower();
		weapons.determineattack();
		weapons.determinerealattack();
		rangedweapon.determineattack();
		rangedweapon.determinerealattack();
		mainplayer.determinemaxshields();
		mainplayer.determinemaxsp();

		randomseed();

		defeat();
		commonenemy.victorychecker();
		if(commonenemy.saylife() <= 0 || runawayfrombattle == true){
			runawayfrombattle = false;
			distanceenemy = 3;
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

		// El jugador ejecuta su turno

		cin >> movement;

		switch(movement){
		case '5':
			break;
		default :
			clear();
			break;
		}

		switch(movement){
		case 'q':
			subcriticalcheckerone = rand() % 100;
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
		case 'w' :
			if(mainplayer.sayresistance() >= 1){
				commonenemy.rangedattacked();
				mainplayer.decreaseresistance();
				mainplayer.increaseultra();
			}
			else{
				cout << "You are too tired to perform that move!" << endl;
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
		case 'p' :
			equipment();
			goto STARTBATTLE;
			break;
		default:
			cout << "Skipped the turn" << endl;
			break;
		}

		if(distanceenemy == 1 || distanceenemy == 2){
			successfulhit = true;
			successfulhit2 = true;
		}
		if(distanceenemy == 3 || distanceenemy == 4 || distanceenemy == 5){
			successfulhit = false;
			successfulhit2 = false;
		}

		 // El enemigo ejecuta su turno
		mainplayer.playerattacked();


		mainplayer.increaseultra();
		mainplayer.limitultra();
		mainplayer.limitresistance();
		mainplayer.limitplayerlife();
		mainplayer.limitsp();
		commonenemy.limitlife();
	}
}
if(battletype == 2){
	while(1){

STARTBOSSBATTLE:

		mainplayer.determinecriticalpower();
		boss.determinecriticalpower();
		weapons.determineattack();
		weapons.determinerealattack();
		rangedweapon.determineattack();
		rangedweapon.determinerealattack();
		mainplayer.determinemaxshields();
		mainplayer.determinemaxsp();

		randomseed();

		defeat();
		boss.victorychecker();
		if(boss.saylife() <= 0 || runawayfrombattle == true){
			runawayfrombattle = false;
			distanceenemy = 3;
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

		// El jugador ejecuta su turno

		cin >> movement;

		switch(movement){
		case '5':
			break;
		default :
			clear();
			break;
		}

		switch(movement){
		case 'q':
			subcriticalcheckerone = rand() % 100;
			if(successfulhit == true && mainplayer.sayresistance() >= 2){
				boss.enemyattacked();
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
		case 'w' :
			if(mainplayer.sayresistance() >= 1){
				boss.rangedattacked();
				mainplayer.decreaseresistance();
				mainplayer.increaseultra();
			}
			else{
				cout << "You are too tired to perform that move!" << endl;
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
					goto STARTBOSSBATTLE;
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
			default : goto STARTBOSSBATTLE;
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
					goto STARTBOSSBATTLE;
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
			default : goto STARTBOSSBATTLE;break;
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
					boss.iceattacked();
				}
				else{
					cout << "You haven't enough MP left to perform this move!" << endl;
				}
				break;
			default :
				goto STARTBOSSBATTLE;
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
							boss.receivedultra();
							mainplayer.decreasetenresistance();
						}
						else{
							cout << "You are too tired to perform that ultra!" << endl;
						}
						break;
					default :
						goto STARTBOSSBATTLE;
				}
			}
			else{
				cout << "Skipped the turn" << endl;
			}
			break;
		case 'p' :
			equipment();
			goto STARTBOSSBATTLE;
			break;
		default:
			cout << "Skipped the turn" << endl;
			break;
		}

		if(distanceenemy == 1 || distanceenemy == 2){
			successfulhit = true;
			successfulhit2 = true;
		}
		if(distanceenemy == 3 || distanceenemy == 4 || distanceenemy == 5){
			successfulhit = false;
			successfulhit2 = false;
		}

		 // El enemigo ejecuta su turno
		mainplayer.playerattackedboss();

		mainplayer.increaseultra();
		mainplayer.limitultra();
		mainplayer.limitresistance();
		mainplayer.limitplayerlife();
		mainplayer.limitsp();
		boss.limitlife();
	}
}
}


int main(){
	// Inicio del programa, se le pregunta al jugador el nombre del main character
	randomseed();
	while(1){
		gotoxy(2,2);
		cout << "########    ###     ######  ######## ####  ######     ###    ##       ";
		gotoxy(2,3);
		cout << "   ##      ## ##   ##    ##    ##     ##  ##    ##   ## ##   ##       ";
		gotoxy(2,4);
		cout << "   ##     ##   ##  ##          ##     ##  ##        ##   ##  ##       ";
		gotoxy(2,5);
		cout << "   ##    ##     ## ##          ##     ##  ##       ##     ## ##       ";
		gotoxy(2,6);
		cout << "   ##    ######### ##          ##     ##  ##       ######### ##       ";
		gotoxy(2,7);
		cout << "   ##    ##     ## ##    ##    ##     ##  ##    ## ##     ## ##       ";
		gotoxy(2,8);
		cout << "   ##    ##     ##  ######     ##    ####  ######  ##     ## ######## ";
		gotoxy(2,9);
		cout << "                                                           [Alpha 1.6]";
		gotoxy(2,12);
		cout << "What will be the main character's name?";
		gotoxy(2,13);
		cin >> playername;
		if(playername == "Trackpoth"){
			gotoxy(2,15);
			cout << "Will it be our god and savior's name, Trackpoth?\a";
		}
		if(playername == "COCOS"){
			gotoxy(2,15);
			cout << "COCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS\aCOCOS";
		}
		if(playername != "Trackpoth"){
			if(playername != "COCOS"){
				gotoxy(2,15);
				cout << "Will it be " << playername << "?\a";
			}
		}
		cout << " [1] Yes [Any other key] No" << endl;
		gotoxy(2,16);
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

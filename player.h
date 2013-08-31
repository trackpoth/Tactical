#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>

using namespace std;

// Defininición de los valores que determinan la frecuencia y el poder de los ataques críticos
int subcriticalcheckerone;
int subcriticalcheckertwo;

// Efectos varios provocados por determinadas causas
bool piercingeyeeffect;
bool damagepilleffect;

// Otros argumentos con funciones secundarias
char movement;
int seed;
int distanceenemy = 3;
bool successfulhit2;
clock_t t;
bool runawayfrombattle;
bool successfulhit;
string playername;
bool firstbattle = true;

int movementint;
int movementfinal;

int section = 1;
int zone = 1;
int travel;

int battletype;

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

class warrior
{
public:
	warrior();
};

warrior::warrior(){
}

class player : public warrior
{
public:
	player();
	int attackparameter();
	int saymaxlife();
	int saylife();
	int saymaxsp();
	int saysp();
	int saymaxmp();
	int saymp();
	int saymagicattack();
	int sayrangedattack();
	int saycriticalchecker();
	int saycriticalpower();
	int saysmallhealthpill();
	int saysmallhealthpillvalue();
	int saydamagepill();
	int sayresistance();
	int saymaxresistance();
	int sayultra();
	int saymaxultra();
	int saydefense();
	int saytp();
	int saytpincrease();
	int saysquares();
	int saysquaresincrease();

	void decreaseplayersp();
	void increaseplayersp();
	void decreaseplayermp();
	void decreaseresistance();
	void decreasetenresistance();
	void increaseresistance();
	void increaseultrar();
	void increaseultra();
	void decreaseultra();
	void limitplayerlife();
	void limitresistance();
	void limitultra();
	void limitsp();

	void determinecriticalpower();
	void determinemaxsp();

	void defeatchecker();

	void smallhealthpilltaken();
	void damagepilltaken();
	void meditateused();

	void playerattacked();
	void playerattackedboss();

	void increasetp();
	void decreasetp();
	void increaseattack();
	void increasemaxlife();
	void increasemaxsp();
	void increasemaxmp();
	void increasemagicattack();
	void increaserangedattack();
	void increasedefense();
	void increasemaxresistance();
	void randomtpincrease();
	void randomtpincreaseboss();

	void upgrading();
	void shop();

protected:
	// Player's parameters
	int playermaxlife;
	int playermaxsp;
	int playermaxmp;
	int playermaxspbase;
	int playerattack;
	int playermagicattack;
	int playerrangedattack;
	int playerlife;
	int playersp;
	int playermp;
	int playercriticalchecker;
	float playercriticalmultiplier;
	int playercriticalpower;
	int playerresistance;
	int playermaxresistance;
	int playerultra;
	int playermaxultra;
	int playerdefense;

	// Player's items
	int smallhealthpill;
	int smallhealthpillvalue;
	int smallhealthpillworth;
	int damagepill;
	int damagepillworth;
	
	// Player's money
	int squares;
	int squaresincrease;

	// Player's train points related parameters
	int playertp;
	int tpincrease;
	int attacktpmeter;
	int ratmeter;
	int matmeter;
	int lifemeter;
	int defensemeter;
	int spmeter;
	int mpmeter;
	int resmeter;
};

player::player()
{
	playermaxlife = 460;
	playermaxspbase = 13;
	playermaxmp = 11;
	playerattack = 18;
	playermagicattack = 16;
	playerrangedattack = 14;
	playerlife = 460;
	playersp = 14;
	playermp = 11;
	playercriticalchecker = 20;
	playercriticalmultiplier = 1.5;
	smallhealthpill = 2;
	smallhealthpillvalue = 100;
	smallhealthpillworth = 8;
	damagepill = 1;
	damagepillworth = 24;
	playerresistance = 90;
	playermaxresistance = 90;
	playerultra = 100;
	playermaxultra = 200;
	playerdefense = 2;
	attacktpmeter = 10;
	ratmeter = 10;
	matmeter = 10;
	lifemeter = 15;
	defensemeter = 12;
	spmeter = 90;
	mpmeter = 120;
	resmeter = 50;
}

int player::attackparameter(){
	return playerattack;
}

int player::saymaxlife(){
	return playermaxlife;
}

int player::saylife(){
	return playerlife;
}

int player::saymaxsp(){
	return playermaxsp;
}

int player::saysp(){
	return playersp;
}

int player::saymaxmp(){
	return playermaxmp;
}

int player::saymp(){
	return playermp;
}

int player::saymagicattack(){
	return playermagicattack;
}

int player::sayrangedattack(){
	return playerrangedattack;
}

int player::saycriticalchecker(){
	return playercriticalchecker;
}

int player::saycriticalpower(){
	return playercriticalpower;
}

int player::saysmallhealthpill(){
	return smallhealthpill;
}

int player::saysmallhealthpillvalue(){
	return smallhealthpillvalue;
}

int player::saydamagepill(){
	return damagepill;
}

int player::sayresistance(){
	return playerresistance;
}

int player::saymaxresistance(){
	return playermaxresistance;
}

int player::sayultra(){
	return playerultra;
}

int player::saymaxultra(){
	return playermaxultra;
}

int player::saydefense(){
	return playerdefense;
}

int player::saytp(){
	return playertp;
}

int player::saytpincrease(){
	return tpincrease;
}

int player::saysquares(){
	return squares;
}

int player::saysquaresincrease(){
	return squaresincrease;
}

void player::decreaseplayersp(){
	playersp--;
}

void player::increaseplayersp(){
	playersp++;
}

void player::decreaseplayermp(){
	playermp--;
}

void player::decreaseresistance(){
	playerresistance--;
}

void player::decreasetenresistance(){
	playerresistance -= 10;
}

void player::increaseresistance(){
	playerresistance++;
}

void player::increaseultrar(){
	playerultra += (playerresistance / 15);
}

void player::increaseultra(){
	playerultra++;
}

void player::decreaseultra(){
	playerultra -= 50;
}

void player::limitplayerlife(){
	if(playerlife >= playermaxlife){
		playerlife = playermaxlife;
	}
}

void player::limitresistance(){
	if(playerresistance >= playermaxresistance){
		playerresistance = playermaxresistance;
	}
}

void player::limitultra(){
	if(playerultra >= playermaxultra){
		playerultra = playermaxultra;
	}
}

void player::limitsp(){
	if(playersp >= playermaxsp){
		playersp = playermaxsp;
	}
}

void player::determinecriticalpower(){
	if(damagepilleffect == false){
		playercriticalpower = (playerattack * playercriticalmultiplier);
	}
	else{
		playercriticalpower = ((playerattack * playercriticalmultiplier) + 10);
	}
}

void player::defeatchecker(){
	if(playerlife <= 0){
		clear();
		cout << playername;
		cout << " has been defeated!\a" << endl;
		_getch();
		exit(0);
	}
}

void player::smallhealthpilltaken(){
	smallhealthpill--;
	playerlife += smallhealthpillvalue;
	printf("Used a Small Health Pill and life was restored by %d points! %d remaining\n",smallhealthpillvalue,smallhealthpill);
}

void player::damagepilltaken(){
	damagepill--;
	damagepilleffect = true;
	printf("Used a Damage Pill and attack was increased by 10 points! %d remaining\n",damagepill);
}

void player::meditateused(){
	playermp -= 5;
	playerlife += 60;
	cout << "Used Meditate and life was restored by 60 points!" << endl;
}

void player::increasetp(){
	playertp++;
}

void player::decreasetp(){
	playertp--;
}

void player::increaseattack(){
	playerattack++;
}

void player::increasedefense(){
	playerdefense++;
}

void player::increasemagicattack(){
	playermagicattack++;
}

void player::increasemaxlife(){
	playermaxlife += 10;
	playerlife += 10;
}

void player::increasemaxmp(){
	playermaxmp++;
	playermp++;
}

void player::increasemaxsp(){
	playermaxsp++;
	playersp;
}

void player::increaserangedattack(){
	playerrangedattack++;
}

void player::increasemaxresistance(){
	playermaxresistance++;
	playerresistance++;
}

void player::randomtpincrease(){
	tpincrease = rand() % 150 + 50;
	playertp += tpincrease;
	squaresincrease = rand() % 25 + 5;
	squares += squaresincrease;
}

void player::randomtpincreaseboss(){
	tpincrease = rand() % 320 + 105;
	playertp += tpincrease;
	squaresincrease = rand() % 60 + 12;
	squares += squaresincrease;
}

player mainplayer;

void player::upgrading(){
UPGRADING:
	cout << "Parameter upgrading center" << endl;
	cout << "Current TP: " << playertp << endl << endl;
	cout << "Attack (AT): " << playerattack << " -> " << playerattack + 1 << endl;
	cout << "Ranged attack (RAT): " << playerrangedattack << " -> " << playerrangedattack + 1 << endl;
	cout << "Magic attack (MAT): " << playermagicattack << " -> " << playermagicattack + 1 << endl;
	cout << "Defense (DEF): " << playerdefense << " -> " << playerdefense + 1 << endl;
	cout << "Max Life: " << playermaxlife << " -> " << playermaxlife + 10 << endl;
	cout << "Max SP: " << playermaxspbase << " -> " << playermaxspbase + 1 << endl;
	cout << "Max MP: " << playermaxmp << " -> " << playermaxmp + 1 << endl;
	cout << "Resistance: " << playermaxresistance << " -> " << playermaxresistance + 2 << endl;
	cout << endl << "[1] Upgrade AT (-" << attacktpmeter << " TP)" << endl;
	cout << "[2] Upgrade RAT (-" << ratmeter << " TP)" << endl;
	cout << "[3] Upgrade MAT (-" << matmeter << " TP)" << endl;
	cout << "[4] Upgrade DEF (-" << defensemeter << " TP)" << endl;
	cout << "[5] Upgrade Max Life (-" << lifemeter << " TP)" << endl;
	cout << "[6] Upgrade Max SP (-" << spmeter << " TP)" << endl;
	cout << "[7] Upgrade Max MP (-" << mpmeter << " TP)" << endl;
	cout << "[8] Upgrade Resistance (-" << resmeter << " TP)" << endl;
	cout << "Type any other key to go back to the menu" << endl;
	cin >> movement;
	clear();
	switch(movement){
	case '1' :
		if(playertp >= attacktpmeter){
			playertp -= attacktpmeter;
			playerattack++;
			if(attacktpmeter >= 60){
			}
			else{
				attacktpmeter += 2;
			}
			goto UPGRADING;
		}
		else{
			cout << "You do not have enough Train Points for that!" << endl << endl;
		}
		break;
	case '2' :
		if(playertp >= ratmeter){
			playertp -= ratmeter;
			playerrangedattack++;
			if(ratmeter >= 70){
			}
			else{
				ratmeter += 3;
			}
			goto UPGRADING;
		}
		else{
			cout << "You do not have enough Train Points for that!" << endl << endl;
		}
		break;
	case '3' :
		if(playertp >= matmeter){
			playertp -= matmeter;
			playermagicattack++;
			if(matmeter >= 70){
			}
			else{
				matmeter += 3;
			}
			goto UPGRADING;
		}
		else{
			cout << "You do not have enough Train Points for that!" << endl << endl;
		}
		break;
	case '4' :
		if(playertp >= defensemeter){
			playertp -= defensemeter;
			playerdefense++;
			if(defensemeter >= 60){
				if(defensemeter >= 80){
				}
				else{
					defensemeter += 2;
				}
			}
			else{
				defensemeter += 3;
			}
			goto UPGRADING;
		}
		else{
			cout << "You do not have enough Train Points for that!" << endl << endl;
		}
		break;
	case '5' :
		if(playertp >= lifemeter){
			playertp -= lifemeter;
			playermaxlife += 10;
			playerlife += 10;
			if(lifemeter >= 85){
			}
			else{
				lifemeter += 5;
			}
			goto UPGRADING;
		}
		else{
			cout << "You do not have enough Train Points for that!" << endl << endl;
		}
		break;
	case '6' :
		if(playertp >= spmeter){
			playertp -= spmeter;
			playermaxspbase++;
			playersp++;
			if(spmeter >= 210){
			}
			else{
				spmeter += 15;
			}
			goto UPGRADING;
		}
		else{
			cout << "You do not have enough Train Points for that!" << endl << endl;
		}
		break;
	case '7' :
		if(playertp >= mpmeter){
			playertp -= mpmeter;
			playermaxmp++;
			playermp++;
			if(mpmeter >= 240){
			}
			else{
				mpmeter += 15;
			}
			goto UPGRADING;
		}
		else{
			cout << "You do not have enough Train Points for that!" << endl << endl;
		}
		break;
	case '8' :
		if(playertp >= resmeter){
			playertp -= resmeter;
			if(resmeter >= 90){
			}
			else{
				resmeter += 4;
			}
			playermaxresistance += 2;
			playerresistance += 2;
			goto UPGRADING;
		}
		else{
			cout << "You do not have enough Train Points for that!" << endl << endl;
		}
		break;
	}
}

class enemy : public warrior
{
public:
	enemy();
	int saymaxlife();
	int saylife();
	int saytype();
	int sayattack();
	int saydefense();
	int saycriticalchecker();
	int saycriticalpower();
	int sayint();
	bool sayhealthdrink();

	void victorychecker();
	void enemyattacked();
	void rangedattacked();
	void receivedultra();
	void iceattacked();
	void determinecriticalpower();
	void limitlife();
	void randomizetype();
	void randomizeparameters();
	void restoreparameters();
	void healthdrinktaken();
	void saystats();
	void randomizeboss();

protected:
	int enemylife;
	int enemymaxlife;
	int enemytype;
	int enemyattack;
	int enemydefense;
	int enemycriticalchecker;
	int enemycriticalpower;
	int enemyint;
	bool healthdrink;
};

enemy::enemy()
{
	enemylife = 120;
	enemymaxlife = 120;
	enemytype = 1;
	enemyattack = 10;
	enemydefense = 1;
	enemycriticalchecker = 20;
}

int enemy::saymaxlife(){
	return enemymaxlife;
}

int enemy::saylife(){
	return enemylife;
}

int enemy::saytype(){
	return enemytype;
}

int enemy::sayattack(){
	return enemyattack;
}

int enemy::saydefense(){
	return enemydefense;
}

int enemy::saycriticalchecker(){
	return enemycriticalchecker;
}

int enemy::saycriticalpower(){
	return enemycriticalpower;
}

int enemy::sayint(){
	return enemyint;
}

bool enemy::sayhealthdrink(){
	return healthdrink;
}

void enemy::receivedultra(){
	enemylife -= mainplayer.attackparameter();
	enemylife -= mainplayer.attackparameter();
	enemylife -= mainplayer.attackparameter();
	mainplayer.decreaseultra();
	mainplayer.decreaseultra();
	cout << playername << " USED ULTRA KICK IN THE NUTS! " << mainplayer.attackparameter() * 3 << " DAMAGE WAS DEALT!" << endl;
}

void enemy::iceattacked(){
	mainplayer.decreaseplayermp();
	mainplayer.decreaseplayermp();
	mainplayer.decreaseplayermp();
	if(enemytype == 1 || enemytype == 6){
		enemylife = (enemylife - mainplayer.saymagicattack() * 1.5);
		cout << "You dealt " << mainplayer.saymagicattack() * 1.5 << " damage to the enemy by using Ice! It was very effective!" << endl;
	}
	if(enemytype == 5){
		enemylife = (enemylife - mainplayer.saymagicattack() * 0.5);
		cout << "You dealt " << mainplayer.saymagicattack() * 0.5 << " damage to the enemy by using Ice. It wasn't very effective..." << endl;
	}
	if(enemytype == 7){
		enemylife = (enemylife + mainplayer.saymagicattack());
		cout << "You healed the enemy " << mainplayer.saymagicattack() << " life points by using Ice!" << endl;
	}
	if(enemytype == 2 || enemytype == 3 || enemytype == 4){
		enemylife = (enemylife - mainplayer.saymagicattack());
		cout << "You dealt " << mainplayer.saymagicattack() << " damage to the enemy by using Ice!" << endl;
	}
}

void enemy::determinecriticalpower(){
	enemycriticalpower = enemyattack * 1.5;
}

void enemy::limitlife(){
	if(enemylife >= enemymaxlife){
		enemylife = enemymaxlife;
	}
}

void enemy::restoreparameters(){
	enemylife = enemymaxlife;
}

void enemy::healthdrinktaken(){
	healthdrink = false;
	enemylife += (enemymaxlife * 0.5);
	if(enemylife >= enemymaxlife){
		enemylife = enemymaxlife;
	}
}

void enemy::saystats(){
	if(battletype == 2){
		cout << "[BOSS] ";
	}
	if(enemytype == 1){
		cout << "Grass ";
	}
	if(enemytype == 2){
		cout << "Normal ";
	}
	if(enemytype == 3){
		cout << "Dark ";
	}
	if(enemytype == 4){
		cout << "Light ";
	}
	if(enemytype == 5){
		cout << "Fire ";
	}
	if(enemytype == 6){
		cout << "Water ";
	}
	if(enemytype == 7){
		cout << "Ice ";
	}
	cout << "Human" << endl;
	if(piercingeyeeffect == false){
		cout << "Life = ";
		cout << enemylife;
		cout << endl;
	}
	else{
		cout << "Life = " << enemylife << "/" << enemymaxlife << endl;
		printf("AT = %d | DEF = %d\n",enemyattack,enemydefense);
	}
	if(piercingeyeeffect == true){
		cout << "Weak to: ";
		if(enemytype == 1){
			cout << "[Darkness (x1.5)] [Fire (x1.5)] [Ice (x1.5)] " << endl;
		}
		if(enemytype == 2){
			cout << "[Darkness (x1.5)] [Fire (x1.5)]" << endl;
		}
		if(enemytype == 3){
			cout << "[Light (x1.5)] [Fire (x1.5)]" << endl;
		}
		if(enemytype == 4){
			cout << "[Darkness (x1.5)] [Water (x1.5)] [Grass (x1.5)]" << endl;
		}
		if(enemytype == 5){
			cout << "[Darkness (x1.5)] [Water (x2)]" << endl;
		}
		if(enemytype == 6){
			cout << "[Ice (x1.5)] [Grass (x2)]" << endl;
		}
		if(enemytype == 7){
			cout << "[Water (x1.5)] [Fire (x1.5)]" << endl;
		}
	}
	printf("Effects = ");
	if(piercingeyeeffect == true){
		cout << "[Piercing Eye]\n" << endl;
	}
	if(piercingeyeeffect == false){
		cout << "None\n" << endl;
	}
}

enemy commonenemy;
enemy boss;

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
					playerlife -= 1;
					printf("You only took 1 damage because of your high defense!\n\n");
				}

				// Crítico defensa inferior a ataque
				else{
					playerlife -= commonenemy.saycriticalpower();
					playerlife += playerdefense;
					printf("The enemy made a critical hit, causing %d damage!\n\n",commonenemy.saycriticalpower() - mainplayer.saydefense());
				}
			}
			else{

				// Normal defensa superior a ataque
				if(playerdefense >= commonenemy.sayattack()){
					playerlife -= 1;
					printf("You only took 1 damage because of your high defense!\n\n");
				}

				// Normal defensa inferior a ataque
				else{
					playerlife -= (commonenemy.sayattack() - playerdefense);
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
					playerlife -= 1;
					printf("You only took 1 damage because of your high defense!\n\n");
				}

				// Crítico defensa inferior a ataque
				else{
					playerlife -= boss.saycriticalpower();
					playerlife += playerdefense;
					printf("The enemy made a critical hit, causing %d damage!\n\n",boss.saycriticalpower() - mainplayer.saydefense());
				}
			}
			else{

				// Normal defensa superior a ataque
				if(playerdefense >= boss.sayattack()){
					playerlife -= 1;
					printf("You only took 1 damage because of your high defense!\n\n");
				}

				// Normal defensa inferior a ataque
				else{
					playerlife -= (boss.sayattack() - playerdefense);
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

void enemy::randomizeboss(){
	enemytype = rand() % 7 + 1;
	enemyint = 4;
	healthdrink = 1;
	enemymaxlife += rand() % 200 + commonenemy.saymaxlife();
	enemyattack += rand() % 8 + commonenemy.sayattack();
	enemydefense += rand() % 6 + commonenemy.saydefense();
	enemylife = enemymaxlife;
}
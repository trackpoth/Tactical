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
	int saycriticalchecker();
	int saycriticalpower();
	int saysmallhealthpill();
	int saysmallhealthpillvalue();
	int saydamagepill();
	int sayresistance();
	int saymaxresistance();
	int sayultra();
	int saymaxultra();

	void decreaseplayersp();
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
	void determinecriticalpower();
	void defeatchecker();
	void smallhealthpilltaken();
	void damagepilltaken();
	void meditateused();
	void playerattacked();

protected:
	int playermaxlife;
	int playermaxsp;
	int playermaxmp;
	int playerattack;
	int playermagicattack;
	int playerlife;
	int playersp;
	int playermp;
	int playercriticalchecker;
	float playercriticalmultiplier;
	int playercriticalpower;
	int smallhealthpill;
	int smallhealthpillvalue;
	int damagepill;
	int playerresistance;
	int playermaxresistance;
	int playerultra;
	int playermaxultra;
};

player::player()
{
	playermaxlife = 460;
	playermaxsp = 10;
	playermaxmp = 16;
	playerattack = 21;
	playermagicattack = 18;
	playerlife = 460;
	playersp = 10;
	playermp = 16;
	playercriticalchecker = 20;
	playercriticalmultiplier = 1.5;
	smallhealthpill = 2;
	smallhealthpillvalue = 100;
	damagepill = 2;
	playerresistance = 80;
	playermaxresistance = 80;
	playerultra = 100;
	playermaxultra = 200;
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

void player::decreaseplayersp(){
	playersp--;
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
	playermp -= 6;
	playerlife += 60;
	cout << "Used Meditate and life was restored by 60 points!" << endl;
}

player mainplayer;

class enemy : public warrior
{
public:
	enemy();
	int saymaxlife();
	int saylife();
	int saytype();
	int sayattack();
	int saycriticalchecker();
	int saycriticalpower();

	void victorychecker();
	void enemyattacked();
	void receivedultra();
	void iceattacked();

protected:
	int enemylife;
	int enemymaxlife;
	int enemytype;
	int enemyattack;
	int enemycriticalchecker;
	int enemycriticalpower;
};

enemy::enemy()
{
	enemylife = 210;
	enemymaxlife = 210;
	enemytype = 1;
	enemyattack = 14;
	enemycriticalchecker = 20;
	enemycriticalpower = 36;
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

int enemy::saycriticalchecker(){
	return enemycriticalchecker;
}

int enemy::saycriticalpower(){
	return enemycriticalpower;
}

void enemy::enemyattacked(){
	if(damagepilleffect == false){
		if(subcriticalcheckerone <= mainplayer.saycriticalchecker()){
			cout << "\a";
			enemylife -= mainplayer.saycriticalpower();
			cout << playername;
			printf(" made a critical hit, causing %d damage!\n",mainplayer.saycriticalpower());
		}
		else{
			enemylife -= mainplayer.attackparameter();
			cout << playername;
			cout << " inflicted ";
			cout << mainplayer.attackparameter(); 
			cout << " to the enemy" << endl;
		}
	}
	if(damagepilleffect == true){
		if(subcriticalcheckerone <= mainplayer.saycriticalchecker()){
			cout << "\a";
			enemylife -= mainplayer.saycriticalpower();
			enemylife -= 10;
			cout << playername;
			printf(" made a critical hit, causing %d damage!\n",mainplayer.saycriticalpower());
		}
		else{
			enemylife -= mainplayer.attackparameter();
			enemylife -= 10;
			cout << playername;
			printf(" inflicted %d damage to the enemy\n",mainplayer.attackparameter() + 10);
		}
	}
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
	if(enemytype == 1){
		enemylife = (enemylife - mainplayer.saymagicattack() * 2);
		printf("You dealt %d damage to the enemy by using Ice! It was very effective!\n",mainplayer.saymagicattack() * 2);
	}
	else{
		enemylife -= mainplayer.saymagicattack();
		printf("You dealt %d damage to the enemy by using Ice!\n",mainplayer.saymagicattack());
	}
}

void enemy::victorychecker(){
	if(enemylife <= 0){
		clear();
		if(firstbattle == true){
			cout << "Hippie: Wow, that did hurt!" << endl;
			_getch();
			cout << "You: What in the heavens were you doing?" << endl;
			_getch();
			cout << "Hippie: I was looking for my Hipercube" << endl;
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
			firstbattle = false;
			exit(0);
		}
		else{
			cout << playername;
			cout << " won the battle!\a" << endl;
			_getch();
			exit(0);
		}
	}
}

enemy commonenemy;

void player::playerattacked(){
	if(subcriticalcheckertwo <= commonenemy.saycriticalchecker()){
		playerlife -= commonenemy.saycriticalpower();
		printf("The enemy made a critical hit, causing %d damage!\n\n",commonenemy.saycriticalpower());
	}
	else{
		playerlife -= commonenemy.sayattack();
		printf("The enemy inflicted %d damage\n\n",commonenemy.sayattack());
	}
}
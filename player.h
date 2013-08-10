#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>

using namespace std;

// Definición de variables principales

	// Definición de los parámetros del jugador y del enemigo
int enemymaxlife = 410;
int enemyattack = 18;
int enemytype = 1;

int playermagicattack = 18;
int playersp = 10;
int playermaxsp = 10;
int playermp = 16;
int playermaxmp = 16;

	// Defininición de los valores que determinan la frecuencia y el poder de los ataques críticos
int subcriticalcheckerone;
int subcriticalcheckertwo;

int enemycriticalchecker = 20;
int enemycriticalpower = 36;

int playercriticalpower;
float playercriticalmultiplier = 1.5;
int playercriticalchecker = 20;

	// Cantidad de objetos que posee el jugador
int smallhealthpill = 2;
int smallhealthpillvalue = 100;
int damagepill = 2;

	// Efectos varios provocados por determinadas causas
bool piercingeyeeffect;
bool damagepilleffect;

	// Otros argumentos con funciones secundarias
bool battlechecker = true;
char movement;
int seed;
int distanceenemy = 3;
bool successfulhit2;
clock_t t;
bool runawayfrombattle;
string playername;
bool successfulhit;

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
	int playerlife;
	int enemylife;
	int playerattack;
	void enemyattacked();
	void playerattacked();
};

warrior::warrior(){
	playerattack = 21;
	playerlife = 460;
}

void warrior::enemyattacked(){
	if(damagepilleffect == false){
		if(subcriticalcheckerone <= playercriticalchecker){
			cout << "\a";
			enemylife -= playercriticalpower;
			cout << playername;
			printf(" made a critical hit, causing %d damage!\n",playercriticalpower);
		}
		else{
			enemylife -= playerattack;
			cout << playername;
			printf(" inflicted %d damage to the enemy\n",playerattack);
		}
	}
	if(damagepilleffect == true){
		if(subcriticalcheckerone <= playercriticalchecker){
			cout << "\a";
			enemylife -= (playercriticalpower + 10);
			cout << playername;
			printf(" made a critical hit, causing %d damage!\n",playercriticalpower);
		}
		else{
			enemylife -= (playerattack + 10);
			cout << playername;
			printf(" inflicted %d damage to the enemy\n",playerattack + 10);
		}
	}
}

void warrior::playerattacked(){
	if(subcriticalcheckertwo <= enemycriticalchecker){
		playerlife -= enemycriticalpower;
		printf("The enemy made a critical hit!\n\n");
	}
	else{
		playerlife -= enemyattack;
		printf("The enemy inflicted %d damage\n\n",enemyattack);
	}
}

class player : public warrior
{
public:
	player();
	void saymaxlife();
	void sayattack();
	void saylife();
	void limitplayerlife();
	void determinecriticalpower();
	void defeatchecker();
	void smallhealthpilltaken();
	void meditateused();

protected:
	int playermaxlife;
};

player::player()
{
	playermaxlife = 460;
}

void player::saymaxlife(){
	cout << playermaxlife;
}

void player::sayattack(){
	cout << playerattack;
}

void player::saylife(){
	cout << playerlife;
}

void player::limitplayerlife(){
	if(playerlife >= playermaxlife){
		playerlife = playermaxlife;
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
		cout << " has lost!\a" << endl;
		battlechecker = false;
		_getch();
		exit(0);
	}
}

void player::smallhealthpilltaken(){
	smallhealthpill--;
	playerlife += smallhealthpillvalue;
	printf("Used a Small Health Pill and life was restored by %d points! %d remaining\n",smallhealthpillvalue,smallhealthpill);
}

void player::meditateused(){
	playermp -= 6;
	playerlife += 60;
	cout << "Used Meditate and life was restored by 60 points!" << endl;
}

class enemy : public warrior
{
public:
	enemy();
	void victorychecker();
	void saylife();
	void firereceived();
};

enemy::enemy()
{
	enemylife = 410;
}

void enemy::victorychecker(){
	if(enemylife <= 0){
		clear();
		cout << playername;
		cout << " won the battle!\a" << endl;
		battlechecker = false;
		_getch();
		exit(0);
	}
}

void enemy::saylife(){
	cout << enemylife;
}

void enemy::firereceived(){
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
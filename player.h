#include "stdafx.h"
#include "enemy.h"
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
int enemylife = 410;

int playermagicattack = 18;
int playersp = 10;
int playermaxsp = 10;
int playermp = 16;
int playermaxmp = 16;
int playerlife = 460;

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

class player
{
public:
	player();
	void saymaxlife();
	void sayattack();
	void limitplayerlife();
	void determinecriticalpower();
	void attackenemy();

private:
	int playerattack;
	int playermaxlife;
};

player::player()
{
	playermaxlife = 460;
	playerattack = 21;
}

void player::saymaxlife(){
	cout << playermaxlife;
}

void player::limitplayerlife(){
	if(playerlife >= playermaxlife){
		playerlife = playermaxlife;
	}
}

void player::sayattack(){
	cout << playerattack;
}

void player::determinecriticalpower(){
	if(damagepilleffect == false){
		playercriticalpower = (playerattack * playercriticalmultiplier);
	}
	else{
		playercriticalpower = ((playerattack * playercriticalmultiplier) + 10);
	}
}

void player::attackenemy(){
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
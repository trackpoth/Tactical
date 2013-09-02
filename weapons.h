#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>

class weapon
{
public:
	weapon();
	float sayattack1();
	int sayattack1equipped();

	float sayattack();
	int sayrealattack();
	void determineattack();
	void determinerealattack();

private:
	float attack1;
	int attack1equipped;
	
	float attack;
	int realattack;
};

weapon::weapon()
{
	attack1 = 0.02;
	attack1equipped = true;
}

float weapon::sayattack1(){
	return attack1;
}

int weapon::sayattack1equipped(){
	return attack1equipped;
}

float weapon::sayattack(){
	return attack;
}

int weapon::sayrealattack(){
	return realattack;
}

void weapon::determineattack(){
	if(attack1equipped == 1){
		attack = attack1;
	}
}

weapon weapons;

class ranged
{
public:
	ranged();
	float sayattack1();
	int saysp1();
	int sayattack1equipped();

	float sayattack();
	int sayrealattack();
	void determineattack();
	void determinerealattack();

private:
	float attack1;
	int sp1;
	int attack1equipped;
	
	float attack;
	int realattack;
};

ranged::ranged()
{
	attack1 = 0.02;
	sp1 = 1;
	attack1equipped = true;
}

float ranged::sayattack1(){
	return attack1;
}

int ranged::saysp1(){
	return sp1;
}

int ranged::sayattack1equipped(){
	return attack1equipped;
}

float ranged::sayattack(){
	return attack;
}

int ranged::sayrealattack(){
	return realattack;
}

void ranged::determineattack(){
	if(attack1equipped == 1){
		attack = attack1;
	}
}

ranged rangedweapon;

class shield
{
public:
	shield();

	int sayshield1();
	int saymaxshield1();
	int sayrecharge1();
	bool sayshield1equipped();

private:
	int shield1;
	int maxshield1;
	int recharge1;
	bool shield1equipped;
};

shield::shield()
{
	shield1 = 10;
	maxshield1 = 10;
	recharge1 = 2;
	shield1equipped = true;
}

int shield::sayshield1(){
	return shield1;
}

int shield::saymaxshield1(){
	return maxshield1;
}

int shield::sayrecharge1(){
	return recharge1;
}

bool shield::sayshield1equipped(){
	return shield1equipped;
}

shield playershields;
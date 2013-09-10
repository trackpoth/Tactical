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

	int sayequippedmelee();
	float sayattack();
	int sayrealattack();

	void determineattack();
	void determinerealattack();
	void restoremelee();

private:
	float attack1;
	
	float attack;
	int realattack;
	int equippedmelee;
};

weapon::weapon()
{
	attack1 = 0.02;
	equippedmelee = 1;
}

float weapon::sayattack1(){
	return attack1;
}

int weapon::sayequippedmelee(){
	return equippedmelee;
}

float weapon::sayattack(){
	return attack;
}

int weapon::sayrealattack(){
	return realattack;
}

void weapon::determineattack(){
	if(equippedmelee == 1){
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

	int sayequippedranged();
	float sayattack();
	int sayrealattack();

	void determineattack();
	void determinerealattack();
	void restoreranged();

private:
	float attack1;
	int sp1;
	
	float attack;
	int realattack;
	int equippedranged;
};

ranged::ranged()
{
	attack1 = 0.02;
	sp1 = 1;
	equippedranged = 1;
}

float ranged::sayattack1(){
	return attack1;
}

int ranged::saysp1(){
	return sp1;
}

int ranged::sayequippedranged(){
	return equippedranged;
}

float ranged::sayattack(){
	return attack;
}

int ranged::sayrealattack(){
	return realattack;
}

void ranged::determineattack(){
	if(equippedranged == 1){
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

	int sayequippedshield();
	void restoreshield();

private:
	int shield1;
	int maxshield1;
	int recharge1;
	int equippedshield;
};

shield::shield()
{
	shield1 = 10;
	maxshield1 = 10;
	recharge1 = 2;
	equippedshield = 1;
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

int shield::sayequippedshield(){
	return equippedshield;
}

shield playershields;
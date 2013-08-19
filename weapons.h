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
	int sayattack1();
	int sayattack1equipped();

	int sayattack();
	void determineattack();

private:
	int attack1;
	int attack1equipped;
	
	int attack;
};

weapon::weapon()
{
	attack1 = 3;
	attack1equipped = true;
}

int weapon::sayattack1(){
	return attack1;
}

int weapon::sayattack1equipped(){
	return attack1equipped;
}

int weapon::sayattack(){
	return attack;
}

void weapon::determineattack(){
	if(attack1equipped == 1){
		attack = attack1;
	}
}

weapon weapons;
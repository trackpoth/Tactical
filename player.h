#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>

using namespace std;

int playermaxlifeclone = 460;

class player
{
public:
	player();
	void saymaxlife();
	void refreshlifeclone();

private:
	int playermaxlife;
};

player::player()
{
	playermaxlife = 460;
}

void player::saymaxlife(){
	cout << playermaxlife;
}

void player::refreshlifeclone(){
	playermaxlifeclone = playermaxlife;
}
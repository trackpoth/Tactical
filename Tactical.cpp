#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>
#include <cstring>
#include <sstream>
#include <winuser.h>
#include "player.h"
#include "key.h"
#include "dialogues.h"
#include "weapons.h"

#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGREY		7
#define DARKGREY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA	13
#define YELLOW			14
#define WHITE			15

using namespace std;

bool start;
bool load;
bool loadfailed;
bool savefileexists;
bool succesfulbuy;
int skilllearnt;

int eventtype;
int eventgenerator;

int shoptype;
int shopsubtype;
float shopvalue;
int shopitema;
int shopitemb;
int shopitemc;
int shopitemd;

char retriever[10];
string encrypter;
string chartostring;
string intEncrypter(int number)
{
   stringstream ss;
   ss << number;
   return ss.str();
}

void encrypt(string data,string key)
{
    for(unsigned i=0;i<data.size();i++){
        data[i] += key[i%key.size()];
	}
	encrypter = data;
}

void decrypt(string data,string key)
{
    for(unsigned i=0;i<data.size();i++){
        data[i] -= key[i%key.size()];
	}
	encrypter = data;
}

void clearcolors(int text, int background){
	int n;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (text + (background * 16)) );
	for(; n < 25; n++){
	gotoxy(0,n);
	cout << "                                                                                ";
	}
	n = 0;
	gotoxy(0,0);
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
	clear();
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

void player::options(){
	string password;
OPTIONS:
	cout << "Options" << endl << endl;
	cout << "[1] Enter debug mode" << endl;
	cin >> movement;
	clear();
	switch(movement){
		case '1' :
			cout << "Enter password" << endl;
			cin >> password;
			if(password != key){
				cout << "Invalid password" << endl;
				_getch();
				clear();
				goto OPTIONS;
			}
			cout << "[1] Add 1000 experience" << endl;
			cin >> movement;
			switch(movement){
			case '1' :
				experience += 1000;
				cout << "Done succesfully" << endl;
				_getch();
				clear();
				goto OPTIONS;
			}
	}
}

void equipment(){
	cout << "Melee weapon : ";
	if(weapons.sayequippedmelee() == 1){
		cout << "[+2% AT]          Tennis Racket" << endl;
	}
	cout << "Ranged weapon: ";
	if(rangedweapon.sayequippedranged() == 1){
		cout << "[+2% RAT | +1 SP] Bullshot" << endl;
	}
	cout << "Magic weapon : ";
	if(magicweapon.sayequippedmagic() == 1){
		cout << "[+2% MAT | +1 MP] DLL injector" << endl;
	}
	cout << "Shields      : ";
	if(playershields.sayequippedshield() == 1){
		cout << "[10 SH | 2 RT]    Full Cracked Shield" << endl;
	}
	cout << endl << "Sector = " << section << " | Zone = " << zone << endl;
	cout << endl << "Squares = " << mainplayer.saysquares() << endl;
	cout << endl << "[t] Enter the parameter upgrading center" << endl;
	cout << "[o] Options" << endl;
	cout << "[Any other key] Go back to the menu" << endl;
	cin >> movement;
	clear();
	switch(movement){
	case 't' :
		mainplayer.upgrading();
		break;
	case 'o' :
		mainplayer.options();
		break;
	default:;
	}
}

int converter;

void stringtoint(string value){
	stringstream ss(value);
	ss >> converter;
}

void player::restoreparameters(int parameter){
	if(parameter == 1){
		playermaxlife = converter;
	}
	if(parameter == 2){
		playermaxspbase = converter;
	}
	if(parameter == 3){
		playermaxmpbase = converter;
	}
	if(parameter == 4){
		playermaxresistance = converter;
	}
	if(parameter == 5){
		playerattack = converter;
	}
	if(parameter == 6){
		playermagicattack = converter;
	}
	if(parameter == 7){
		playerrangedattack = converter;
	}
	if(parameter == 8){
		playerdefense = converter;
	}
	if(parameter == 9){
		playerlife = converter;
	}
	if(parameter == 10){
		playersp = converter;
	}
	if(parameter == 11){
		playermp = converter;
	}
	if(parameter == 12){
		playerresistance = converter;
	}
	if(parameter == 13){
		playerultra = converter;
	}
	if(parameter == 14){
		playercriticalchecker = converter;
	}
	if(parameter == 15){
		smallhealthpill = converter;
	}
	if(parameter == 16){
		damagepill = converter;
	}
	if(parameter == 17){
		squares = converter;
	}
	if(parameter == 18){
		playertp = converter;
	}
	if(parameter == 19){
		attacktpmeter = converter;
	}
	if(parameter == 20){
		ratmeter = converter;
	}
	if(parameter == 21){
		matmeter = converter;
	}
	if(parameter == 22){
		defensemeter = converter;
	}
	if(parameter == 23){
		lifemeter = converter;
	}
	if(parameter == 24){
		spmeter = converter;
	}
	if(parameter == 25){
		mpmeter = converter;
	}
	if(parameter == 26){
		resmeter = converter;
	}
	if(parameter == 27){
		experience = converter;
	}
}

void weapon::restoremelee(){
	equippedmelee = converter;
}

void ranged::restoreranged(){
	equippedranged = converter;
}

void magic::restoremagic(){
	equippedmagic = converter;
}

void shield::restoreshield(){
	equippedshield = converter;
}

void enemy::restoreparameters(int parameter){
	if(parameter == 1){
		enemymaxlife = converter;
	}
	if(parameter == 2){
		enemyattack = converter;
	}
	if(parameter == 3){
		enemydefense = converter;
	}
}

void savegame(int savetype){
	FILE * save;
	int integritychecker;
	if(savetype == 2){
		save = fopen("resources.txt","r");
		if(save != NULL){
				rewind(save);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
			playername = encrypter.c_str();
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			section = converter;
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			zone = converter;
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(1);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(2);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(3);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(4);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(5);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(6);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(7);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(8);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(9);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(10);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(11);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(12);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(13);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(14);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(15);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(16);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(17);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(18);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(19);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(20);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(21);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(22);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(23);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(24);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(25);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(26);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mainplayer.restoreparameters(27);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			weapons.restoremelee();
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			rangedweapon.restoreranged();
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			magicweapon.restoremagic();
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			playershields.restoreshield();
			mainplayer.determinemaxshields();
			mainplayer.restoreshields();
			fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			commonenemy.restoreparameters(1);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			commonenemy.restoreparameters(2);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			commonenemy.restoreparameters(3);
				fscanf(save,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			integritychecker = converter;
			if(integritychecker == (section + zone + mainplayer.saymaxlife() + mainplayer.saymaxspbase() + mainplayer.saymaxmpbase() + mainplayer.saymaxresistance() +
				mainplayer.attackparameter() + mainplayer.saymagicattack() + mainplayer.sayrangedattack() + mainplayer.saydefense() + mainplayer.saylife() +
				mainplayer.saysp() + mainplayer.saymp() + mainplayer.sayresistance() + mainplayer.sayultra() + mainplayer.saycriticalchecker() +
				mainplayer.saysmallhealthpill() + mainplayer.saydamagepill() + mainplayer.saysquares() + mainplayer.saytp() + mainplayer.sayattacktpmeter() +
				mainplayer.sayratmeter() + mainplayer.saymatmeter() + mainplayer.saydefensemeter() + mainplayer.saylifemeter() + mainplayer.sayspmeter() +
				mainplayer.saympmeter() + mainplayer.sayresmeter() + mainplayer.sayexperience() + weapons.sayequippedmelee() + rangedweapon.sayequippedranged() + magicweapon.sayequippedmagic() +
				playershields.sayequippedshield() + commonenemy.saymaxlife() + commonenemy.sayattack() + commonenemy.saydefense())){
					gotoxy(2,18);
					cout << "                                               ";
					gotoxy(2,18);
					cout << "Game loaded correctly!" << endl;
					_getch();
					fclose(save);
					remove("resources.txt");
			}
			else{
				gotoxy(2,18);
				cout << "                                               ";
				gotoxy(2,18);
				cout << "Save game corrupted." << endl;
				fclose(save);
				remove("resources.txt");
				_getch();
				exit(1);
			}
		}
		else{
			gotoxy(2,18);
			cout << "                                               ";
			gotoxy(2,18);
			cout << "There isn't any save to load";
			loadfailed = true;
		}
	}
	if(savetype == 1){
		save = fopen("resources.txt","w");
		if(save != NULL){
			cout << "Saving the game... Wait a second..." << endl;
			cout << "Saving 1/9 block of data..." << endl;
				encrypt(playername,key);											// Playername
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(section),key);									// Section
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(zone),key);									// Zone
				fprintf(save,"%s ",encrypter.c_str());
			cout << "Saving 2/9 block of data..." << endl;
				encrypt(intEncrypter(mainplayer.saymaxlife()),key);					// [mainplayer] Max life
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saymaxspbase()),key);				// [mainplayer] Max SP base
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saymaxmpbase()),key);				// [mainplayer] Max MP base
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saymaxresistance()),key);			// [mainplayer] Max resistance
				fprintf(save,"%s ",encrypter.c_str());
			cout << "Saving 3/9 block of data..." << endl;
				encrypt(intEncrypter(mainplayer.attackparameter()),key);			// [mainplayer] Attack
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saymagicattack()),key);				// [mainplayer] Magic attack
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.sayrangedattack()),key);			// [mainplayer] Ranged attack
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saydefense()),key);					// [mainplayer] Defense
				fprintf(save,"%s ",encrypter.c_str());
			cout << "Saving 4/9 block of data..." << endl;
				encrypt(intEncrypter(mainplayer.saylife()),key);					// [mainplayer] Life
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saysp()),key);						// [mainplayer] SP
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saymp()),key);						// [mainplayer] MP
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.sayresistance()),key);				// [mainplayer] Resistance
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.sayultra()),key);					// [mainplayer] Ultra
				fprintf(save,"%s ",encrypter.c_str());
			cout << "Saving 5/9 block of data..." << endl;
				encrypt(intEncrypter(mainplayer.saycriticalchecker()),key);			// [mainplayer] Critical checker
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saysmallhealthpill()),key);			// [mainplayer] Small Health Pill [quantity]
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saydamagepill()),key);				// [mainplayer] Damage Pill [quantity]
				fprintf(save,"%s ",encrypter.c_str());
			cout << "Saving 6/9 block of data..." << endl;
				encrypt(intEncrypter(mainplayer.saysquares()),key);					// [mainplayer] Squares
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saytp()),key);						// [mainplayer] Train Points
				fprintf(save,"%s ",encrypter.c_str());
			cout << "Saving 7/9 block of data..." << endl;
				encrypt(intEncrypter(mainplayer.sayattacktpmeter()),key);			// [mainplayer] TP meter [attack]
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.sayratmeter()),key);				// [mainplayer] TP meter [ranged attack]
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saymatmeter()),key);				// [mainplayer] TP meter [magic attack]
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saydefensemeter()),key);			// [mainplayer] TP meter [defense]
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saylifemeter()),key);				// [mainplayer] TP meter [life]
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.sayspmeter()),key);					// [mainplayer] TP meter [sp]
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.saympmeter()),key);					// [mainplayer] TP meter [mp]
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.sayresmeter()),key);				// [mainplayer] TP meter [resistance]
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(mainplayer.sayexperience()),key);				// [mainplayer] Experience
				fprintf(save,"%s ",encrypter.c_str());
			cout << "Saving 8/9 block of data..." << endl;
				encrypt(intEncrypter(weapons.sayequippedmelee()),key);				// [weapons]       Equipped melee ID
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(rangedweapon.sayequippedranged()),key);		// [rangedweapon]  Equipped ranged ID
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(magicweapon.sayequippedmagic()),key);			// [magicweapon]   Equipped magic ID
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(playershields.sayequippedshield()),key);		// [playershields] Equipped shields ID
				fprintf(save,"%s ",encrypter.c_str());
			cout << "Saving 9/9 block of data..." << endl;
				encrypt(intEncrypter(commonenemy.saymaxlife()),key);				// [commonenemy] Max life
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(commonenemy.sayattack()),key);					// [commonenemy] Attack
				fprintf(save,"%s ",encrypter.c_str());
				encrypt(intEncrypter(commonenemy.saydefense()),key);				// [commonenemy] Defense
				fprintf(save,"%s ",encrypter.c_str());

			integritychecker = (section + zone + mainplayer.saymaxlife() + mainplayer.saymaxspbase() + mainplayer.saymaxmpbase() + mainplayer.saymaxresistance() +
				mainplayer.attackparameter() + mainplayer.saymagicattack() + mainplayer.sayrangedattack() + mainplayer.saydefense() + mainplayer.saylife() +
				mainplayer.saysp() + mainplayer.saymp() + mainplayer.sayresistance() + mainplayer.sayultra() + mainplayer.saycriticalchecker() +
				mainplayer.saysmallhealthpill() + mainplayer.saydamagepill() + mainplayer.saysquares() + mainplayer.saytp() + mainplayer.sayattacktpmeter() +
				mainplayer.sayratmeter() + mainplayer.saymatmeter() + mainplayer.saydefensemeter() + mainplayer.saylifemeter() + mainplayer.sayspmeter() +
				mainplayer.saympmeter() + mainplayer.sayresmeter() + mainplayer.sayexperience() + weapons.sayequippedmelee() + rangedweapon.sayequippedranged() + magicweapon.sayequippedmagic() +
				playershields.sayequippedshield() + commonenemy.saymaxlife() + commonenemy.sayattack() + commonenemy.saydefense());

				encrypt(intEncrypter(integritychecker),key);
				fprintf(save,"%s ",encrypter.c_str());

			cout << "Saved successfully! Hope to see you again soon!" << endl;
			_getch();
			fclose(save);
		}
		else{
			cout << "An error ocurred while saving the game" << endl;
			_getch();
		}
		exit(0);
	}
	if(savetype == 3){
		save = fopen("resources.txt","r");
		if(save != NULL){
			cout << "There is a save file! Come back later when you finish the current game" << endl;
			savefileexists = true;
		}
		else{
			savefileexists = false;
		}
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
	cout << "[6] Save & quit" << endl;
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
		break;
	case '5' :
		itemmenu();
		goto TRAVELING;
		break;
	case '6' :
		savegame(1);
		goto TRAVELING;
		break;
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

void player::upgrading(){
UPGRADING:
	cout << "Parameter upgrading center" << endl;
	cout << "Current TP: " << playertp << endl;
	cout << "Current experience: " << experience << endl << endl;
	cout << "[1] Stealth tier  [" << masterstealth << " skill points]" << endl;
	cout << "[2] Strength tier [" << masterstrength << " skill points]" << endl;
	cout << "[3] Magic tier    [" << mastermagic << " skill points]" << endl;
	cout << "[4] Health tier   [" << masterhealth << " skill points]" << endl;
	cout << endl << "[w] Experience center" << endl;
	cout << "[Any other key] Go back to the main menu" << endl;
	cin >> movement;
	clear();
	switch(movement){
	case '1' :
STEALTH:
		cout << "Parameter upgrading center | Stealth tier" << endl;
		cout << "Current TP: " << playertp << endl;
		cout << "Current experience: " << experience << endl << endl;
		cout << "Ranged attack (RAT): " << playerrangedattack << " -> " << playerrangedattack + 1 << endl;
		if(masterstealth >= 1){
			cout << "Max SP             : " << playermaxspbase << " -> " << playermaxspbase + 1 << endl;
		}
		if(masterstealth >= 2){
			cout << "Resistance         : " << playermaxresistance << " -> " << playermaxresistance + 2 << endl;
		}
		cout << endl << "[1] Upgrade RAT        (-" << 90 - (12 * masterstealth) << " TP)" << endl;
		if(masterstealth >= 1){
			cout << "[2] Upgrade Max SP     (-" << 240 - (30 * masterstealth) << " TP)" << endl;
		}
		if(masterstealth >= 2){
			cout << "[3] Upgrade Resistance (-" << 120 - (12 * masterstealth) << " TP)" << endl;
		}
		cout << endl << "[q] Go back to the upgrading menu" << endl;
		cout << "[Any other key] Go back to the main menu" << endl;
		cin >> movement;
		clear();
		switch(movement){
		case '1' :
			if(playertp >= 90 - (12 * masterstealth)){
				playertp -= 90 - (12 * masterstealth);
				experience += 9 - (0.6 * masterstealth);
				playerrangedattack++;
				goto STEALTH;
			}
			else{
				cout << "You do not have enough Train Points for that!" << endl << endl;
			}
			break;
		case '2' :
			if(masterstealth >= 1){
				if(playertp >= 240 - (30 * masterstealth)){
					playertp -= 240 - (30 * masterstealth);
					experience += 24 - (1.5 * masterstealth);
					playermaxspbase++;
					playersp++;
					goto STEALTH;
				}
				else{
					cout << "You do not have enough Train Points for that!" << endl << endl;
				}
			}
			break;
		case '3' :
			if(masterstealth >= 2){
				if(playertp >= 120 - (12 * masterstealth)){
					playertp -= 120 - (12 * masterstealth);
					experience += 12 - (0.6 * masterstealth);
					playermaxresistance += 2;
					playerresistance += 2;
					goto STEALTH;
				}
				else{
					cout << "You do not have enough Train Points for that!" << endl << endl;
				}
			}
			break;
		case 'q' :
			goto UPGRADING;
			break;
		}
		break;
	case '2' :
STRENGTH:
		cout << "Parameter upgrading center | Strength tier" << endl;
		cout << "Current TP: " << playertp << endl;
		cout << "Current experience: " << experience << endl << endl;
		cout << "Attack (AT)        : " << playerattack << " -> " << playerattack + 1 << endl;
		if(masterstrength >= 1){
			cout << "Defense (DEF)      : " << playerdefense << " -> " << playerdefense + 1 << endl;
		}
		cout << endl << "[1] Upgrade AT         (-" << 80 - (12 * masterstrength) << " TP)" << endl;
		if(masterstrength >= 1){
			cout << "[2] Upgrade DEF        (-" << 80 - (9 * masterstrength) << " TP)" << endl;
		}
		cout << endl << "[q] Go back to the upgrading menu" << endl;
		cout << "[Any other key] Go back to the main menu" << endl;
		cin >> movement;
		clear();
		switch(movement){
		case '1' :
			if(playertp >= 80 - (12 * masterstrength)){
				playertp -= 80 - (12 * masterstrength);
				experience += 8 - (0.6 * masterstrength);
				playerattack++;
				goto STRENGTH;
			}
			else{
				cout << "You do not have enough Train Points for that!" << endl << endl;
			}
			break;
		case '2' :
			if(masterstrength >= 1){
				if(playertp >= 80 - (9 * masterstrength)){
					playertp -= 80 - (9 * masterstrength);
					experience += 8 - (0.45 * masterstrength);
					playerdefense++;
					goto STRENGTH;
				}
				else{
					cout << "You do not have enough Train Points for that!" << endl << endl;
				}
			}
			break;
		case 'q' :
			goto UPGRADING;
			break;
		}
		break;
	case '3' :
MAGIC:
		cout << "Parameter upgrading center | Magic tier" << endl;
		cout << "Current TP: " << playertp << endl;
		cout << "Current experience: " << experience << endl << endl;
		cout << "Magic attack (MAT) : " << playermagicattack << " -> " << playermagicattack + 1 << endl;
		if(mastermagic >= 2){
			cout << "Max MP             : " << playermaxmp << " -> " << playermaxmp + 1 << endl;
		}
		cout << endl << "[1] Upgrade MAT        (-" << 90 - (12 * mastermagic) << " TP)" << endl;
		if(mastermagic >= 2){
			cout << "[2] Upgrade Max MP     (-" << 240 - (30 * mastermagic) << " TP)" << endl;
		}
		cout << endl << "[q] Go back to the upgrading menu" << endl;
		cout << "[Any other key] Go back to the main menu" << endl;
		cin >> movement;
		clear();
		switch(movement){
		case '1' :
			if(playertp >= 90 - (12 * mastermagic)){
				playertp -= 90 - (12 * mastermagic);
				experience += 9 - (0.6 * mastermagic);
				playermagicattack++;
				goto MAGIC;
			}
			else{
				cout << "You do not have enough Train Points for that!" << endl << endl;
			}
			break;
		case '2' :
			if(mastermagic >= 2){
				if(playertp >= 240 - (30 * mastermagic)){
					playertp -= 240 - (30 * mastermagic);
					experience += 24 - (1.5 * mastermagic);
					playermaxmpbase++;
					playermp++;
					goto MAGIC;
				}
				else{
					cout << "You do not have enough Train Points for that!" << endl << endl;
				}
			}
			break;
		case 'q' :
			goto UPGRADING;
			break;
		}
		break;
	case '4' :
HEALTH:
		cout << "Parameter upgrading center | Health tier" << endl;
		cout << "Current TP: " << playertp << endl;
		cout << "Current experience: " << experience << endl << endl;
		cout << "Max Life           : " << playermaxlife << " -> " << playermaxlife + 10 << endl << endl;
		cout << "[1] Upgrade Max Life   (-" << 90 - (9 * masterhealth) << " TP)" << endl;
		cout << endl << "[q] Go back to the upgrading menu" << endl;
		cout << "[Any other key] Go back to the main menu" << endl;
		cin >> movement;
		clear();
		switch(movement){
		case '1' :
			if(playertp >= 90 - (9 * masterhealth)){
				playertp -= 90 - (9 * masterhealth);
				experience += 9 - (0.45 * masterhealth);
				playermaxlife += 10;
				playerlife += 10;
				goto HEALTH;
			}
			else{
				cout << "You do not have enough Train Points for that!" << endl << endl;
			}
			break;
		case 'q' :
			goto UPGRADING;
			break;
		}
		break;
	case 'w' :
XPCENTER:
		string xpinvest;

		cout << "Experience center" << endl;
		cout << "Current TP: " << playertp << endl;
		cout << "Current experience: " << experience << endl << endl;
		cout << "[1] Train" << endl;
		if(masterhealth + mastermagic + masterstealth + masterstrength >= 7){
			cout << "[2] Meditate {+1 skill point} (-200 XP)" << endl;
		}
		if(masterhealth + mastermagic + masterstealth + masterstrength <= 7){
			cout << "[2] Meditate {+1 skill point} (-140 XP)" << endl;
		}
		cout << endl << "[q] Go back to the upgrading menu" << endl;
		cout << "[Any other key] Go back to the main menu" << endl;
		cin >> movement;
		randomseed();
		clear();
		switch(movement){
		case '1' :
			cout << "Experience center | Train" << endl;
			cout << "Current TP: " << playertp << endl;
			cout << "Current experience: " << experience << endl << endl;
			cout << "[1] Train magic" << endl;
			cout << "[2] Train tactics" << endl;
			cout << endl << "[q] Go back to the upgrading menu" << endl;
			cout << "[Any other key] Go back to the main menu" << endl;
			cin >> movement;
			randomseed();
			clear();
			switch(movement){
			case '1' :
				cout << "Current experience: " << experience << endl << endl;
				cout << "How much XP you want to invest in training? Min 10 XP" << endl;
				cout << endl << "{Each XP adds up 4% of learning a skill}" << endl;
				cout << "(25 XP invested = 100% of learning a tier 1 skill)" << endl;
				cout << "(50 XP invested = 100% of learning a tier 2 skill)" << endl;
				cout << "(75 XP invested = 100% of learning a tier 3 skill)" << endl;
				cout << "[Note: If a tier 1 skill has a tier 2/3 version, you wont be able" << endl << "to unlock the tier 2/3 version until you unlock the tier 1 one]" << endl << endl;
				cin >> xpinvest;
				randomseed();
				stringtoint(xpinvest);
				clear();
				if(converter < 10){
					converter = 0;
					cout << "The minimum is 10 XP" << endl << endl;
					goto XPCENTER;
				}
				if(converter > experience){
					converter = 0;
					cout << "You haven't enough experience" << endl << endl;
					goto XPCENTER;
				}
				else{
					experience -= converter;
					subcriticalcheckerone = rand() % 101;
					if(converter <= 25){
						if(subcriticalcheckerone > converter * 4){
TIER1AFAILED:
							cout << "Bad luck! Training turned up with nothing new" << endl << endl;
						}
						else{
STARTTIER1A:
							subcriticalcheckertwo = rand() % 7;
TIER1A:
							if(grasslearnt == false && subcriticalcheckertwo == 1){
								grasslearnt = true;
								skilllearnt = 1;
								cout << "'Grass' was learnt!" << endl << endl;
							}
							if(darklearnt == false && subcriticalcheckertwo == 2){
								darklearnt = true;
								skilllearnt = 1;
								cout << "'Dark' was learnt!" << endl << endl;
							}
							if(lightlearnt == false && subcriticalcheckertwo == 3){
								lightlearnt = true;
								skilllearnt = 1;
								cout << "'Light' was learnt!" << endl << endl;
							}
							if(firelearnt == false && subcriticalcheckertwo == 4){
								firelearnt = true;
								skilllearnt = 1;
								cout << "'Fire' was learnt!" << endl << endl;
							}
							if(waterlearnt == false && subcriticalcheckertwo == 5){
								waterlearnt = true;
								skilllearnt = 1;
								cout << "'Water' was learnt!" << endl << endl;
							}
							if(groundlearnt == false && subcriticalcheckertwo == 6){
								groundlearnt = true;
								skilllearnt = 1;
								cout << "'Ground' was learnt!" << endl << endl;
							}
							if(skilllearnt == 0){
								subcriticalcheckertwo = 1;
								while((subcriticalcheckertwo == 1 && grasslearnt == true) || (subcriticalcheckertwo == 2 && darklearnt == true) || (subcriticalcheckertwo == 3 && lightlearnt == true)
								|| (subcriticalcheckertwo == 4 && firelearnt == true) || (subcriticalcheckertwo == 5 && waterlearnt == true) || (subcriticalcheckertwo == 6 && groundlearnt == true)){
									subcriticalcheckertwo++;
									if(subcriticalcheckertwo > 6){
										goto TIER1AFAILED;
									}
								}
								goto TIER1A;
							}
							skilllearnt = 0;
						}
						converter = 0;
						goto XPCENTER;
					}
					if(converter <= 50 && converter > 25){
						if(subcriticalcheckerone > (converter - 25) * 4){
							goto STARTTIER1A;
						}
						else{
STARTTIER2A:
							subcriticalcheckertwo = rand() % 8;
TIER2A:
							if(frostbitelearnt == false && subcriticalcheckertwo == 1){
								frostbitelearnt = true;
								skilllearnt = 1;
								cout << "'Frostbite' was learnt!" << endl << endl;
							}
							if(ustilagolearnt == false && subcriticalcheckertwo == 2){
								ustilagolearnt = true;
								skilllearnt = 1;
								cout << "'Ustilago' was learnt!" << endl << endl;
							}
							if(isolationlearnt == false && subcriticalcheckertwo == 3){
								isolationlearnt = true;
								skilllearnt = 1;
								cout << "'Perversion' was learnt!" << endl << endl;
							}
							if(illuminationlearnt == false && subcriticalcheckertwo == 4){
								illuminationlearnt = true;
								skilllearnt = 1;
								cout << "'Illumination' was learnt!" << endl << endl;
							}
							if(flarelearnt == false && subcriticalcheckertwo == 5){
								flarelearnt = true;
								skilllearnt = 1;
								cout << "'Flare' was learnt!" << endl << endl;
							}
							if(hydrolearnt == false && subcriticalcheckertwo == 6){
								hydrolearnt = true;
								skilllearnt = 1;
								cout << "'Hydro' was learnt!" << endl << endl;
							}
							if(shakelearnt == false && subcriticalcheckertwo == 7){
								shakelearnt = true;
								skilllearnt = 1;
								cout << "'Shake' was learnt!" << endl << endl;
							}
							if(skilllearnt == 0){
								subcriticalcheckertwo = 1;
								while((subcriticalcheckertwo == 1 && frostbitelearnt == true) || (subcriticalcheckertwo == 2 && ustilagolearnt == true) || (subcriticalcheckertwo == 3 && isolationlearnt == true)
								|| (subcriticalcheckertwo == 4 && illuminationlearnt == true) || (subcriticalcheckertwo == 5 && flarelearnt == true) || (subcriticalcheckertwo == 6 && hydrolearnt == true)
								|| (subcriticalcheckertwo == 7 && shakelearnt == true)){
									subcriticalcheckertwo++;
									if(subcriticalcheckertwo > 7){
										goto STARTTIER1A;
									}
								}
								goto TIER2A;
							}
							skilllearnt = 0;
						}
						converter = 0;
						goto XPCENTER;
					}
					if(converter > 50){
						if(subcriticalcheckerone > (converter - 50) * 4){
							goto STARTTIER2A;
						}
						else{
							subcriticalcheckertwo = rand() % 8;
TIER3A:
							if(hypothermialearnt == false && subcriticalcheckertwo == 1){
								hypothermialearnt = true;
								skilllearnt = 1;
								cout << "'Hypothermia' was learnt!" << endl << endl;
							}
							if(phytoplasmalearnt == false && subcriticalcheckertwo == 2){
								phytoplasmalearnt = true;
								skilllearnt = 2;
								cout << "'Phythoplasma' was learnt!" << endl << endl;
							}
							if(corruptionlearnt == false && subcriticalcheckertwo == 3){
								corruptionlearnt = true;
								skilllearnt = 3;
								cout << "'Corruption' was learnt!" << endl << endl;
							}
							if(lethalblindnesslearnt == false && subcriticalcheckertwo == 4){
								lethalblindnesslearnt = true;
								skilllearnt = 4;
								cout << "'Lethal Blindness' was learnt!" << endl << endl;
							}
							if(hyperthermialearnt == false && subcriticalcheckertwo == 5){
								hyperthermialearnt = true;
								skilllearnt = 5;
								cout << "'Hyperthermia' was learnt!" << endl << endl;
							}
							if(drownlearnt == false && subcriticalcheckertwo == 6){
								drownlearnt = true;
								skilllearnt = 6;
								cout << "'Drown' was learnt!" << endl << endl;
							}
							if(earthquakelearnt == false && subcriticalcheckertwo == 7){
								earthquakelearnt = true;
								skilllearnt = 7;
								cout << "'Earthquake' was learnt!" << endl << endl;
							}
							if(skilllearnt == 0){
								subcriticalcheckertwo = 1;
								while((subcriticalcheckertwo == 1 && hypothermialearnt == true) || (subcriticalcheckertwo == 2 && phytoplasmalearnt == true) || (subcriticalcheckertwo == 3 && corruptionlearnt == true)
								|| (subcriticalcheckertwo == 4 && lethalblindnesslearnt == true) || (subcriticalcheckertwo == 5 && hyperthermialearnt == true) || (subcriticalcheckertwo == 6 && drownlearnt == true)
								|| (subcriticalcheckertwo == 7 && earthquakelearnt == true)){
									subcriticalcheckertwo++;
									if(subcriticalcheckertwo > 7){
										goto STARTTIER2A;
									}
								}
								goto TIER3A;
							}
							skilllearnt = 0;
						}
						converter = 0;
						goto XPCENTER;
					}
				}
				break;
			case '2' :
				cout << "Current experience: " << experience << endl << endl;
				cout << "How much XP you want to invest in training? Min 10 XP" << endl;
				cout << endl << "{Each XP adds up 4% of learning a skill}" << endl;
				cout << "(25 XP invested = 100% of learning a tier 1 skill)" << endl;
				cout << "(50 XP invested = 100% of learning a tier 2 skill)" << endl;
				cout << "(75 XP invested = 100% of learning a tier 3 skill)" << endl;
				cout << "[Note: If a tier 1 skill has a tier 2/3 version, you wont be able" << endl << "to unlock the tier 2/3 version until you unlock the tier 1 one]" << endl << endl;
				cin >> xpinvest;
				randomseed();
				stringtoint(xpinvest);
				clear();
				if(converter < 10){
					converter = 0;
					cout << "The minimum is 10 XP" << endl << endl;
					goto XPCENTER;
				}
				if(converter > experience){
					converter = 0;
					cout << "You haven't enough experience" << endl << endl;
					goto XPCENTER;
				}
				else{
					experience -= converter;
					subcriticalcheckerone = rand() % 101;
					if(converter <= 25){
						if(subcriticalcheckerone > converter * 4){
TIER1BFAILED:
							cout << "Bad luck! Training turned up with nothing new" << endl << endl;
						}
						else{
STARTTIER1B:
							subcriticalcheckertwo = rand() % 1;
TIER1B:
							if(skilllearnt == 0){
								subcriticalcheckertwo = 1;
								while(1){
									subcriticalcheckertwo++;
									if(subcriticalcheckertwo > 1){
										goto TIER1BFAILED;
									}
								}
								goto TIER1B;
							}
							skilllearnt = 0;
						}
						converter = 0;
						goto XPCENTER;
					}
					if(converter <= 50 && converter > 25){
						if(subcriticalcheckerone > (converter - 25) * 4){
							goto STARTTIER1B;
						}
						else{
STARTTIER2B:
							subcriticalcheckertwo = rand() % 1;
TIER2B:
							if(skilllearnt == 0){
								subcriticalcheckertwo = 1;
								while(1){
									subcriticalcheckertwo++;
									if(subcriticalcheckertwo > 1){
										goto STARTTIER1B;
									}
								}
								goto TIER2B;
							}
							skilllearnt = 0;
						}
						converter = 0;
						goto XPCENTER;
					}
					if(converter > 50){
						if(subcriticalcheckerone > (converter - 50) * 4){
							goto STARTTIER2B;
						}
						else{
							subcriticalcheckertwo = rand() % 1;
TIER3B:
							if(skilllearnt == 0){
								subcriticalcheckertwo = 1;
								while(1){
									subcriticalcheckertwo++;
									if(subcriticalcheckertwo > 1){
										goto STARTTIER2B;
									}
								}
								goto TIER3B;
							}
							skilllearnt = 0;
						}
						converter = 0;
						goto XPCENTER;
					}
				}
				break;
			case 'q' :
				goto UPGRADING;
				break;
			}
		case '2' :
			if(masterhealth + mastermagic + masterstealth + masterstrength >= 7){
				if(experience >= 200){
					experience -= 200;
					succesfulbuy = true;
				}
			}
			if(masterhealth + mastermagic + masterstealth + masterstrength <= 7){
				if(experience >= 140){
					experience -= 140;
					succesfulbuy = true;
				}
			}
			if(succesfulbuy == true){
APPLYSKILL:
				cout << "Apply skill point to: " << endl << endl;
				cout << "[1] Stealth" << endl;
				cout << "[2] Strength" << endl;
				cout << "[3] Magic" << endl;
				cout << "[4] Health" << endl;
				cout << "[Any other key] Go back to the main menu" << endl;
				cin >> movement;
				clear();
				switch(movement){
				case '1' :
					masterstealth++;
					break;
				case '2' :
					masterstrength++;
					break;
				case '3' :
					mastermagic++;
					break;
				case '4' :
					masterhealth++;
					break;
				default : goto APPLYSKILL;
				}
				succesfulbuy = false;
			}
			goto XPCENTER;
			break;
		case 'q' :
			goto UPGRADING;
			break;
		}
		break;
	}
}

void player::customizecharacter(int type){
	FILE * character;
	char answer;
	if(type == 1){
CUSTOMIZATIONSTART:
		character = fopen("character.txt","w+");
		cout << "                                ";
		clear();
		masterstealth = 0;
		masterstrength = 0;
		mastermagic = 0;
		masterhealth = 0;
		cout << "Welcome to the character customization!" << endl;
		cout << "Just answer some questions and your character will have its own personality!" << endl;
		_getch();
CUSTOMIZATION:
		clear();
		cout << "1º Do you want to be feared, or to be admired?" << endl;
		cout << endl << "1: Feared" << endl;
		cout << "2: Admired" << endl;
		movement = _getch();
		clear();
		switch(movement){
			case '1' :
				cout << "2º Do you like to act slow and steady, or quickly?" << endl;
				cout << endl << "1: Slow and steady" << endl;
				cout << "2: Quickly" << endl;
				answer = _getch();
				switch(answer){
				case '1' :
					masterstealth++;
					break;
				case '2' :
					masterstrength++;
					break;
				default :
					masterstealth = 0;
					masterstrength = 0;
					mastermagic = 0;
					masterhealth = 0;
					goto CUSTOMIZATION;
					break;
				}
				break;
			case '2' :
				cout << "2º Do you want to use magic to punish the evil, or to help the poor?" << endl;
				cout << endl << "1: Punish the evil" << endl;
				cout << "2: Help the poor" << endl;
				answer = _getch();
				switch(answer){
				case '1' :
					mastermagic++;
					break;
				case '2' :
					masterhealth++;
					break;
				default :
					masterstealth = 0;
					masterstrength = 0;
					mastermagic = 0;
					masterhealth = 0;
					goto CUSTOMIZATION;
					break;
				}
				break;
			default :
				masterstealth = 0;
				masterstrength = 0;
				mastermagic = 0;
				masterhealth = 0;
				goto CUSTOMIZATION;
				break;
		}
		clear();
		cout << "3º You find an old man with a knife stabbed in his chest.\nSeems like the bandit who caused it is running away" << endl;
		cout << endl << "1: Kill the bandit with your ranged weapon" << endl;
		cout << "2: Finish the old man and loot him" << endl;
		cout << "3: Heal the old man with magic" << endl;
		cout << "4: Stop the bandit with magic and take him to prison" << endl;
		movement = _getch();
		switch(movement){
			case '1' :
				masterstealth++;
				break;
			case '2' :
				masterstrength++;
				break;
			case '3' :
				masterhealth++;
				break;
			case '4' :
				mastermagic++;
				break;
			default :
				masterstealth = 0;
				masterstrength = 0;
				mastermagic = 0;
				masterhealth = 0;
				goto CUSTOMIZATION;
				break;
		}
		clear();
		cout << "4º You find a group of bandits.\nThey are well equipped, and they seem to be looking for you" << endl;
		cout << endl << "1: Kill them one by one using magic" << endl;
		cout << "2: Deploy shields on the ground to run away safely" << endl;
		cout << "3: Run away using stealth" << endl;
		cout << "4: Quickly murder them before they know what's happening" << endl;
		movement = _getch();
		switch(movement){
			case '1' :
				mastermagic++;
				break;
			case '2' :
				masterhealth++;
				break;
			case '3' :
				masterstealth++;
				break;
			case '4' :
				masterstrength++;
				break;
			default :
				masterstealth = 0;
				masterstrength = 0;
				mastermagic = 0;
				masterhealth = 0;
				goto CUSTOMIZATION;
				break;
		}
		clear();
		cout << "5º You hear a voice. 'What are your dreams, young adventurer?'" << endl;
		cout << endl << "1: To find the secrets" << endl;
		cout << "2: To reach world peace" << endl;
		cout << "3: To destroy the evil without mercy" << endl;
		movement = _getch();
		switch(movement){
			case '1' :
				clear();
				cout << "5.2º What secrets?" << endl;
				cout << endl << "1: The secrets of stealth" << endl;
				cout << "2: The secrets of magic" << endl;
				answer = _getch();
				switch(answer){
				case '1' :
					masterstealth++;
					break;
				case '2' :
					mastermagic++;
					break;
				default :
					masterstealth = 0;
					masterstrength = 0;
					mastermagic = 0;
					masterhealth = 0;
					goto CUSTOMIZATION;
					break;
				}
				break;
			case '2' :
				masterhealth++;
				break;
			case '3' :
				masterstrength++;
				break;
			default :
				masterstealth = 0;
				masterstrength = 0;
				mastermagic = 0;
				masterhealth = 0;
				goto CUSTOMIZATION;
				break;
		}
		clear();
		cout << "Okay! The stats of your character will be:" << endl;
		cout << endl << "Stealth skill : " << masterstealth << endl;
		cout << "Strength skill: " << masterstrength << endl;
		cout << "Magic skill   : " << mastermagic << endl;
		cout << "Health skill  : " << masterhealth << endl;
		_getch();
		encrypt(intEncrypter(masterstealth),key);					// Stealth skill
		fprintf(character,"%s ",encrypter.c_str());
		encrypt(intEncrypter(masterstrength),key);					// Strength skill
		fprintf(character,"%s ",encrypter.c_str());
		encrypt(intEncrypter(mastermagic),key);						// Magic skill
		fprintf(character,"%s ",encrypter.c_str());
		encrypt(intEncrypter(masterhealth),key);					// Health skill
		fprintf(character,"%s ",encrypter.c_str());
		fclose(character);
		clearcolors(15,8);
	}
	if(type == 2){
		character = fopen("character.txt","r");
		if(character != NULL){
			rewind(character);
			cout << "Loading character file..." << endl;
				fscanf(character,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			masterstealth = converter;
				fscanf(character,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			masterstrength = converter;
				fscanf(character,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			mastermagic = converter;
				fscanf(character,"%s",retriever);
				chartostring = retriever;
				decrypt(chartostring,key);
				stringtoint(encrypter);
			masterhealth = converter;
			fclose(character);
			if((masterstealth + masterstrength + mastermagic + masterhealth) != 4){
				cout << "character.txt is corrupted" << endl << "You will be now redirected to the 'Character customization'" << endl;
				_getch();
				clearcolors(LIGHTGREY,BLACK);
				goto CUSTOMIZATIONSTART;
			}
			else{
				cout << "Loaded succesfully!" << endl;
				cout << endl << "Stealth skill : " << masterstealth << endl;
				cout << "Strength skill: " << masterstrength << endl;
				cout << "Magic skill   : " << mastermagic << endl;
				cout << "Health skill  : " << masterhealth << endl;
			}
			_getch();
			clear();
			fclose(character);
		}
		else{
			cout << "Warning! character.txt not found!" << endl << "You will be now redirected to the 'Character customization'" << endl;
			_getch();
			clearcolors(LIGHTGREY,BLACK);
			goto CUSTOMIZATIONSTART;
		}
	}
}

void player::determinemaxshields(){
	if(playershields.sayequippedshield() == 1){
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
			enemylife += 0.05 * (consecutiveattacks * mainplayer.saycriticalpower());
			enemylife += enemydefense;
			cout << playername;
			cout << " made a critical hit, causing " << mainplayer.saycriticalpower() + weapons.sayrealattack() - enemydefense - 0.05 * (consecutiveattacks * mainplayer.saycriticalpower()) << " damage!" << endl;
		}
		else{
			enemylife -= mainplayer.attackparameter();
			enemylife -= weapons.sayrealattack();
			enemylife += 0.05 * (consecutiveattacks * mainplayer.attackparameter());
			enemylife += enemydefense;
			cout << playername;
			cout << " inflicted " << mainplayer.attackparameter() + weapons.sayrealattack() - enemydefense - 0.05 * (consecutiveattacks * mainplayer.attackparameter()) << " damage to the enemy" << endl;
		}
	}
	if(damagepilleffect == true){
		if(subcriticalcheckerone <= mainplayer.saycriticalchecker()){
			cout << "\a";
			enemylife -= mainplayer.saycriticalpower();
			enemylife -= weapons.sayrealattack();
			enemylife += 0.05 * (consecutiveattacks * mainplayer.saycriticalpower());
			enemylife += enemydefense;
			cout << playername;
			cout << " made a critical hit, causing " << mainplayer.saycriticalpower() + weapons.sayrealattack() + 10 - enemydefense - 0.05 * (consecutiveattacks * mainplayer.saycriticalpower()) << " damage!" << endl;
		}
		else{
			enemylife -= mainplayer.attackparameter();
			enemylife -= weapons.sayrealattack();
			enemylife += 0.05 * (consecutiveattacks * mainplayer.attackparameter());
			enemylife += enemydefense;
			enemylife -= 10;
			cout << playername;
			cout << " inflicted " << mainplayer.attackparameter() + weapons.sayrealattack() + 10 - enemydefense - 0.05 * (consecutiveattacks * mainplayer.attackparameter()) << " damage to the enemy" << endl;
		}
	}
	consecutiveattacks++;
	attackmade = true;
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

void enemy::magicattacked(int type, float strength, int mpdecrease, string skillname){

	for(int n = 1; n <= mpdecrease; n++){
		mainplayer.decreaseplayermp();
	}

	if(type == 1){
		if(enemytype == 6){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 2 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 2 * strength << " damage to the enemy by using " << skillname << "! It was extremely effective!" << endl;
		}
		if(enemytype == 4 || enemytype == 8){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength << " damage to the enemy by using " << skillname << "! It was very effective!" << endl;
		}
		if(enemytype == 3 || enemytype == 5 || enemytype == 7){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength << " damage to the enemy by using " << skillname << ". It wasn't very effective..." << endl;
		}
		if(enemytype == 1){
			enemylife += (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You healed the enemy " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " life points by using " << skillname << "!" << endl;
		}
		if(enemytype == 2){
			enemylife -= (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " damage to the enemy by using " << skillname << "!" << endl;
		}
	}
	if(type == 3){
		if(enemytype == 1 || enemytype == 2 || enemytype == 4 || enemytype == 5){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength << " damage to the enemy by using " << skillname << "! It was very effective!" << endl;
		}
		if(enemytype == 8){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength << " damage to the enemy by using " << skillname << ". It wasn't very effective..." << endl;
		}
		if(enemytype == 3 || enemytype == 6){
			enemylife += (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You healed the enemy " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " life points by using " << skillname << "!" << endl;
		}
		if(enemytype == 7){
			enemylife -= (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " damage to the enemy by using " << skillname << "!" << endl;
		}
	}
	if(type == 4){
		if(enemytype == 3){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 2 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 2 * strength << " damage to the enemy by using " << skillname << "! It was extremely effective!" << endl;
		}
		if(enemytype == 5){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength << " damage to the enemy by using " << skillname << ". It wasn't very effective..." << endl;
		}
		if(enemytype == 4 || enemytype == 1){
			enemylife += (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You healed the enemy " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " life points by using " << skillname << "!" << endl;
		}
		if(enemytype == 7 || enemytype == 2 || enemytype == 8  || enemytype == 6){
			enemylife -= (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " damage to the enemy by using " << skillname << "!" << endl;
		}
	}
	if(type == 5){
		if(enemytype == 3 || enemytype == 7 || enemytype == 1 || enemytype == 2){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength << " damage to the enemy by using " << skillname << "! It was very effective!" << endl;
		}
		if(enemytype == 6 || enemytype == 8){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength << " damage to the enemy by using " << skillname << ". It wasn't very effective..." << endl;
		}
		if(enemytype == 4 || enemytype == 5){
			enemylife += (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You healed the enemy " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " life points by using " << skillname << "!" << endl;
		}
	}
	if(type == 6){
		if(enemytype == 5){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 2 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 2 * strength << " damage to the enemy by using " << skillname << "! It was extremely effective!" << endl;
		}
		if(enemytype == 7 || enemytype == 8){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength << " damage to the enemy by using " << skillname << "! It was very effective!" << endl;
		}
		if(enemytype == 3){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength << " damage to the enemy by using " << skillname << ". It wasn't very effective..." << endl;
		}
		if(enemytype == 6 || enemytype == 1){
			enemylife += (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You healed the enemy " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " life points by using " << skillname << "!" << endl;
		}
		if(enemytype == 2 || enemytype == 4){
			enemylife -= (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " damage to the enemy by using " << skillname << "!" << endl;
		}
	}
	if(type == 7){
		if(enemytype == 6){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 2 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 2 * strength << " damage to the enemy by using " << skillname << "! It was extremely effective!" << endl;
		}
		if(enemytype == 1){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength << " damage to the enemy by using " << skillname << "! It was very effective!" << endl;
		}
		if(enemytype == 5){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength << " damage to the enemy by using " << skillname << ". It wasn't very effective..." << endl;
		}
		if(enemytype == 7){
			enemylife += (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You healed the enemy " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " life points by using " << skillname << "!" << endl;
		}
		if(enemytype == 2 || enemytype == 3 || enemytype == 4 || enemytype == 8){
			enemylife -= (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " damage to the enemy by using " << skillname << "!" << endl;
		}
	}
	if(type == 8){
		if(enemytype == 5){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 2 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 2 * strength << " damage to the enemy by using " << skillname << "! It was extremely effective!" << endl;
		}
		if(enemytype == 4){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 1.5 * strength << " damage to the enemy by using " << skillname << "! It was very effective!" << endl;
		}
		if(enemytype == 1){
			enemylife -= ((mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength);
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * 0.5 * strength << " damage to the enemy by using " << skillname << ". It wasn't very effective..." << endl;
		}
		if(enemytype == 8){
			enemylife += (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You healed the enemy " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " life points by using " << skillname << "!" << endl;
		}
		if(enemytype == 6 || enemytype == 3 || enemytype == 7 || enemytype == 2){
			enemylife -= (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength;
			cout << "You dealt " << (mainplayer.saymagicattack() + magicweapon.sayrealmagicattack()) * strength << " damage to the enemy by using " << skillname << "!" << endl;
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
	enemytype = rand() % 8 + 1;
	enemyint = rand() % 3 + 1;
	healthdrink = rand() % 1;
}

void enemy::randomizeparameters(){
	enemymaxlife += rand() % 25 + 2;
	enemyattack += rand() % 3 + 1;
	enemydefense += rand() % 2;
	enemylife = enemymaxlife;
}

void weapon::determinerealattack(){
	realattack = (attack * mainplayer.attackparameter());
}

void ranged::determinerealattack(){
	realattack = (attack * mainplayer.sayrangedattack());
}

void magic::determinerealmagicattack(){
	realmagicattack = (magicattack * mainplayer.saymagicattack());
}

void player::determinemaxsp(){
	playermaxsp = (playermaxspbase + rangedweapon.saysp1());
}

void player::determinemaxmp(){
	playermaxmp = (playermaxmpbase + magicweapon.saymp1());
}

void enemy::victorychecker(){
	if(enemylife <= 0 || runawayfrombattle == true){
		clearcolors(7,0);
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

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (15 + (backgroundcolor * 16)) );
		cout << playername << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );

	if(mainplayer.saylife() <= mainplayer.saymaxlife() * 0.25){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12 + (backgroundcolor * 16)) );
	}
		cout << "Life = " << mainplayer.saylife() << "/" << mainplayer.saymaxlife();

		if(mainplayer.sayshields() <= 0){
			mainplayer.increaserecharge();
			if(mainplayer.sayrechargemeter() >= 100){
				mainplayer.restoreshields();
			}
		}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );

	cout << " | ";

	if(mainplayer.sayshields() <= 0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (3 + (backgroundcolor * 16)) );
		cout << "Shields = Recharge: " << mainplayer.sayrechargemeter() << "%";
	}
	else{
		cout << "Shields = " << mainplayer.sayshields() << "/" << mainplayer.saymaxshields();
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );

	cout << " | ";

	if(mainplayer.saysp() <= mainplayer.saymaxsp() * 0.1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (8 + (backgroundcolor * 16)) );
	}
		cout << "SP = " << mainplayer.saysp() << "/" << mainplayer.saymaxsp();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );

	cout << " | ";

	if(mainplayer.saymp() <= mainplayer.saymaxmp() * 0.1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (8 + (backgroundcolor * 16)) );
	}
		cout << "MP = " << mainplayer.saymp() << "/" << mainplayer.saymaxmp() << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );

	if(mainplayer.sayresistance() <= 10){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12 + (backgroundcolor * 16)) );
	}
		cout << "Resistance = " << mainplayer.sayresistance() << "/" << mainplayer.saymaxresistance();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );

	cout << " | ";

	if(mainplayer.sayultra() >= 100){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (13 + (backgroundcolor * 16)) );
	}
		cout << "Ultra meter = " << mainplayer.sayultra();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );

	cout << " | Distance = ";
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
	cout << "AT = " << mainplayer.attackparameter() << " + " << weapons.sayattack() * 100 << "%";
	cout << " | ";
	cout << "MAT = " << mainplayer.saymagicattack() << " + " << magicweapon.saymagicattack() * 100 << "%";
	cout << " | RAT = " << mainplayer.sayrangedattack() << " + " << rangedweapon.sayattack() * 100 << "%";
	cout << " | DEF = " << mainplayer.saydefense() << endl;
	cout << "Effects = ";
	if(damagepilleffect == true){
		cout << "[Damage Pill] " << endl;
	}
	else{
		cout << "None" << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (8 + (backgroundcolor * 16)) );
		printf("\n[q] Meelee attack [w] Ranged attack\n");
		printf("[2] Items         [3] Special       [4] Magic\n");
		printf("[5] Move          [6] Rest");
		if(mainplayer.sayultra() >= 100){
			cout << "          [7] Ultra";
		}
		printf("\n[p] Other\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );
}

void battle(){
EVENT:
	if(load == true){
		load = false;
		traveling();
	}
	clear();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (8 + (0 * 16)) );
		if(start == true){
			cout << "Name applied correctly" << endl;
		}
		cout << "Press always any key to show the next lines of text" << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (0 * 16)) );

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

	if(battletype == 1 || battletype == 2){
		if(battletype == 1){
			clearcolors(7,0);
			backgroundcolor = 0;
		}
		if(battletype == 2){
			clearcolors(7,4);
			backgroundcolor = 4;
		}
		while(1){
STARTBATTLE:
			mainplayer.determinecriticalpower();
			if(battletype == 1){
				commonenemy.determinecriticalpower();
			}
			if(battletype == 2){
				boss.determinecriticalpower();
			}
			weapons.determineattack();
			weapons.determinerealattack();
			rangedweapon.determineattack();
			rangedweapon.determinerealattack();
			magicweapon.determinemagicattack();
			magicweapon.determinerealmagicattack();
			mainplayer.determinemaxshields();
			mainplayer.determinemaxsp();
			mainplayer.determinemaxmp();

			randomseed();

			defeat();
			if(battletype == 1){
				commonenemy.victorychecker();
				if(commonenemy.saylife() <= 0 || runawayfrombattle == true){
					runawayfrombattle = false;
					distanceenemy = 3;
					goto EVENT;
				}
			}
			if(battletype == 2){
				boss.victorychecker();
				if(boss.saylife() <= 0 || runawayfrombattle == true){
					runawayfrombattle = false;
					distanceenemy = 3;
					goto EVENT;
				}
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
					if(battletype == 1){
						commonenemy.enemyattacked();
					}
					if(battletype == 2){
						boss.enemyattacked();
					}
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
					if(battletype == 1){
						commonenemy.rangedattacked();
					}
					if(battletype == 2){
						boss.rangedattacked();
					}
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
				clearcolors(7,backgroundcolor);
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
						cout << "Used Quick Eye!" << endl;
						cout << "The enemy couldn't react!" << endl << endl;
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
				cout << "List of Magic learned:" << endl << endl;
				cout << "[1] Meditate			[5 MP]" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
				cout << "{Tier 1} Heals the player by 60 life points" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				cout << "[2] Ice				[2 MP]" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
				cout << "{Tier 1} [Ice] Harms the enemy using the Ice element" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				if(mainplayer.saygrasslearnt() == true){
					cout << "[3] Grass			[2 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 1} [Grass] Harms the enemy using the Grass element" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.saydarklearnt() == true){
					cout << "[4] Darkness			[3 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 1} [Darkness] Harms the enemy using the Darkness element" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.saylightlearnt() == true){
					cout << "[5] Light			[1 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 1} [Light] Harms the enemy using the Light element" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayfirelearnt() == true){
					cout << "[6] Fire			[3 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 1} [Fire] Harms the enemy using the Fire element" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.saywaterlearnt() == true){
					cout << "[7] Water			[2 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 1} [Water] Harms the enemy using the Water element" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.saygroundlearnt() == true){
					cout << "[8] Ground			[2 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 1} [Ground] Harms the enemy using the Ground element" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayfrostbitelearnt() == true){
					cout << "[9] Frostbite			[5 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 2} [Ice] Puts the enemy through an extremely low temperature" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayustilagolearnt() == true){
					cout << "[0] Ustilago			[5 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 2} [Grass] Makes parasites grow on the enemy" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayisolationlearnt() == true){
					cout << "[q] Isolation			[7 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 2} [Darkness] Puts the enemy through the most absolute darkness" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayilluminationlearnt() == true){
					cout << "[w] Illumination		[4 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 2} [Light] Causes the enemy a short state of severe amnesia" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayflarelearnt() == true){
					cout << "[e] Flare			[7 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 2} [Fire] Puts the enemy on fire, causing severe damage" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayhydrolearnt() == true){
					cout << "[r] Hydro			[6 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 2} [Water] Puts the enemy in a strong water vortex" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayshakelearnt() == true){
					cout << "[t] Shake			[5 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 2} [Ground] Causes a small earthquake that stuns the enemy" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayhypothermialearnt() == true){
					cout << "[y] Hypothermia			[10 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 3} [Ice] Severely freezes the enemy" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayphytoplasmalearnt() == true){
					cout << "[u] Phytoplasma			[10 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 3} [Grass] Makes thousands of deadly parasites grow on the enemy" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.saycorruptionlearnt() == true){
					cout << "[i] Corruption			[14 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 3} [Darkness] Corrupts the inner thoughts of the enemy" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.saylethalblindnesslearnt() == true){
					cout << "[o] Lethal Blindness		[7 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 3} [Light] Brutally stuns the enemy's brain" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayhyperthermialearnt() == true){
					cout << "[p] Hyperthermia		[14 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 3} [Fire] Burns all the body parts of the enemy with the deadliest fire" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.saydrownlearnt() == true){
					cout << "[a] Drown			[12 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 3} [Water] Suffocates the enemy causing extreme damage" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				if(mainplayer.sayearthquakelearnt() == true){
					cout << "[s] Earthquake			[10 MP]" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (DARKGREY + (BLACK * 16)) );
					cout << "{Tier 3} [Ground] Creates a deadly earthquake below the enemy" << endl;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (LIGHTGREY + (BLACK * 16)) );
				}
				cout << endl << "Type any other key to go back to the main menu" << endl;
				cin >> movement;
				clearcolors(7,backgroundcolor);
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
					if(mainplayer.saymp() >= 2){
						if(battletype == 1){
							commonenemy.magicattacked(7,1,2,"Ice");
						}
						if(battletype == 2){
							boss.magicattacked(7,1,2,"Ice");
						}
					}
					else{
						cout << "You haven't enough MP left to perform this move!" << endl;
					}
					break;
				case '3' :
					if(mainplayer.saygrasslearnt() == true){
						if(mainplayer.saymp() >= 2){
							if(battletype == 1){
								commonenemy.magicattacked(1,1,2,"Grass");
							}
							if(battletype == 2){
								boss.magicattacked(1,1,2,"Grass");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case '4' :
					if(mainplayer.saydarklearnt() == true){
						if(mainplayer.saymp() >= 3){
							if(battletype == 1){
								commonenemy.magicattacked(3,1,3,"Darkness");
							}
							if(battletype == 2){
								boss.magicattacked(3,1,3,"Darkness");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case '5' :
					if(mainplayer.saylightlearnt() == true){
						if(mainplayer.saymp() >= 1){
							if(battletype == 1){
								commonenemy.magicattacked(4,1,1,"Light");
							}
							if(battletype == 2){
								boss.magicattacked(4,1,1,"Light");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case '6' :
					if(mainplayer.sayfirelearnt() == true){
						if(mainplayer.saymp() >= 3){
							if(battletype == 1){
								commonenemy.magicattacked(5,1,3,"Fire");
							}
							if(battletype == 2){
								boss.magicattacked(5,1,3,"Fire");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case '7' :
					if(mainplayer.saywaterlearnt() == true){
						if(mainplayer.saymp() >= 2){
							if(battletype == 1){
								commonenemy.magicattacked(6,1,2,"Water");
							}
							if(battletype == 2){
								boss.magicattacked(6,1,2,"Water");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case '8' :
					if(mainplayer.saygroundlearnt() == true){
						if(mainplayer.saymp() >= 2){
							if(battletype == 1){
								commonenemy.magicattacked(8,1,2,"Ground");
							}
							if(battletype == 2){
								boss.magicattacked(8,1,2,"Ground");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case '9' :
					if(mainplayer.sayfrostbitelearnt() == true){
						if(mainplayer.saymp() >= 5){
							if(battletype == 1){
								commonenemy.magicattacked(7,1.7,5,"Frostbite");
							}
							if(battletype == 2){
								boss.magicattacked(7,1.7,5,"Frostbite");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case '0' :
					if(mainplayer.sayustilagolearnt() == true){
						if(mainplayer.saymp() >= 5){
							if(battletype == 1){
								commonenemy.magicattacked(1,1.7,5,"Ustilago");
							}
							if(battletype == 2){
								boss.magicattacked(1,1.7,5,"Ustilago");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 'q' :
					if(mainplayer.sayisolationlearnt() == true){
						if(mainplayer.saymp() >= 7){
							if(battletype == 1){
								commonenemy.magicattacked(3,1.7,7,"Isolation");
							}
							if(battletype == 2){
								boss.magicattacked(3,1.7,7,"Isolation");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 'w' :
					if(mainplayer.sayilluminationlearnt() == true){
						if(mainplayer.saymp() >= 4){
							if(battletype == 1){
								commonenemy.magicattacked(4,1.7,4,"Illumination");
							}
							if(battletype == 2){
								boss.magicattacked(4,1.7,4,"Illumination");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 'e' :
					if(mainplayer.sayflarelearnt() == true){
						if(mainplayer.saymp() >= 7){
							if(battletype == 1){
								commonenemy.magicattacked(5,1.7,7,"Flare");
							}
							if(battletype == 2){
								boss.magicattacked(5,1.7,7,"Flare");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 'r' :
					if(mainplayer.sayhydrolearnt() == true){
						if(mainplayer.saymp() >= 6){
							if(battletype == 1){
								commonenemy.magicattacked(6,1.7,6,"Hydro");
							}
							if(battletype == 2){
								boss.magicattacked(6,1.7,6,"Hydro");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 't' :
					if(mainplayer.sayshakelearnt() == true){
						if(mainplayer.saymp() >= 5){
							if(battletype == 1){
								commonenemy.magicattacked(8,1.7,5,"Shake");
							}
							if(battletype == 2){
								boss.magicattacked(8,1.7,5,"Shake");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 'y' :
					if(mainplayer.sayhypothermialearnt() == true){
						if(mainplayer.saymp() >= 10){
							if(battletype == 1){
								commonenemy.magicattacked(7,2.4,10,"Hypothermia");
							}
							if(battletype == 2){
								boss.magicattacked(7,2.4,10,"Hypothermia");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 'u' :
					if(mainplayer.sayphytoplasmalearnt() == true){
						if(mainplayer.saymp() >= 10){
							if(battletype == 1){
								commonenemy.magicattacked(1,2.4,10,"Phytoplasma");
							}
							if(battletype == 2){
								boss.magicattacked(1,2.4,10,"Phytoplasma");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 'i' :
					if(mainplayer.saycorruptionlearnt() == true){
						if(mainplayer.saymp() >= 14){
							if(battletype == 1){
								commonenemy.magicattacked(3,2.4,14,"Corruption");
							}
							if(battletype == 2){
								boss.magicattacked(3,2.4,14,"Corruption");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 'o' :
					if(mainplayer.saylethalblindnesslearnt() == true){
						if(mainplayer.saymp() >= 7){
							if(battletype == 1){
								commonenemy.magicattacked(4,2.4,7,"Lethal Blindness");
							}
							if(battletype == 2){
								boss.magicattacked(4,2.4,7,"Lethal Blindness");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 'p' :
					if(mainplayer.sayhyperthermialearnt() == true){
						if(mainplayer.saymp() >= 14){
							if(battletype == 1){
								commonenemy.magicattacked(5,2.4,14,"Hyperthermia");
							}
							if(battletype == 2){
								boss.magicattacked(5,2.4,14,"Hyperthermia");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 'a' :
					if(mainplayer.saydrownlearnt() == true){
						if(mainplayer.saymp() >= 12){
							if(battletype == 1){
								commonenemy.magicattacked(6,2.4,12,"Drown");
							}
							if(battletype == 2){
								boss.magicattacked(6,2.4,12,"Drown");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
					}
					break;
				case 's' :
					if(mainplayer.sayearthquakelearnt() == true){
						if(mainplayer.saymp() >= 10){
							if(battletype == 1){
								commonenemy.magicattacked(8,2.4,10,"Earthquake");
							}
							if(battletype == 2){
								boss.magicattacked(8,2.4,10,"Earthquake");
							}
						}
						else{
							cout << "You haven't enough MP left to perform this move!" << endl;
						}
					}
					else{
						goto STARTBATTLE;
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
					clearcolors(7,backgroundcolor);
					switch(movement){
						case '1' :
							if(mainplayer.sayresistance() >= 10){
								if(battletype == 1){
									commonenemy.receivedultra();
								}
								if(battletype == 2){
									boss.receivedultra();
								}
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
				clearcolors(7,backgroundcolor);
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
			if(battletype == 1){
				mainplayer.playerattacked();
			}
			if(battletype == 2){
				mainplayer.playerattackedboss();
			}

			mainplayer.increaseultra();
			mainplayer.limitultra();
			mainplayer.limitresistance();
			mainplayer.limitplayerlife();
			mainplayer.limitsp();
			if(battletype == 1){
				commonenemy.limitlife();
			}
			if(battletype == 2){
				boss.limitlife();
			}

			if(attackmade == false){
				consecutiveattacks -= 2;
				if(consecutiveattacks < 0){
					consecutiveattacks = 0;
				}
			}
			else{
				attackmade = false;
			}
		}
	}
}

void maintitle(){
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
	cout << "                                                        [Alpha 2.2.1] ";
}

int main(){
	SetConsoleTitle(L"Tactical");
	bool startupmenu;
	bool controlsshown;
	clearcolors(15,8);
	randomseed();
	mainplayer.customizecharacter(2);
	selectory = 1;
	while(1){
		while(startupmenu == false){
			maintitle();
			gotoxy(2,12);
			if(selectory == 1){
				cout << "-> ";
			}
			cout << "	New Game" << endl;
			gotoxy(2,14);
			if(selectory == 2){
				cout << "-> ";
			}
			cout << "	Continue" << endl;
			gotoxy(2,16);
			if(selectory == 3){
				cout << "-> ";
			}
			cout << "	Customize Character" << endl;
			if(controlsshown == false){
				gotoxy(2,18);
				cout << "WASD to move the cursor, space to confirm";
				controlsshown = true;
			}
			gotoxy(2,18);
			movement = _getch();
			switch(movement){
			case 'w' :
				if(selectory > 1) selectory--;
				break;
			case 's' :
				if(selectory < 3) selectory++;
				break;
			case ' ' :
				startupmenu = true;
				if(selectory == 1){
					movement = '1';
				}
				if(selectory == 2){
					movement = '2';
				}
				if(selectory == 3){
					movement = '3';
				}
				break;
			}
		}
		switch(movement){
		case '1':
			gotoxy(20,75);
			clear();
			maintitle();
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
			if(playername != "Trackpoth" && playername != "COCOS"){
				gotoxy(2,15);
				cout << "Will it be " << playername << "?\a";
			}
			cout << " [1] Yes [Any other key] No" << endl;
			gotoxy(2,16);
			movement = _getch();
			switch (movement){
			case '1' :
				start = true;
				clearcolors(7,0);
				battle();
				break;
			}
			gotoxy(20,75);
			clear();
			break;
		case '2':
			savegame(2);
			if(loadfailed == false){
				load = true;
				firstbattle = false;
				clearcolors(7,0);
				battle();
			}
			break;
		case '3':
			savegame(3);
			if(savefileexists == false){
				clearcolors(7,0);
				mainplayer.customizecharacter(1);
			}
			break;
		default :
			cout << "                             ";
			break;
		}
		startupmenu = false;
	}
	return 0;
}

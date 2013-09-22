#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <windows.h>

using namespace std;

// Definición de variables locales

int subcriticalcheckerone;
int subcriticalcheckertwo;

bool piercingeyeeffect;
bool damagepilleffect;

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

void gotoxy(int column, int line)
{
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

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
	int saymaxspbase();
	int saymaxsp();
	int saysp();
	int saymaxmpbase();
	int saymaxmp();
	int saymp();
	int saymagicattack();
	int sayrangedattack();
	int saycriticalchecker();
	int saycriticalpower();
	float saycriticalmultiplier();
	int saysmallhealthpill();
	int saysmallhealthpillvalue();
	int saysmallhealthpillworth();
	int saydamagepill();
	int saydamagepillworth();
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
	void determinemaxmp();

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

	void determinemaxshields();
	void restoreshields();
	void increaserecharge();

	void restoreparameters(int parameter);

	void customizecharacter(int type);

	int sayshields();
	int saymaxshields();
	int sayrechargerate();
	int sayrechargemeter();

	int sayattacktpmeter();
	int sayratmeter();
	int saymatmeter();
	int saylifemeter();
	int saydefensemeter();
	int sayspmeter();
	int saympmeter();
	int sayresmeter();

protected:
	// Player's parameters
	int playermaxlife;
	int playermaxsp;
	int playermaxmp;
	int playermaxspbase;
	int playermaxmpbase;
	int playermaxresistance;
	int playermaxultra;

	int playerattack;
	int playermagicattack;
	int playerrangedattack;
	int playerdefense;

	int playerlife;
	int playersp;
	int playermp;
	int playerresistance;
	int playerultra;

	int playercriticalchecker;
	int playercriticalpower;
	float playercriticalmultiplier;

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

	int masterstealth;
	int masterstrength;
	int mastermagic;
	int masterhealth;

	// Player's shields
	int shields;
	int maxshields;
	int rechargerate;
	int rechargemeter;
};

player::player()
{
	playermaxlife = 460;
	playermaxspbase = 13;
	playermaxmpbase = 11;
	playerattack = 18;
	playermagicattack = 16;
	playerrangedattack = 14;
	playerlife = 460;
	playersp = 14;
	playermp = 12;
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

int player::saymaxspbase(){
	return playermaxspbase;
}

int player::saymaxsp(){
	return playermaxsp;
}

int player::saysp(){
	return playersp;
}

int player::saymaxmpbase(){
	return playermaxmpbase;
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

float player::saycriticalmultiplier(){
	return playercriticalmultiplier;
}

int player::saysmallhealthpill(){
	return smallhealthpill;
}

int player::saysmallhealthpillvalue(){
	return smallhealthpillvalue;
}

int player::saysmallhealthpillworth(){
	return smallhealthpillworth;
}

int player::saydamagepill(){
	return damagepill;
}

int player::saydamagepillworth(){
	return damagepillworth;
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

void player::restoreshields(){
	shields = maxshields;
	rechargemeter = 0;
}

void player::increaserecharge(){
	rechargemeter += rechargerate;
}

int player::sayshields(){
	return shields;
}

int player::saymaxshields(){
	return maxshields;
}

int player::sayrechargerate(){
	return rechargerate;
}

int player::sayrechargemeter(){
	return rechargemeter;
}

int player::sayattacktpmeter(){
	return attacktpmeter;
}

int player::sayratmeter(){
	return ratmeter;
}

int player::saymatmeter(){
	return matmeter;
}

int player::saydefensemeter(){
	return defensemeter;
}

int player::saylifemeter(){
	return lifemeter;
}

int player::sayspmeter(){
	return spmeter;
}

int player::saympmeter(){
	return mpmeter;
}

int player::sayresmeter(){
	return resmeter;
}

player mainplayer;

void player::upgrading(){
	cout << "Parameter upgrading center" << endl;
	cout << "Current TP: " << playertp << endl << endl;
	cout << "[1] Stealth tier  [" << masterstealth << " skill points]" << endl;
	cout << "[2] Strength tier [" << masterstrength << " skill points]" << endl;
	cout << "[3] Magic tier    [" << mastermagic << " skill points]" << endl;
	cout << "[4] Health tier   [" << masterhealth << " skill points]" << endl;
	cout << "Type any other key to go back to the menu" << endl;
	cin >> movement;
	clear();
	switch(movement){
	case '1' :
STEALTH:
		cout << "Parameter upgrading center | Stealth tier" << endl;
		cout << "Current TP: " << playertp << endl << endl;
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
		cout << "Type any other key to go back to the menu" << endl;
		cin >> movement;
		clear();
		switch(movement){
		case '1' :
			if(playertp >= 90 - (12 * masterstealth)){
				playertp -= 90 - (12 * masterstealth);
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
					playermaxresistance += 2;
					playerresistance += 2;
					goto STEALTH;
				}
				else{
					cout << "You do not have enough Train Points for that!" << endl << endl;
				}
			}
			break;
		}
		break;
	case '2' :
STRENGTH:
		cout << "Parameter upgrading center | Strength tier" << endl;
		cout << "Current TP: " << playertp << endl << endl;
		cout << "Attack (AT)        : " << playerattack << " -> " << playerattack + 1 << endl;
		if(masterstrength >= 1){
			cout << "Defense (DEF)      : " << playerdefense << " -> " << playerdefense + 1 << endl;
		}
		cout << endl << "[1] Upgrade AT         (-" << 80 - (12 * masterstrength) << " TP)" << endl;
		if(masterstrength >= 1){
			cout << "[2] Upgrade DEF        (-" << 80 - (9 * masterstrength) << " TP)" << endl;
		}
		cout << "Type any other key to go back to the menu" << endl;
		cin >> movement;
		clear();
		switch(movement){
		case '1' :
			if(playertp >= 80 - (12 * masterstrength)){
				playertp -= 80 - (12 * masterstrength);
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
					playerdefense++;
					goto STRENGTH;
				}
				else{
					cout << "You do not have enough Train Points for that!" << endl << endl;
				}
				break;
			}
		}
		break;
	case '3' :
MAGIC:
		cout << "Parameter upgrading center | Magic tier" << endl;
		cout << "Current TP: " << playertp << endl << endl;
		cout << "Magic attack (MAT) : " << playermagicattack << " -> " << playermagicattack + 1 << endl;
		if(mastermagic >= 2){
			cout << "Max MP             : " << playermaxmp << " -> " << playermaxmp + 1 << endl;
		}
		cout << endl << "[1] Upgrade MAT        (-" << 90 - (12 * mastermagic) << " TP)" << endl;
		if(mastermagic >= 2){
			cout << "[2] Upgrade Max MP     (-" << 240 - (30 * mastermagic) << " TP)" << endl;
		}
		cout << "Type any other key to go back to the menu" << endl;
		cin >> movement;
		clear();
		switch(movement){
		case '1' :
			if(playertp >= 90 - (12 * mastermagic)){
				playertp -= 90 - (12 * mastermagic);
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
					playermaxmpbase++;
					playermp++;
					goto MAGIC;
				}
				else{
					cout << "You do not have enough Train Points for that!" << endl << endl;
				}
			}
			break;
		}
		break;
	case '4' :
HEALTH:
		cout << "Parameter upgrading center | Health tier" << endl;
		cout << "Current TP: " << playertp << endl << endl;
		cout << "Max Life           : " << playermaxlife << " -> " << playermaxlife + 10 << endl << endl;
		cout << "[1] Upgrade Max Life   (-" << 90 - (9 * masterhealth) << " TP)" << endl;
		cout << "Type any other key to go back to the menu" << endl;
		cin >> movement;
		clear();
		switch(movement){
		case '1' :
			if(playertp >= 90 - (9 * masterhealth)){
				playertp -= 90 - (9 * masterhealth);
				playermaxlife += 10;
				playerlife += 10;
				goto HEALTH;
			}
			else{
				cout << "You do not have enough Train Points for that!" << endl << endl;
			}
			break;
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

	void magicattacked(int type, float strength, int mpdecrease);

	void determinecriticalpower();
	void limitlife();
	void randomizetype();
	void randomizeparameters();
	void restoreparameters();
	void healthdrinktaken();
	void saystats();
	void randomizeboss();

	void restoreparameters(int parameter);

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
	if(enemytype == 8){
		cout << "Ground ";
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
			cout << "[Light (x2)] [Fire (x1.5)]" << endl;
		}
		if(enemytype == 4){
			cout << "[Darkness (x1.5)] [Ground (x1.5)] [Grass (x1.5)]" << endl;
		}
		if(enemytype == 5){
			cout << "[Darkness (x1.5)] [Water (x2)] [Ground (x2)]" << endl;
		}
		if(enemytype == 6){
			cout << "[Ice (x2)] [Grass (x2)]" << endl;
		}
		if(enemytype == 7){
			cout << "[Water (x1.5)] [Fire (x1.5)]" << endl;
		}
		if(enemytype == 8){
			cout << "[Water (x1.5)] [Grass (x1.5)]" << endl;
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

void enemy::randomizeboss(){
	enemytype = rand() % 8 + 1;
	enemyint = 4;
	healthdrink = 1;
	enemymaxlife += rand() % 200 + commonenemy.saymaxlife();
	enemyattack += rand() % 8 + commonenemy.sayattack();
	enemydefense += rand() % 6 + commonenemy.saydefense();
	enemylife = enemymaxlife;
}
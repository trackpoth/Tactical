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

int selectory;

int section = 1;
int zone = 1;
int travel;

int battletype;
int backgroundcolor;

int consecutiveattacks;
bool attackmade;

void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
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
	int sayexperience();

	bool saygrasslearnt();
	bool saydarklearnt();
	bool saylightlearnt();
	bool sayfirelearnt();
	bool saywaterlearnt();
	bool saygroundlearnt();
	bool sayfrostbitelearnt();
	bool sayustilagolearnt();
	bool sayisolationlearnt();
	bool sayilluminationlearnt();
	bool sayflarelearnt();
	bool sayhydrolearnt();
	bool sayshakelearnt();
	bool sayhypothermialearnt();
	bool sayphytoplasmalearnt();
	bool saycorruptionlearnt();
	bool saylethalblindnesslearnt();
	bool sayhyperthermialearnt();
	bool saydrownlearnt();
	bool sayearthquakelearnt();

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
	void options();

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

	// Player's skills
		// TIER 1 MAGIC
	bool grasslearnt;
	bool darklearnt;
	bool lightlearnt;
	bool firelearnt;
	bool waterlearnt;
	bool groundlearnt;

		// TIER 2 MAGIC
	bool frostbitelearnt;
	bool ustilagolearnt;
	bool isolationlearnt;
	bool illuminationlearnt;
	bool flarelearnt;
	bool hydrolearnt;
	bool shakelearnt;

		// TIER 3 MAGIC
	bool hypothermialearnt;
	bool phytoplasmalearnt;
	bool corruptionlearnt;
	bool lethalblindnesslearnt;
	bool hyperthermialearnt;
	bool drownlearnt;
	bool earthquakelearnt;

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

	float experience;

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
	playermaxlife				= 460;
	playermaxspbase				= 13;
	playermaxmpbase				= 11;
	playerattack				= 18;
	playermagicattack			= 16;
	playerrangedattack			= 14;
	playerlife					= 460;
	playersp					= 14;
	playermp					= 12;
	playercriticalchecker		= 20;
	playercriticalmultiplier	= 1.5;
	smallhealthpill				= 2;
	smallhealthpillvalue		= 100;
	smallhealthpillworth		= 8;
	damagepill					= 1;
	damagepillworth				= 24;
	playerresistance			= 90;
	playermaxresistance			= 90;
	playerultra					= 100;
	playermaxultra				= 200;
	playerdefense				= 2;
	attacktpmeter				= 10;
	ratmeter					= 10;
	matmeter					= 10;
	lifemeter					= 15;
	defensemeter				= 12;
	spmeter						= 90;
	mpmeter						= 120;
	resmeter					= 50;
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

int player::sayexperience(){
	return experience;
}

bool player::saygrasslearnt(){
	return grasslearnt;
}

bool player::saydarklearnt(){
	return darklearnt;
}

bool player::saylightlearnt(){
	return lightlearnt;
}

bool player::sayfirelearnt(){
	return firelearnt;
}

bool player::saywaterlearnt(){
	return waterlearnt;
}

bool player::saygroundlearnt(){
	return groundlearnt;
}

bool player::sayfrostbitelearnt(){
	return frostbitelearnt;
}

bool player::sayustilagolearnt(){
	return ustilagolearnt;
}

bool player::sayisolationlearnt(){
	return isolationlearnt;
}

bool player::sayilluminationlearnt(){
	return illuminationlearnt;
}

bool player::sayflarelearnt(){
	return flarelearnt;
}

bool player::sayhydrolearnt(){
	return hydrolearnt;
}

bool player::sayshakelearnt(){
	return shakelearnt;
}

bool player::sayhypothermialearnt(){
	return hypothermialearnt;
}

bool player::sayphytoplasmalearnt(){
	return phytoplasmalearnt;
}

bool player::saycorruptionlearnt(){
	return corruptionlearnt;
}

bool player::saylethalblindnesslearnt(){
	return lethalblindnesslearnt;
}

bool player::sayhyperthermialearnt(){
	return hyperthermialearnt;
}

bool player::saydrownlearnt(){
	return drownlearnt;
}

bool player::sayearthquakelearnt(){
	return earthquakelearnt;
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

	void magicattacked(int type, float strength, int mpdecrease, string skillname);

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
	enemylife =				120;
	enemymaxlife =			120;
	enemytype =				1;
	enemyattack =			10;
	enemydefense =			1;
	enemycriticalchecker =	20;
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
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12 + (backgroundcolor * 16)) );
			cout << "[BOSS] ";
		}
		if(enemytype == 1){
			cout << "Grass ";
		}
		if(enemytype == 2){
			cout << "Normal ";
		}
		if(enemytype == 3){
			cout << "Darkness ";
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );

	if(piercingeyeeffect == false){
		if(enemylife <= enemymaxlife * 0.25){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12 + (backgroundcolor * 16)) );
		}
		cout << "Life = ";
		cout << enemylife;
		cout << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );
	}
	else{
		if(enemylife <= enemymaxlife * 0.25){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12 + (backgroundcolor * 16)) );
		}
		cout << "Life = " << enemylife << "/" << enemymaxlife << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );
		printf("AT = %d | DEF = %d\n",enemyattack,enemydefense);
	}
	if(piercingeyeeffect == true){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (13 + (backgroundcolor * 16)) );
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7 + (backgroundcolor * 16)) );
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
	enemymaxlife += rand() % 160 + commonenemy.saymaxlife();
	enemyattack += rand() % 8 + commonenemy.sayattack();
	enemydefense += rand() % 4 + commonenemy.saydefense();
	enemylife = enemymaxlife;
}
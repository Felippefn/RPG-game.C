#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<conio.h>
#include <string.h>
#include <Windows.h>
// RPG GAME. Create a RPG game which you can choose your class, name before you start.
// You will have at least three classes to choose and play with (in development...). 
//When you chose your class, you will be able to fight against monsters, check inventory, run from monsters, find chests and level up.
//Each time you defeat a monster, you get coins and xp to change for better weapons and potential chest to spawn

typedef struct monster{
  char name[100];
  int health;
  int attack;
  int xp;
  int coin;
} typeMonster;

typedef struct classes{
	char dname[100];
	int weapon;
	int life;
	int maxLife;
	int speed;
} typeClasses;

typeMonster randomMonster();
typeMonster monsters[16];

typeClasses classesValues();
typeClasses classList[3];

void generateMonster();

int characClass = 0;

typeMonster x; 
typeClasses y; 

int recive_attack_()
{
	int attempt_enemy;

	attempt_enemy = rand() % 100;
	if (attempt_enemy >= 50)
	{
		printf("\n\nENEMY ATTACK: %d\n\n", x.attack);
		y.life = y.life - x.attack;
	}
	else
	{
		printf("\n\nENEMY MISSED!\n\n");	
	}
}

int chances_escape()
{
	int value1,
		prob;
	value1 = rand() % 10;
	prob = y.speed * value1;
	if (prob >= 400)
	{
		printf("ESCAPED!");
		x.health = 0;	
	}
	else
	{
		recive_attack_();
		printf("ATTEMPT FAILED!");
		printf("try again.");
	}
}

int main() 
{
	generateMonster();
	srand((unsigned) time(NULL)); //Declare a random seed 
	
	int command,
		playerAction =0,
		gameMode = 0,
		coin_get = 0,
		xp_get =0,
		cnf = 0,
		start_coin,
		start_xp;
	
	char namePlayer[100];
			
	do{
		printf("Select your hero name: ");
		fgets(namePlayer, 100, stdin);  // Read the names ultil 100 characters, similar to scanf
		printf("Do you want to confirm or try again? \n[1]-Confirm  [2]-Try again\n[?]: ");
		scanf("%d", &cnf);
		char c; while ((c = fgetc(stdin)) != EOF && c != '\n'){}
		namePlayer[strlen(namePlayer) - 1] = '\0';
		if(cnf==1)
		{
			printf("Confirmed!");
			printf("\nYour hero name is: %s\n", namePlayer);
		}
		
	}
	while(cnf!=1);
	
	do{
		printf("Choose your class: [0]- Knight    ||    [1]- Wizard    ||    [2]- Rogue\n[?]: ");
		scanf("%d", &characClass);
		//=sleep(2);
		if(characClass == 0)
		{
			
			printf("\nSucess!! You are now a knight!\nSpecial habilities: MELEE and TANK\n");
		}
		else if(characClass == 1)
		{
			
			printf("\nSucess!! You are now a wizard!\nSpecial habilities: DAMAGE and MAGIC\n");
		}
		else if(characClass == 2)
		{
			
			printf("\nSucess!! You are now a rogue!\nSpecial habilities: SPEED ATTACK and DODGE\n");
		}
	}
	while(characClass > 2 && characClass < 0);
	
	y = classesValues();
	
	while(y.life > 0)
	{
		printf("\nWhat will we be doing today, %s?\n", namePlayer);
		printf("\n[1]- EXPLORE THE FOREST   ||   [2]- CHECK INVENTORY   ||   [3]- MARKETPLACE\n");
		scanf("%d", &gameMode);
	
		switch(gameMode)
		{
			
			case 1:
				printf("\n*walking by the forest*\n");
				//sleep(3);
				x = randomMonster();
				start_coin = 0;
				start_xp = 0;
				printf("\nYou've found a monster!!");
				//sleep(1);
				printf("\nLooks like it's a %s ", x.name);
				printf("\n------------------------------\n");
				printf("Your status: %s\n Life: %d\nWeapon Damage: %d\nSpeed: %d", y.dname, y.life, y.weapon, y.speed);
				printf("\n------------------------------\n");
				//sleep(1);
				printf("%s || Life: %d || Damage: %d || Coins: %d || XP: %d", x.name, x.health, x.attack, x.coin, x.xp);
				//sleep(2);
				printf("\nIt's definely not friendly, you gotta make a move:\n");
				while (x.health > 0)
				{
					int potion = 100;
					int attack_enemy = x.health - y.weapon;
					//int recive_attack = y.life - x.attack;
					printf("\n[1]- ATTACK 	||	[2]- HEAL	||	[3]- TRY TO RUN\n");
					//sleep(1);
					scanf("%d", &playerAction);
					switch (playerAction)
					{
						case 1:			
							x.health = attack_enemy;
										
							printf("\n\nDAMAGE: %d!\n\n", y.weapon);
							//sleep(2);
							recive_attack_();
							printf("\n\nYour Life: %d\n\n", y.life);
							if (x.health <= 0)
							{
								printf("\nMonster DEFEATED!\n");
								printf("\nCoins: %d\nXp: %d\nCheck your inventory for more.\n", x.coin, x.xp);
								start_xp = x.xp;
								start_coin = x.coin;
								break;
							}
							printf("\n%s, Life: %d\n", x.name, x.health);
							
							break;
						
						case 2:
							recive_attack_();
							if (y.life + potion <= y.maxLife)
							{
								y.life = y.life + potion;
								printf("\nPotion used! Current LIFE: %d\n", y.life);
								//sleep(1);
							}
							else
							{
								y.life = y.maxLife;
								printf("\nMax life reached.\Current LIFE: %d\n", y.life);
							}
							break;
						
						case 3:
							chances_escape();
							break;
					}
				}
				xp_get = start_xp + xp_get;
				coin_get = start_coin + coin_get;
				break;
			
			
			case 2: 
				y.life = y.maxLife;
				printf("\nHealing HP.\n\n");
				//sleep(1);
				printf("%s", y.dname);
				printf("\n ||  Backpack  ||\n");
				//sleep(1);
				printf("\nYour coins: %d ", coin_get);
				//sleep(1);
				printf("\nYour XP: %d ", xp_get);
				//sleep(1);
				printf("\nYour status: Life: %d\nWeapon Damage: %d\nSpeed: %d\n\n", y.life, y.weapon, y.speed);
				//sleep(1);
				break;
			
			case 3:
				int question_weapon, 
					boost_weapon1 = 40,
					boost_weapon2 = 70,
					boost_weapon3 = 100;
				printf("\nYour coins: %d ", coin_get);
				printf("Your XP: %d \n", xp_get);
				printf("MARKET:");
				printf("------------------------------------\n");
				printf("[1] - Blue crystal, increase 50 DAMAGE\nPrice: 1500 ----- XP required: 2000\n");
				printf("[2] - Red crystal, increase 70 DAMAGE\nPrice: 3000 ----- XP required: 7000\n");
				printf("[3] - Purple crystal, increase 100 DAMAGE\nPrice: 4000 ----- XP required: 9000\n");
				printf("------------------------------------\nWhich one would you like to buy? ");
				scanf("%d", &question_weapon);
				
				switch(question_weapon)
				{
					case 1:
						if (coin_get >= 1500 && xp_get >= 2000)
						{
							coin_get = coin_get - 1500;
							y.weapon = y.weapon + boost_weapon1;
							printf("SUCESS!\n BLUE crystal achieved");
							printf("\nYour coins: %d ", coin_get);
							printf("Your weapon damage: %d", y.weapon);
						}
						else
						{
							printf("YOU DON'T HAVE THE NECESSARY AMOUNT TO BUY THAT!");
							y.weapon = y.weapon;
							coin_get = coin_get;
						}
						break;
					case 2:
						
						if (coin_get >= 3000 && xp_get >= 7000)
						{
							coin_get = coin_get - 3000;
							y.weapon = y.weapon + boost_weapon2;
							printf("SUCESS!\n RED crystal achieved");
							printf("\nYour coins: %d ", coin_get);
							printf("Your weapon damage: %d", y.weapon);
						}
						else
						{
							printf("YOU DON'T HAVE THE NECESSARY AMOUNT TO BUY THAT!");
							y.weapon = y.weapon;
							coin_get = coin_get;
						}
						break;
						
					case 3:
						if (coin_get >= 4000 && xp_get >= 9000)
						{
							coin_get = coin_get - 4000;
							y.weapon = y.weapon + boost_weapon3;
							printf("SUCESS!\n PURPLE crystal achieved");
							printf("\nYour coins: %d ", coin_get);
							printf("Your weapon damage: %d", y.weapon);
						}
						else
						{
							printf("YOU DON'T HAVE THE NECESSARY AMOUNT TO BUY THAT!");
							y.weapon = y.weapon;
							coin_get = coin_get;
						}
						break;
				}
				break;
				
		}
	}
	//sleep(2)
	printf("----------|| GAMEOVER ||----------\n[Thank you for playing]\n*try again if you want.*");
}	

typeMonster randomMonster()
{
	srand((unsigned) time(NULL));
	int getMonster = rand() % 10;

	if(getMonster < 7)
  		getMonster = rand() % 9;
	else
  		getMonster = rand() % 10;
  	if(getMonster < 7)
    	getMonster = rand() % 14;
  	else
    	getMonster = rand() % 15;
	return monsters[getMonster];
}

typeClasses classesValues()
{
	if (characClass==0)
		{
		strcpy(classList[0].dname, "Knight");
		classList[0].life=500;
		classList[0].maxLife=500;
		classList[0].speed=70;
		classList[0].weapon=50;
		}
	else if (characClass==1)
		{
		strcpy(classList[1].dname, "Wizard");
		classList[1].life=270;
		classList[1].maxLife=270;
		classList[1].speed=100;
		classList[1].weapon=100;
		}
	else if (characClass==2)
		{
		strcpy(classList[2].dname, "Rogue");
		classList[2].life=350;
		classList[2].maxLife=350;
		classList[2].speed=130;
		classList[2].weapon=70;
		}
	return classList[characClass];
}

void generateMonster()
{
	//bat, goblins, elf, slime, witch, zombie, snake, skeleton, werewolf, vampire, kingGorila, darkElf, giantLizzard,  beholder, cyclopes, dragon;
	//bat
	strcpy(monsters[0].name,"Bat");
	monsters[0].health=150;
	monsters[0].attack=15;
	monsters[0].xp=20;
	monsters[0].coin=10;
	
	//goblins
	strcpy(monsters[1].name,"Goblin");
	monsters[1].health=125;
	monsters[1].attack=20;
	monsters[1].xp=35;
	monsters[1].coin=15;
	
	//elf
	strcpy(monsters[2].name,"Elf");
	monsters[2].health=140;
	monsters[2].attack=25;
	monsters[2].xp=40;
	monsters[2].coin=20;
	
	//slime
	strcpy(monsters[3].name,"Slime");
	monsters[3].health=135;
	monsters[3].attack=20;
	monsters[3].xp=40;
	monsters[3].coin=20;
	
	//witch
	strcpy(monsters[4].name,"Witch");
	monsters[4].health=160;
	monsters[4].attack=80;
	monsters[4].xp=55;
	monsters[4].coin=25;
	
	//zombie
	strcpy(monsters[5].name,"Zombie");
	monsters[5].health=165;
	monsters[5].attack=40;
	monsters[5].xp=55;
	monsters[5].coin=25;
	
	//snake
	strcpy(monsters[6].name,"Giant Snake");
	monsters[6].health=140;
	monsters[6].attack=35;
	monsters[6].xp=70;
	monsters[6].coin=30;
	
	//skeleton
	strcpy(monsters[7].name,"Skeleton");
	monsters[7].health=180;
	monsters[7].attack=45;
	monsters[7].xp=75;
	monsters[7].coin=40;
	
	//werewolf
	strcpy(monsters[8].name,"Werewolf");
	monsters[8].health=280;
	monsters[8].attack=50;
	monsters[8].xp=100;
	monsters[8].coin=50;
	
	//vampire
	strcpy(monsters[9].name,"Vampire");
	monsters[9].health=320;
	monsters[9].attack=80;
	monsters[9].xp=120;
	monsters[9].coin=60;
	
	//kingGorila
	strcpy(monsters[10].name,"King Gorila");
	monsters[10].health=440;
	monsters[10].attack=65;
	monsters[10].xp=500;
	monsters[10].coin=200;
	
	//darkElf
	strcpy(monsters[11].name,"Dark Elf");
	monsters[11].health=275;
	monsters[11].attack=80;
	monsters[11].xp=375;
	monsters[11].coin=220;
	
	//giantLizzard
	strcpy(monsters[12].name,"Killer Lizzard");
	monsters[12].health=280;
	monsters[12].attack=85;
	monsters[12].xp=340;
	monsters[12].coin=250;
	
	//beholder
	strcpy(monsters[13].name,"Beholder God");
	monsters[13].health=370;
	monsters[13].attack=90;
	monsters[13].xp=610;
	monsters[13].coin=350;
	
	//cyclopes
	strcpy(monsters[14].name,"Cyclope God");
	monsters[14].health=540;
	monsters[14].attack=60;
	monsters[14].xp=570;
	monsters[14].coin=320;
	
	//dragon
	strcpy(monsters[15].name,"Lord Dragon");
	monsters[15].health=700;
	monsters[15].attack=120;
	monsters[15].xp=1000;
	monsters[15].coin=1000;
	
	
}

#include<iostream>
#include<stdlib.h> //random
#include<crtdbg.h>
#include "Monster.h"
#include "Player.h"
#include "Vector.cpp" //linked error

using namespace std;
int main()
{
	//variables
	int gridWidth = 100, gridHeight = 100;
	int monNumber = 0;//number of monsters
	int monCount = 0; //For naming
	char move;
	Monster * mon;
	Vector<Monster *> * monVec;
	char playerName[50], monName[50];

	//startup
	srand(123);
	cout << "Enter number of monsters to start: \n";
	cin >> monNumber;
	cout << "Enter the name of monster:\n";
	cin >> monName;
	cout << "Enter Player's Name\n";
	cin >> playerName;
	monCount = monNumber;
	//intialize player
	Player *player = new Player(playerName);
	player->Pos.setX(rand() % 51);
	player->Pos.setY(rand() % 101);

	cout<<"Player "<<player->Name<<" enters the arena at [" << player->Pos.getX() << ", " << player->Pos.getY() << "].\n";
	//create monsters
	monVec = new Vector<Monster *>();
	for (int i = 0; i < monNumber;)
	{
		mon = new Monster();
		mon->respawn(monName, i);
		monVec->push(mon);
	}
	mon = nullptr;
	//mon = new Monster[monNumber];
	//for (int i = 0; i < monNumber;)
	//{
	//	mon[i].respawn(monName, i);
	//	cout << i << endl;
	//	std::cout << "To catch player, Monster named " << mon[i - 1].Name << " appears at [" << mon[i - 1].Pos.getX() << ", " << mon[i - 1].Pos.getY() << "].\n";
	//}

	cout << "OK, Battle begins.\n" <<
		"Use WASD to move, Q to quit, try to live as long as you can!\n";
	for (;;)
	{
		cout << "--------------------------------------\n" <<
			"Make your move: \n";
		cin >> move;
		if (move == 'Q' || move == 'q')
			break;
		else if (move != 'W' && move != 'S' && move != 'A' && move != 'D' && move != 'w' && move != 'a' && move != 's' && move != 'd')
		{
			cout << "Use WASD to move, Q to quit, try to live as long as you can!\n";
			continue;
		}
		else
		{
			player->Move(move);
			//suicide
			for (int i = 0; i < monNumber; ++i)
			{
				if (player->Pos == (*monVec)[i]->Pos)
				{
					cout << playerName << "'s head hit right on a monster named " << (*monVec)[i]->Name << ".\n";
					if (--player->Lives > 0)
					{
						cout << playerName << "'s head is so hard that " << (*monVec)[i]->Name << " ends up dead.\n";
						(*monVec)[i]->respawn(monName, monCount);
						cout << "However, to avenge its friend another monster named " << (*monVec)[i]->Name << " appears at[" << (*monVec)[i]->Pos.getX() << ", " << (*monVec)[i]->Pos.getY() << "].\n";
					}
					break;
				}
			}
			for (int i = 0; i < monNumber; ++i)
			{
				(*monVec)[i]->Move(player->Pos, monCount, monName);
			}
			if (player->Lives <= 0)
			{
				cout << playerName << " Suffered an unfortunate fate and died.\n";
				break;
			}
		}
	}

	std::cout << "Game Over.\n";
	delete player;
	//monVec->clear();
	delete monVec;
	_CrtDumpMemoryLeaks();
	return 0;
}
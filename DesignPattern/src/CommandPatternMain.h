#pragma once

#include "CommandPattern.h"

using namespace std;

void Menu()
{
	cout <<
		"Enter ['q' to exit] : \n"
		"'w' to Jump\n"
		"'a' to Move\n"
		"'d' to Fire\n"
		"'s' to Duck\n";
}

int callMain()
{
	Actor<int>			actor;
	InputHandler<int>	inputHanlder;

	inputHanlder.setJump('t');
	inputHanlder.setMove('y');
	inputHanlder.setFire('u');
	inputHanlder.setDuck('i');

	while (1)
	{
		char ch;
		Menu();
		cin >> ch;

		if (ch == 'q')
		{
			break;
		}

		cin.ignore(INT_MAX, '\n');
		Command<int> *command = inputHanlder.HandleInput(ch);

		if (ch == 'y')
		{
			cout << "Enter new location : ";
			int x, y;
			cin >> x;
			cin.ignore(INT_MAX, '\n');
			cin >> y;
			cin.ignore(INT_MAX, '\n');

			actor.setPosition(x, y);
		}
		command->execute(actor);
	}

	return 0;
}
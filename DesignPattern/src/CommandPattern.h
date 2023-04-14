#pragma once

#include "Actor.h"
#include <iostream>
#include <map>

template<typename T>
class Command
{
public:
	virtual ~Command() = default;
	virtual void execute(Actor<T> &actor) = 0;
};

template<typename T>
class NullCommand : public Command<T>
{
public:
	void execute(Actor<T> &actor) override
	{
		std::cout << "NULL Command\n";
	}
};

template<typename T>
class JumpCommand : public Command<T>
{
public:
	void execute(Actor<T> &actor) override
	{
		actor.jump();
	}
};

template<typename T>
class MoveCommand : public Command<T>
{
public:
	void execute(Actor<T> &actor) override
	{
		actor.move();
	}
};

template<typename T>
class FireCommand : public Command<T>
{
public:
	void execute(Actor<T> &actor) override
	{
		actor.fire();
	}
};

template<typename T>
class DuckCommand : public Command<T>
{
public:
	void execute(Actor<T> &actor) override
	{
		actor.duck();
	}
};

template<typename T>
class InputHandler
{
	enum BUTTON_INDEX
	{
		JUMP_BUTTON,
		MOVE_BUTTON,
		FIRE_BUTTON,
		DUCK_BUTTON,
		MAX_BUTTON,
	};
public:
	InputHandler()
		:m_pNullCommand{ new NullCommand<T>() }
	{
		m_vCommandChars[JUMP_BUTTON] = 'w';
		m_vCommandChars[MOVE_BUTTON] = 'a';
		m_vCommandChars[FIRE_BUTTON] = 'd';
		m_vCommandChars[DUCK_BUTTON] = 's';

		m_mCommands[m_vCommandChars[JUMP_BUTTON]] = new JumpCommand<T>();
		m_mCommands[m_vCommandChars[MOVE_BUTTON]] = new MoveCommand<T>();
		m_mCommands[m_vCommandChars[FIRE_BUTTON]] = new FireCommand<T>();
		m_mCommands[m_vCommandChars[DUCK_BUTTON]] = new DuckCommand<T>();
	}

	~InputHandler()
	{
		delete m_pNullCommand;
		for (auto &x : m_mCommands)
		{
			delete x.second;
		}
		m_mCommands.clear();
	}

	void setJump(char ch)
	{
		setNewButton(JUMP_BUTTON, ch);
	}

	void setMove(char ch)
	{
		setNewButton(MOVE_BUTTON, ch);
	}

	void setFire(char ch)
	{
		setNewButton(FIRE_BUTTON, ch);
	}

	void setDuck(char ch)
	{
		setNewButton(DUCK_BUTTON, ch);
	}

	Command<T>* HandleInput(char ch)
	{
		if (m_mCommands.count(ch))
		{
			return m_mCommands[ch];
		}
		else
		{
			return m_pNullCommand;
		}
	}

private:
	void setNewButton(BUTTON_INDEX index, char ch)
	{
		Command<T> *p = m_mCommands[m_vCommandChars[index]];
		m_mCommands.erase(m_vCommandChars[index]);

		m_vCommandChars[index] = ch;
		m_mCommands[m_vCommandChars[index]] = p;
	}

private:
	char							m_vCommandChars[MAX_BUTTON];
	std::map<char, Command<T> *>	m_mCommands;
	Command<T>						*m_pNullCommand;
};

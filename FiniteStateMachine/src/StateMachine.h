#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include "State.h"
#include <iostream>
#include <unordered_map>

class StateMachine
{
	public:
		StateMachine();
		~StateMachine();

		void insert(std::string szStateName, void (*enter)(void));

		void insert(std::string szStateName, void (*enter)(void), void (*exit)(void));

		void insertAfter(std::string szStateName, void (*enter)(void));

		void insertAfter(std::string szStateName, void (*enter)(void), void (*exit)(void));

		void insertBefore(std::string szStateName, void (*enter)(void));

		void insertBefore(std::string szStateName, void (*enter)(void), void (*exit)(void));

		void nextState();
		void gotoState(std::string szStateName);

	private:
		std::unordered_map<std::string, State>	m_StateMap;
		State 									*m_pCurrentState;
		std::string 							m_pszCurrentStateName;
};

StateMachine::StateMachine()
{
	cout << __func__ << "::ctor called.";
	m_pCurrentState = NULL;
}

StateMachine::~StateMachine()
{
	cout << __func__ << "::dtor called.";
}

StateMachine::insert(std::string szStateName, void (*enter)(void))
{
	m_StateMap.insert(make_pair<string, State>(szStateName, State(szStateName, enter)));
}

StateMachine::insert(std::string szStateName, void (*enter)(void), void (*exit)(void))
{
	m_StateMap.insert(make_pair<string, State>(szStateName, State(szStateName, enter, exit)));
}

void StateMachine::insertAfter(std::string szStateName, void (*enter)(void))
{
	unordered_map<string, State>::iterator it;
	it = m_StateMap.find(sz);

	m_StateMap.insert(it+1, make_pair<string, State>(szStateName, State(szStateName, enter)));
}

void StateMachine::insertAfter(std::string szStateName, void (*enter)(void), void (*exit)(void))
{
	unordered_map<string, State>::iterator it;
	it = m_StateMap.find(sz);

	m_StateMap.insert(it+1, make_pair<string, State>(szStateName, State(szStateName, enter, exit)));
}

void StateMachine::insertBefore(std::string szStateName, void (*enter)(void))
{
	unordered_map<string, State>::iterator it;
	it = m_StateMap.find(sz);

	m_StateMap.insert(it, make_pair<string, State>(szStateName, State(szStateName, enter)));
}

void StateMachine::insertBefore(std::string szStateName, void (*enter)(void), void (*exit)(void))
{
	unordered_map<string, State>::iterator it;
	it = m_StateMap.find(sz);

	m_StateMap.insert(it, make_pair<string, State>(szStateName, State(szStateName, enter, exit)));
}

void StateMachine::nextState()
{
	if(m_pCurrentState == NULL)
	{
		m_pszCurrentStateName = m_StateMap.begin()->first;
		m_pCurrentState = m_StateMap.begin()->second;
	}
	else
	{
		unordered_map<string, State>::iterator it = m_StateMap.find(m_pszCurrentStateName);
		if(it == m_StateMap.end())
		{
			assert("NO SUCH STATE.");
		}
		else if((it+1) != m_StateMap.end())
		{
			m_pszCurrentStateName = (it+1)->first;
			m_pCurrentState = (it+1)->second;
		}
		else
		{
			// LOOP BACK TO FIRST STATE
			m_pszCurrentStateName = m_StateMap.begin()->first;
			m_pCurrentState = m_StateMap.begin()->second;
		}
	}
}

void StateMachine::gotoState(std::string szStateName)
{
	unordered_map<string, State>::iterator it = m_StateMap.find(szStateName);
	if(it == m_StateMap.end())
	{
		assert("NO SUCH STATE.");
	}
	else
	{
		m_pszCurrentStateName = (it)->first;
		m_pCurrentState = (it)->second;
	}
}

#endif
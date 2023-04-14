#ifndef __STATE_H__
#define __STATE_H__

#include <iostream>
#include <string>

class State
{
	private:
		State();

	public:
		State(std::string szName, void (*enter)(void));

		State(std::string szName , void (*exit)(void));
		~State();

		void OnEnter();
		void OnExit();

	private:
		const std::string 	m_szStateName;
		const void (*m_FuncOnEnter)(void);
		const void (*m_FuncOnExit)(void);
};
#endif

State::State(std::string szName, void (*enter)void()):
	m_szStateName(szName)
	,m_FuncOnEnter(enter)
	,m_FuncOnExit(NULL)
{
	cout << __func__ << "::dtor with 2 params.";
}

State::State(std::string szName, void (*enter)(void), void (*exit)(void)):
	m_szStateName(szName)
	,m_FuncOnEnter(enter)
	,m_FuncOnExit(exit)
{
	cout << "Ctor with 3 params.";
}

State::~State()
{
	cout << __func__ << "::dtor is Called."
}

void State::OnEnter()
{
	if(m_FuncOnEnter)
	{
		m_FuncOnEnter();
	}
}

void State::OnExit()
{
	if(m_FuncOnExit)
	{
		m_FuncOnExit();
	}
}
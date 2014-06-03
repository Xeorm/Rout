#pragma once
#include <iostream>
#include "EntityManager.h"

using namespace std;

/*
	Dan Hall: GameState is an enumerator that holds the different Game States
*/
enum GameState {Intro=0, Title, Options, InGame, Pause, Dead, Win};

/*
	Dan Hall: StateManager handles all access to GameState-relevant data
*/

class StateManager
{
private:
	GameState sm_prevState;
	static StateManager *sm_instance;
	StateManager(void);
public:
	GameState sm_currentState;
	GameState CurrentState() const;
	GameState PrevState() const;
	static StateManager *getInstance();
	void changeState(GameState newState);
	~StateManager(void);
	
};

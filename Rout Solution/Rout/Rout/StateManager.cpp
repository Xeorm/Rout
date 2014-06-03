#include "StateManager.h"

StateManager* StateManager::sm_instance = NULL;

StateManager::StateManager(void)
{
	sm_prevState = Intro;//to avoid a null on the first state change
}


StateManager::~StateManager(void)
{

}

StateManager* StateManager::getInstance(void)
{
	if(sm_instance == NULL)
	{
		sm_instance = new StateManager();
	}
	return sm_instance;
}



/*
	Dan Hall :changeState takes in a GameState value
	to change the currentState too.  The prevState 
	backlogs the old currentState for the sake of 
	state shifting logic.
*/
void StateManager::changeState(GameState newState)
{
	if(sm_currentState != NULL)
	{
		sm_prevState = sm_currentState;
	}
	EntityManager::getInstance()->endState();
	sm_currentState = newState;
	EntityManager::getInstance()->initState();
}

/* Accessors and Mutators */

GameState StateManager::CurrentState(void) const
{
	return sm_currentState;
}

GameState StateManager::PrevState(void) const
{
	return sm_prevState;
}
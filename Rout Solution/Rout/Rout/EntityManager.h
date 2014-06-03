#pragma once
#include <list>
#include <vector>
#include "GameEntity2D.h"
#include "GameEntity3D.h"
#include "FullTile.h"
#include "EmptyTile.h"
#include "Torch.h"
#include "Player.h"
#include "BoxEntity.h"
#include "Bonewheel.h"
#include "Eater.h"
#include "Faded.h"
#include "Key.h"
#include "TextField.h"
#include "Phylactery.h"
#include "EntityManager.h"
#include "Door.h"
#include "TextTutorial.h"
using namespace std;

class EntityManager
{
private:
	static EntityManager *em_instance;

	/*
		Dan Hall: EntityManager handles the maintenance of all Entities in the 
		game.  Entities include the Player, the Enemies, the Torches,
		the Phylactery, the Walls and the Floor.

	*/
	EntityManager(void);
	
public:	
	/* Lists of GameEntities. Used for all relevant Entity calls */
	vector<GameEntity3D*> entity3DList;

	vector<FullTile*>  fullTileVector;
	vector<EmptyTile*> emptyTileVector;
	vector<Torch*>	   torchVector;
	vector<Bonewheel*> bonewheelVector;
	vector<Eater*>	   eaterVector;
	vector<Faded*>	   fadedVector;
	vector<Door*>	   doorVector;
	vector<BoxEntity*> boxVector;
	vector<Key*>	   keyVector;
	Collider*		   winCollider;
	list<GameEntity2D> entity2DList;
	/* Lists of textFields to be drawn */
	list<TextField*> textFieldList;	
	bool readyToLoad;
	bool loaded;
	/* Holds the Tallied totals of all current GameEntity3Ds in entity3DList */
	int entityTally[3];
	Player* currentPlayer;
	Phylactery* currentPhylactery;
public:
	/*
		Dan Hall: getInstance is the global static function called when we want 
		to access our EntityManager.  It takes in no parameters and 
		checks to see if our EntityManager exists.  If it doesn't 
		exist yet, it creates itself and then returns the new instance.
		If it does exist, then it returns the current instance of 
		EntityManager.
	*/
	static EntityManager *getInstance(void);
	~EntityManager(void);
	static void initState(void);
	static void endState(void);
	bool entity2DListChanged;
	bool entity3DListChanged;
	void clearEntities(void);
	void initEntities(ID3D10Device* device);
	void checkCollision(void);
	textTutorial textTut;

	bool eaterDeathFlag;
	bool bonewheelDeathFlag;
	bool fadedDeathFlag;
	bool purpleKeyFlag;
	bool greenKeyFlag;
	bool blueKeyFlag;
	bool doorFlag;
	bool exitFlag;
};


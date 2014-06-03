#include "EntityManager.h"
#include "StateManager.h"
#include "LevelManager.h"
#include "DeathScreen.h"
#include "AudioManager.h"

EntityManager* EntityManager::em_instance = NULL;

//Private Constructor
EntityManager::EntityManager(void)
{

}

EntityManager::~EntityManager(void)
{
	eaterDeathFlag = bonewheelDeathFlag = fadedDeathFlag = purpleKeyFlag = greenKeyFlag = blueKeyFlag = doorFlag = exitFlag = false;
}

EntityManager* EntityManager::getInstance(void)
{
	if(em_instance == NULL)
	{
		em_instance = new EntityManager();
		em_instance->readyToLoad = false;
		em_instance->entity2DListChanged = false;
		em_instance->entity3DListChanged = false;
	}
	return em_instance;
}



void EntityManager::initState(void)
{
	//any objects that need to be created upon the initialization of a state
	//should be done here, set to their initial settings.
	GameEntity2D tempEntity2D;
	
	switch(StateManager::getInstance()->sm_currentState)
	{
	case Intro:
		tempEntity2D.textureLoc = L"\\..\\Assets\\Images\\Rout Splash Screen.png";
		D3DXMatrixIdentity(&tempEntity2D.sprite.matWorld);
		tempEntity2D.sprite.matWorld._11 *= 2.0f;
		tempEntity2D.sprite.matWorld._22 *= 2.0f;
		em_instance->entity2DList.push_back(tempEntity2D);
		em_instance->entity2DListChanged = true;

		break;
	case  Title:
		tempEntity2D.textureLoc = L"\\..\\Assets\\Images\\Background.png";
		D3DXMatrixIdentity(&tempEntity2D.sprite.matWorld);
		tempEntity2D.sprite.matWorld._11 *= 2.0f;
		tempEntity2D.sprite.matWorld._22 *= 2.0f;
		em_instance->entity2DList.push_back(tempEntity2D);
		em_instance->entity2DListChanged = true;
		break;
	case Options:
		tempEntity2D.textureLoc = L"\\..\\Assets\\Images\\Background.png";
		D3DXMatrixIdentity(&tempEntity2D.sprite.matWorld);
		tempEntity2D.sprite.matWorld._11 *= 2.0f;
		tempEntity2D.sprite.matWorld._22 *= 2.0f;
		em_instance->entity2DList.push_back(tempEntity2D);
		em_instance->entity2DListChanged = true;
		break;
	case Dead:
		tempEntity2D.textureLoc = L"\\..\\Assets\\Images\\Background.png";
		D3DXMatrixIdentity(&tempEntity2D.sprite.matWorld);
		tempEntity2D.sprite.matWorld._11 *= 2.0f;
		tempEntity2D.sprite.matWorld._22 *= 2.0f;
		em_instance->entity2DList.push_back(tempEntity2D);
		em_instance->entity2DListChanged = true;
		break;
	case Win:
		tempEntity2D.textureLoc = L"\\..\\Assets\\Images\\WinScreen.png";
		D3DXMatrixIdentity(&tempEntity2D.sprite.matWorld);
		tempEntity2D.sprite.matWorld._11 *= 2.0f;
		tempEntity2D.sprite.matWorld._22 *= 2.0f;
		em_instance->entity2DList.push_back(tempEntity2D);
		em_instance->entity2DListChanged = true;
		break;
		
	case InGame:
		LevelManager::getInstance()->LoadLevel("Level1.txt");
		em_instance->eaterDeathFlag = em_instance->bonewheelDeathFlag = em_instance->fadedDeathFlag = 
			em_instance->purpleKeyFlag = em_instance->greenKeyFlag = em_instance->blueKeyFlag = 
			em_instance->doorFlag = em_instance->exitFlag = false;

		break;
	case Pause:

		break;
	default:
		break;

	}
	em_instance->readyToLoad = true;
	em_instance->loaded = false;

}

void EntityManager::endState()
{
	switch(StateManager::getInstance()->sm_currentState)
	{
	case Intro:
		em_instance->entity2DList.clear();
		em_instance->entity2DListChanged = true;
		break;
	case  Title:
		em_instance->entity2DList.clear();
		em_instance->entity2DListChanged=true;
		em_instance->textFieldList.clear();
		
		break;
	case Options:
		em_instance->textFieldList.clear();
		break;
		
	case InGame:
		//em_instance
		break;
	case Pause:

		break;
	case Dead:
		em_instance->entity2DList.clear();
		em_instance->entity2DListChanged=true;
		em_instance->textFieldList.clear();
		break;
	case Win:
		em_instance->entity2DList.clear();
		em_instance->entity2DListChanged=true;
		em_instance->textFieldList.clear();
		break;
	default:
		break;
	}
	
	em_instance->readyToLoad = false;
	em_instance->entity2DListChanged = true;
}

void EntityManager::clearEntities(void)
{
	for each(FullTile* fullTile in fullTileVector)
	{
		delete fullTile;
	}
	fullTileVector.clear();

	for each(EmptyTile* emptyTile in emptyTileVector)
	{
		delete emptyTile;
	}
	emptyTileVector.clear();

	for each(Torch* torch in torchVector)
	{
		delete torch;
	}
	torchVector.clear();

	for each(BoxEntity* box in boxVector)
	{
		delete box;
	}
	boxVector.clear();

	for each(Bonewheel* bonewheel in bonewheelVector)
	{
		delete bonewheel;
	}
	bonewheelVector.clear();

	for each(Eater* eater in eaterVector)
	{
		delete eater;
	}
	eaterVector.clear();

	for each(Faded* faded in fadedVector)
	{
		delete faded;
	}
	fadedVector.clear();

	for each(Door* door in doorVector)
	{
		delete door;
	}
	fadedVector.clear();

	for each(Key* key in keyVector)
	{
		delete key;
	}
	keyVector.clear();

	if(currentPlayer != NULL)
	{
		//delete currentPlayer;
	}

}

void EntityManager::initEntities(ID3D10Device* device)
{
	for each(FullTile* fullTile in fullTileVector)
	{
		fullTile->init(device);
	}

	for each(EmptyTile* emptyTile in emptyTileVector)
	{
		emptyTile->init(device);
	}

	for each(Torch* torch in torchVector)
	{
		torch->init(device);
	}
	
	for each(BoxEntity* box in boxVector)
	{
		box->init(device);
	}

	for each(Bonewheel* bonewheel in bonewheelVector)
	{
		bonewheel->init(device);
	}

	for each(Eater* eater in eaterVector)
	{
		eater->init(device);
	}

	for each(Faded* faded in fadedVector)
	{
		faded->init(device);
	}

	for each(Door* door in doorVector)
	{
		door->init(device);
	}

	for each(Key* key in keyVector)
	{
		key->init(device);
	}

	currentPlayer->init(device);

	currentPhylactery->init(device);
		 eaterDeathFlag = false;
	 bonewheelDeathFlag= false;
	 fadedDeathFlag= false;
	 purpleKeyFlag= false;
	 greenKeyFlag= false;
	 blueKeyFlag= false;
	 doorFlag= false;
	 exitFlag= false;
	
}

void EntityManager::checkCollision(void)
{
		for each(FullTile* fullTile in fullTileVector)
		{
			if(currentPlayer->getCollider()->Collides(fullTile->getCollider()))
			{
				fullTile->interact(currentPlayer);
			}
		}

		for each(Eater* eater in eaterVector)
		{
			
			if(currentPlayer->getCollider()->Collides(eater->getCollider()))
			{
				eater->interact(currentPlayer);
				eaterDeathFlag = true;
			}
		}

		for each(Bonewheel* bonewheel in bonewheelVector)
		{
			if(currentPlayer->getCollider()->Collides(bonewheel->getCollider()))
			{
				bonewheel->interact(currentPlayer);
				bonewheelDeathFlag = true;
			}
		}

		for each(Faded* faded in fadedVector)
		{
			if(currentPlayer->getCollider()->Collides(faded->getCollider()))
			{
				faded->interact(currentPlayer);
				fadedDeathFlag = true;
			}
		}
		for each(Door* door in doorVector)
		{
			if(currentPlayer->getCollider()->Collides(door->getCollider()))
			{
				door->interact();
				doorFlag = true;
			}
		}
		for each(Key* key in keyVector)
		{
			if(currentPlayer->getCollider()->Collides(key->getCollider()))
			{
				key->interact();
				switch(key->id)
				{
				case 1:
					//purple key
					purpleKeyFlag = true;
					break;
				case 2:
					//green key
					greenKeyFlag = true;
					break;
				case 3:
					//blue key
					blueKeyFlag = true;
					break;
				default:
					break;
				}
			}
		}

		if(currentPlayer->getCollider()->Collides(winCollider) && currentPlayer->HasPhylactery())
		{
			StateManager::getInstance()->changeState(GameState::Win);
			AudioManager::getInstance()->StopBackground();
		}
		else if(currentPlayer->getCollider()->Collides(winCollider))
		{
			exitFlag = true;
		}
}

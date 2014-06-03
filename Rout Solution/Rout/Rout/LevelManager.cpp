#include "LevelManager.h"

LevelManager* LevelManager::lm_instance = NULL;

LevelManager* LevelManager::getInstance(void)
{
	if(lm_instance == NULL)
	{
		lm_instance = new LevelManager();
	}
	return lm_instance;
}

LevelManager::LevelManager(void)
{
}

LevelManager::~LevelManager(void)
{
}

bool LevelManager::compare_nodes(Node* node1, Node* node2)
{
	if (node1->getNum() < node2->getNum())
	{
		return true;
	}
    else
	{
		return false;
	}
}

void LevelManager::LoadLevel(string fileName)
{
	vector<FullTile*>	fullTileVector;
	vector<EmptyTile*>	emptyTileVector;
	vector<Torch*>		torchVector;
	vector<Bonewheel*>	bonewheelVector;
	vector<Eater*>		eaterVector;
	vector<BoxEntity*>	boxVector;
	vector<Faded*>		fadedVector;
	vector<Door*>		doorVector;
	vector<Key*>		keyVector;
	list<Node*>			nodeList;
	Collider*			winCollider;

	Player* player;
	ifstream levelFile (fileName);
	if(levelFile.is_open())
	{
		string line = "";
		string type = "";
		float  x = 0;
		float  y = 0;
		float  z = 0;
		int    nodeID = 0;
		int    facing = 0;
		int    nodeNumber = 0;
		int*   nodePath;
		int    nodeTimer;
		bool   isEating;
		while ( levelFile.good() )
		{
			getline(levelFile, line);
			type = line.substr(0, line.find_first_of("|"));
			
			if(type == "EmptyTile")
			{
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				x =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				y =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				z =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				if(y > 0.5)
				{
					y = y;
				}
				emptyTileVector.push_back(new EmptyTile(D3DXVECTOR3(x, y, z)));

			}
			else if(type == "FullTile")
			{
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				x =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				y =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				z =  atoi(line.substr(0, line.find_first_of("|")).c_str());

				fullTileVector.push_back(new FullTile(D3DXVECTOR3(x, y, z)));

			}
			else if(type == "Player")
			{
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				x =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				y =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				z =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				
				player = new Player(D3DXVECTOR3(x, y, z));
				
			}
			else if(type == "Torch")
			{
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				x =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				y =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				z =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				facing =  atoi(line.substr(0, line.find_first_of("|")).c_str());

				torchVector.push_back(new Torch(D3DXVECTOR3(x, y, z), facing));

			}
			else if(type == "Bonewheel")
			{
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				x =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				y =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				z =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				nodeID = atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				line = line.substr(0, line.find_first_of("|")).c_str();
				nodePath = new int[ line.size() ] ;
				for (int i = 0; i < line.size(); i++)
				{
					nodePath[i] = line[i] - 49;
				}
				bonewheelVector.push_back(new Bonewheel (D3DXVECTOR3(x, y, z), nodeID, nodePath, line.size(), false));
			}
			else if(type == "Eater")
			{
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				x =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				y =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				z =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				nodeID = atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				line = line.substr(0, line.find_first_of("|")).c_str();
				nodePath = new int[ line.size() ] ;
				for (int i = 0; i < line.size(); i++)
				{
					nodePath[i] = line[i] - 49;
				}
				eaterVector.push_back(new Eater (D3DXVECTOR3(x, y, z), nodeID, nodePath, line.size(), true));
			}
			else if(type == "Faded")
			{
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				x =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				y =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				z =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				nodeID = atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				line = line.substr(0, line.find_first_of("|")).c_str();
				nodePath = new int[ line.size() ] ;
				for (int i = 0; i < line.size(); i++)
				{
					nodePath[i] = line[i] - 49;
				}
				fadedVector.push_back(new Faded (D3DXVECTOR3(x, y, z), nodeID, nodePath, line.size(), false));
			}
			else if(type == "Node")
			{
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				x =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				y =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				z =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				nodeID = atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				nodeNumber = atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				nodeTimer = atoi(line.substr(0, line.find_first_of("|")).c_str());
				
				nodeList.push_back(new Node(D3DXVECTOR3(x, y, z), nodeID, nodeNumber, 1000));
			}
			else if(type == "Door")
			{
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				x =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				y =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				z =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				nodeID = atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				facing = atoi(line.substr(0, line.find_first_of("|")).c_str());
				doorVector.push_back(new Door(D3DXVECTOR3(x, y, z), nodeID, facing));
			}
			else if(type == "Key")
			{
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				x =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				y =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				z =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				nodeID = atoi(line.substr(0, line.find_first_of("|")).c_str());
				keyVector.push_back(new Key(D3DXVECTOR3(x, y, z), nodeID)); 
			}
			else if(type == "WinTile")
			{
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				x =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				y =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				line = line.substr(line.find_first_of("|") + 1, line.length() - 1);
				z =  atoi(line.substr(0, line.find_first_of("|")).c_str());
				winCollider = new Collider(8.0f, 8.0f, 8.0f, D3DXVECTOR3(x - 4, y - 4, z - 4));
			}
		}
		levelFile.close();
		nodeList.sort(compare_nodes);
		for each(Node* node in nodeList)
		{
			for each(Bonewheel* bonewheel in bonewheelVector)
			{
				if(node->getID() == bonewheel->getNodeID())
				{
					bonewheel->addNode(node);
				}
			}
			for each(Eater* eater in eaterVector)
			{
				if(node->getID() == eater->getNodeID())
				{
					eater->addNode(node);
				}
			}
			for each(Faded* faded in fadedVector)
			{
				if(node->getID() == faded->getNodeID())
				{
					faded->addNode(node);
				}
			}
		}
		//Builds the TilePath
		for each(EmptyTile* tileA in emptyTileVector)
		{
			for each(EmptyTile* tileB in emptyTileVector)
			{
				if(tileB->getDistance(tileA->getPos()) <= 8.0f)
				{
					if(tileA != tileB)
					{
						if(tileB->getPos().x - tileA->getPos().x == 8.0f && tileB->getPos().z - tileA->getPos().z == 0.0f)
						{
							tileA->addBTile(3, tileB);
						}
						else if(tileB->getPos().x - tileA->getPos().x == -8.0f && tileB->getPos().z - tileA->getPos().z == 0.0f)
						{
							tileA->addBTile(1, tileB);
						}
						else if(tileB->getPos().z - tileA->getPos().z == 8.0f && tileB->getPos().x - tileA->getPos().x == 0.0f)
						{
							tileA->addBTile(2, tileB);
						}
						else if(tileB->getPos().z - tileA->getPos().z == -8.0f && tileB->getPos().x - tileA->getPos().x == 0.0f)
						{
							tileA->addBTile(0, tileB);
						}
					}
				}
			}
			for each(Eater* eater in eaterVector)
			{
				if(eater->getPos().x == tileA->getPos().x && eater->getPos().z == tileA->getPos().z)
				{
					eater->eTile = tileA;
				}
			}
			if(player->getPos().x == tileA->getPos().x && player->getPos().z == tileA->getPos().z)
			{
				player->pTile = tileA;
			}
		}
		boxVector.push_back(new BoxEntity(D3DXVECTOR3(128.0f, 8.5f, 128.0f), 256.0f, 1.0f, 256.0f));
		boxVector.push_back(new BoxEntity(D3DXVECTOR3(128.0f, -0.5f, 128.0f), 256.0f, 1.0f, 256.0f));
		EntityManager::getInstance()->clearEntities();
		EntityManager::getInstance()->emptyTileVector = emptyTileVector;
		EntityManager::getInstance()->fullTileVector =	fullTileVector;
		EntityManager::getInstance()->torchVector =		torchVector;
		EntityManager::getInstance()->bonewheelVector = bonewheelVector;
		EntityManager::getInstance()->eaterVector =		eaterVector;
		EntityManager::getInstance()->fadedVector =		fadedVector;
		EntityManager::getInstance()->doorVector =		doorVector;
		EntityManager::getInstance()->keyVector =		keyVector;
		EntityManager::getInstance()->boxVector =		boxVector;
		EntityManager::getInstance()->currentPlayer =	player;
		EntityManager::getInstance()->winCollider =		winCollider;
		EntityManager::getInstance()->currentPhylactery = new Phylactery(player->getPos());
	}
}
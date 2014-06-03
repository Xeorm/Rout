#pragma once
#include "GameEntity3D.h"
#include "FullTile.h"
#include "EmptyTile.h"
#include "Torch.h"
#include "Player.h"
#include "BoxEntity.h"
#include "d3dUtil.h"
#include "EntityManager.h"
#include "Bonewheel.h"
#include "Eater.h"
#include "Collider.h"
#include "Node.h"
#include "Phylactery.h"
#include "Faded.h"
#include "Door.h"
#include "Key.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


class LevelManager
{
private:
	
	static LevelManager *lm_instance;
public:
	LevelManager(void);
	~LevelManager(void);
	static LevelManager *getInstance();
	void LoadLevel(string fileName);
	static bool compare_nodes(Node* node1, Node* node2);
};


#include "Main.h"


#include "GameMenu.h"
#include "DeathScreen.h"
#include "WinScreen.h"
#include <WindowsX.h>
#include <time.h>
#include <random>
// Much of the code in this class was constructed with the guidance of the tutorials found at
// http://www.rastertek.com/tutindex.html.

//Global variables
//HWND hWnd;
bool isFullScreen;
bool fIsPressed;
bool fState;
int mouseX;
int mouseY;
int windowWidth = 800;
int windowHeight = 600;
AudioManager am;
D3DXVECTOR3 oldPos;
D3DXVECTOR3 topView;
D3DXVECTOR3 oldLook;
D3DXVECTOR3 topLook;
D3DXVECTOR3 topUp;
D3DXVECTOR3 oldTop;
D3DXVECTOR3 topRight;
D3DXVECTOR3 oldRight;


bool topLooking;

HINSTANCE hint;

Main::Main(void)
{
}


Main::~Main(void)
{
}


//Derived from the RasterTek tutorials
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	hint = hInstance;
	Main* main;

	main = new Main();
	//game = new Game(hInstance);

	if(main->initialize(hInstance))
	{
		//Starts our draw and update loops.
		main->run();
	}
	main->shutdown();
}


//Modified from the RasterTek tutorials
bool Main::initialize(HINSTANCE hInstance)
{
	bool worked = true;

	mOldMousePos.x = mOldMousePos.y = mNewMousePos.x = mNewMousePos.y = walkSpeed = strafeSpeed = 0;
	leaveOK = false;
	lastTickCount = GetTickCount();
	isFullScreen = isRecentering = isSneaking = tabHeld = false;

	InitializeWindows(windowWidth, windowHeight);

	//set up managers here
	AudioManager::getInstance()->Initialize(m_hwnd);
	AudioManager::getInstance()->Play("sound02.wav", D3DXVECTOR3(0, 0, 0));

	dxMan.initialize(&m_hwnd);
	//	topView.x = 128;
	//	topView.z = 128;
	topView.y = 220;
	topLook.x = 0;
	topLook.y = -1;
	topLook.z = 0;
	topUp.x = -1;
	topUp.z = 0;
	topUp.y = 0;
	topRight.y = 0;
	topRight.x = 0;
	topRight.z = 1;

	topLooking = false;

	playing = false;
	//Beginning state is intro
	StateManager::getInstance()->changeState(Intro);
	updateInterval = 17;
	lastUpdate = 0;

	return worked;
}



//From the RasterTek tutorials
void Main::run()
{
	MSG msg;
	bool done, worked;
	ZeroMemory(&msg, sizeof(MSG));
	done = false;
	while(!done)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			worked = Frame();
			if(!worked)
			{
				done = true;
			}
		}
	}
}

void Main::getEntityManagerFlags()
{
	if(EntityManager::getInstance()->eaterDeathFlag != eaterDeathFlag)
	{
		eaterDeathFlag = EntityManager::getInstance()->eaterDeathFlag;
		EntityManager::getInstance()->textTut.addString(L"Those things are disgusting.  Good thing they're not smart enough to look for this little gem.");

	}
	if(EntityManager::getInstance()->bonewheelDeathFlag != bonewheelDeathFlag)
	{
		bonewheelDeathFlag = EntityManager::getInstance()->bonewheelDeathFlag;
		EntityManager::getInstance()->textTut.addString(L"Those big guys didn't react to me--so long as I keep away from their front, I should be good.");
	}
	if(EntityManager::getInstance()->fadedDeathFlag != fadedDeathFlag)
	{
		fadedDeathFlag = EntityManager::getInstance()->fadedDeathFlag;
		EntityManager::getInstance()->textTut.addString(L"Those things can come at me through walls!");
	}
	if(EntityManager::getInstance()->purpleKeyFlag != purpleKeyFlag)
	{
		purpleKeyFlag = EntityManager::getInstance()->purpleKeyFlag;
		EntityManager::getInstance()->textTut.addString(L"Purple key acquired!");
	}
	if(EntityManager::getInstance()->greenKeyFlag != greenKeyFlag)
	{
		greenKeyFlag = EntityManager::getInstance()->greenKeyFlag;
		EntityManager::getInstance()->textTut.addString(L"Green key acquired!");
	}

	if(EntityManager::getInstance()->blueKeyFlag != blueKeyFlag)
	{
		blueKeyFlag = EntityManager::getInstance()->blueKeyFlag;
		EntityManager::getInstance()->textTut.addString(L"Blue key acquired!");
	}
	if(EntityManager::getInstance()->doorFlag != doorFlag)
	{
		doorFlag = EntityManager::getInstance()->doorFlag;
		EntityManager::getInstance()->textTut.addString(L"I need a key to open this door.  I think there was one back in the first chamber...");
	}
	if(EntityManager::getInstance()->exitFlag != exitFlag)
	{
		exitFlag = EntityManager::getInstance()->exitFlag;
		EntityManager::getInstance()->textTut.addString(L"Oh no, I forgot my phylactery! I'll have to run back and bring it out.");
	}
	
	if(dxMan.firstTorchLitFlag != firstTorchLitFlag)
	{
		firstTorchLitFlag = dxMan.firstTorchLitFlag;
		EntityManager::getInstance()->textTut.addString(L"Press Tab to open the map");

	}
}


bool Main::Frame()
{
	bool worked = true;
	//UPDATE LOOP
	lastTickCount = currentTickCount;
	currentTickCount = GetTickCount();

	//if we're ready to load our textures but haven't yet, do so
	if(EntityManager::getInstance()->readyToLoad && !EntityManager::getInstance()->loaded)
	{	
		dxMan.entity2DList = EntityManager::getInstance()->entity2DList;
		//dxMan.entity3DList = EntityManager::getInstance()->entity3DList;
		dxMan.loadTextures();
		EntityManager::getInstance()->loaded = true;
	}
	//keep dxMan's entity2DList synced with entityManager's entity2DList

	//Starts our draw and update loops.
	MSG msg = {0};
	//Change update logic based on state.
	switch (StateManager::getInstance()->CurrentState())
	{
		//game logic 
	case Intro:
		while (ShowCursor(true) < 1)
		{
		};
		dxMan.renderScene();
		break;
	case Title:
		while (ShowCursor(true) < 1)
		{
		};
		dxMan.renderScene();
		break;
	case Options:
		while (ShowCursor(true) < 1)
		{
		};
		dxMan.renderScene();
		break;
	case Dead:
		while (ShowCursor(true) < 1)
		{
		};
		dxMan.renderScene();
		break;
	case Win:
		while(ShowCursor(true) <1)
		{
		};
		dxMan.renderScene();
		break;
	case InGame:
		while (ShowCursor(false) > 0)
		{
		};
		getEntityManagerFlags();

		EntityManager::getInstance()->currentPlayer->update(currentTickCount - lastTickCount);
		if (EntityManager::getInstance()->currentPlayer->IsAlive())
		{
			closestDistanceBoneWheel = MAX_DISTANCE_BONEWHEEL;
			closestDistanceEater = MAX_DISTANCE_EATER;
			closestDistanceFaded = MAX_DISTANCE_FADED;
			if(EntityManager::getInstance()->currentPlayer->getPos().x > 160 && !firstChamberExitedFlag)
			{
				firstChamberExitedFlag = true;
				EntityManager::getInstance()->textTut.addString(L"Press 'Space' to light wall torches.");
			}
			POINT mousePos;
			GetCursorPos(&mousePos);
			mNewMousePos.x = mousePos.x;
			mNewMousePos.y = mousePos.y;
			RECT windRect;
			GetClientRect(m_hwnd, (LPRECT)&windRect);
			ClientToScreen(m_hwnd, (LPPOINT)&windRect.left);
			ClientToScreen(m_hwnd, (LPPOINT)&windRect.right);
			SetCursorPos((windRect.left + windRect.right) / 2, (windRect.top + windRect.bottom) / 2);
			GetCursorPos(&mousePos);
			mMouseDelta.x = mNewMousePos.x - mousePos.x;
			mMouseDelta.y = mNewMousePos.y - mousePos.y;
			for each(Bonewheel* bonewheel in EntityManager::getInstance()->bonewheelVector)
			{
				bonewheel->update(currentTickCount - lastTickCount);
				//loop through the bonewheel list finding the closest for sound reasons
				if(bonewheel->getDistance(EntityManager::getInstance()->currentPlayer->getPos()) < closestDistanceBoneWheel)
				{
					closestVectorBoneWheel = bonewheel->getPos()-(EntityManager::getInstance()->currentPlayer->getPos());
					closestDistanceBoneWheel = bonewheel->getDistance(EntityManager::getInstance()->currentPlayer->getPos());
				}
			}
			for each(Eater* eater in EntityManager::getInstance()->eaterVector)
			{
				eater->update(currentTickCount - lastTickCount);
				if(!eater->isHunting)
				{
					eater->hunt(EntityManager::getInstance()->currentPlayer);
				}
				//loop through the eater list finding the closest for sound reasons
				if(eater->getDistance(EntityManager::getInstance()->currentPlayer->getPos()) < closestDistanceEater)
				{
					closestDistanceEater = eater->getDistance(EntityManager::getInstance()->currentPlayer->getPos());
					closestVectorEater = eater->getPos()-(EntityManager::getInstance()->currentPlayer->getPos());
				}
			}

			for each(Faded* faded in EntityManager::getInstance()->fadedVector)
			{
				faded->update(currentTickCount - lastTickCount);
				//loop through the faded list finding the closest for sound reasons
				if(faded->getDistance(EntityManager::getInstance()->currentPlayer->getPos()) < closestDistanceFaded)
				{
					closestDistanceFaded = faded->getDistance(EntityManager::getInstance()->currentPlayer->getPos()); 
					closestVectorFaded = faded->getPos()-(EntityManager::getInstance()->currentPlayer->getPos());
				}
			}
			//call audio helper
			AudioHelper();
			//and update the background audio
			AudioBackgroundHelper();
			if(!topLooking)
			{
				dxMan.getCamera()->rotateY(0.0025f * (mMouseDelta.x));
				dxMan.getCamera()->pitch(0.0025f * (mMouseDelta.y));
				if(walkSpeed != 0 || strafeSpeed != 0)
				{
					AudioWalkHelper(false);
				}
				else
				{
					AudioWalkHelper(true);
				}
				if(isSneaking)
				{
					EntityManager::getInstance()->currentPlayer->move((float)walkSpeed / 4, (float)strafeSpeed / 4, currentTickCount - lastTickCount);
				}
				else
				{
					EntityManager::getInstance()->currentPlayer->move(walkSpeed, strafeSpeed, currentTickCount - lastTickCount);
				}
			}
			getEntityManagerFlags();
			EntityManager::getInstance()->textTut.update(currentTickCount - lastTickCount);

		}
		EntityManager::getInstance()->checkCollision();
		dxMan.getCamera()->rebuildView();
		dxMan.render3DScene();

		break;
	case Pause:
		break;

		lastUpdate = currentTickCount;
	}
	//If there is a chance of something failing in a manager that would break the program,
	//handle the breaking case in here.
	return worked;
}


//From the RasterTek tutorials, with inapplicable parts removed
LRESULT CALLBACK Main::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{

	int x = 1;
	int i = 1;
	switch(umsg)
	{
	case WM_KEYDOWN:
		//KEY DOWN INPUT HANDLING CODE HERE
		switch (wparam)
		{
		case VK_ESCAPE:
			shutdown();
			break;
		case VK_SHIFT:
			isSneaking = true;
			break;
		case 81: //"Q" key
			leaveOK = !leaveOK;
			break;

		case VK_SPACE: //"F" key
			switch(StateManager::getInstance()->CurrentState())
			{
			case InGame:
				dxMan.lightTorches();
			}
			break;	
		case 87: //"W" key
			switch(StateManager::getInstance()->CurrentState())
			{
			case InGame:
				if(!topLooking)
				{
					walkSpeed = 4;
				}
				break;
			}
			break;

		case 83: //"S" key
			switch(StateManager::getInstance()->CurrentState())
			{
			case InGame:
				if(!topLooking)
				{
					walkSpeed = -4;
				}
				break;
			}
			break;
		case 65: //"A" key
			switch(StateManager::getInstance()->CurrentState())
			{
			case InGame:
				if(!topLooking)
				{
					strafeSpeed = -2.5f;
				}
				break;
			}
			break;
		case 68: //"D" key
			switch(StateManager::getInstance()->CurrentState())
			{
			case InGame:
				if(!topLooking)
				{
					strafeSpeed = 2.5f;
				}
				break;
			}
			break;
		case 69: //"E" key

			break;
		case 75: //"K" key
			break;	
		case VK_TAB:
			switch(StateManager::getInstance()->CurrentState())
			{
			case InGame:
				if(!topLooking && !tabHeld)
				{
					tabHeld = true;
					if(!mapOpenedFlag)
					{
						mapOpenedFlag = true;
						EntityManager::getInstance()->textTut.addString(L"I need to get out of here.");
						//DISPLAY TEXT

					}
					EntityManager::getInstance()->currentPlayer->switchTop();
					oldPos = dxMan.getCamera()->position();
					oldLook = dxMan.getCamera()->mLook;
					oldTop = dxMan.getCamera()->mUp;
					oldRight = dxMan.getCamera()->mRight;
					topView.x = dxMan.getCamera()->position().x;
					topView.z = dxMan.getCamera()->position().z;
					dxMan.getCamera()->setPosition(topView);
					dxMan.getCamera()->mLook = topLook;
					dxMan.getCamera()->mUp = topUp;
					dxMan.getCamera()->mRight = topRight;
					topLooking = true;
					EntityManager::getInstance()->boxVector[0]->Visible = false;
				}
				else if (!tabHeld)
				{
					EntityManager::getInstance()->currentPlayer->switchTop();
					tabHeld = true;
					if(!mapClosedFlag)
					{
						mapClosedFlag = true;
						EntityManager::getInstance()->textTut.addString(L"And I'll need to bring my phylactery with me. Gotta do this carefully. \nPress left click to place the phylactery");
						//DISPLAY TEXT

					}
					EntityManager::getInstance()->boxVector[0]->Visible = true;
					topLooking = false;
					dxMan.getCamera()->setPosition(oldPos);
					dxMan.getCamera()->mLook = oldLook;
					dxMan.getCamera()->mUp = oldTop;
					dxMan.getCamera()->mRight = oldRight;
				}
				break;
			}
			break;
		}
		switch (StateManager::getInstance()->CurrentState())
		{
			//splash screen
		case Intro:
			switch (wparam)
			{
				//press Enter to leave the splash screen
			case VK_RETURN:
				StateManager::getInstance()->changeState(Title);
				GameMenu::getInstance();
				break;
			}
			break;
			//game logic
		case Title:

			break;
		case InGame:
			switch(wparam)
			{
				//press P to pause
			case 80: //"P" key
				StateManager::getInstance()->changeState(Pause);
				break;
				//press F2 to return to main menu
			case VK_F2:
				StateManager::getInstance()->changeState(Options);
				GameMenu::getInstance()->options();

				break;
			}
			break;
		case Pause:
			switch(wparam)
			{
				//press "P" to unpause
			case 80:
				StateManager::getInstance()->changeState(InGame);
				break;
				//press F2 to return to main menu
			case VK_F2:
				StateManager::getInstance()->changeState(Title);
				break;
			}

			break;
		}
		return 0;
		break;
	case WM_KEYUP:
		//KEY UP INPUT HANDLING CODE HERE
		//Might be a good idea to pass it on through to StateManager or reference
		//StateManager from here so we know what do with it.
		//sMan->KeyDown((unsigned int)wparam);
		switch (wparam)
		{
		case VK_TAB:
			tabHeld = false;
			break;
		case VK_SHIFT:
			isSneaking = false;
			break;
		case 87: //"W" key
			switch(StateManager::getInstance()->CurrentState())
			{
			case InGame:
				if(walkSpeed > 0)
				{
					walkSpeed = 0;

				}
				break;
			}
			break;
		case 83: //"S" key
			switch(StateManager::getInstance()->CurrentState())
			{
			case InGame:
				if(walkSpeed < 0)
				{
					walkSpeed = 0;
				}
				break;
			}
			break;
		case 65: //"A" key
			switch(StateManager::getInstance()->CurrentState())
			{
			case InGame:
				if(strafeSpeed < 0)
				{
					strafeSpeed = 0;
				}
				break;
			}
			break;
		case 68: //"D" key
			switch(StateManager::getInstance()->CurrentState())
			{
			case InGame:
				if(strafeSpeed > 0)
				{
					strafeSpeed = 0;
				}
				break;
			}
			break;

		}
		return 0;
		break;
	case WM_LBUTTONDOWN:
		//AudioManager::getInstance()->Play("sound02.wav", D3DXVECTOR3(-50, 0, 0));
		switch (StateManager::getInstance()->CurrentState())
		{
		case Title:
		case Options:
			GameMenu::getInstance()->handleLeftDownClick(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			break;
		case InGame:
			EntityManager::getInstance()->currentPlayer->placePhylactery();
			if(!phylacteryPlacedFlag)
			{
				phylacteryPlacedFlag = true;
				EntityManager::getInstance()->textTut.addString(L"If those things catch me, I'll reform here at my phylactery.  I can't let them catch me with it...");
				//DISPLAY TEXT

			}
			break;
		case Dead:
			DeathScreen::getInstance()->handleLeftDownClick(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			break;
		case Win:
			WinScreen::getInstance()->handleLeftDownClick(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			break;
		}

		return 0;
		break;

	case WM_RBUTTONDOWN:
		switch(StateManager::getInstance()->CurrentState())
			{
			case InGame:
				EntityManager::getInstance()->currentPlayer->kill(true);
				break;
			}
			break;	
	case WM_MOUSEMOVE:
		switch (StateManager::getInstance()->CurrentState())
		{
		case Title:
		case Options:
			GameMenu::getInstance()->handleMouseMoving(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			break;
		case Dead:
			DeathScreen::getInstance()->handleMouseMoving(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			break;
		case Win:
			WinScreen::getInstance()->handleMouseMoving(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			break;
		case InGame:
			//mNewMousePos.x = GET_X_LPARAM(lparam);
			//mNewMousePos.y = GET_Y_LPARAM(lparam);
			break;


			break;
		}
		break;
	case WM_LBUTTONUP:
		switch (StateManager::getInstance()->CurrentState())
		{
		case Title:
		case Options:
			x = GameMenu::getInstance()->handleLeftUpClick(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			if (x == 1)
			{
				shutdown();
			}
			if (x == 2 && playing == false)
			{
				playing = true;
				ShowCursor(false);
				dxMan.newGame();
				EntityManager::getInstance()->textTut.addString(L"Use WASD to move. Press P to pause.");
					 eaterDeathFlag = false;
	 bonewheelDeathFlag= false;
	 fadedDeathFlag= false;
	 purpleKeyFlag= false;
	 greenKeyFlag= false;
	 blueKeyFlag= false;
	 doorFlag= false;
	 exitFlag= false;
	 	  phylacteryPlacedFlag= false;
	 mapClosedFlag= false;
	 mapOpenedFlag= false;
	 firstTorchLitFlag= false;
	 firstChamberExitedFlag= false;
	 gameStartedFlag= false;
			}
			break;
		case Dead:
			i = DeathScreen::getInstance()->handleLeftUpClick(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			if (i == 1)
			{
				shutdown();
			}
			if (i == 2)
			{
				playing = true;
				ShowCursor(false);
				walkSpeed = 0;
				strafeSpeed = 0;
				dxMan.newGame();
				EntityManager::getInstance()->textTut.addString(L"Use WASD to move. Press P to pause.");
					 eaterDeathFlag = false;
	 bonewheelDeathFlag= false;
	 fadedDeathFlag= false;
	 purpleKeyFlag= false;
	 greenKeyFlag= false;
	 blueKeyFlag= false;
	 doorFlag= false;
	 exitFlag= false;
	 	  phylacteryPlacedFlag= false;
	 mapClosedFlag= false;
	 mapOpenedFlag= false;
	 firstTorchLitFlag= false;
	 firstChamberExitedFlag= false;
	 gameStartedFlag= false;
			}
			if (i == 3)
			{
				StateManager::getInstance()->changeState(Title);
				GameMenu::getInstance()->changeMenu(true);
				playing = false;
				walkSpeed = 0;
				strafeSpeed = 0;
			}
			break;
		case Win:
			i = WinScreen::getInstance()->handleLeftUpClick(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			if( i == 1)
			{
				shutdown();
			}
			if( i ==2)
			{
				playing = true;
				ShowCursor(false);
				walkSpeed = 0;
				strafeSpeed = 0;
				dxMan.newGame();
				EntityManager::getInstance()->textTut.addString(L"Use WASD to move. Press P to pause.");
					 eaterDeathFlag = false;
	 bonewheelDeathFlag= false;
	 fadedDeathFlag= false;
	 purpleKeyFlag= false;
	 greenKeyFlag= false;
	 blueKeyFlag= false;
	 doorFlag= false;
	 exitFlag= false;
	  phylacteryPlacedFlag= false;
	 mapClosedFlag= false;
	 mapOpenedFlag= false;
	 firstTorchLitFlag= false;
	 firstChamberExitedFlag= false;
	 gameStartedFlag= false;
			}
			if( i == 3)
			{
				StateManager::getInstance()->changeState(Title);
				GameMenu::getInstance()->changeMenu(true);
				playing = false;
				walkSpeed = 0;
				strafeSpeed = 0;
			}
			break;
		}
		break;
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
		break;
	}
	return 0;
}

//keeps the mouse within the client area
void Main::boundMouse(HWND hwnd)
{
	RECT windRect;
	GetClientRect(hwnd, (LPRECT)&windRect);
	ClientToScreen(hwnd, (LPPOINT)&windRect.left);
	ClientToScreen(hwnd, (LPPOINT)&windRect.right);

	POINT mousePos;
	SetCursorPos((windRect.left + windRect.right) / 2, (windRect.top + windRect.bottom) / 2);
	isRecentering = true;
	GetCursorPos(&mousePos);
	mOldMousePos.x = mousePos.x;
	mOldMousePos.y = mousePos.y;
	//if(mousePos.x < windRect.left)
	//{
	//	SetCursorPos(windRect.right, mousePos.y);
	//	mOldMousePos.x = windRect.right;
	//	mOldMousePos.y = mousePos.y;
	//	mNewMousePos = mOldMousePos;
	//}
	//if(mousePos.x > windRect.right)
	//{
	//	SetCursorPos(windRect.left, mousePos.y);
	//	mOldMousePos.x = windRect.left;
	//	mOldMousePos.y = mousePos.y;
	//	mNewMousePos = mOldMousePos;
	//}
	//if(mousePos.y < windRect.top)
	//{
	//	SetCursorPos(mousePos.x, windRect.bottom);
	//	mOldMousePos.y = windRect.bottom;
	//	mOldMousePos.x = mousePos.x;
	//	mNewMousePos = mOldMousePos;
	//}
	//if(mousePos.y > windRect.bottom)
	//{
	//	SetCursorPos(mousePos.x, windRect.top);
	//	mOldMousePos.y = windRect.top;
	//	mOldMousePos.x = mousePos.x;
	//	mNewMousePos = mOldMousePos;
	//}

	//need to keep checking for mouse movement 'beyond the edges' for the purposes of camera movement
}

//From the RasterTek tutorials
void Main::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;

	//window's onscreen coords
	int x;
	int y;

	ApplicationHandle = this;

	m_hinstance = GetModuleHandle(NULL);

	m_applicationName = L"Rout";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//Register the window class
	RegisterClassEx(&wc);

	if(isFullScreen)
	{
		windowWidth = GetSystemMetrics(SM_CXSCREEN);
		windowHeight = GetSystemMetrics(SM_CYSCREEN);
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)windowWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)windowHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		x = y = 0;
	}
	else
	{
		x = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
		y = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;
	}
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		x, y, windowWidth, windowHeight, NULL, NULL, m_hinstance, NULL);
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	ShowCursor(true);
	UpdateWindow(m_hwnd);
	return;
}

//Modified from the RasterTek tutorials.
void Main::shutdown()
{
	// Release any created managers here.  Example:
	/*if(m_Graphics)
	{
	m_Graphics->Shutdown();
	delete m_Graphics;
	m_Graphics = 0;
	}*/

	// Shutdown the window.
	ShutdownWindows();

	return;
}


//From the RasterTek tutorials directly.
void Main::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(isFullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}

//From the RasterTek tutorials
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
	case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
	default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}

//play/update the background music
void Main::AudioBackgroundHelper()
{
	AudioManager::getInstance()->PlayBackground("BackgroundMusic.wav", D3DXVECTOR3(0, 2, 0));
	/*float boneWheelVolume = (closestDistanceBoneWheel/MAX_DISTANCE_BONEWHEEL) * DSBVOLUME_MIN;
	float eaterVolume = (closestDistanceEater/MAX_DISTANCE_EATER) * DSBVOLUME_MIN;
	float fadedVolume = (closestDistanceFaded/MAX_DISTANCE_FADED) * DSBVOLUME_MIN;
	float maxVolume = boneWheelVolume;
	if(eaterVolume > maxVolume)
	{
		maxVolume = eaterVolume;
	}
	if(fadedVolume > maxVolume)
	{
		maxVolume = fadedVolume;
	}
	*/
	//AudioManager::getInstance()->AdjustBackgroundVolume(Math-);
}

//play all of the audio cues for the closest of each enemy
void Main::AudioHelper()
{
	float boneWheelVolume = (closestDistanceBoneWheel/MAX_DISTANCE_BONEWHEEL) * DSBVOLUME_MIN;
	float eaterVolume = (closestDistanceEater/MAX_DISTANCE_EATER) * DSBVOLUME_MIN;
	float fadedVolume = (closestDistanceFaded/MAX_DISTANCE_FADED) * DSBVOLUME_MIN;
	AudioManager::getInstance()->PlayBoneWheel("BoneWheel.wav", D3DXVECTOR3(0, 2, 0), boneWheelVolume);
	AudioManager::getInstance()->PlayEater("Eater.wav", D3DXVECTOR3(0, 2, 0), eaterVolume);
	AudioManager::getInstance()->PlayFaded("Faded.wav", D3DXVECTOR3(0, 2, 0), fadedVolume);
}

//play the audio for walking, or stop it, depending on stopAudio
void Main::AudioWalkHelper(bool stopAudio)
{
	if(!stopAudio)
	{
		AudioManager::getInstance()->PlayFootSteps("FootSteps.wav", D3DXVECTOR3(0, 2, 0));
	}
	else
	{
		AudioManager::getInstance()->Stop();
	}
}




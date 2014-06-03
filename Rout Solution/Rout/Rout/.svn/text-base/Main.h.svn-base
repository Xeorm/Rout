#ifndef _MAIN_H_
#define _MAIN_H_

#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include "stdafx.h"
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include "AudioManager.h"
#include "StateManager.h"
#include "EntityManager.h"
#include "Camera.h"

class Main
{
public:
	Main(void);
	~Main(void);

	bool initialize(HINSTANCE hInstance);
	void shutdown();
	void run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	void AudioBackgroundHelper();
	void AudioHelper();
	void AudioWalkHelper(bool stopAudio);
	dxManager dxMan;


private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	void boundMouse(HWND hwnd);

	bool playing;
	D3DXVECTOR2 mOldMousePos;
	D3DXVECTOR2 mNewMousePos;
	D3DXVECTOR2 mMouseDelta;
	float	walkSpeed;
	float	strafeSpeed;
	bool	leaveOK;
	bool	isRecentering;
	bool	isSneaking;
	bool	tabHeld;
	DWORD	lastTickCount;
	DWORD	currentTickCount;
	DWORD	lastUpdate;
	DWORD	updateInterval;
	D3DXVECTOR3	closestVectorEater;
	D3DXVECTOR3	closestVectorBoneWheel;
	D3DXVECTOR3	closestVectorFaded;
	float	closestDistanceEater;
	float	closestDistanceBoneWheel;
	float	closestDistanceFaded;


	
	bool eaterDeathFlag;
	bool bonewheelDeathFlag;
	bool fadedDeathFlag;
	bool purpleKeyFlag;
	bool greenKeyFlag;
	bool blueKeyFlag;
	bool doorFlag;
	bool exitFlag;

	bool phylacteryPlacedFlag;
	bool mapClosedFlag;
	bool mapOpenedFlag;
	bool firstTorchLitFlag;
	bool firstChamberExitedFlag;
	bool gameStartedFlag;
	void getEntityManagerFlags();
};
	
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static Main* ApplicationHandle = 0;

static const float MAX_DISTANCE_EATER = 100;
static const float MAX_DISTANCE_BONEWHEEL = 150;
static const float MAX_DISTANCE_FADED = 100;

#endif
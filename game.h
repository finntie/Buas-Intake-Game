#pragma once
#include "template.h"
#include "surface.h"
#include "Player.h"
#include "Effects.h"
#include "Buttons.h"

namespace Tmpl8 {

class Surface;
class Game
{

private:
	Surface* screen;
	Player* player;
	Effects* DamageEffect;
	Effects* BreakEffect;
	Effects backgroundeffect;
	bool Start = false;
	bool ControlsMenu = false;
	bool HighScoreMenu = false;
	bool Shop = false;
	int damage;
	int Cash;
	bool maxStackBoxesSave = false;
	int mousex = 0, mousey = 0;
	bool click = false;
	bool pause = false;
	bool GameOver = false;
	int frame = 0;
	float SpawnTimeCrates = 300;
	float formuleXY = 320; //320

	bool PlayAgain = false;

	//damage button
	bool damageUpgrade = false;
	float DamageMultiplier = 3;
	int DamageUpgradeCost = 200;

	//MovePrecision button
	bool moveprecisionUpgrade = false;
	bool moveprecisionActive = false;

	//Faster Charge button
	bool fasterChargeUpgrade = false;
	int fasterChargeUpgradeCost = 100;
	float fasterChargeMultiplier = 1;

public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void TryAgain();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown(int button) { click = true; }
	void MouseMove( int x, int y ) { mousex = x, mousey = y; }
	void KeyUp(int key) {  }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
	void Escape() { Start = false; pause = true; Shop = false; }
};

}; // namespace Tmpl8

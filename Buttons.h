#pragma once
#include "template.h"
#include "surface.h"

using namespace Tmpl8;

class Buttons
{
public:
	bool drawPlayButton(Surface* screen, vec2 mousepos, bool clicked, bool pause);
	void drawQuitButton(Surface* screen, vec2 mousepos, bool clicked);
	bool drawControlsButton(Surface* screen, vec2 mousepos, bool clicked);
	bool drawHighScoreButton(Surface* screen, vec2 mousepos, bool clicked);

	bool drawGoBackButton(Surface* screen, vec2 mousepos, bool clicked);
	bool drawGoToShopButton(Surface* screen, vec2 mousepos, bool clicked);
	bool drawPlayAgainButton(Surface* screen, vec2 mousepos, bool clicked);
	bool drawDamageButton(Surface* screen, vec2 mousepos, bool clicked, int cash);
	bool drawMovePrecisionButton(Surface* screen, vec2 mousepos, bool clicked, int cash);
	bool drawFasterChargeButton(Surface* screen, vec2 mousepos, bool clicked, int cash);

	void drawBeginnersAdvice(Surface* screen);
	void drawControlsMenu(Surface* screen);
	void drawShopMenu(Surface* screen);
	void drawHighScoreMenu(Surface* screen);
	void drawTitleScreen(Surface* screen);

	void resetUpgradeCost();

private:
	int Playbuttonx = 300, Playbuttony = 200;
	bool HoveroffPlayButton = false;
	int Quitbuttonx = 300, Quitbuttony = 400;
	bool HoveroffQuitButton = false;
	int Controlsbuttonx = 300, Controlsbuttony = 300;
	bool HoveroffControlsButton = false;
	int HighScoreButtonx = 600, HighScoreButtony = 430;
	bool HoveroffHighScoreButton = false;
	int GoBackButtonx = 20, GoBackButtony = 420;
	bool HoveroffGoBackButton = false;
	int GoToShopButtonx = 700, GoToShopButtony = 20;
	bool HoveroffToShopButton = false;
	int DamageButtonx = 270, DamageButtony = 50;
	int MovePrecisionButtonx = 270, MovePrecisionButtony = 150;
	int FasterChargeButtonx = 270, FasterChargeButtony = 250;
	int PlayAgainButtonx = 350, PlayAgainButtony = 300;
	bool HoveroffPlayAgainButton = false;
	//Damage Button
	int DamageUpgradeCost = 200;
	//Move Precision Button
	int MovePrecisionUpgradeCost = 500;
	bool canBuy = true;
	//Faster Charge Button
	int FasterChargeUpgradeCost = 100;
};


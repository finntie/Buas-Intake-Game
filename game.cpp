#include <Audio/Sound.hpp>

#include "game.h"
#include "Crate.h"
#include "Math.h"
#include "Player.h"
#include "template.h"
#include "surface.h"
#include "Math.h"
#include "Numbers.h"
#include "Buttons.h"
#include <vector>

using namespace std;

namespace Tmpl8
{
	Sprite* CrateSprite(new Sprite(new Surface("assets/Crate.png"), 10));
	Sprite* playerBall(new Sprite(new Surface("assets/Player.png"), 6));
	Sprite* crateDamageEffect(new Sprite(new Surface("assets/BreakEffect.png"), 9));
	Sprite* crateBrokenEffect(new Sprite(new Surface("assets/BrokenCrateEffect.png"), 6));
	Sprite ground(new Surface("assets/Ground.png"), 1);
	
	//Sound system by Jeremiah in the 3dgep.com discord
	Audio::Sound CrateBrokenSoundeffect{ "assets/Sounds/CrateBrokenSound.mp3", Audio::Sound::Type::Sound };
	Audio::Sound DangerSoundeffect{ "assets/Sounds/WarningSound.mp3", Audio::Sound::Type::Sound };

	Numbers number;
	Buttons button;

	vector<Crate*> crateVector;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()		
	{

		player = new Player({ 400, 300 }); 
		DamageEffect = new Effects;
		BreakEffect = new Effects;
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		for (size_t i = 0; i < crateVector.size(); i++)
		{
			delete crateVector[i];
		}
		delete player;
		delete DamageEffect;
		delete BreakEffect;
		
	}

	// -----------------------------------------------------------
	// Play the game from the beginning
	// -----------------------------------------------------------

	void Game::TryAgain()
	{
		crateVector[0]->fullClearArray();
		for (size_t i = 0; i < crateVector.size(); i++)
		{
			crateVector[i]->destroy;
			crateVector.clear();
		}
		Cash = 0;
		frame = 0;
		SpawnTimeCrates = 300;
		formuleXY = 320;

		//damage button
		DamageMultiplier = 3;
		DamageUpgradeCost = 200;

		//MovePrecision button
		moveprecisionActive = false;

		//Faster Charge button
		fasterChargeUpgradeCost = 100;
		fasterChargeMultiplier = 1;

		player->PlayerReset();
		button.resetUpgradeCost();

		//Way to destroy the crates. Got this code from the 3dgep.com discord. 
		auto deleteDestroyedCrate = [](Crate* c)
		{
			if (c->destroy)
			{
				delete c;
				return true;
			}
			return false;
		};
		crateVector.erase(std::remove_if(crateVector.begin(), crateVector.end(), deleteDestroyedCrate), crateVector.end());
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------


	void Game::Tick(float deltaTime)
	{	
		if (GameOver == true) //If Game over
		{
			pause = true;
			maxStackBoxesSave = false;
			number.highScoreManager(frame);
			backgroundeffect.PlayAnimationBackground(screen, player->getPos(), maxStackBoxesSave, pause);
			number.PrintNum(screen, frame, { 400, 7 }, true);
			backgroundeffect.drawGameOver(screen);
			button.drawQuitButton(screen, { (float)mousex, (float)mousey }, click);
			PlayAgain = button.drawPlayAgainButton(screen, { (float)mousex, (float)mousey }, click);
			click = false;

			if (PlayAgain == true)
			{
				TryAgain();
				GameOver = false;
				Start = false;
				pause = false;
			}
		}
		else
		{
			if (Start == false)
			{
				if (ControlsMenu == false) 
				{
					if (HighScoreMenu == false) //If pause menu is open
					{
						backgroundeffect.PlayAnimationBackground(screen, player->getPos(), maxStackBoxesSave, pause);
						button.drawTitleScreen(screen);
						Start = button.drawPlayButton(screen, { (float)mousex, (float)mousey }, click, pause);
						button.drawQuitButton(screen, { (float)mousex, (float)mousey }, click);
						ControlsMenu = button.drawControlsButton(screen, { (float)mousex, (float)mousey }, click);
						HighScoreMenu = button.drawHighScoreButton(screen, { (float)mousex, (float)mousey }, click);
						button.drawBeginnersAdvice(screen);
						click = false;
					}
					else //If highscore menu is open
					{
						backgroundeffect.PlayAnimationBackground(screen, player->getPos(), maxStackBoxesSave, pause);
						HighScoreMenu = button.drawGoBackButton(screen, { (float)mousex, (float)mousey }, click);
						button.drawHighScoreMenu(screen);
						number.highScoreManager(1);
						number.drawHighScore(screen);
						click = false;
					}
				}
				else  //If Controlsmenu is open
				{
					backgroundeffect.PlayAnimationBackground(screen, player->getPos(), maxStackBoxesSave, pause);
					button.drawControlsMenu(screen);
					ControlsMenu = button.drawGoBackButton(screen, { (float)mousex, (float)mousey }, click);
					click = false;
				}

			}
			else
			{
				if (Shop == true)   //If shop menu is open
				{
					pause = true;
					backgroundeffect.PlayAnimationBackground(screen, player->getPos(), maxStackBoxesSave, pause);
					Shop = button.drawGoBackButton(screen, { (float)mousex, (float)mousey }, click);
					button.drawShopMenu(screen);

					//Damage Upgrade
					damageUpgrade = button.drawDamageButton(screen, { (float)mousex, (float)mousey }, click, Cash);
					if (damageUpgrade == true)
					{
						Cash -= DamageUpgradeCost;
						DamageMultiplier += 0.6;
						DamageUpgradeCost += 150;
						damageUpgrade = false;
					}

					//MovePrecision Upgrade
					moveprecisionUpgrade = button.drawMovePrecisionButton(screen, { (float)mousex, (float)mousey }, click, Cash);					
					if (moveprecisionUpgrade == true)
					{
						Cash -= 500;
						moveprecisionActive = true;
						moveprecisionUpgrade = false;
					}

					//Faster Charge Upgrade
					fasterChargeUpgrade = button.drawFasterChargeButton(screen, { (float)mousex, (float)mousey }, click, Cash);
					if (fasterChargeUpgrade == true)
					{
						Cash -= fasterChargeUpgradeCost;
						fasterChargeMultiplier += 0.1;
						fasterChargeUpgradeCost += 100;
						fasterChargeUpgrade = false;
					}
					click = false;
				}
				else    //Game is playing
				{
					pause = false;
					GameOver = backgroundeffect.PlayAnimationBackground(screen, player->getPos(), maxStackBoxesSave, pause);
					Shop = button.drawGoToShopButton(screen, { (float)mousex, (float)mousey }, click);
					ground.Draw(screen, 0, 0);
					player->playerMove(screen, playerBall, moveprecisionActive, fasterChargeMultiplier);
					DamageEffect->PlayAnimationDamage(crateDamageEffect, screen);
					BreakEffect->PlayAnimationBroken(crateBrokenEffect, screen);
					number.PrintNum(screen, Cash, { 320, 0 }, true);
					number.PrintNum(screen, frame, { 0, 0 }, false);
					frame++;
					if (frame % (int)SpawnTimeCrates == 0) //Spawns crates with an interval that decreases over time
					{
						SpawnTimeCrates = 0.000005 * pow(formuleXY, 3) + 100;
						formuleXY -= 1;
						crateVector.emplace_back(new Crate(CrateSprite, { (float)(RandomNumber(0, 7, frame / 5) * 100 + 40), -32 }, { 100, 150 }, RandomNumber(0, 10, 20)));
						crateVector[crateVector.size() - 1]->animationDown(screen, crateVector.size() - 1);
						if (crateVector[crateVector.size() - 1]->crateStackMax() == true || crateVector.size() >= 29)
						{
							crateVector.pop_back();
							crateVector[crateVector.size() - 1]->crateStackMaxsetfalse(false);
						}
					}
					

					for (size_t i = 0; i < crateVector.size(); i++)
					{
						player->CheckCol(crateVector[i]->getpos(), screen, playerBall);
						damage = player->PlayerDamage(crateVector[i]->getpos(), DamageMultiplier, screen);
						if (crateVector[i]->UpdateHP(damage) == true) //updates HP of crate. If its HP is less then 0, It gets deleted
						{
							CrateBrokenSoundeffect.play();
							Cash += crateVector[i]->getCash();
							crateVector[i]->destroy = true;
							BreakEffect->BrokenSetTrue(crateVector[i]->getpos());
							crateVector[i]->clearArray();				 //clears position in array									
						}
					}
					for (size_t i = 0; i < crateVector.size(); i++)
					{
						if (crateVector[i]->destroy == false)		//Draws the crates if they aren't marked "destroy".
						{
							crateVector[i]->setFrame();
							crateVector[i]->CrateDraw(screen);
							crateVector[i]->animationDown(screen, i);
						}
					}

					for (size_t i = 0; i < crateVector.size(); i++)
					{
						maxStackBoxesSave = crateVector[i]->crateStackDeathZone(); //If crates are higher then the max, warnings will play
						if (maxStackBoxesSave == true)
						{
							DangerSoundeffect.setVolume(0.2);
							DangerSoundeffect.setPitch(2);
							DangerSoundeffect.play();
							break;
						}
					}

					//Way to destroy the crates. Got this code from the 3dgep.com discord. 
					auto deleteDestroyedCrate = [](Crate* c)
					{
						if (c->destroy)
						{
							delete c;
							return true;
						}
						return false;
					};
					crateVector.erase(std::remove_if(crateVector.begin(), crateVector.end(), deleteDestroyedCrate), crateVector.end());
					
					click = false;
				}
			}
		}
	}
	
};
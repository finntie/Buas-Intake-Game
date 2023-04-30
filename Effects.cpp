#include "Effects.h"
#include "game.h"
#include <cmath>
#include "template.h"
#include "surface.h"
#include <Audio/Sound.hpp>

using namespace Tmpl8;
int gameFrameDamage = 0;
int spriteFrameDamage = 0;
int gameFrameBroken = 0;
int spriteFrameBroken = 0;
bool CrateCollisionOccured = false;
bool CrateBroken = false;
bool CrateBrokenForBackground = false;


vec2 _PositionDamage;
vec2 _PositionBroken;
Surface backgroundt("assets/BackGround.png");
Sprite GameOverScreen(new Surface("assets/Game_Over.png"), 1);

Audio::Sound GameOverSoundeffect{ "assets/Sounds/GameOverSound.mp3", Audio::Sound::Type::Sound };


void Effects::CollisionSetTrue(vec2 Pos) 
{
	CrateCollisionOccured = true;
	_PositionDamage = Pos;
}


void Effects::BrokenSetTrue(vec2 Pos2)
{
	CrateBroken = true;
	CrateBrokenForBackground = true;
	_PositionBroken = Pos2;
}



void Effects::PlayAnimationDamage(Sprite* sprite, Surface* screen) //Plays the animation when player does damage on a crate
{
	if (CrateCollisionOccured == true)
	{
		sprite->SetFrame(spriteFrameDamage);
		sprite->Draw(screen, (int)_PositionDamage.x, (int)_PositionDamage.y - 10);
		if (gameFrameDamage % 2 == 0)
		{
			spriteFrameDamage++;
		}
		gameFrameDamage++;

		if (gameFrameDamage >= 16)
		{
			CrateCollisionOccured = false;
			gameFrameDamage = 0;
			spriteFrameDamage = 0;
		}
	}
}

void Effects::PlayAnimationBroken(Sprite* sprite, Surface* screen) //Plays the animation when player breaks crate
{
	if (CrateBroken == true)
	{
		sprite->SetFrame(spriteFrameBroken);
		sprite->Draw(screen, (int)_PositionBroken.x - 10, (int)_PositionBroken.y - 10);
		if (gameFrameBroken % 4 == 0)
		{
			spriteFrameBroken++;
		}
		gameFrameBroken++;

		if (gameFrameBroken >= 20)
		{
			CrateBroken = false;
			gameFrameBroken = 0;
			spriteFrameBroken = 0;
		}
	}
}

bool Effects::PlayAnimationBackground(Surface* screen, vec2 playerpos, bool maxstack, bool pause) //true == game over
{
	backgroundt.CopyTo(screen, Xback, Yback);
	Yback = -(playerpos.y / 20); //
	Xback = -(playerpos.x / 20); // Moves the background with the player
	if (pause == false)
	{
		if (maxstack == true)  //If there are boxes higher then the max, the screen will shake
		{
			Xback = FormuleCurveIncrease * sin(FormuleCurve);
			FormuleCurve++;
			Alive -= 0.2;
			if (FormuleCurveIncrease < 7)
			{
				FormuleCurveIncrease += 0.01;
			}
			if (Alive <= 0) // After a while the game will say game over
			{
				GameOverSoundeffect.setPitch(0.8);
				GameOverSoundeffect.setVolume(0.5);
				GameOverSoundeffect.play();
				Alive = 100;
				FormuleCurveIncrease = 0;
				return true;
			}
			else
			{
				return false;
			}

		}
		else
		{
			Alive = 100;
			FormuleCurve = 0;
			FormuleCurveIncrease = 0;
			return false;
		}
	}
	else
	{
		Yback = -(playerpos.y / 20); 
		Xback = -(playerpos.x / 20); 
		return false;
	}
	return false;
	
}

void Effects::PlayAnimationCriticalHit(Sprite* sprite, Surface* screen, bool CriticalHit) //Plays the animation of a critical hit
{
	if (CriticalHit == true)
	{
		CriticalHitAnimationPlaying = true;
	}
	if (CriticalHitAnimationPlaying == true)
	{		
		sprite->Draw(screen, (int)_PositionDamage.x - 10, (int)_PositionDamage.y - 10);
		sprite->SetFrame(CriticalHitSpriteFrame);

		if (TimeCriticalHitAnimationPlaying % 16 == 0)
		{
			CriticalHitSpriteFrame++;
		}
		TimeCriticalHitAnimationPlaying++;
	}
	if (CriticalHitSpriteFrame == 8)
	{
		CriticalHitAnimationPlaying = false;
		TimeCriticalHitAnimationPlaying = 0;
		CriticalHitSpriteFrame = 0;
	}
}

void Effects::drawGameOver(Surface* screen)
{
	GameOverScreen.Draw(screen, 0, 0);
}
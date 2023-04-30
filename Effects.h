#pragma once

#include "template.h"
#include "surface.h"

using namespace Tmpl8;

class Effects
{

public:

	void CollisionSetTrue(vec2 Pos1);
	void BrokenSetTrue(vec2 Pos2);
	void PlayAnimationDamage(Sprite* sprite, Surface* screen);
	void PlayAnimationBroken(Sprite* sprite, Surface* screen);
	void drawGameOver(Surface* screen);
	bool PlayAnimationBackground(Surface* screen, vec2 playerpos, bool maxstack, bool pause);
	void PlayAnimationCriticalHit(Sprite* sprite, Surface* screen, bool CriticalHit);

private:
	float Xback = 0, Yback = 0;
	float FormuleCurve = 0;
	float FormuleCurveIncrease = 0;
	float Alive = 100;
	bool CriticalHitAnimationPlaying = false;
	int TimeCriticalHitAnimationPlaying = 0;
	int CriticalHitSpriteFrame = 0;
	Surface* screen;

};

 

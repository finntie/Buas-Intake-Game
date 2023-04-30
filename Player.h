#pragma once
#include "template.h"
#include "surface.h"

namespace Tmpl8
{
	class Surface;


	class Player
	{
	public:

		Player(vec2 _pos);
	
		void CheckCol(vec2 CPos, Surface* screen, Sprite* sprite);
		void playerMove(Surface* surface, Sprite* sprite, bool MovePrecision, float ChargeMultiplier);
		int PlayerDamage(vec2 cratepos, float DamageMultiplier, Surface* screen);
		void PlayerReset();
		vec2 getPos() { return position; }
	private:

		bool CriticalHit = false;
		Surface* screen;
		vec2 position;

	};

} // namespace Tmpl8


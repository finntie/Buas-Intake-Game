#pragma once
#include "template.h"
#include "surface.h"



using namespace Tmpl8;

	class Crate
	{
	public:
		Crate(Sprite* sprite, vec2 position, vec2 HP, int chanceGoldenCrate);
		void CrateDraw(Surface* screen);
		void animationDown(Surface* surface, unsigned int cratenumber);
		void setFrame();
		vec2 getpos() {	return this->position;}
		bool crateStackMax() { return CrateStackMax; }
		bool crateStackDeathZone() { return CrateStackDanger; }
		void Crate::crateStackMaxsetfalse(bool setfalse) { CrateStackMax = setfalse; }
		bool UpdateHP(int damage);
		int getCash() { if (_GoldenCrateNumber == 5) { return 150; } else { return 50;  } }
		void clearArray();
		void fullClearArray();
		void playCrateDamageSound(int damagestate);
		bool CheckBoxesOnXRow(int j);
		bool destroy = false;


	private:
		bool Damagestate1 = false;
		bool Damagestate2 = false;
		bool Damagestate3 = false;


		Sprite* sprite = nullptr;
		Surface* screen;
		int posIsInUse = 0;
		int _GoldenCrateNumber = 0;
		vec2 position;
		bool CrateStackMax = false;
		bool CrateStackDanger = false;
		int crateToGolden = 0;
		vec2 _HP;
	};



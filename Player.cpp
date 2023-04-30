#include "Player.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <cmath>
#include "surface.h"
#include "template.h"
#include "game.h"
#include "Effects.h"

#include <Audio/Sound.hpp>

using namespace Tmpl8;


	
	Sprite* CriticalHitEffectSprite(new Sprite(new Surface("assets/CriticalHitEffect.png"), 8));
	Audio::Sound BounceSoundeffect{ "assets/Sounds/BounceSound.mp3", Audio::Sound::Type::Sound };
	Audio::Sound ChargeSoundeffect{ "assets/Sounds/ChargeSound.mp3", Audio::Sound::Type::Sound };
	Audio::Sound SpecialHitSoundeffect{ "assets/Sounds/SpecialMoveHitSound.mp3", Audio::Sound::Type::Sound };

	float PreviousX = 402;
	float PreviousY = 300;
	float DeltaY = 0;
	float DeltaX = 0;
	float maxSpeed = 10; //default maxspeed = 10
	int wait = 30;
	float specialMovePower = 0;
	bool specialMoveHit = false;
	bool specialMoveHitCheck = false;
	int framePlayer = 0;
	int specialMovePowerSave = 0;
	int Damage = 0;
	float MultiplierCratePos = 1;
	Effects DamageEffect;

	Effects CriticalhitEffect;
	
	Player::Player(vec2 _pos)
	{
		position = _pos;		
	}
	
	void Player::PlayerReset()
	{
		PreviousX = 402; position.x = 400;
		PreviousY = 300; position.y = 300;
	}


	//Player moves

	void Player::playerMove(Surface* screen, Sprite* sprite, bool MovePrecision, float ChargeMultiplier)
	{
		sprite->Draw(screen, (int)position.x - 9, (int)position.y - 9);		//Draws the player on the screen.
		//Adds gravity to the player.
		DeltaY = position.y - PreviousY;
		DeltaX = position.x - PreviousX;

		PreviousY = position.y;
		PreviousX = position.x;

		position.y += DeltaY;
		position.x += DeltaX;

		
		position.y += 0.2f;
		

		//slows player down in the air
		if (MovePrecision == true)
		{
			PreviousX = position.x;
		}
		else
		{
			if (PreviousX > position.x)
			{
				PreviousX -= 0.04f;
			}
			else if (PreviousX < position.x)
			{
				PreviousX += 0.04f;
			}
		}
		//Checks if player is not going too fast
		if (DeltaX >= 6)
		{
			PreviousX = position.x;
		}
		if (DeltaX <= -6)
		{
			PreviousX = position.x;
		}
		if (DeltaY >= maxSpeed + 1)
		{
			PreviousY = position.y - maxSpeed;
		}
		if (DeltaY <= -maxSpeed - 1)
		{
			PreviousY = position.y + maxSpeed;
		}

		//prevents going off the bottom of the map
		if (position.y >= 500 - 34)
		{
			specialMoveHit = false;
			if (DeltaY < 1) 
			{

				position.y = 500 - 34;
			}
			else
			{
				sprite->SetFrame(0);
				BounceSoundeffect.setPitch(1);
				BounceSoundeffect.play();
				PreviousY = ((position.y - PreviousY) + position.y) - 1;
			}

			//slows player down on X-as on the ground
			if (MovePrecision == true)
			{
				PreviousX = position.x;
			}
			else
			{
				if (DeltaX < 0.15f && DeltaX > -0.15f)
				{
					PreviousX = position.x; //If player is too slow (moving in the x-as) then it stops.
				}
				else
				{
					if (PreviousX > position.x)
					{
						PreviousX -= 0.4f;
					}
					else if (PreviousX < position.x)
					{
						PreviousX += 0.4f;
					}
				}
			}
		}
		//prevents player going higher than the screen
		if (position.y <= 20)
		{
			PreviousY = ((position.y - PreviousY) + position.y) - 1;
		}

		//left wall collision
		if (position.x <= 0)
		{
			PreviousX = (DeltaX + position.x) - 1;
			if (position.x < -1)
			{
				position.x = 0;
				PreviousX = position.x;
			}
		}
		//right wall collision
		if (position.x >= ScreenWidth - 36)
		{
			PreviousX = (DeltaX - position.x) + 1;
			if (position.x > ScreenWidth - 37)
			{
				position.x = ScreenWidth - 36;
				PreviousX = position.x;
			}
		}

		//checks if player is out of screen
		if (position.x > ScreenWidth || position.x < 0 - 10)
		{
			position.x = 100; PreviousX = position.x;	
		}
		if (position.y > ScreenHeight || position.y < 0)
		{
			position.y = 100; PreviousY = position.y;
		}

		if (specialMoveHit == false)
		{
			//input from the player
			if (GetAsyncKeyState(VK_LEFT))
			{
				sprite->SetFrame(0);
				if (DeltaX > -5) //Max speed
				{
					if (MovePrecision == true)
					{
						position.x -= 5;
					}
					else
					{
						position.x -= 1;
					}
				}
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				sprite->SetFrame(5);

				if (DeltaX < 5) //Max speed
				{
					if (MovePrecision == true)
					{
						position.x += 5;
					}
					else
					{
						position.x += 1;
					}
				}
			}
			if (GetAsyncKeyState(VK_UP))
			{
				if (wait <= 0 && position.y > 500 - 38) //Can only jump when on ground and with a timer
				{
					PreviousY = position.y + 8;
					wait = 30;
				}
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (DeltaY < maxSpeed) //Max speed downwards
				{
					position.y += 0.4;
				}
			}
		}
		if (GetAsyncKeyState(VK_SPACE)) //Special move
		{
			ChargeSoundeffect.setPitch(specialMovePower / 1 + 3);
			ChargeSoundeffect.setVolume(0.2);
			specialMoveHit = true;
			PreviousX = position.x;
			PreviousY = position.y;
			specialMovePower += 0.2f * ChargeMultiplier;
			if (specialMovePower >= maxSpeed)
			{
				specialMovePower = maxSpeed;
			}
			ChargeSoundeffect.play();
			position.y -= 0.2;
			sprite->SetFrame((int)((specialMovePower + 0.25f) / maxSpeed * 4 - 1));
			std::cout << specialMovePower << std::endl;
		}
		else
		{
			ChargeSoundeffect.setVolume(0);
			PreviousY -= specialMovePower;
			if (specialMovePower > 0)
			{
				sprite->SetFrame(4);
				specialMovePowerSave = (int)specialMovePower; //Saves the power of the move
			}
		
			specialMovePower = 0;
			Damage = 0;
		}

		wait--;	
	}
	
	//check collision with crates
	void Player::CheckCol(vec2 CratePos, Surface* screen, Sprite* sprite)
	{
		//collision with top of the crates
		if (position.y + 34 >= CratePos.y && position.y + 34 <= CratePos.y + 32 && position.x + 34 >= CratePos.x + 6 && position.x <= CratePos.x + 74)
		{
			if (specialMoveHit == true)
			{
				SpecialHitSoundeffect.setVolume(3);
				SpecialHitSoundeffect.setPitch(0.5);
				SpecialHitSoundeffect.replay();
				specialMoveHitCheck = true;
				sprite->SetFrame(0);
				DamageEffect.CollisionSetTrue({position});
			}
			specialMoveHit = false;
			if (DeltaY < 1)
			{	

				position.y = CratePos.y - 38;
			}
			else
			{
				BounceSoundeffect.setPitch(0.7);
				BounceSoundeffect.play();
				PreviousY = (DeltaY + position.y) + 0.5f;
			}
		}
		else
		{
		}
		//collision with the left of crate
		if (position.x + 34 >= CratePos.x && position.x + 34 <= CratePos.x + 10 && position.y >= CratePos.y - 34 && position.y + 34 <= CratePos.y + 40)
		{
			
			if (DeltaX > 4)
			{
				position.x = CratePos.x - 35;
				PreviousX = position.x;
			}
			if (DeltaX < 1)
			{
				position.x = CratePos.x - 34;
			}
			else
			{
				PreviousX = (DeltaX + position.x) - 1;
			}
		}
		//collision with the right of crate
		if (position.x <= CratePos.x + 80 && position.x >= CratePos.x + 70 && position.y >= CratePos.y - 34 && position.y + 34 <= CratePos.y + 40)
		{
			if (DeltaX < 4)
			{
				position.x = CratePos.x + 81;
				PreviousX = position.x;
			}
			if (DeltaX < 1)
			{
				position.x = CratePos.x + 81;
			}
			else
			{
				PreviousX = (DeltaX - position.x) + 1;
			}
		}
		

	}

	
	int Player::PlayerDamage(vec2 cratepos, float DamageMultiplier, Surface* screen)
	{
		CriticalhitEffect.PlayAnimationCriticalHit(CriticalHitEffectSprite, screen, CriticalHit);
		CriticalHit = false;
		//calculates the damage on hit
		if (specialMovePowerSave > 0 && specialMoveHitCheck == true)
		{
			if (position.x + 16 < cratepos.x + 40) //Calculates if player is in the middle of the crate for more damage
			{
				MultiplierCratePos = ((position.x + 16) - (cratepos.x)) / 20;
			}
			else if (position.x + 16 >= cratepos.x + 40)
			{
				MultiplierCratePos = ((position.x + 16) - (cratepos.x + 80)) / 20;
			}			
			if (MultiplierCratePos < 0) MultiplierCratePos *= -1;
			if (MultiplierCratePos > 1.8) //Critical hit 
			{
				CriticalHit = true; 
				MultiplierCratePos = 5;
			}
			std::cout << MultiplierCratePos << std::endl;
			//Damage
			Damage = specialMovePowerSave * int(DamageMultiplier * MultiplierCratePos);
			specialMovePowerSave = 0;
			specialMoveHitCheck = false;
			return (Damage);
		}
		else
		{
			specialMoveHitCheck = false;
			Damage = 0;
			return (Damage);
		}
	}



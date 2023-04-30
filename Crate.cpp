#include "Crate.h"
#include <vector>
#include "template.h"
#include "surface.h"

#include <Audio/Sound.hpp>

using namespace Tmpl8;

int CratePositions[9][6];
bool boxActive = true;
Audio::Sound CrateDamageSoundeffect{ "assets/Sounds/CrateDamageSound.mp3", Audio::Sound::Type::Sound };

//Gives own crate a sprite, position and HP.
Crate::Crate(Sprite* sprite, vec2 position, vec2 HP, int goldenCrate)
{
	this->sprite = sprite;
	this->position = position;
   	this->_HP = HP;
	this->_GoldenCrateNumber = goldenCrate;
}



//Draws Crate.
void Crate::CrateDraw(Surface* screen)
{
	sprite->Draw(screen, (int)position.x, (int)position.y);
	
}

//Animation going down 
void Crate::animationDown(Surface* surface, unsigned int cratenumber)
{		
	if (position.y != 500 - 32) //only counts for boxes not on the ground
	{
		if (position.y != 500 - 32 * 2) // and only counts for the boxes above the second row but if not... (line 91)
		{
			if (position.y != 500 - 32 * 3) // third time is the charm
			{
				if (position.y != 500 - 32 * 4) // Nope, going four times
				{
					if (position.y != 500 - 32 * 5) // Okay now you know the drill
					{
						if (position.y != 500 - 32 * 6) // Sure, just one more
						{
							posIsInUse = -1;
							for (int j = 0; j < 6; j++)
							{
								for (int i = 0; i < 9; i++)
								{
									if ((int)position.x == CratePositions[i][j]) //checks if the position where the crates want to land, is already in use
									{
										posIsInUse = j + 1;
									}
								}
							}
							if (posIsInUse == -1)
							{
								posIsInUse = 0;
							}

							if (posIsInUse == 1)
							{
								if (position.y >= 500 - 32 - 32)                     //Sets the position in the array
								{
									position.y = 500 - 32 - 32;
									CratePositions[(int)(position.x / 100)][1] = (int)position.x;
								}
								else
								{
									position.y++;
								}
							}
							else if (posIsInUse == 2)
							{
								if (position.y >= 500 - 32 - 32 - 32)
								{
									position.y = 500 - 32 - 32 - 32;
									CratePositions[(int)(position.x / 100)][2] = (int)position.x;

								}
								else
								{
									position.y++;
								}
							}
							else if (posIsInUse == 3)
							{
								if (position.y >= 500 - 32 - 32 - 32 - 32)
								{
									position.y = 500 - 32 - 32 - 32 - 32;
									CratePositions[(int)(position.x / 100)][3] = (int)position.x;
									CrateStackDanger = true;
								}
								else
								{
									position.y++;
								}
							}
							else if (posIsInUse == 4)
							{
								if (position.y >= 500 - 32 * 5)
								{
									position.y = 500 - 32 * 5;
									CratePositions[(int)(position.x / 100)][4] = (int)position.x;

								}
								else
								{
									position.y++;
								}
							}
							else if (posIsInUse == 5)
							{
								if (position.y >= 500 - 32 * 6)
								{
									position.y = 500 - 32 * 6;
									CratePositions[(int)(position.x / 100)][5] = (int)position.x;
									CrateStackMax = true;
								}
								else
								{
									position.y++;
								}
							}
							else if (posIsInUse == 6)
							{
								CrateStackMax = true;
							}
							else if (posIsInUse == 0)
							{
								position.y++;
								if (position.y >= 500 - 32)
								{
									position.y = 500 - 32;
									CratePositions[(int)(position.x / 100)][0] = (int)position.x;
								}

							}
						}
						else //Checks if there are boxes on the fifth row
						{
							boxActive = CheckBoxesOnXRow(5);
						}
					}
					else //Checks if there are boxes on the fourth row
					{
						boxActive = CheckBoxesOnXRow(4);
					}
				}
				else //Checks if there are boxes on the third row
				{
					boxActive = CheckBoxesOnXRow(3);
				}
			}
			else //Checks if there are boxes on the second row
			{
				boxActive = CheckBoxesOnXRow(2);
			}
		}
		else //Checks if there are boxes on the first row
		{
			boxActive = CheckBoxesOnXRow(1);
		}
		
	}
	
}

void Crate::setFrame() //sets the correct sprite-frame to the correct crate
{
	if (_GoldenCrateNumber == 5)
	{
		crateToGolden = 5;
	}

	if (position.y == 500 - 32 || position.y == 500 - 32 - 32 || position.y == 500 - 32 - 32 - 32)
	{
		if (_GoldenCrateNumber == 5)
		{
			if (_HP.y <= 120 && _HP.y >= 85)
			{
				playCrateDamageSound(1);
				sprite->SetFrame(7);
			}
			else if (_HP.y < 85 && _HP.y >= 50)
			{
				playCrateDamageSound(2);
				sprite->SetFrame(8);
			}
			else if (_HP.y < 50)
			{
				playCrateDamageSound(3);
				sprite->SetFrame(9);
			}
			else
			{
				sprite->SetFrame(6);
			}
		}
		else
		{

			if (_HP.x <= 75 && _HP.x >= 50)
			{
				playCrateDamageSound(1);
				sprite->SetFrame(2);
			}
			else if (_HP.x < 50 && _HP.x >= 25)
			{
				playCrateDamageSound(2);
				sprite->SetFrame(3);
			}
			else if (_HP.x < 25)
			{
				playCrateDamageSound(3);
				sprite->SetFrame(4);
			}
			else
			{
				sprite->SetFrame(1);
			}
		}
	}
	else if (position.y == 500 - 32 * 4|| position.y == 500 - 32 * 5 || position.y == 500 - 32 * 6)
	{
		sprite->SetFrame(5);
	}
	else
	{
		sprite->SetFrame(0);
	}
}


bool Crate::UpdateHP(int damage)
{
	if (_GoldenCrateNumber == 5)
	{
		this->_HP.y -= damage;
	}
	else
	{
		this->_HP.x -= damage;
	}
	if (this->_HP.x <= 0 || this->_HP.y <= 0)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

void Crate::clearArray()
{
	
	if (posIsInUse == 0)
	{
	CratePositions[(int)(position.x / 100)][0] = 0;
	}
	else if (posIsInUse == 1)
	{
		CratePositions[(int)(position.x / 100)][1] = 0;
	}
	else if (posIsInUse == 2)
	{
		CratePositions[(int)(position.x / 100)][2] = 0;
	}
	else if (posIsInUse == 3)
	{
		CratePositions[(int)(position.x / 100)][3] = 0;
	}
	else if (posIsInUse == 4)
	{
		CratePositions[(int)(position.x / 100)][4] = 0;
	}
	else if (posIsInUse == 5)
	{
		CratePositions[(int)(position.x / 100)][5] = 0;
	}
}

void Crate::fullClearArray()
{
	CrateStackMax = false;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			CratePositions[i][j] = 0;
		}
	}
}


void Crate::playCrateDamageSound(int damagestate)
{
	if (this->Damagestate1 == false && damagestate == 1)
	{
		CrateDamageSoundeffect.setPitch(0.7);

		CrateDamageSoundeffect.replay();

		this->Damagestate1 = true;
	}
	else if (Damagestate2 == false && damagestate == 2)
	{
		CrateDamageSoundeffect.setPitch(0.7);

		CrateDamageSoundeffect.replay();

		this->Damagestate2 = true;

	}
	else if (Damagestate3 == false && damagestate == 3)
	{
		CrateDamageSoundeffect.setPitch(0.7);

		CrateDamageSoundeffect.replay();

		this->Damagestate3 = true;

	}
}

bool Crate::CheckBoxesOnXRow(int j)
{
	{
		for (int i = 0; i < 9; i++)
		{
			if (position.x == CratePositions[i][j])
			{
				return true;
				break;
			}
			else
			{
				boxActive = false;
			}
		}
		if (boxActive == false) //If there are none, the position will go 1 down and the statement doesn't count anymore
		{
			position.y++;
		}
		return false;
	}
}
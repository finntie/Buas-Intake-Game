#include "Buttons.h"

#include "template.h"
#include "surface.h"
#include "Numbers.h"
#include <Audio/Sound.hpp>

using namespace Tmpl8;

extern int exitapp;

//buttons
Sprite UnpauseButton(new Surface("assets/Buttons/Unpause_Button.png"), 1);
Sprite GoBackButton(new Surface("assets/Buttons/GoBack_Button.png"), 1);
Sprite PlayButton(new Surface("assets/Buttons/Play_Button.png"), 1);
Sprite QuitButton(new Surface("assets/Buttons/Quit_Button.png"), 1);
Sprite ControlsButton(new Surface("assets/Buttons/Controls_Button.png"), 1);
Sprite HighScoresButton(new Surface("assets/Buttons/HighScores_Button.png"), 1);
Sprite ToShopButton(new Surface("assets/Buttons/ToShop_Button.png"), 1);
Sprite DamageButton(new Surface("assets/Buttons/Damage_Button.png"), 2);
Sprite MovePrecisionButton(new Surface("assets/Buttons/MovePrecision_Button.png"), 3);
Sprite FasterChargeButton(new Surface("assets/Buttons/FasterCharge_Button.png"), 1);
Sprite PlayAgainButton(new Surface("assets/Buttons/PlayAgain_Button.png"), 1);

//menus
Sprite ControlsMenu(new Surface("assets/Controls_List.png"), 1);
Sprite ShopMenu(new Surface("assets/Shop.png"), 1);
Sprite HighscoreMenu(new Surface("assets/HighScore.png"), 1);


//other
Sprite TitleScreen(new Surface("assets/Title.png"), 1);
Sprite BeginnersAdviceText(new Surface("assets/StartScreenAdvice2.png"), 1);
Audio::Sound ButtonHoverSoundeffect{ "assets/Sounds/ButtonHoverSound.mp3", Audio::Sound::Type::Sound };
Audio::Sound ButtonPressSoundeffect{ "assets/Sounds/ButtonPressSound.mp3", Audio::Sound::Type::Sound };
Audio::Sound UpgradeSoundeffect{ "assets/Sounds/UpgradeSound.mp3", Audio::Sound::Type::Sound };

Numbers number;

void Buttons::resetUpgradeCost()
{
	DamageUpgradeCost = 200;
	FasterChargeUpgradeCost = 100;
	MovePrecisionUpgradeCost = 500;
	canBuy = true;
}

//Draws the buttons on the screen and updates the game if clicked on
bool Buttons::drawPlayButton(Surface* screen, vec2 mousepos, bool clicked, bool pause) //Draws the playbutton and if its paused, it draws the unpause button
{
	ButtonHoverSoundeffect.setPitch(2);
	ButtonPressSoundeffect.setVolume(2);
	ButtonPressSoundeffect.setPitch(0.5);
	UpgradeSoundeffect.setPitch(0.7);
	UpgradeSoundeffect.setVolume(0.8);

	if (mousepos.x > Playbuttonx && mousepos.x < Playbuttonx + 140 * 1.3 && mousepos.y > Playbuttony && mousepos.y < Playbuttony + 60 * 1.3)
	{
		if (HoveroffPlayButton == true)
		{
		ButtonHoverSoundeffect.replay();
		HoveroffPlayButton = false;
		}
		if (pause == true)
		{
			UnpauseButton.DrawScaled(Playbuttonx - 7, Playbuttony - 3, 140 * 1.4, 60 * 1.4, screen);
		}
		else
		{
			PlayButton.DrawScaled(Playbuttonx - 7, Playbuttony - 3, 140 * 1.4, 60 * 1.4, screen);

		}
		if (clicked == true)
		{
			ButtonPressSoundeffect.play();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		HoveroffPlayButton = true;
		if (pause == true)
		{
			UnpauseButton.DrawScaled(Playbuttonx, Playbuttony, 140 * 1.3, 60 * 1.3, screen);
		}
		else
		{
			PlayButton.DrawScaled(Playbuttonx, Playbuttony, 140 * 1.3, 60 * 1.3, screen);
		}
		return false;
	}
} 

void Buttons::drawQuitButton(Surface* screen, vec2 mousepos, bool clicked) //Draws the quit button and exits the game if clicked on.
{
	if (mousepos.x > Quitbuttonx && mousepos.x < Quitbuttonx + 140 * 1.3 && mousepos.y > Quitbuttony && mousepos.y < Quitbuttony + 60 * 1.3)
	{
		if (HoveroffQuitButton == true)
		{
			ButtonHoverSoundeffect.replay();
			HoveroffQuitButton = false;
		}

		QuitButton.DrawScaled(Quitbuttonx - 7, Quitbuttony - 3, 140 * 1.4, 60 * 1.4, screen);
		if (clicked == true)
		{
			exitapp = 1;
		}
		
	}
	else
	{
		HoveroffQuitButton = true;
		QuitButton.DrawScaled(Quitbuttonx, Quitbuttony, 140 * 1.3, 60 * 1.3, screen);
	}
} //


bool Buttons::drawControlsButton(Surface* screen, vec2 mousepos, bool clicked) //Draws the controls button
{

	
	if (mousepos.x > Controlsbuttonx && mousepos.x < Controlsbuttonx + 220 * 1.3 && mousepos.y > Controlsbuttony && mousepos.y < Controlsbuttony + 60 * 1.3)
	{		
		if (HoveroffControlsButton == true)
		{
			ButtonHoverSoundeffect.replay();
			HoveroffControlsButton = false;
		}

		ControlsButton.DrawScaled(Controlsbuttonx - 61, Controlsbuttony - 3, 220 * 1.4, 60 * 1.4, screen);
		
		if (clicked == true)
		{
			ButtonPressSoundeffect.play();

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		HoveroffControlsButton = true;
		ControlsButton.DrawScaled(Controlsbuttonx - 50, Controlsbuttony, 220 * 1.3, 60 * 1.3, screen);

		return false;
	}
}

bool Buttons::drawHighScoreButton(Surface* screen, vec2 mousepos, bool clicked)
{


	if (mousepos.x > HighScoreButtonx - 50 && mousepos.x < HighScoreButtonx + 145 * 0.9 && mousepos.y > HighScoreButtony && mousepos.y < HighScoreButtony + 56 * 0.9)
	{
		if (HoveroffHighScoreButton == true)
		{
			ButtonHoverSoundeffect.replay();
			HoveroffHighScoreButton = false;
		}

		HighScoresButton.DrawScaled(HighScoreButtonx - 60, HighScoreButtony - 0, 220 * 0.9, 60 * 0.9, screen);

		if (clicked == true)
		{
			ButtonPressSoundeffect.play();

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		HoveroffHighScoreButton = true;
		HighScoresButton.DrawScaled(HighScoreButtonx - 50, HighScoreButtony, 220 * 0.8, 60 * 0.8, screen);

		return false;
	}
}

bool Buttons::drawGoBackButton(Surface * screen, vec2 mousepos, bool clicked)
{
	if (mousepos.x > GoBackButtonx && mousepos.x < GoBackButtonx + 60 * 1.3 && mousepos.y > GoBackButtony && mousepos.y < GoBackButtony + 60 * 1.3)
	{
		if (HoveroffGoBackButton == true)
		{
			ButtonHoverSoundeffect.replay();
			HoveroffGoBackButton = false;
		}


		GoBackButton.DrawScaled(GoBackButtonx - 3, GoBackButtony - 3, 60 * 1.4, 60 * 1.4, screen);

		if (clicked == true)
		{
			ButtonPressSoundeffect.play();

			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		HoveroffGoBackButton = true;
		GoBackButton.DrawScaled(GoBackButtonx, GoBackButtony, 60 * 1.3, 60 * 1.3, screen);
		return true;
	}
}


bool Buttons::drawGoToShopButton(Surface* screen, vec2 mousepos, bool clicked)
{
	if (mousepos.x > GoToShopButtonx && mousepos.x < GoToShopButtonx + 60 * 1.3 && mousepos.y > GoToShopButtony && mousepos.y < GoToShopButtony + 60 * 1.3)
	{
		if (HoveroffToShopButton == true)
		{
			ButtonHoverSoundeffect.replay();
			HoveroffToShopButton = false;
		}

		ToShopButton.DrawScaled(GoToShopButtonx - 3, GoToShopButtony - 3, 60 * 1.4, 60 * 1.4, screen);

		if (clicked == true)
		{
			ButtonPressSoundeffect.play();

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		HoveroffToShopButton = true;
		ToShopButton.DrawScaled(GoToShopButtonx, GoToShopButtony, 60 * 1.3, 60 * 1.3, screen);
		return false;
	}
}

bool Buttons::drawDamageButton(Surface* screen, vec2 mousepos, bool clicked, int cash)
{
	number.PrintNum(screen, DamageUpgradeCost, { 600, 80 }, false);
	number.PrintNum(screen, cash, { 470, 30 }, false	);


	if (mousepos.x > DamageButtonx && mousepos.x < DamageButtonx + 60 * 1.3 && mousepos.y > DamageButtony && mousepos.y < DamageButtony + 60 * 1.3)
	{
		
		DamageButton.DrawScaled(DamageButtonx - 3, DamageButtony - 3, 60 * 1.4, 60 * 1.4, screen);

		if (clicked == true)
		{
			if (cash >= DamageUpgradeCost)
			{		

				UpgradeSoundeffect.replay();
				DamageUpgradeCost += 150;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;

		}
	}
	else
	{
		DamageButton.DrawScaled(DamageButtonx, DamageButtony, 60 * 1.3, 60 * 1.3, screen);
		return false;

	}
}

bool Buttons::drawMovePrecisionButton(Surface* screen, vec2 mousepos, bool clicked, int cash)
{
	if (canBuy == true)
	{
		number.PrintNum(screen, MovePrecisionUpgradeCost, { 600, 180 }, false);
	}

	if (mousepos.x > MovePrecisionButtonx && mousepos.x < MovePrecisionButtonx + 60 * 1.3 && mousepos.y > MovePrecisionButtony && mousepos.y < MovePrecisionButtony + 60 * 1.3)
	{
		MovePrecisionButton.DrawScaled(MovePrecisionButtonx - 3, MovePrecisionButtony - 3, 60 * 1.4, 60 * 1.4, screen);

		if (clicked == true)
		{
			if (canBuy == true)
			{
				if (cash >= MovePrecisionUpgradeCost)
				{

					UpgradeSoundeffect.play();

					canBuy = false;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		
		}
		else
		{
			return false;

		}
	}
	else
	{
		MovePrecisionButton.DrawScaled(MovePrecisionButtonx, MovePrecisionButtony, 60 * 1.3, 60 * 1.3, screen);
		return false;

	}
}

bool Buttons::drawFasterChargeButton(Surface* screen, vec2 mousepos, bool clicked, int cash)
{
	number.PrintNum(screen, FasterChargeUpgradeCost, { 600, 280 }, false);


	if (mousepos.x > FasterChargeButtonx && mousepos.x < FasterChargeButtonx + 60 * 1.3 && mousepos.y > FasterChargeButtony && mousepos.y < FasterChargeButtony + 60 * 1.3)
	{

		FasterChargeButton.DrawScaled(FasterChargeButtonx - 3, FasterChargeButtony - 3, 60 * 1.4, 60 * 1.4, screen);

		if (clicked == true)
		{
			if (cash >= FasterChargeUpgradeCost)
			{
				UpgradeSoundeffect.replay();

				FasterChargeUpgradeCost += 100;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;

		}
	}
	else
	{
		FasterChargeButton.DrawScaled(FasterChargeButtonx, FasterChargeButtony, 60 * 1.3, 60 * 1.3, screen);
		return false;

	}
}

bool Buttons::drawPlayAgainButton(Surface* screen, vec2 mousepos, bool clicked)
{
	if (mousepos.x > PlayAgainButtonx && mousepos.x < PlayAgainButtonx + 60 * 1.3 && mousepos.y > PlayAgainButtony && mousepos.y < PlayAgainButtony + 60 * 1.3)
	{
		if (HoveroffPlayAgainButton == true)
		{
			ButtonHoverSoundeffect.play();
			HoveroffPlayAgainButton = false;
		}

		GoBackButton.DrawScaled(PlayAgainButtonx - 3, PlayAgainButtony - 3, 60 * 1.4, 60 * 1.4, screen);

		if (clicked == true)
		{
			ButtonPressSoundeffect.play();

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		HoveroffPlayAgainButton = true;
		GoBackButton.DrawScaled(PlayAgainButtonx, PlayAgainButtony, 60 * 1.3, 60 * 1.3, screen);
		return false;
	}
}

void Buttons::drawControlsMenu(Surface* screen)
{
	ControlsMenu.Draw(screen, 0, 0);
}

void Buttons::drawShopMenu(Surface* screen)
{
	ShopMenu.Draw(screen, 0, 0);
}

void Buttons::drawHighScoreMenu(Surface* screen)
{
	HighscoreMenu.Draw(screen, 0, 0);
}

void Buttons::drawBeginnersAdvice(Surface* screen)
{
	BeginnersAdviceText.Draw(screen, 540, 250);
}

void Buttons::drawTitleScreen(Surface* screen)
{
	TitleScreen.Draw(screen, 0, 0);
}
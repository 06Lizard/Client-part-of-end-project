#pragma once
#include "Colors.h"

/*
Color codes for SetColor()
0 = Black
1 = Blue
2 = Green
3 = Aqua
4 = Red
5 = Purple
6 = Yellow
7 = White
8 = Gray
9 = Light Blue
10 = Light Green
11 = Light Aqua
12 = Light Red
13 = Light Purple
14 = Light Yellow
15 = Bright White
*/

void Colors::SetColor(int textColor, int backgroundColor)
{
	// Avoiding errors in case someone were to input an invalid color code.
	if ((0 <= textColor && textColor <= 15) && (0 <= backgroundColor && backgroundColor <= 15))
	{
		// Moves the bits of bg color 4 steps to the left to combine the colors in a way that the compiler can can read both the bg and text color from the same int. 
		int color = textColor + (backgroundColor << 4); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
}

void Colors::SetColor(int textColor)
{
	// 0 is black (default bg color).
	SetColor(textColor, 0);
}

void Colors::ResetColor()
{
	SetColor(7, 0); // White and black
}

void Colors::PrintError(std::string error)
{
	SetColor(12); // Red
	std::cerr << error << std::endl;
	LogMessage("->  " + error);
    ResetColor();
}

void Colors::PrintWarning(std::string warning)
{
	SetColor(6); // Yellow
	std::cout << warning << std::endl;
	LogMessage("->  "  + warning);
	ResetColor();
}

void Colors::PrintSuccessful(std::string successful)
{
	SetColor(10); // Green
	std::cout << successful << std::endl;
	LogMessage("->  " + successful);
	ResetColor();
}

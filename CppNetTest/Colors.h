#pragma once
#include <iostream>
#include <windows.h>

class Colors 
{
protected:
	/// <summary>
	/// Input color code 0-15 for text and background.
	/// </summary>
	/// <param name="textColor"></param>
	/// <param name="backgroundColor"></param>
	void SetColor(int textColor, int backgroundColor);

	/// <summary>
	/// Input color code 0-15 for text and background.
	/// </summary>
	/// <param name="textColor"></param>
	/// <param name="backgroundColor"></param>
	void SetColor(int textColor);

	/// <summary>
	/// Sets the color to default.
	/// </summary>
	void ResetColor();
};

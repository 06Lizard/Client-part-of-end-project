#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include "DataManager.h"

class Colors : public DataManager
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
	/// Sets the color to default (white text, black bg).
	/// </summary>
	void ResetColor();


	// Debug messages:

	/// <summary>
	/// Sends the input string as an error in red.
	/// </summary>
	/// <param name=""></param>
	void PrintError(std::string errorText);

	/// <summary>
	/// Sends the input string as a warning in yellow.
	/// </summary>
	/// <param name=""></param>
	void PrintWarning(std::string warningText);

	/// <summary>
	/// Sends the input string as a successful message in green.
	/// </summary>
	/// <param name="successful"></param>
	void PrintSuccessful(std::string successfulText);
};

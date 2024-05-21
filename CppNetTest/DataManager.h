#pragma once
#include <string.h>
#include <fstream>
#include <iostream>

class DataManager
{
private:
    std::ofstream logFile;
    std::string filename = "Log.txt"; // Must include ".txt" for it to become a txt file.

protected:
	/// <summary>
	/// Returns true if successfully saved data.
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="data"></param>
	/// <returns></returns>
	void LogMessage(const std::string& data);
};

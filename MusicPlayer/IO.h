#pragma once
#include "pch.h"

#define i_ std::stoi
#define d_ std::stod
#define ll_ std::stoll
#define s_ std::to_string
namespace IO
{
	static string GetSegmentFromLine(string fileName, unsigned int lineNumber, int segment);
	static int GetNumberOfLines(string fileName);

	static string extention = ".txt";

	static void ChangeExtention(string ext) { extention = ext; }
	static bool CheckFileExtension(const string& fileName, const string& ext = extention)
	{
		if (fileName.find('.') == string::npos) return false;
		return fileName.substr(fileName.find_last_of('.')) == ext;
	}

	static string GetFileExtension(const string& fileName)
	{
		if (fileName.find('.') == string::npos) return "";
		return fileName.substr(fileName.find_last_of('.'));
	}

	static bool CheckForExtension(const string& fileName)
	{
		return fileName.find('.') != string::npos;
	}

	static std::fstream& GotoLine(std::fstream& file, unsigned int num)
	{
		if (num < 1) return file;

		file.seekg(std::ios::beg);
		for (unsigned int i = 0; i < num - 1; ++i) {
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return file;
	}



	static int GetLineFromWord(string fileName, string word)
	{
		if (!CheckForExtension(fileName)) fileName += extention;
		int returnLine = 1;
		fstream inFile(fileName);
		string temp = "", buffer = "";
		while (!inFile.eof())
		{
			std::getline(inFile, temp);
			std::stringstream ss(temp);
			while (ss >> buffer)
			{
				if (buffer == word)	return returnLine;
			}
			++returnLine;
		}
		return NULL;
	}

	static bool CheckForWord(string fileName, string word, int segment = 1)
	{
		if (!CheckForExtension(fileName)) fileName += extention;
		short i = 0, numOfLines = GetNumberOfLines(fileName);
		while (i++ < numOfLines)
			if (GetSegmentFromLine(fileName, i, segment) == word) return true;
		return false;
	}

	static string CheckForFile(string fileName)
	{
		if (!CheckForExtension(fileName)) fileName += extention;
		fstream check(fileName);
		if (!check.is_open())
		{
			ofstream create(fileName);
			create.close();
		}
		else check.close();
		return fileName;
	}

	static void SaveLine(short line, string newLine, string fileName)
	{
		vector<string> temp;
		short lineCounter = 1, i = 0;
		string buffer = "", t = "temp.txt";
		if (!CheckForExtension(fileName)) fileName += extention;
		fstream fileIn(fileName);
		while (!fileIn.eof())
		{
			std::getline(fileIn, buffer);
			if (lineCounter == line) temp.push_back(newLine);
			else temp.push_back(buffer);
			++lineCounter;
		}
		fileIn.close();

		std::remove(fileName.c_str());

		ofstream create(t);
		create.close();

		fileIn.open(t);

		for (i = 0; i < temp.size() - 1; i++)
		{
			fileIn << temp[i] + "\n";
		}
		GotoLine(fileIn, i + 1);
		fileIn << temp[i];

		fileIn.close();

		while(!std::rename(t.c_str(), fileName.c_str()));
		std::remove(t.c_str());
	}

	static void SaveMultipleLines(vector<short> newLines, vector<string> newValues, string fileName, bool AllLines = false)
	{
		vector<string> temp;
		short i = 0;
		fstream fileIn;
		string buffer = "", t = "temp.txt";
		if (!CheckForExtension(fileName)) fileName += extention;
		if (AllLines) temp = newValues;
		else
		{
			short lineCounter = 1, index = 0;
			fileIn.open(fileName);
			while (!fileIn.eof())
			{
				std::getline(fileIn, buffer);
				if (lineCounter == newLines[index])
				{
					temp.push_back(newValues[index]);
					if (index < newLines.size() - 1) ++index;
				}
				else temp.push_back(buffer);
				++lineCounter;
			}
			fileIn.close();
		}

		std::remove(fileName.c_str());

		ofstream create(t);
		create.close();

		fileIn.open(t);

		for (i = 0; i < temp.size() - 1; i++)
		{
			fileIn << temp[i] + "\n";
		}
		GotoLine(fileIn, i + 1);
		fileIn << temp[i];

		fileIn.close();

		while(!std::rename(t.c_str(), fileName.c_str()));
		std::remove(t.c_str());
	}

	static int GetNumberOfLines(string fileName)
	{
		if (!CheckForExtension(fileName)) fileName += extention;
		fstream countLines(fileName);
		int numOfLines = 0;
		string Null = "";
		while (!countLines.eof())
		{
			std::getline(countLines, Null);
			if (Null == "" && numOfLines == 0)
			{
				countLines.close();
				return 0;
			}
			++numOfLines;
		}
		countLines.close();
		return numOfLines;
	}

	static void AddLine(string newLine, string fileName)
	{
		if (!CheckForExtension(fileName)) fileName += extention;
		fstream addLine(fileName, std::ios::app);
		addLine.seekg(std::ios::end);
		if (GetNumberOfLines(fileName) > 0) addLine << "\n" + newLine;
		else addLine << newLine;
		addLine.close();
	}

	static void AddMultipleLines(vector<string>& newValues, string fileName)
	{
		if (!CheckForExtension(fileName)) fileName += extention;
		fstream addLine;
		for (short i = 0; i < newValues.size(); i++)
		{
			addLine.open(fileName, std::ios::app);
			addLine.seekg(std::ios::end);
			addLine << "\n" + newValues[i];
			addLine.close();
		}
		if (addLine.is_open()) addLine.close();
	}

	static string GetLine(unsigned int line, string fileName)
	{
		if (!CheckForExtension(fileName)) fileName += extention;
		fstream getLine(fileName);
		string returnValue = "";
		GotoLine(getLine, line);
		std::getline(getLine, returnValue);
		getLine.close();
		return returnValue;
	}

	static void ReplaceLine(string fileName, string replaceLine)
	{
		if (!CheckForExtension(fileName)) fileName += extention;
		std::remove(fileName.c_str());

		string t = "temp.txt";
		ofstream create(t);
		create << replaceLine;
		create.close();

		while(!std::rename(t.c_str(), fileName.c_str()));
	}

	static string GetSegmentFromLine(string fileName, unsigned int lineNumber, int segment)
	{
		int tracker = 1;
		if (!CheckForExtension(fileName)) fileName += extention;
		fstream search(fileName);
		GotoLine(search, lineNumber);

		string inputLine = "", buffer = "";

		std::getline(search, inputLine);
		std::stringstream ss(inputLine);
		search.close();

		while (ss >> buffer)
		{
			if (tracker == segment)	return buffer;
			++tracker;
		}
		return "";
	}

	static void ReplaceSegementInLine(string fileName, unsigned int lineNumber, int segment, string replace)
	{
		int tracker = 1;
		bool firstLine = false;
		if (lineNumber == 1) firstLine = true;
		string tempFN = fileName;
		if (!CheckForExtension(fileName)) fileName += extention;
		fstream search(fileName);
		GotoLine(search, lineNumber);

		string inputLine = "", buffer = "", outputLine = "";

		std::getline(search, inputLine);
		std::stringstream ss(inputLine);
		search.close();

		while (ss >> buffer)
		{
			if (tracker == segment) outputLine += replace + " ";
			else outputLine += buffer + " ";
			++tracker;
		}
		SaveLine(lineNumber, outputLine, tempFN);
	}

	static void RemoveLine(string fileName, unsigned lineNumber)
	{
		vector<string> temp;
		short lineCounter = 1, i = 0;
		string buffer = "", t = "temp.txt";
		if (!CheckForExtension(fileName)) fileName += extention;
		fstream fileIn(fileName);
		while (!fileIn.eof())
		{
			std::getline(fileIn, buffer);
			if (lineCounter != lineNumber) temp.push_back(buffer);
			++lineCounter;
		}
		fileIn.close();

		std::remove(fileName.c_str());

		ofstream create(t);
		create.close();

		fileIn.open(t);
		if (temp.size() > 0)
		{
			for (i = 0; i < temp.size() - 1; i++)
			{
				fileIn << temp[i] + "\n";
			}
			GotoLine(fileIn, i + 1);
			fileIn << temp[i];
		}

		fileIn.close();

		while(!std::rename(t.c_str(), fileName.c_str()));
		std::remove(t.c_str());
	}

	static bool DeleteSecondInstanceOfWord(string fileName, string word)
	{
		if (!CheckForExtension(fileName)) fileName += extention;
		int line = GetLineFromWord(fileName, word), numofLines = GetNumberOfLines(fileName);
		if (line == NULL) return false;
		for (line = line + 1; line <= numofLines; line++)
		{
			if (GetSegmentFromLine(fileName, line, 1) == word)
			{
				RemoveLine(fileName, line);
				return true;
			}
		}
		return false;
	}

	static bool DeleteSecondInstanceOfWord(string fileName)
	{
		if (!CheckForExtension(fileName)) fileName += extention;
		int numOfLines = GetNumberOfLines(fileName), i = 1;
		do
		{
			if (GetSegmentFromLine(fileName, i, 1) == GetSegmentFromLine(fileName, i + 1, 1))
			{
				RemoveLine(fileName, i + 1);
				return true;
			}
		} while (i++ < numOfLines - 1);
		return false;
	}
}
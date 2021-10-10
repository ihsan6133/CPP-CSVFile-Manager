#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#pragma once

class CSVFile {
public:

	//Debug opening mode. Prints a debug message if successfully opened the file.
	static int debug;

	//Writes a new line after function
	static int addNewLine;

	//Does not write new line after function
	static int doNotAddLine;

	//Default Constructor
	CSVFile(const char* _name);

	//Create and open file with opening modes.
	CSVFile(const char* _name, int num);


	//Clear file, write a new row and end line
	//Opens file in write mode (fstream::out)
	void WriteRow(std::string txt, int num = 2);

	//Adds a new row to the file without clearing data and ends line
	//Opens file in append mode (fstream::app)
	void AppendRow(std::string txt, int num = 2);

	//Clears Data in the file
	void EmptyContents();

	//Returns value in cell. Returns 
	//last value if row or column is out of bounds.
	//Arguments: row and column of cell
	std::string GetCell(int row, int column);

	//Goes to next line by writing a newline character('\n')
	void NextLine();

	//Deletes file
	void DeleteFile();

	std::string operator()(int row, int column);

	//Overloading extraction operator for 2d vectors
	void operator>> (std::vector<std::vector<std::string>>& csvVector);

	//Overloading insertion operator for 2d vectors
	void operator<< (std::vector<std::vector<std::string>> myVector);

	//Parsing from text file to map. 
	// If first column of file is not a number, 
	// characters from a-z or A-Z gets converted to integers from 1-26
	void operator>> (std::map<int, std::string>& map);

	//Overloading insertion operator for map<int, string>
	void operator<< (std::map<int, std::string> map);
private:
	std::fstream file;
	std::string name;
};


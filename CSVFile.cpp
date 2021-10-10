#include "CSVFile.h"

CSVFile::CSVFile(const char* _name) : name(_name) {
	file.open(name, std::fstream::app);
	file.close();
}

CSVFile::CSVFile(const char* _name, int num) : name(_name) {
	file.open(name, std::fstream::app);
	if (num == 1)
	{
		file << "Debug: File opened successfully\n";
	}
	file.close();
}

void CSVFile::WriteRow(std::string txt, int num) {
	file.open(name, std::fstream::out);
	file.clear();
	file.seekg(0);
	file << txt;
	if (num == 2) {
		file << "\n";
	}
	file.close();
}

void CSVFile::AppendRow(std::string txt, int num) {
	file.open(name, std::fstream::app);
	file.clear();
	file.seekg(0);
	file << txt;
	if (num == 2) {
		file << "\n";
	}
	file.close();
}

void CSVFile::EmptyContents() {
	file.open(name, std::fstream::out);
	file.close();
}

std::string CSVFile::GetCell(int row, int column) {
	file.open(name, std::fstream::in);
	file.clear();
	file.seekg(0);
	std::string rowData;
	std::string cellData;
	for (int i = 0; i < row; i++) {
		std::getline(file, rowData, '\n');

	}
	std::stringstream sso;
	sso << rowData;
	for (int c = 0; c < column; c++) {
		std::getline(sso, cellData, ',');
	}
	return cellData;
	file.close();
}

void CSVFile::NextLine() {
	file.open(name, std::fstream::app);
	file << "\n";
	file.close();
}

void CSVFile::DeleteFile() {
	remove(name.c_str());
}

std::string CSVFile::operator()(int row, int column)
{
	return this->GetCell(row, column);
}

void CSVFile::operator>> (std::vector<std::vector<std::string>>& csvVector) {

	std::vector<std::string> rows;
	file.open(name, std::fstream::in);
	file.clear();
	file.seekg(0);
	while (file.peek() != std::fstream::traits_type::eof()) {
		std::string row;
		std::getline(file, row, '\n');
		if (row != "")
		{
			std::stringstream string;
			string << row;
			std::string value;
			while (std::getline(string, value, ','))
			{
				rows.push_back(value);
			}
			csvVector.push_back(rows);
			rows.clear();
		}
		else
		{
			csvVector.push_back({ "" });
		}

	}
	file.close();
}

void CSVFile::operator<< (std::vector<std::vector<std::string>> myVector) {
	file.open(name, std::fstream::app);
	for (std::size_t r = 0; r < myVector.size(); r++)
	{
		for (std::size_t c = 0; c < myVector[r].size(); c++)
		{
			file << myVector[r][c];
			if (c != myVector[r].size() - 1) {
				file << ",";
			}
			else if (r != myVector.size() - 1) {
				file << "\n";
			}
		}
	}
	file.close();
}

void CSVFile::operator>>(std::map<int, std::string>& map)
{
	file.open(name, std::fstream::in);
	file.clear();
	file.seekg(0);
	while (file.peek() != std::fstream::traits_type::eof()) {
		std::string row;
		std::getline(file, row, '\n');
		if (row != "")
		{
			std::string keyString;
			std::string value;
			std::stringstream sso;
			sso << row;
			std::getline(sso, keyString, ',');
			std::getline(sso, value);
			if (keyString.find_first_not_of("0123456789") == std::string::npos) {
				map[std::stoi(keyString)] = value;
			}
			else {
				char keyChar = keyString[0];
				keyChar = std::tolower(keyChar);
				if (int(keyChar) > 96 && int(keyChar) <= 122) {
					map[int(keyChar) - 96] = value;
				}
			}
		}
	}
	file.close();

}

void CSVFile::operator<<(std::map<int, std::string> map)
{
	file.open(name, std::fstream::app);
	for (auto pair : map) {
		file << pair.first << "," << pair.second;
		if (map.rbegin()->first != pair.first) {
			file << "\n";
		}
	}
	file.close();
}

int CSVFile::debug = 1;
int CSVFile::addNewLine = 2;
int CSVFile::doNotAddLine = 3;
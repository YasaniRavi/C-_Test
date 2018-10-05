#pragma once
#include "FileDataFields.h"

class FileData
{
public:
	FileData();
	~FileData();
	bool FileProcess(std::string filename, std::string outFilePath);
private:
	std::vector<fields> ParseCsvData(std::string inputFileName);
	static bool SortbyTicker(const fields &a, const fields &b);
	bool WriteOutFile(std::vector<std::string> data, std::string outFilePath);
};


#include "stdafx.h"
#include "FileData.h"
#include <algorithm>
#include <stdlib.h>
#include<iostream>
#include "FileDataFields.h"
constexpr char delimiter=',';
using namespace std;

FileData::FileData()
{
}


FileData::~FileData()
{
}

vector<fields> FileData::ParseCsvData(std::string inputFileName)
{
	std::vector<fields> data;
	//fileds data;


	std::ifstream inputFile(inputFileName);
	inputFile.seekg(3);

	int l = 0;
	bool bExists = false;
	while (inputFile) {
		l++;
		string s;
		if (!getline(inputFile, s)) break;

		if (s[0] != '#') {
			istringstream ss(s);
			vector<double> record;
			std::vector<string> dataLine;
			while (ss) {
				string line;
				if (!getline(ss, line, delimiter))
					break;
				try {
					dataLine.push_back(line);

				}
				catch (const std::invalid_argument e) {
					cout << "NaN found in file " << inputFileName << " line " << l
						<< endl;
					e.what();
				}
			}
			fields fd;
			fd.Timestamp = stol(dataLine.at(0));
			fd.Ticker = dataLine.at(1);
			fd.bid = stod(dataLine.at(2));
			fd.bidSize = stoi(dataLine.at(3));
			fd.ask = stod(dataLine.at(4));
			fd.askSize = stoi(dataLine.at(5));
			fd.valume = stoi(dataLine.at(6));
			data.push_back(fd);

		}
	}

	if (!inputFile.eof()) {
		cerr << "Could not read file " << inputFileName << "\n";
		exit(EXIT_FAILURE);
	}

	return data;
}
bool FileData::SortbyTicker(const fields &a, const fields &b)
{
	return (a.Ticker < b.Ticker);
}
bool FileData::WriteOutFile(vector<std::string> data, string outFilePath)
{
	try {
		std::ofstream outputFile(outFilePath);
		for (auto value : data)
			outputFile << value << "\n";
		return true;
	}
	catch (...)
	{
		cout << "data write to output file failed."<<endl;
		return false;
	}
}
bool FileData::FileProcess(string inFilePath, string outFilePath)
{
	
	try {
		vector<string> outData;
		std::vector<fields> data = ParseCsvData(inFilePath);
		std::sort(data.begin(), data.end(), SortbyTicker);

		output op;
		for (auto f : data)
		{
			if (op.tic.empty()) {
				op.tic = f.Ticker;
				op.minBid = f.ask - f.bid;
				op.maxBid = f.ask - f.bid;
				op.sumValume = f.valume;
				op.timeStampDiff = 0;
				op.preTimeStamp = f.Timestamp;
				op.sumOfAskBidMul = f.bid*f.askSize + f.ask*f.bidSize;
				op.sumOfAskBid = f.askSize + f.bidSize;
			}
			else {
				if (op.tic == f.Ticker) {
					if (op.maxBid < (f.ask - f.bid))
						op.maxBid = f.ask - f.bid;
					if (op.minBid > (f.ask - f.bid))
						op.minBid = f.ask - f.bid;
					op.sumValume += f.valume;
					if (op.timeStampDiff < abs(f.Timestamp - op.preTimeStamp))
						op.timeStampDiff = abs(f.Timestamp - op.preTimeStamp);
					op.preTimeStamp = f.Timestamp;

					op.sumOfAskBidMul += f.bid*f.askSize + f.ask*f.bidSize;
					op.sumOfAskBid += f.askSize + f.bidSize;
				}
				else {

					string str = op.tic + "," + std::to_string(op.maxBid) + "," + std::to_string(op.minBid) + "," + std::to_string(op.sumValume) + "," + std::to_string(op.timeStampDiff) + "," + std::to_string(op.sumOfAskBidMul / op.sumOfAskBid);
					outData.push_back(str);

					op.tic = f.Ticker;
					op.minBid = f.ask - f.bid;
					op.maxBid = f.ask - f.bid;
					op.sumValume = f.valume;
					op.timeStampDiff = 0;
					op.preTimeStamp = f.Timestamp;
					op.sumOfAskBidMul = f.bid*f.askSize + f.ask*f.bidSize;
					op.sumOfAskBid = f.askSize + f.bidSize;
				}
			}
		}
		bool resp = WriteOutFile(outData, outFilePath);
		return resp;
		
	}
	catch (...) {
		cout << "file process failed" << endl;
		return false;
	}
}
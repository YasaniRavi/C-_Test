// C++_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include "FileData.h"
using namespace std;


int main(int argc,      // Number of strings in array argv  
	char *argv[])
{
	if (argc == 1)
	{
		cout << "please provide input and output file.";
		return 0;
	}
	else if (argc == 2)
	{
		cout << "please provide output file.";
	}
	else if (argc > 2)
	{
		vector<string> outData;
		string inFilePath = argv[1];
		string outFilePath = argv[2];
		FileData fileData;
		bool bResp = fileData.FileProcess(inFilePath, outFilePath);
		if(bResp)
		{
			cout << "Succesfully completed data process.";
		}
		else {
			cout << "data process failed.";
		}
		
	}
	
    return 0;
}


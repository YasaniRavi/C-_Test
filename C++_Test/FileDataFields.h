#pragma once
#include <stdafx.h>

struct fields
{
	long Timestamp;
	std::string Ticker;
	double bid;
	int bidSize;
	double ask;
	int askSize;
	int valume;
};
struct output
{
	std::string tic;
	double minBid;
	double maxBid;
	unsigned long long sumValume;
	long timeStampDiff;
	long preTimeStamp;
	double sumOfAskBidMul;
	double sumOfAskBid;
};


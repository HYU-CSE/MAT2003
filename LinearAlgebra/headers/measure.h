#pragma once

#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "to_string.h"

using namespace std;
#define TEST_END(t_, tName, result) \
	cout << "test: " << (tName) << " is finished!" << endl; \
	cout << "result: " << (result) << endl; \
	cout << "execution time(" << (t_).repeat << ") total: " << (t_).total << ", average: " << (t_).average << endl << endl;

#define TIME_TEST(t_, repeat) \
	measure::time (t_)((repeat));\
	for((t_).start(); (t_).end(); (t_).endTick())
	
namespace measure
{
	class time{
	public:
		double total, average;
		double * result = nullptr;
		size_t repeat = 0;

		time(size_t repeat = 1) : repeat(repeat) {}
		~time(){}

		void start()
		{
			this->tick = 0;
			this->total = 0;
			this->average = 0;
			this->result = (double*)malloc(sizeof(double) * this->repeat + sizeof(double));
			lapStart();
		}
		void endTick()
		{
			result[this->tick++] = lapEnd();
			total += result[this->tick - 1];
			lapStart();
		}
		bool end()
		{
			if(this->tick == this->repeat)
			{
				total /= CLOCKS_PER_SEC;
				average = total / repeat;
				return false;
			}
			return true;
		}
	private:
		clock_t lap;
		size_t tick = 0;

		void lapStart()
		{
			lap = clock();
		}
		double lapEnd()
		{
			return (double)clock() - lap;
		}
	};
}
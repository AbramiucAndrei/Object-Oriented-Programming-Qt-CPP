#pragma once
#include <Service.h>
#include <assert.h>
class Test
{
	string filename;
public:
	Test(string s):filename{s}{}
	void run_test();
};


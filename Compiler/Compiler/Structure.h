#pragma once
#include "LexicalAnalizer.h"
#include <vector>
using namespace std;


class Sbase
{
	int x;
public:
	Sbase() {}
	virtual string getId()
	{
		return "Sbase";
	}
	virtual string getName()
	{
		return "Sbase";
	}
};

class Sl : public Sbase
{
public:
	lexeme_type lexeme;
	Sl(lexeme_type _lexeme) : lexeme(_lexeme) {}
	string getId()
	{
		return "Sl";
	}
	string getName()
	{
		return to_string(lexeme);
	}
};

class Sunit : public Sbase
{
public:
	vector<vector<Sbase*>> sub;
	bool repeatable;
	bool optional;
	Sunit(vector<vector<Sbase*>> _sub, bool _optional= false, bool _repeatable = false) : optional(_optional), repeatable(_repeatable), sub(_sub) {};
	string getId()
	{
		return "Sunit";
	}
	string getName()
	{
		return "";
	}
};

Sunit* init_syntax_model();
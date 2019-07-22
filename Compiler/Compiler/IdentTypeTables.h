#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

class TypeTableNode
{
public:
	TypeTableNode() {};
	TypeTableNode(string name_) : name(name_) {};
	string name;
	virtual ~TypeTableNode() {}
};

struct IdentTableNode
{
public:
	IdentTableNode() {};
	IdentTableNode(string name_) : name(name_) {};
	string name;
	TypeTableNode* type;
};

class RecTableNode: public TypeTableNode
{
public:
	RecTableNode() {};
	RecTableNode(string name_): TypeTableNode(name_) { };
	map<string, IdentTableNode> fields;
};


extern map<string, IdentTableNode> identTable;
extern map<string, TypeTableNode*> typeTable;

void addIdent(string name);

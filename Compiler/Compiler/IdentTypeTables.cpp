#include "IdentTypeTables.h"

map<string, IdentTableNode> identTable;
map<string, TypeTableNode*> typeTable;


void addIdent(string name)
{
	if (identTable.find(name) == identTable.end())
		identTable[name] = IdentTableNode(name);
}
#include <string>
#include "Errors.h"
#include <vector>
#include <list>
#include "LexicalAnalizer.h"
#include "Structure.h"

#pragma once
using namespace std;

struct P_model 
{
	Sunit* root;
	int x, y;
	P_model(Sunit* _root, int _x, int _y) : root(_root), x(_x), y(_y) {};
};


extern vector<lexeme_type> allowed_lexemes;
extern vector<P_model> MODEL_STACK;
extern Sbase* SYNTAX_MODEL;
extern Sbase* CURRENT_SSTATE;
extern vector<Lexeme> syntax_stack;

bool is_expected(lexeme_type lexeme);
bool lexeme_equal(lexeme_type l1, lexeme_type l2);
Sbase* move_to_next();
void init_syntax_analyzer();
Sbase* choose_next_way(lexeme_type lexeme, Sunit* current_workin_unit);
Sbase* check_branch(vector<Sbase*> branch, lexeme_type lexeme, int k = 0);
TypeTableNode* GetRvalType(vector<Lexeme*> r_val);
bool canBe educt(TypeTableNode* t1, TypeTableNode* t2);
TypeTableNode* isRecField(vector<Lexeme*> r_val);
vector<sError> get_syntax(string line, vector<Lexeme*> lexemes, int line_num);
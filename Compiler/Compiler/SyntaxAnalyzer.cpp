#include "SyntaxAnalyzer.h"

vector<lexeme_type> allowed_lexemes{ PROGRAM };
vector<P_model> MODEL_STACK;
Sbase* CURRENT_SSTATE;
bool initialised = false;
lexeme_type expected_lexeme = PROGRAM;
 
vector<Lexeme> syntax_stack;

enum SemantState { None, Var, VarDecl, Type, TypeDecl, TypeRec,Lval, Rval, RvalEnd, Assign};
SemantState semantState = None;
Ident* last_ident = nullptr;
TypeTableNode* assignType = nullptr;
vector<Lexeme*> r_val, l_val;
RecTableNode* recTypePtr = nullptr;

void init_syntax_analyzer()
{
	initialised = true;
	Sunit* SYNTAX_MODEL_ROOT = init_syntax_model();
	MODEL_STACK.push_back(P_model(SYNTAX_MODEL_ROOT,0,0));
	CURRENT_SSTATE = SYNTAX_MODEL_ROOT;
}

void error_neutralize(lexeme_type lexeme)
{
	int n = MODEL_STACK.size();
	for (int i = n - 1; i >= 0; i--)
	{
		P_model& p_model = MODEL_STACK[i];
		int x = p_model.x;
		int y = p_model.y;
		Sbase* last_node = p_model.root->sub[x][p_model.root->sub[x].size() - 1];
		
		if (last_node->getId() == "Sl" && lexeme == ((Sl*)last_node)->lexeme)
		{
			for (int j = n - 1; j > i; j--)
				MODEL_STACK.pop_back();
			return;
		}
	}
}

bool is_expected(lexeme_type lexeme)
{
	if (CURRENT_SSTATE==nullptr)
		return false;

	

	bool result = false;
	if(CURRENT_SSTATE->getId() == "Sl")
	{

		result = lexeme_equal(((Sl*)CURRENT_SSTATE)->lexeme, lexeme);
		if (result == true)
		{
			CURRENT_SSTATE = move_to_next();
			//semantic states
			if (lexeme == VAR)
				semantState = Var;
			if (lexeme == COLON && semantState == Var)
				semantState = VarDecl;
			if (lexeme == BEGIN)
				semantState = None;
			if (lexeme == TYPE || semantState == None && lexeme == END)
				semantState = Type;
			if (recTypePtr != nullptr && lexeme == END) 
			{
				recTypePtr = nullptr;
				semantState = Type;
			}
			if (lexeme == EQUAL && semantState == Type)
				semantState = TypeDecl;
			if (lexeme == RECORD && semantState == TypeDecl)
			{
				semantState = Var;
				recTypePtr = new RecTableNode();
			}
			if (lexeme == ASSIGN)
				semantState = Assign;
			if ((lexeme == SEMI || lexeme == END || lexeme == ELSE) && semantState == Rval)
				semantState = RvalEnd;
		}
		else
			error_neutralize(lexeme);
	}
	else if(CURRENT_SSTATE->getId() == "Sunit")
	{
		Sunit* CURRENT_SSTATE_SUnit = (Sunit*)CURRENT_SSTATE;
		Sbase* new_CURRENT_SSTATE = choose_next_way(lexeme, CURRENT_SSTATE_SUnit);
		if (new_CURRENT_SSTATE == nullptr)
			if (CURRENT_SSTATE_SUnit->optional)
				CURRENT_SSTATE = move_to_next();
			else
				return false;
		else
			CURRENT_SSTATE = new_CURRENT_SSTATE;

		result = is_expected(lexeme);
	}
	return result;
}

bool lexeme_equal(lexeme_type l1, lexeme_type l2)
{
	expected_lexeme = l1;
	return l1 == l2;
}

Sbase* move_to_next()
{
	P_model& p_model = MODEL_STACK[MODEL_STACK.size() - 1];
	Sunit* SYNTAX_MODEL_ROOT = p_model.root;
	int& x = p_model.x;
	int& y = p_model.y;
	int n = SYNTAX_MODEL_ROOT->sub[x].size();

	if (y < n-1)
	{
		return SYNTAX_MODEL_ROOT->sub[x][++y];
	}
	else
	{
		if (MODEL_STACK.size() > 0)
		{
			if (p_model.root->repeatable)
			{
				MODEL_STACK.pop_back();
				P_model& p_model = MODEL_STACK[MODEL_STACK.size() - 1];
				Sunit* SYNTAX_MODEL_ROOT = p_model.root;
				int x = p_model.x;
				int y = p_model.y;
				return SYNTAX_MODEL_ROOT->sub[x][y];
			}
			else
			{
				MODEL_STACK.pop_back();
				return move_to_next();
			}
		}
		else
		{
			return nullptr;
		}
	}
}

Sbase* choose_next_way(lexeme_type lexeme, Sunit* current_workin_unit)
{
	int n = current_workin_unit->sub.size();
	Sbase* new_CURRENT_STATE = nullptr;
	MODEL_STACK.push_back(P_model(current_workin_unit, 0, 0));

	P_model& p_model = MODEL_STACK[MODEL_STACK.size() - 1];
	Sunit* SYNTAX_MODEL_ROOT = p_model.root;
	int& x = p_model.x;
	int& y = p_model.y;

	int i = 0;
	for (; i < n && new_CURRENT_STATE==nullptr; i++)
	{
		if (current_workin_unit->sub[i].size() >0)
		{
			new_CURRENT_STATE = check_branch(current_workin_unit->sub[i], lexeme);
		}
	}
	x = i-1;

	if (new_CURRENT_STATE == nullptr)
		MODEL_STACK.pop_back();
		
	return new_CURRENT_STATE;
}

Sbase* check_branch(vector<Sbase*> branch, lexeme_type lexeme, int k)
{
	P_model& p_model = MODEL_STACK[MODEL_STACK.size() - 1];
	Sunit* SYNTAX_MODEL_ROOT = p_model.root;
	int& x = p_model.x;
	int& y = p_model.y;

	Sbase* new_CURRENT_STATE = nullptr;
	Sbase* first_Sbase = branch[k];
	if (first_Sbase->getId() == "Sl")
	{
		if (lexeme_equal(((Sl*)first_Sbase)->lexeme, lexeme))
		{
			new_CURRENT_STATE = first_Sbase;
		}
	}
	else if (first_Sbase->getId() == "Sunit")
	{
		Sunit* first_Sunit = (Sunit*)first_Sbase;
		new_CURRENT_STATE = choose_next_way(lexeme, first_Sunit);
		if (new_CURRENT_STATE == nullptr && first_Sunit->optional)
		{
			y=k+1;
			new_CURRENT_STATE = check_branch(branch, lexeme, k+1);
		}
	}
	return new_CURRENT_STATE;
}

vector<sError> get_syntax(string line, vector<Lexeme*> lexemes, int line_num=0)
{
	vector<sError> errors;
	if (!initialised)
	{
		cout << "Syntax analiser is not inicialised" << endl;
		return errors;
	}
	vector<Ident*> idents;
	for (Lexeme* lexeme : lexemes)
	{
		if (!is_expected(lexeme->type))
		{
			errors.push_back(sError(expected_lexeme, line_num, 0, line));
			if (semantState == Rval || semantState == Lval)
				semantState = None;
		}
		else
		{
			//semantic
			if (lexeme->type == IDENT && semantState != Var && semantState != VarDecl && semantState != Type && semantState != TypeDecl) last_ident = (Ident*)lexeme;
			if (semantState == None && lexeme->type == IDENT)
			{
				l_val.clear();
				semantState = Lval;

			}
			if (semantState == Lval)
			{
				l_val.push_back(lexeme);
				if (isRecField(l_val))
				{
					assignType = isRecField(l_val);
					r_val.clear();
				}
				else if (l_val.size() == 1 && l_val[0]->type==IDENT && identTable.find(((Ident*)l_val[0])->name) != identTable.end())
				{
					assignType = identTable[last_ident->name].type;
					r_val.clear();
				}
				else
				{
					//errors.push_back(sError(104, line_num, 0, line));
					assignType = nullptr;
					semantState = None;
				}
			}
			if (semantState == Rval)
			{
				r_val.push_back(lexeme);
			}
			if (semantState == Assign) 
			{
				if (assignType != nullptr)
					semantState = Rval;
				else
				{
					errors.push_back(sError(104, line_num, 0, line));
					semantState = None;
				}
				/*if (identTable.find(last_ident->name) != identTable.end())
				{
					assignType = identTable[last_ident->name].type;
					r_val.clear();
					semantState = Rval;
				}
				else
				{
					errors.push_back(sError(104, line_num, 0, line));
					semantState = None;
				}*/
			}
			if (semantState == RvalEnd)
			{
				TypeTableNode* rvalType = GetRvalType(r_val);
				if(rvalType == nullptr)
					errors.push_back(sError(328, line_num, 0, line));
				else if (rvalType->name != assignType->name) {
					if(!canBeÊeduct(rvalType, assignType))
						errors.push_back(sError(328, line_num, 0, line));
				}
				r_val.clear();
				semantState = None;
			}
			if (lexeme->type == IDENT && (semantState == Var || semantState == Type))
				idents.push_back((Ident*)lexeme);
			if (semantState == VarDecl && lexeme->type == IDENT)
			{
				if (recTypePtr == nullptr)
				{
					for (auto ident : idents)
					{
						if (typeTable.find(ident->name) != typeTable.end() || identTable.find(ident->name) != identTable.end())
							errors.push_back(sError(101, line_num, 0, line));
						else
							identTable[ident->name] = IdentTableNode(ident->name);
					}
					Ident* type = (Ident*)lexeme;
					if (typeTable.find(type->name) != typeTable.end())
					{
						TypeTableNode* typeNode = typeTable.find(type->name)->second;
						for (auto ident : idents)
						{
							if (identTable.find(ident->name) != identTable.end())
								identTable[ident->name].type = typeNode;
						}
					}
					else
						errors.push_back(sError(331, line_num, 0, line));
				}
				else//record
				{
					for (auto ident : idents)
					{
						if (recTypePtr->fields.find(ident->name) != recTypePtr->fields.end())
							errors.push_back(sError(101, line_num, 0, line));
						else
							recTypePtr->fields[ident->name] = IdentTableNode(ident->name);
					}
					Ident* type = (Ident*)lexeme;
					if (typeTable.find(type->name) != typeTable.end())
					{
						TypeTableNode* typeNode = typeTable.find(type->name)->second;
						for (auto ident : idents)
						{
							if (recTypePtr->fields.find(ident->name) != recTypePtr->fields.end())
								recTypePtr->fields[ident->name].type = typeNode;
						}
					}
					else
						errors.push_back(sError(331, line_num, 0, line));
				}
				semantState = Var;
			}
			if (semantState == TypeDecl && lexeme->type == IDENT)
			{
				for (auto ident : idents)
				{
					if (typeTable.find(ident->name) == typeTable.end())
						typeTable[ident->name] = new TypeTableNode(ident->name);
					else
						errors.push_back(sError(101, line_num, 0, line));
				}
			}
			if (lexeme->type == RECORD)
			{
				if (recTypePtr != nullptr)
					for (auto ident : idents)
					{
						if (typeTable.find(ident->name) == typeTable.end())
							typeTable[ident->name] = recTypePtr;
						else
							errors.push_back(sError(101, line_num, 0, line));
					}
			}
		}
	}
	return errors;
}


TypeTableNode* GetRvalType(vector<Lexeme*> r_val)
{
	if (r_val.size() == 0)
		return nullptr;
	if (r_val.size() == 1)
	{
		if(r_val[0]->type == INT_NUMBER)
			return typeTable["INTEGER"];
		if(r_val[0]->type == TRUE || r_val[0]->type == FALSE)
			return  typeTable["BOOLEAN"];
		if (r_val[0]->type == REAL_NUMBER)
			return typeTable["REAL"];
		if (r_val[0]->type == CHAR)
			return typeTable["CHAR"];
		if (r_val[0]->type == IDENT)
			if (identTable.find(((Ident*)r_val[0])->name) != identTable.end())
				return identTable[((Ident*)r_val[0])->name].type;
			else
				return nullptr;
	}
	else
	{
		TypeTableNode* recType = isRecField(r_val);
		if(recType != nullptr)
			return recType;
		vector<Lexeme*> l_part;
		vector<Lexeme*> r_part;
		bool fill_l_part = true;
		for (int i = 0; i < r_val.size(); i++)
		{
			if (r_val[i]->type == LBRACKET || r_val[i]->type == RBRACKET || r_val[i]->type == LPAR || r_val[i]->type == RPAR)
				continue;
			if (fill_l_part)
			{
				if (r_val[i]->type == PLUS || r_val[i]->type == MINUS || r_val[i]->type == MULT || r_val[i]->type == DIVISION)
					fill_l_part = false;
				else
					l_part.push_back(r_val[i]);
			}
			else
				r_part.push_back(r_val[i]);
		}
		if (r_part.size() == 0 && l_part.size() > 0 && isRecField(l_part) == nullptr)
			return nullptr;
		auto l_type = GetRvalType(l_part);
		auto r_type = GetRvalType(r_part);

		if (l_type == nullptr || r_type == nullptr)
			return nullptr;

		if (l_type->name == r_type->name)
			return l_type;

		else {
			if (l_type->name == "INTEGER" && r_type->name == "REAL")
				return r_type;
			if (r_type->name == "INTEGER" && l_type->name == "REAL")
				return l_type;
		}
		return nullptr;
	}
}

bool canBeÊeduct(TypeTableNode* t1, TypeTableNode* t2)
{
	if (t1 == nullptr || t2 == nullptr)
		return false;
	if (t1->name == "INTEGER" && t2->name == "REAL")
		return true;
	if (t2->name == "INTEGER" && t1->name == "REAL")
		return true;
	return false;
}

TypeTableNode* isRecField(vector<Lexeme*> r_val)
{
	TypeTableNode* last_Type = nullptr;
	map<string, IdentTableNode> _identTable = identTable;
	for (int i = 0; i < r_val.size(); i++)
	{
		if (r_val[i]->type != IDENT && r_val[i]->type != DOT)
			return nullptr;
		if (i % 2 == 0)//ident
		{
			if (r_val[i]->type != IDENT)
				return nullptr;
			Ident* id = (Ident*)r_val[i];
			if (_identTable.find(id->name) == _identTable.end())
				return nullptr;
			last_Type = _identTable[id->name].type;
			RecTableNode* a = dynamic_cast<RecTableNode *>(last_Type);
			if (a != nullptr)
				_identTable = ((RecTableNode*)last_Type)->fields;
			else
				if (i == r_val.size() - 1)
					return last_Type;
				else
					return nullptr;
		}
		else
			if (r_val[i]->type != DOT) return nullptr;
	}
	return last_Type;
}
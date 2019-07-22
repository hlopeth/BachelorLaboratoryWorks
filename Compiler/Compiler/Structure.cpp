#include "Structure.h"

Sunit* init_syntax_model()
{
	Sunit* _Sign = new Sunit({
		{new Sl(PLUS)},
		{new Sl(MINUS)} }, true);

	//constants
	Sunit* _Constant = new Sunit(vector<vector<Sbase*>> { {new Sl(INT_NUMBER) }, { _Sign, new Sl(INT_NUMBER) } });
	Sunit* _Const_defenition = new Sunit(vector<vector<Sbase*>> { {new Sl(IDENT), new Sl(EQUAL), _Constant, new Sl(SEMI)} }, true, true);
	Sunit* _Constant_definition_part = new Sunit(vector<vector<Sbase*>> { {new Sl(CONST), new Sl(IDENT), new Sl(EQUAL), _Constant, new Sl(SEMI), _Const_defenition} }, true);

	Sunit* _Relation_operator = new Sunit({
		{new Sl(EQUAL)},
		{new Sl(NOEQUAL)},
		{new Sl(LESS)},
		{new Sl(LESS_EQUAL)},
		{new Sl(GREATER)},
		{new Sl(GREATER_EQUAL)},
		{new Sl(IN)} });

	Sunit* _Multiplying_operator = new Sunit({
		{new Sl(MULT)},
		{new Sl(DIVISION)},
		{new Sl(DIV)},
		{new Sl(MOD)},
		{new Sl(AND)} });

	Sunit* _Adding_operator = new Sunit({
		{new Sl(PLUS)},
		{new Sl(MINUS)},
		{new Sl(OR)} });

	//expression
	Sunit* _Expression = new Sunit(vector<vector<Sbase*>>{});

	Sunit* _Element = new Sunit(vector<vector<Sbase*>>{ {_Expression}, });
	Sunit* _Comma_Element = new Sunit(vector<vector<Sbase*>>{ { new Sl(COMMA), _Element }}, true, true);
	Sunit* _Element_list = new Sunit(vector<vector<Sbase*>>{ {_Element, _Comma_Element} });
	Sunit* _Set = new Sunit(vector<vector<Sbase*>>{ { new Sl(LBRACKET), _Element_list, new Sl(RBRACKET) }}, true, true);
	Sunit* _Variable = new Sunit(vector<vector<Sbase*>> { { new Sl(DOT), new Sl(IDENT)}}, true, true);

	Sunit* _Factor = new Sunit(vector<vector<Sbase*>>{});
	_Factor->sub = { {new Sl(IDENT), _Variable}, {new Sl(INT_NUMBER)}, {new Sl(NOT), _Factor}, {new Sl(LPAR),_Expression, new Sl(RPAR)} };

	Sunit* _Term = new Sunit(vector<vector<Sbase*>>{});
	Sunit* _Mult_op_Term = new Sunit(vector<vector<Sbase*>>{ {_Multiplying_operator, _Term} }, true, true);
	_Term->sub = { {_Factor, _Mult_op_Term } };

	Sunit* _Simple_expression = new Sunit(vector<vector<Sbase*>>{});
	Sunit* _Add_op_Simple_expression = new Sunit(vector<vector<Sbase*>>{ {_Adding_operator, _Simple_expression}}, true, true);
	_Simple_expression->sub = { {_Term, _Add_op_Simple_expression} };
	Sunit* _Rel_Simple_expr = new Sunit({ {_Relation_operator, _Simple_expression} }, true);
	_Expression->sub = { {_Simple_expression, _Rel_Simple_expr} };

	//statement
	Sunit* _Statement = new Sunit(vector<vector<Sbase*>> {}, true, true);
	Sunit* _For_list = new Sunit(vector<vector<Sbase*>> { {new Sl(TO), _Expression}, { new Sl(DOWNTO), _Expression } });
	Sunit* _CaseLabel = new Sunit(vector<vector<Sbase*>> { {new Sl(COMMA), _Constant}}, true, true);
	Sunit* _CaseVariant = new Sunit(vector<vector<Sbase*>> { {_Constant, _CaseLabel, new Sl(COLON), _Statement}}, true, true);
	Sunit* _Else_Statement = new Sunit(vector<vector<Sbase*>> {}, true);
	_Statement->sub = {
	{new Sl(IDENT), _Variable, new Sl(ASSIGN), _Expression, new Sl(SEMI)},										//variable := expression;
	{new Sl(BEGIN), _Statement, new Sl(END)},																	//begin statement-list end
	{new Sl(IF), _Expression, new Sl(THEN), _Statement, _Else_Statement, new Sl(SEMI)},							//if expression then statement (else statement);
	{new Sl(WHILE), _Expression, new Sl(DO), _Statement},														//while expression do statement;
	{new Sl(REPEAT), _Statement, new Sl(UNTIL), _Expression, new Sl(SEMI)},										//repeat statement-list until expression;
	{new Sl(FOR), new Sl(IDENT), new Sl(EQUAL), _Expression, _For_list, new Sl(DO), _Statement },				//for varid := for-list do statement
	{new Sl(CASE), new Sl(IDENT), new Sl(OF), _CaseVariant },													//case A of 0: ...; 1: ...;
	{new Sl(WITH), new Sl(IDENT), new Sl(DO), _Statement}
	};
	_Else_Statement->sub = { {new Sl(ELSE), _Statement} };
	Sunit* _Label_declaration_part = new Sunit(vector<vector<Sbase*>> { {} }, true);
	Sunit* _Statement_part = new Sunit(vector<vector<Sbase*>> { {new Sl(BEGIN), _Statement, new Sl(END) } });


	//types
	Sunit* _Rec_names = new Sunit(vector<vector<Sbase*>> { {new Sl(COMMA), new Sl(IDENT)} }, true, true);
	Sunit* _Fixed_Part = new Sunit(vector<vector<Sbase*>> { {new Sl(IDENT), _Rec_names, new Sl(COLON), new Sl(IDENT), new Sl(SEMI) } }, true, true);
	Sunit* _Record_Fields = new Sunit(vector<vector<Sbase*>> { { _Fixed_Part } });
	Sunit* _Type = new Sunit(vector<vector<Sbase*>> { {new Sl(RECORD), _Record_Fields, new Sl(END)} });
	Sunit* _IdEqType = new Sunit(vector<vector<Sbase*>> { {new Sl(IDENT), new Sl(EQUAL), _Type, new Sl(SEMI)} }, true, true);
	Sunit* _Type_definition_part = new Sunit(vector<vector<Sbase*>> { {new Sl(TYPE), new Sl(IDENT), new Sl(EQUAL), _Type, new Sl(SEMI), _IdEqType} }, true);

	//variables
	Sunit* _VIdent = new Sunit(vector<vector<Sbase*>>{ {new Sl(COMMA), new Sl(IDENT)} }, true, true);
	Sunit* _Var_declaration = new Sunit(vector<vector<Sbase*>> { {new Sl(IDENT), _VIdent, new Sl(COLON), new Sl(IDENT), new Sl(SEMI)} }, true, true);
	Sunit* _Variable_declaration_part = new Sunit(vector<vector<Sbase*>> { {new Sl(VAR), _Var_declaration} }, true);

	//procedure
	Sunit* _Procedure_function_declaration_part = new Sunit(vector<vector<Sbase*>> { {} }, true);
	Sunit* _Block = new Sunit(vector<vector<Sbase*>> { { _Label_declaration_part, _Constant_definition_part, _Type_definition_part, _Variable_declaration_part,
		_Procedure_function_declaration_part, _Statement_part } });
	Sunit* _Program = new Sunit(vector<vector<Sbase*>> { { new Sl(PROGRAM), new Sl(IDENT), new Sl(SEMI), _Block, new Sl(DOT)} });

	Sunit* SYNTAX_MODEL = _Program;
	return SYNTAX_MODEL;
}
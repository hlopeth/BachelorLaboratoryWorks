#include "LexicalAnalizer.h"
using namespace std;

bool comment = false;

bool is_name(string s)
{
	regex rx("[A-Z][A-Z0-9]*");
	return regex_match(s.begin(), s.end(), rx);
}

bool is_int_number(string s)
{
	regex rx("[+-]?[0-9]+");
	return regex_match(s.begin(), s.end(), rx);
}

bool is_real_number(string s)
{
	regex rx("[+-]?[0-9]+\\.[0-9]*");
	return regex_match(s.begin(), s.end(), rx);
}

bool is_char(string s)
{
	regex rx("'.'");
	return regex_match(s.begin(), s.end(), rx);
}

int add_lexeme(string word, vector<Lexeme*>& lexemes)
{
		 if (word == "" || comment)			return 0;
	else if (word == "DO")					lexemes.push_back(new Lexeme(DO));
	else if (word == "IF")					lexemes.push_back(new Lexeme(IF));
	else if (word == "IN")					lexemes.push_back(new Lexeme(IN));
	else if (word == "OF")					lexemes.push_back(new Lexeme(OF));
	else if (word == "OR")					lexemes.push_back(new Lexeme(OR));
	else if (word == "TO")					lexemes.push_back(new Lexeme(TO));
	else if (word == "AND")					lexemes.push_back(new Lexeme(AND));
	else if (word == "DIV")					lexemes.push_back(new Lexeme(DIV));
	else if (word == "END")					lexemes.push_back(new Lexeme(END));
	else if (word == "FOR")					lexemes.push_back(new Lexeme(FOR));
	else if (word == "MOD")					lexemes.push_back(new Lexeme(MOD));
	else if (word == "NIL")					lexemes.push_back(new Lexeme(NIL));
	else if (word == "NOT")					lexemes.push_back(new Lexeme(NOT));
	else if (word == "SET")					lexemes.push_back(new Lexeme(SET));
	else if (word == "VAR")					lexemes.push_back(new Lexeme(VAR));
	else if (word == "CASE")				lexemes.push_back(new Lexeme(CASE));
	else if (word == "ELSE")				lexemes.push_back(new Lexeme(ELSE));
	else if (word == "FILE")				lexemes.push_back(new Lexeme(FILE_S));
	else if (word == "GOTO")				lexemes.push_back(new Lexeme(GOTO));
	else if (word == "ONLY")				lexemes.push_back(new Lexeme(ONLY));
	else if (word == "THEN")				lexemes.push_back(new Lexeme(THEN));
	else if (word == "TYPE")				lexemes.push_back(new Lexeme(TYPE));
	else if (word == "UNIT")				lexemes.push_back(new Lexeme(UNIT));
	else if (word == "USES")				lexemes.push_back(new Lexeme(USES));
	else if (word == "WITH")				lexemes.push_back(new Lexeme(WITH));
	else if (word == "ARRAY")				lexemes.push_back(new Lexeme(ARRAY));
	else if (word == "BEGIN")				lexemes.push_back(new Lexeme(BEGIN));
	else if (word == "CONST")				lexemes.push_back(new Lexeme(CONST));
	else if (word == "LABEL")				lexemes.push_back(new Lexeme(LABEL));
	else if (word == "UNTIL")				lexemes.push_back(new Lexeme(UNTIL));
	else if (word == "WHILE")				lexemes.push_back(new Lexeme(WHILE));
	else if (word == "EXPORT")				lexemes.push_back(new Lexeme(EXPORT));
	else if (word == "IMPORT")				lexemes.push_back(new Lexeme(IMPORT));
	else if (word == "DOWNTO")				lexemes.push_back(new Lexeme(DOWNTO));
	else if (word == "MODULE")				lexemes.push_back(new Lexeme(MODULE));
	else if (word == "PACKED")				lexemes.push_back(new Lexeme(PACKED));
	else if (word == "PROGRAM")				lexemes.push_back(new Lexeme(PROGRAM));
	else if (word == "RECORD")				lexemes.push_back(new Lexeme(RECORD));
	else if (word == "REPEAT")				lexemes.push_back(new Lexeme(REPEAT));
	else if (word == "VECTOR")				lexemes.push_back(new Lexeme(VECTOR));
	else if (word == "STRING")				lexemes.push_back(new Lexeme(STRING));
	else if (word == "FORWARD")				lexemes.push_back(new Lexeme(FORWARD));
	else if (word == "FUNCTION")			lexemes.push_back(new Lexeme(FUNCTION));
	else if (word == "SEPARATE")			lexemes.push_back(new Lexeme(SEPARATE));
	else if (word == "INTERFACE")			lexemes.push_back(new Lexeme(INTERFACE));
	else if (word == "QUALIFIED")			lexemes.push_back(new Lexeme(QUALIFIED));
	else if (word == "IMPLEMENTATION")		lexemes.push_back(new Lexeme(IMPLEMENTATION));
	else if (word == ":=")					lexemes.push_back(new Lexeme(ASSIGN));
	else if (word == ":")					lexemes.push_back(new Lexeme(COLON));
	else if (word == ";")					lexemes.push_back(new Lexeme(SEMI));
	else if (word == "+")					lexemes.push_back(new Lexeme(PLUS));
	else if (word == "-")					lexemes.push_back(new Lexeme(MINUS));
	else if (word == "*")					lexemes.push_back(new Lexeme(MULT));
	else if (word == "/")					lexemes.push_back(new Lexeme(DIVISION));
	else if (word == ",")					lexemes.push_back(new Lexeme(COMMA));
	else if (word == ".")					lexemes.push_back(new Lexeme(DOT));
	else if (word == "=")					lexemes.push_back(new Lexeme(EQUAL));
	else if (word == "(")					lexemes.push_back(new Lexeme(LPAR));
	else if (word == ")")					lexemes.push_back(new Lexeme(RPAR));
	else if (word == "[")					lexemes.push_back(new Lexeme(LBRACKET));
	else if (word == "]")					lexemes.push_back(new Lexeme(RBRACKET));
	else if (word == "{")					lexemes.push_back(new Lexeme(LFPAR));
	else if (word == "}")					lexemes.push_back(new Lexeme(RFPAR));
	else if (word == "<")					lexemes.push_back(new Lexeme(LESS));
	else if (word == ">")					lexemes.push_back(new Lexeme(GREATER));
	else if (word == "<=")					lexemes.push_back(new Lexeme(LESS_EQUAL));
	else if (word == ">=")					lexemes.push_back(new Lexeme(GREATER_EQUAL));
	else if (word == "<>")					lexemes.push_back(new Lexeme(NOEQUAL));
	else if (word == "TRUE")				lexemes.push_back(new Lexeme(TRUE));
	else if (word == "FALSE")				lexemes.push_back(new Lexeme(FALSE));
	else if (is_name(word))				    lexemes.push_back(new Ident(word));
	else if (is_int_number(word))			lexemes.push_back(new Int_Number(boost::lexical_cast<int>(word)));
	else if (is_real_number(word))			lexemes.push_back(new Real_Number(boost::lexical_cast<double>(word)));
	else if (is_char(word))					lexemes.push_back(new Char(word[1]));
	else
		return 6;
	return 0;
}

vector<sError> get_lexems(string line, vector<Lexeme*>& lexemes, int line_num = 0)
{
	int n = line.size();
	vector<sError> errors;
	string word = "";
	int error_code;
	boost::to_upper(line);

	for (int i = 0; i < n; i++)
	{
		char ch = line[i];
		error_code = 0;
		switch (ch)
		{
		case ' ':
		case '\t':
			error_code = add_lexeme(word, lexemes);
			word = "";
			break;
		case ':':
			error_code = add_lexeme(word, lexemes);
			if (i < n && line[i + 1] == '=')
			{
				add_lexeme(":=", lexemes);
				i++;
			}
			else
			{
				add_lexeme(":", lexemes);
			}
			word = "";
			break;
		case '.':
			if (!is_int_number(word)) 
			{
				error_code = add_lexeme(word, lexemes);
				add_lexeme(".", lexemes);
				word = "";
			}
			break;
		case ';':
			error_code = add_lexeme(word, lexemes);
			add_lexeme(";", lexemes);
			word = "";
			break;
		case '+':
			error_code = add_lexeme(word, lexemes);
			add_lexeme("+", lexemes);
			word = "";
			break;
		case '-':
			error_code = add_lexeme(word, lexemes);
			add_lexeme("-", lexemes);
			word = "";
			break;
		case '*':
			error_code = add_lexeme(word, lexemes);
			if (i < n && line[i + 1] == ')') 
			{
				i++;
				comment = false;
			}
			else
				add_lexeme("*", lexemes);
			word = "";
			break;
		case '/':
			error_code = add_lexeme(word, lexemes);
			if (i < n && line[i + 1] == '/')
				return errors;
			else
				add_lexeme("/", lexemes);
			word = "";
			break;
		case '=':
			error_code = add_lexeme(word, lexemes);
			add_lexeme("=", lexemes);
			word = "";
			break;
		case ',':
			error_code = add_lexeme(word, lexemes);
			add_lexeme(",", lexemes);
			word = "";
			break;
		case '<':
			error_code = add_lexeme(word, lexemes);
			if (i < n && line[i + 1] == '=')
			{
				add_lexeme("<=", lexemes);
				i++;
			}
			else if (i < n && line[i + 1] == '>')
			{
				add_lexeme("<>", lexemes);
				i++;
			}
			else
				add_lexeme("<", lexemes);
			word = "";
			break;
		case '>':
			error_code = add_lexeme(word, lexemes);
			if (i < n && line[i + 1] == '=')
			{
				add_lexeme(">=", lexemes);
				i++;
			}
			else
				add_lexeme(">", lexemes);
			word = "";
			break;
		case '(':
			error_code = add_lexeme(word, lexemes);
			if (i < n && line[i + 1] == '*')
				comment = true;
			else
				add_lexeme("(", lexemes);
			word = "";
			break;
		case ')':
			error_code = add_lexeme(word, lexemes);
			add_lexeme(")", lexemes);
			word = "";
			break;
		case '[':
			error_code = add_lexeme(word, lexemes);
			add_lexeme("[", lexemes);
			word = "";
			break;
		case ']':
			error_code = add_lexeme(word, lexemes);
			add_lexeme("]", lexemes);
			word = "";
			break;
		case '{':
			error_code = add_lexeme(word, lexemes);
			add_lexeme("{", lexemes);
			word = "";
			break;
		case '}':
			error_code = add_lexeme(word, lexemes);
			add_lexeme("}", lexemes);
			word = "";
			break;
		default:
			word += ch;
			break;
		}
		if (error_code != 0)
			errors.push_back(sError(error_code, line_num, i, line));
	}
	error_code = add_lexeme(word, lexemes);
	if (error_code != 0)
		errors.push_back(sError(error_code, line_num, n, line));

	return errors;
}

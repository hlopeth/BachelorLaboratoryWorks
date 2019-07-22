#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "Errors.h"
#include "LexicalAnalizer.h"
#include "SyntaxAnalyzer.h"
#include "IdentTypeTables.h"

using namespace std;

extern map<int, string> mErrors;

void initTypeTable();

std::ostream &operator<<(std::ostream &os, Lexeme const &m) {
	return os << m.type;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream source_file;
	source_file.open("input3.txt");
	ifstream errors_file;
	errors_file.open("Err.msg");
	init_syntax_analyzer();

	mErrors = load_errors(errors_file);
	int line_num=0;

	initTypeTable();

	while (!source_file.eof())
	{
		string line;
		vector<Lexeme*> lexemes;
		getline(source_file, line);
		vector<sError> lexecal_errors = get_lexems(line, lexemes, line_num + 1);
		vector<sError> syntax_errors  = get_syntax(line, lexemes, line_num + 1);
		cout << line << endl;
		for (auto error : lexecal_errors)
			print_error(error);

		for (auto error : syntax_errors)
			print_error(error);

		line_num++;
	}

	/*ofstream lexical_out_file;
	lexical_out_file.open("lexical_output.txt");

	for (auto lexeme : lexemes)
	{
		lexical_out_file << lexeme << " ";
	}
	lexical_out_file.close();*/

	source_file.close();
	errors_file.close();
	cin.get();
	return 0;
}

void initTypeTable()
{
	typeTable["INTEGER"] = new TypeTableNode("INTEGER");
	typeTable["REAL"] = new TypeTableNode("REAL");
	typeTable["CHAR"] = new TypeTableNode("CHAR");
	typeTable["BOOLEAN"] = new TypeTableNode("BOOLEAN");
}
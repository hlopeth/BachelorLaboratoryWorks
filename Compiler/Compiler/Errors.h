#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

struct sError
{
	int error_code;
	int line_num;
	int simbol_num;
	std::string line;
	sError(int _error_code, int _line_num, int _simbol_num, std::string _line)
	{
		error_code = _error_code;
		line_num = _line_num;
		simbol_num = _simbol_num;
		line = _line;
	}
};

extern std::map<int, std::string> mErrors;

std::map<int,  std::string> load_errors(std::ifstream &);
void print_error(sError error);
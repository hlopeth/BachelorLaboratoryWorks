#include "Errors.h"

using namespace std;

std::map<int, std::string> mErrors;

map<int, string> load_errors(ifstream & errors_stream)
{
	map<int, string> _mErrors;
	string line;
	while (!errors_stream.eof())
	{
		std::getline(errors_stream, line);
		std::vector<std::string> results;
		boost::split(results, line, [](char c) {return c == ':'; });

		int num = boost::lexical_cast<int>(results[0]);
		string descr = results[1];
		_mErrors[num] = descr;
	}
	return _mErrors;
}

void print_error(sError error)
{
	cout << "Error " << error.error_code << " at (" << error.line_num << ":" << error.simbol_num << ")" << endl;
	cout << mErrors[error.error_code] << endl;	
}

#include <string>
#include <vector>
using namespace std;

class Words
{

	vector<string> lines;                     // Vector with lines
	int            numberoflines;             // Number of lines in array

public:

	int  readfile (std::string inputfile  );  // Readsfile, returns number of lines
	int  writefile(std::string outputfile );  // Writes file, returns number of lines

	void reorganize(); 				          // Reorganizes words 
	
};
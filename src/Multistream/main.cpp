#include <iostream>
#include <fstream>

#include "Multistream.h"

using namespace std;
using namespace Tyleo;

int main()
{
    auto outputFilestream = ofstream{ "OutputFile.txt" };
    // auto errorFilestream = ofstream{ "ErrorFile.txt" };

    auto outputMultistream = MakeMultistream(cout, outputFilestream, cout);
    //auto errorMultistream = MakeMultistream(cout, errorFilestream);

    cout << std::endl;
    //errorFilestream << std::endl;
    outputMultistream << "Hello" << std::endl;
    outputMultistream << "Hello World!" << std::endl;
    //errorMultistream << "Error!" << "\n";

}

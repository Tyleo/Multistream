#include <iostream>
#include <fstream>

#include "Multistream.h"

using namespace std;
using namespace Tyleo;

int main()
{
    ofstream fileStream = ofstream{ "Output.txt" };

    auto multistream = MakeMultistream(cout, fileStream);
    multistream << "Hello World!";
}

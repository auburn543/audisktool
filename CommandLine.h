//
//  Ryan English
//  CommandLine.h
//

#ifndef CommandLine_h
#define CommandLine_h

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
typedef unsigned int uint_t;

struct Command {
    string type;
    string flag;
    string value;
};

/* CommandLine Class */
class CommandLine {
private:
    
public:
    uint_t getCommand(Command&);
};

#endif /* CommandLine_h */

//
//  Ryan English
//  CommandLine.cpp
//

#include "CommandLine.h"

/* Returns size of the commandline */
uint_t CommandLine::getCommand(Command& cmd) {
    string cmdline;
    int position;
    
    do {
        cout << "\n>";
        getline(cin, cmdline);
    } while (cmdline.compare("") == 0);
    
    position = (int) cmdline.find(" ");
    cmd.type = cmdline.substr(0, position);
    
    cmdline = cmdline.substr(position+1);
    
    if (cmdline != cmd.type) {
        position = (int) cmdline.find(" ");
        cmd.flag = cmdline.substr(0, position);
        cmdline = cmdline.substr(position+1);
        if (cmdline != cmd.flag) { //cmdline has a value
            cmd.value = cmdline;
            return 3;
        }
        else { //cmdline doesn't have a value
            cmd.value.clear();
            return 2;
        }
    }
    else { //cmdline has no flag or value
        cmd.flag.clear();
        cmd.value.clear();
        return 1;
    }
}
//
//  Ryan English
//  main.cpp
//

#include "auDiskTool.h"
using namespace DiskTool;

/* main function */
int main() {
    CommandLine cmdline;
    auDiskTool tool;
    Command cmd;
    int cmd_length, cont;
    
    cout << "auDiskTool version 1.0.0. Type 'help' to see a list of valid commands." << endl;
    do {
        cmd_length = cmdline.getCommand(cmd);
        cont = tool.processCommand(cmd, cmd_length);
        if (cont == 2) cout << "Invalid command!" << endl;
    } while (cont != 0);
    
    return 0;
}

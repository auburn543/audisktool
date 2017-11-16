//
//  Ryan English
//  auDiskTool.h
//

#ifndef auDiskTool_h
#define auDiskTool_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "CommandLine.h"
#include "Configuration.h"
#include "Report.h"
using namespace std;
typedef unsigned int uint_t;

enum cmd_t {HELP, RUN, SET, PRINT, SAVE, EXIT, NO_CMD};
enum flag_t {INTERVAL, COUNT, REPORT, BLK_READ, BLK_READ_S, KB_READ_S, BLK_WRITE, BLK_WRITE_S, KB_WRITE, CONF, NO_FLAG};

namespace DiskTool {
    /* auDiskTool Class */
    class auDiskTool : public CommandLine, public Configuration, public Report {
    private:
        Configuration config;
        Report report;
        bool conf_changed;
        cmd_t StrToCmd(string const& cmd_s);
        flag_t StrToFlag(string const& cmd_s);
    public:
        auDiskTool();
        uint_t processCommand(Command cmd, uint_t length);
        void help();
        void run(Command cmd);
        uint_t set(Command cmd);
        void print(Command cmd);
        void save(Command cmd);
    };
}

#endif /* auDiskTool_h */

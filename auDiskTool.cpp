//
//  Ryan English
//  auDiskTool.cpp
//

#include "auDiskTool.h"
using namespace DiskTool;

auDiskTool::auDiskTool() {
    config.loadConfiguration();
    conf_changed = false;
}

uint_t auDiskTool::processCommand(Command cmd, uint_t length) {
    cmd_t command_type;
    command_type = StrToCmd(cmd.type);
    
    if (command_type == HELP) help();
    else if (command_type == RUN) run(cmd);
    else if (command_type == SET) set(cmd);
    else if (command_type == PRINT) print(cmd);
    else if (command_type == SAVE) save(cmd);
    else if (command_type == EXIT) {
        if (conf_changed) config.saveConfiguration();
        return 0;
    }
    else if (command_type == NO_CMD) return 2;
    else return 2;
    return 1;
}

cmd_t auDiskTool::StrToCmd(string const& cmd_s) {
    if (cmd_s == "help") return HELP;
    if (cmd_s == "run") return RUN;
    if (cmd_s == "set") return SET;
    if (cmd_s == "print") return PRINT;
    if (cmd_s == "save") return SAVE;
    if (cmd_s == "exit") return EXIT;
    else return NO_CMD;
}

flag_t auDiskTool::StrToFlag(string const& cmd_s) {
    if (cmd_s == "interval") return INTERVAL;
    if (cmd_s == "count") return COUNT;
    if (cmd_s == "report") return REPORT;
    if (cmd_s == "blk_read") return BLK_READ;
    if (cmd_s == "blk_read/s") return BLK_READ_S;
    if (cmd_s == "kb_read/s") return KB_READ_S;
    if (cmd_s == "blk_write") return BLK_WRITE;
    if (cmd_s == "blk_write/s") return BLK_WRITE_S;
    if (cmd_s == "kb_write") return KB_WRITE;
    if (cmd_s == "conf") return CONF;
    else return NO_FLAG;
}

void auDiskTool::help() {
    cout << "run - run the monitoring tool" << endl;
    cout << "set interval [value] - set sampling period to [value]" << endl;
    cout << "set count [value] - set the number of records to [value]" << endl;
    cout << "set report [name] - set report file name to [name]" << endl;
    cout << "set blk_read\t[0|1] - set print_blk_read to 0 or 1" << endl;
    cout << "set blk_read/s\t[0|1] – set print_blk_read/s to 0 or 1" << endl;
    cout << "set kb_read/s\t[0|1] – set print_kb_read/s to 0 or 1" << endl;
    cout << "set blk_write\t[0|1] – set print_blk_write to 0 or 1" << endl;
    cout << "set blk_write/s\t[0|1] – set print_blk_write/s to 0 or 1" << endl;
    cout << "set kb_write\t[0|1] – set print_kb_write to 0 or 1" << endl;
    cout << "print conf - display all the parameters" << endl;
    cout << "print report - open and display the report file" << endl;
    cout << "save - the configuration file \"audisktool.conf\" is updated" << endl;
    cout << "exit - exit the tool" << endl;
}

void auDiskTool::run(Command cmd) {
    config.printConf();
    cout << "Please wait..." << endl;
    
    //Get data from /proc/diskstat
    ifstream in_stream;
    vector<string> data, sda;
    string line;
    in_stream.open("/proc/diskstats");
    if (!in_stream.is_open()) cout << "Oops, something went wrong - DiskStat file not found." << endl;
    else {
        for (uint_t i = 0; i < config.getCount(); i++) {
            while (!in_stream.eof()) {
                getline(in_stream, line);
                data.push_back(line);
            }
            for (uint_t i = 0; i < data.size(); i++) {
                int pos = (int) data[i].find("sda");
                if (pos > 0) {
                    sda.push_back(data[i]);
                }
            }
            report.processReport(sda);
            if (!report.saveReport(config.getBlkRead(), config.getBlkReadS(), config.getKbReadS(), config.getBlkWrite(), config.getBlkWriteS(), config.getKbWriteS()))
                cout << "Error - the file \"" << report.getFileName() << "\" could not be updated." << endl;
            else
                usleep(config.getInterval() * 1000000); //waits according to interval until next report sequence
        }
        cout << "The file \"" << report.getFileName() << "\" was just updated." << endl;
    }
}

uint_t auDiskTool::set(Command cmd) {
    flag_t flag_type;
    uint_t val;
    if (cmd.flag == "") return 1;
    else {
        flag_type = StrToFlag(cmd.flag);
        if (flag_type == INTERVAL) {
            if (cmd.value == "") return 2;
            val = atoi(cmd.value.c_str());
	    if (val == config.getInterval()) cout << "The interval was already " << val << ". The configuration will not be changed." << endl;
	    else if (val > 60) cout << "The interval cannot be greater than 60. The configuration will not be changed." << endl;
	    else {
                config.setInterval(val);
                cout << "Interval was updated to " << val << endl;
		conf_changed = true;
            }
	    return 0;
        }
        if (flag_type == COUNT) {
            if (cmd.value == "") return 2;
            val = atoi(cmd.value.c_str());
	    if (val == config.getCount()) cout << "The count was already " << val << ". The configuration will not be changed." << endl;
	    else if (val > 50) cout << "The count cannot be greater than 50. The configuration will not be changed." << endl;
	    else {
            	config.setCount(val);
            	cout << "Count was updated to " << val << endl;
		conf_changed = true;
            }
	    return 0;
        }
        if (flag_type == BLK_READ) {
            if (cmd.value == "") return 2;
            val = atoi(cmd.value.c_str());
            if (val > 1) return 3;
	    if (val == config.getBlkRead()) cout << "blk_read was already set to " << val << ". The configuration will not be changed." << endl;
	    else {
            	config.setBlkRead(val);
            	cout << "blk_read has been updated to " << val << endl;
		conf_changed = true;
            }
	    return 0;
        }
        if (flag_type == BLK_READ_S) {
            if (cmd.value == "") return 2;
            val = atoi(cmd.value.c_str());
            if (val > 1) return 3;
            if (val == config.getBlkReadS()) cout << "blk_read/s was already set to " << val << ". The configuration will not be changed." << endl;
	    else {
		config.setBlkReadS(val);
            	cout << "blk_read/s has been updated to " << val << endl;
		conf_changed = true;
            }
	    return 0;
        }
        if (flag_type == KB_READ_S) {
            if (cmd.value == "") return 2;
            val = atoi(cmd.value.c_str());
            if (val > 1) return 3;
            if (val == config.getKbReadS()) cout << "kb_read/s was already set to " << val << ". The configuration will not be changed." << endl;
	    else {
		config.setKbReadS(val);
            	cout << "kb_read/s has been updated to " << val << endl;
		conf_changed = true;
            }
	    return 0;
        }
        if (flag_type == BLK_WRITE) {
            if (cmd.value == "") return 2;
            val = atoi(cmd.value.c_str());
            if (val > 1) return 3;
            if (val == config.getBlkWrite()) cout << "blk_write was already set to " << val << ". The configuration will not be changed." << endl;
	    else {
		config.setBlkWriteS(val);
            	cout << "blk_write has been updated to " << val << endl;
		conf_changed = true;
            }
	    return 0;
        }
        if (flag_type == BLK_WRITE_S) {
            if (cmd.value == "") return 2;
            val = atoi(cmd.value.c_str());
            if (val > 1) return 3;
	    if (val == config.getBlkWriteS()) cout << "blk_write/s was already set to " << val << ". The configuration will not be changed." << endl;
	    else {
            	config.setBlkWriteS(val);
            	cout << "blk_write/s has been updated to " << val << endl;
		conf_changed = true;
            }
	    return 0;
        }
        if (flag_type == KB_WRITE) {
            if (cmd.value == "") return 2;
            val = atoi(cmd.value.c_str());
            if (val > 1) return 3;
            if (val == config.getKbWriteS()) cout << "kb_write/s was alread set to " << val << ". The Congifuration will not be changed." << endl;
	    else {
		config.setKbWriteS(val);
            	cout << "kb_write/s has been updated to " << val << endl;
		conf_changed = true;
            }
	    return 0;
        }
        if (flag_type == REPORT) {
            if (cmd.value == "") return 2;
            report.setRecordFileName(cmd.value);
            conf_changed = true;
        }
        return true;
    }
}

void auDiskTool::print(Command cmd) {
    flag_t flag_type;
    if (cmd.flag == "")
        cout << "Invalid command! Please specify what you want to print." << endl;
    else {
        flag_type = StrToFlag(cmd.flag);
        if (flag_type == CONF) {
	    config.printConf();
            cout << "Report name = " << report.getFileName() << endl;
        }
        else if (flag_type == REPORT) {
            if (report.loadReport()) report.printReport();
            else cout << "The file \"" << report.getFileName() << "\" could not be found." << endl;
        }
        else cout << "Invalid command! You may only print 'conf' or 'report'" << endl;
    }
}

void auDiskTool::save(Command cmd) {
    if (!conf_changed) {
        cout << "audisktool.conf has not been updated, so there is no need to save the file." << endl;
    }
    else {
        if (config.saveConfiguration()) {
            cout << "The file \"audisktool.conf\" has been updated and saved." << endl;
            conf_changed = false; //resets the configuration changed flag to "no changes"
        }
        else cout << "Something went wrong and the file was not saved." << endl;
    }
}

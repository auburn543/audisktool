//
//  Ryan English
//  Report.h
//

#ifndef Report_h
#define Report_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <iomanip>
using namespace std;
typedef unsigned int uint_t;

/* Record Structure */
struct Record {
    string deviceName;
    double blk_read;
    double blk_read_s;
    double kb_read_s;
    double blk_write;
    double blk_write_s;
    double kb_write_s;
};

/* Report Class */
class Report {
private:
    vector<Record> record_list;
    string filename_;
public:
    Report();
    void addRecord(Record newRecord);
    bool loadReport();
    bool saveReport(bool, bool, bool, bool, bool, bool);
    void printReport();
    void processReport(vector<string>);
    void setRecordFileName(string filename) {filename_ = filename;}
    string getFileName() {return filename_;}
};

#endif /* Report_h */

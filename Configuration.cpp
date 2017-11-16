//
//  Ryan English
//  Configuration.cpp
//

#include "Configuration.h"

void Configuration::loadConfiguration() {
    ifstream in_stream;
    uint_t blkr, blkrs, kbrs, blkw, blkws, kbws;
    in_stream.open("audisktool.conf");
    if (!in_stream.is_open()) { //Assumes no configuration file exists - creates default conf file
        interval = 1;
        count = 3;
        blk_read = true;
        blk_read_s = true;
        kb_read_s = true;
        blk_write = true;
        blk_write_s = true;
        kb_write_s = true;
        report = "report.adt";
        saveConfiguration();
    }
    else {
        in_stream >> interval;
        in_stream >> count;
        in_stream >> blkr;
        setBlkRead(blkr);
        in_stream >> blkrs;
        setBlkReadS(blkrs);
        in_stream >> kbrs;
        setKbReadS(kbrs);
        in_stream >> blkw;
        setBlkWrite(blkw);
        in_stream >> blkws;
        setBlkWriteS(blkws);
        in_stream >> kbws;
        setKbWriteS(kbws);
        in_stream.close();
    }
}

bool Configuration::saveConfiguration() {
    remove("audisktool.conf");
    ofstream newfile("audisktool.conf", ios::ios_base::app);
    if (!newfile.is_open()) return false;
    newfile << interval << " ";
    newfile << count << " ";
    newfile << blk_read << " ";
    newfile << blk_read_s << " ";
    newfile << kb_read_s << " ";
    newfile << blk_write << " ";
    newfile << blk_write_s << " ";
    newfile << kb_write_s << " ";
    newfile.close();
    return true;
}

void Configuration::printConf() {
    cout << "Monitoring Time = " << interval << " seconds" << endl;
    cout << "Number of Records = " << count << endl;
    cout << "print_blk_read = " << blk_read << endl;
    cout << "print_blk_read/s = " << blk_read_s << endl;
    cout << "print_kb_read/s = " << kb_read_s << endl;
    cout << "print_blk_write = " << blk_write << endl;
    cout << "print_blk_write/s = " << blk_write_s << endl;
    cout << "print_kb_write/s = " << kb_write_s << endl;
}

void Configuration::setBlkRead(uint_t value) {
    if (value == 1) blk_read = true;
    else blk_read = false;
}

void Configuration::setBlkReadS(uint_t value) {
    if (value == 1) blk_read_s = true;
    else blk_read_s = false;
}

void Configuration::setKbReadS(uint_t value) {
    if (value == 1) kb_read_s = true;
    else kb_read_s = false;
}

void Configuration::setBlkWrite(uint_t value) {
    if (value == 1) blk_write = true;
    else blk_write = false;
}

void Configuration::setBlkWriteS(uint_t value) {
    if (value == 1) blk_write_s = true;
    else blk_write_s = false;
}

void Configuration::setKbWriteS(uint_t value) {
    if (value == 1) kb_write_s = true;
    else kb_write_s = false;
}

//
//  Ryan English
//  Configuration.h
//

#ifndef Configuration_h
#define Configuration_h

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
typedef unsigned int uint_t;

/* Configuration Class */
class Configuration {
private:
    uint_t interval;
    uint_t count;
    bool blk_read;
    bool blk_read_s;
    bool kb_read_s;
    bool blk_write;
    bool blk_write_s;
    bool kb_write_s;
    string report;
public:
    void loadConfiguration();
    bool saveConfiguration();
    void setInterval(uint_t value) {interval = value;}
    uint_t getInterval() {return interval;}
    void setCount(uint_t value) {count = value;}
    uint_t getCount() {return count;}
    void setBlkRead(uint_t value);
    bool getBlkRead() {return blk_read;}
    void setBlkReadS(uint_t value);
    bool getBlkReadS() {return blk_read_s;}
    void setKbReadS(uint_t value);
    bool getKbReadS() {return kb_read_s;}
    void setBlkWrite(uint_t value);
    bool getBlkWrite() {return blk_write;}
    void setBlkWriteS(uint_t value);
    bool getBlkWriteS() {return blk_write_s;}
    void setKbWriteS(uint_t value);
    bool getKbWriteS() {return kb_write_s;}
    void printConf();
};

#endif /* Configuration_h */

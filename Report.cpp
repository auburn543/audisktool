//
//  Ryan English
//  Report.cpp
//

#include "Report.h"

Report::Report() {
    filename_ = "report.adt";
}

void Report::addRecord(Record newRecord) {
    record_list.push_back(newRecord);
}

bool Report::loadReport() {
    ifstream in_stream;
    Record newRecord;
    string devname;
    double blkr, blkrs, kbrs, blkw, blkws, kbws;
    
    in_stream.open(filename_.c_str());
    if (!in_stream.is_open()) return false;
    while (in_stream >> devname >> blkr >> blkrs >> kbrs >> blkw >> blkws >> kbws) {
        newRecord.deviceName = devname;
        newRecord.blk_read = blkr;
        newRecord.blk_read_s = blkrs;
        newRecord.kb_read_s = kbrs;
        newRecord.blk_write = blkw;
        newRecord.blk_write_s = blkws;
        newRecord.kb_write_s = kbws;
        record_list.push_back(newRecord);
    }
    in_stream.close();
    return true;
}

bool Report::saveReport(bool blkr, bool blkrs, bool kbrs, bool blkw, bool blkws, bool kbws) {
    Record newRecord;
    remove(filename_.c_str());
    ofstream newfile(filename_.c_str(), ios::ios_base::app);
    if (!newfile.is_open()) return false;
    if (record_list.empty()) return false;
    for (uint_t i = 0; i < record_list.size(); i++) {
        newRecord = record_list[i];
        newfile << newRecord.deviceName << " ";
        if (blkr) newfile << newRecord.blk_read << " ";
        else newfile << "0 ";
        if (blkrs) newfile << newRecord.blk_read_s << " ";
        else newfile << "0 ";
        if (kbrs) newfile << newRecord.kb_read_s << " ";
        else newfile << "0 ";
        if (blkw) newfile << newRecord.blk_write << " ";
        else newfile << "0 ";
        if (blkws) newfile << newRecord.blk_write_s << " ";
        else newfile << "0 ";
        if (kbws) newfile << newRecord.kb_write_s << endl;
        else newfile << "0 " << endl;
    }
    newfile.close();
    return true;
}

void Report::printReport() {
    Record record;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);
    if (record_list.empty()) cout << "No records were found. Run the tool to create a report." << endl;
    else {
        cout << record_list.size() << " records found in '" << filename_ << "'" << endl;
        cout << left << setw(10) << "Device";
        cout << left << setw(10) << "blk_read\t";
        cout << left << setw(10) << "blk_read/s\t";
        cout << left << setw(10) << "kb_read/s\t";
        cout << left << setw(10) << "blk_write\t";
        cout << left << setw(10) << "blk_write/s\t";
        cout << left << setw(10) << "kb_write/s" << endl;
        for (uint_t i = 0; i < record_list.size(); i++) {
            record = record_list[i];
            cout << left << setw(10) << record.deviceName;
            if (record.blk_read == 0) cout << "N/A\t";
            else cout << left << setw(10) << record.blk_read << "\t";
            if (record.blk_read_s == 0) cout << "N/A\t";
            else cout << left << setw(10) << record.blk_read_s << "\t";
            if (record.kb_read_s == 0) cout << "N/A\t";
            else cout << left << setw(10) << record.kb_read_s << "\t";
            if (record.blk_write == 0) cout << "N/A\t";
            else cout << left << setw(10) << record.blk_write << "\t";
            if (record.blk_write_s == 0) cout << "N/A\t";
            else cout << left << setw(10) << record.blk_write_s << "\t";
            if (record.kb_write_s == 0) cout << "N/A\t";
            else cout << left << setw(10) << record.kb_write_s << endl;
        }
    }
}

void Report::processReport(vector<string> data) {
    Record newRecord;
    stringstream ss;
    string deviceName;
    uint_t majDevice, minDevice, totalNumReads, readsMerged, sectorsRead, readTime, totalNumWrites, writesMerged, sectorsWritten, writeTime, numIO, ioTime, ioTimeWeighted;
    for (uint_t i = 0; i < data.size(); i++) {
        ss << data[i];
        ss >> majDevice >> minDevice >> deviceName >> totalNumReads >> readsMerged >> sectorsRead >> readTime >> totalNumWrites >> writesMerged >> sectorsWritten >> writeTime >> numIO >> ioTime >> ioTimeWeighted;
        newRecord.deviceName = deviceName;
        newRecord.blk_read = totalNumReads;
        newRecord.blk_read_s = totalNumReads / (readTime / 1000);
        newRecord.kb_read_s = sectorsRead / (readTime / 1000);
        newRecord.blk_write = totalNumWrites;
        newRecord.blk_write_s = totalNumWrites / (writeTime / 1000);
        newRecord.kb_write_s = sectorsWritten / (writeTime / 1000);
        addRecord(newRecord);
        ss.clear();
    }
}

#ifndef __CSV_PARSER_H__
#define __CSV_PARSER_H__

#include "globals.h"

const char CSV_SEPARATOR_CHAR = ',';




class CsvParser {
public:
    CsvParser();
    ~CsvParser();

public:
    bool LoadCsvFile(const string& filepath);

    bool CreateNewCsvFile(const string& filepath, const string& commSymbol, unsigned int width, unsigned int height);

    unsigned int GetWidth()
    {
        if (csvSymbolMatrix.empty()) {
            return 0;
        }

        return csvSymbolMatrix[0].size();
    }

    unsigned int GetHeight() { return csvSymbolMatrix.size(); }

public:

    vector<vector<string> > csvSymbolMatrix;
    string csvContent;

};


#endif

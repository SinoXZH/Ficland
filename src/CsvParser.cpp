#include "CsvParser.h"

CsvParser::CsvParser()
{

}

CsvParser::~CsvParser()
{

}

bool CsvParser::LoadCsvFile(const string& filepath)
{
    string info;

    ifstream ifs;
    ifs.open(filepath.c_str(), ios_base::in);
    if (!ifs.is_open()) {
        FormatString(info, "Load file failed: %s", filepath.c_str());
        PrintErr(info);
        return false;
    }

    csvSymbolMatrix.clear();

    unsigned int lineIndex = 0;

    string line;
    while (!ifs.eof()) {
        ifs >> line;
        csvContent += line;
        csvContent += '\n';

        while (!line.empty()) {
            string::size_type pos = line.find_first_of(CSV_SEPARATOR_CHAR);
            if (pos == string::npos) {
                break;
            }
            string curSymbol = line.substr(0, pos);
            if (lineIndex >= csvSymbolMatrix.size()) {
                vector<string> vec;
                csvSymbolMatrix.push_back(vec);
            }
            csvSymbolMatrix[lineIndex].push_back(curSymbol);
            line = line.substr(pos + 1);
        }

        ++lineIndex;
    }
    ifs.close();

    return true;
}

bool CsvParser::CreateNewCsvFile(const string& filepath, const string& commSymbol, unsigned int width, unsigned int height)
{
    ofstream ofs;
    ofs.open(filepath.c_str(), ios_base::out);
    if (!ofs.is_open()) {
        return false;
    }

    for (unsigned int h = 0; h < height; ++h) {
        for (unsigned int w = 0; w < width; ++w) {
            if (h >= csvSymbolMatrix.size()) {
                vector<string> vec;
                csvSymbolMatrix.push_back(vec);
            }
            csvSymbolMatrix[h].push_back(commSymbol);
            csvContent += commSymbol;
            csvContent += CSV_SEPARATOR_CHAR;
        }
        csvContent += '\n';
    }

    ofs << csvContent;

    ofs.close();

    return true;
}

#ifndef STATS_H
#define STATS_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include "read.h"

using namespace std;

class Stats{
public:
    // this @guessedCycles parameter should be calculated using the first several records
    Stats(int guessedCycles, int bufferMargin = 1000);
    ~Stats();
    int getCycles();
    long getReads();
    long getBases();
    long getQ20();
    long getQ30();
    // by default the qualified qual score is Q20 ('5')
    void statRead(Read* r, int& lowQualNum, int& nBaseNum, char qualifiedQual = '5');

    static Stats* merge(vector<Stats*>& list);
    void print();
    void summarize();
    // a port of JSON report
    void reportJson(ofstream& ofs, string padding);
    // a port of HTML report
    void reportHtml(ofstream& ofs, string filteringType, string readName);
    void reportHtmlQuality(ofstream& ofs, string filteringType, string readName);
    void reportHtmlContents(ofstream& ofs, string filteringType, string readName);

public:
    static string list2string(double* list, int size);
    static string list2string(long* list, int size);

private:
    long mReads;
    /* 
    why we use 8 here?
    map A/T/C/G/N to 0~7 by their ASCII % 8:
    'A' % 8 = 1
    'T' % 8 = 4
    'C' % 8 = 3
    'G' % 8 = 7
    'N' % 8 = 6
    */
    long *mCycleQ30Bases[8];
    long *mCycleQ20Bases[8];
    long *mCycleBaseContents[8];
    long *mCycleBaseQual[8];
    long *mCycleTotalBase;
    long *mCycleTotalQual;

    map<string, double*> mQualityCurves;
    map<string, double*> mContentCurves;

    int mCycles;
    int mBufLen;
    long mBases;
    long mQ20Bases[8];
    long mQ30Bases[8];
    long mQ20Total;
    long mQ30Total;
    bool summarized;
};

#endif
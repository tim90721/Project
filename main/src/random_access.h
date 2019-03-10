#ifndef RANDOM_ACCESS
#define RANDOM_ACCESS

#include "includefile.h"

struct RAR{
    int raoIndex;
    int preambleIndex;
    int uplinkResourceIndex;
    int tc_rnti;
};

struct Msg3{
    int uplinkResourceIndex;
    int tc_rnti;
    int ueIndex;
};

int binarySearchPreamble(const std::vector<RAR*>& subframeRars, const int raoLeft, const int raoRight, const int raoFoundIndex, const int preambleIndex);
int binarySearchRAO(const std::vector<RAR*>& subframeRars, int* raoLeft, int* raoRight, const int raoIndex);
int binarySeachMsg3(const std::vector<Msg3*>& msg3s, const int tc_rnti);
int searchRAR(const vector<RAR*>& subframeRars, const int raoIndex, const int preambleIndex);
int searchRAR(const std::vector<RAR*>& subframeRars, RAR &rar);
int searchMsg3(const std::vector<Msg3*>& msg3s, int tc_rnti);
int searchMsg3(const std::vector<Msg3*>& msg3s, Msg3& msg3);


#endif

#ifndef PREAMBLE_FORMAT
#define PREAMBLE_FORMAT

#include "includefile.h"

enum Format{
    Format_0,
    Format_1,
    Format_2,
    Format_3,
    Format_A1,
    Format_A2,
    Format_A3,
    Format_B1,
    Format_B2,
    Format_B3,
    Format_B4,
    Format_C0,
    Format_C2
};

class PreambleFormat{
    private:
        Format format;
};
#endif

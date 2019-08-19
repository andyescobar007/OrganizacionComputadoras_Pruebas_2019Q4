#ifndef __EJER1_H
#define __EJER1_H

#include <stdint.h>
#include "VEjer1.h"

#define INPUT  0
#define OUTPUT 1

#define EXPORT_C extern "C"

#define SIMPLE_ELEM 0
#define RAM_ELEM 1

struct ElemSignal {
    int type;
    const char *name;
    const char *desc;
    int bits;
};

struct ElemInfo {
    int id;
    int type;
    int dataSize;
    int dataBits;
    const char *name;
};

struct DigElem {
    ElemInfo   *info;
    ElemSignal *signals;
};

#define EJER1_ID 0

#endif
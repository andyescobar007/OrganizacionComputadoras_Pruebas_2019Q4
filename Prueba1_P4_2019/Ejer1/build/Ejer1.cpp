#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include "Ejer1.h"

using namespace std;

static set<void *> elemInst;

static ElemInfo elemInfo[] = {
    {EJER1_ID, SIMPLE_ELEM, -1, -1, "Ejer1"}, 
};

#define ELEM_COUNT 1
#define MIN_ID 0
#define MAX_ID 0

static int signalCount[] = {
    14, //Ejer1
};

static ElemSignal ejer1_signals[] = {
    {INPUT, "opc", "Opcode", 6},
    {INPUT, "func", "Function", 6},
    {OUTPUT, "isJmp", "Jump signal", 1},
    {OUTPUT, "isBeq", "BEQ signal", 1},
    {OUTPUT, "isBne", "BNE signal", 1},
    {OUTPUT, "rfWriteDataSel", "Register File Write Data Select", 2},
    {OUTPUT, "rfWriteAddrSel", "Register File Write Address Select", 1},
    {OUTPUT, "rfWriteEnable", "Register Write Enable", 1},
    {OUTPUT, "memWrite", "Memory Write", 1},
    {OUTPUT, "memRead", "Memory Read", 1},
    {OUTPUT, "aluSrc", "ALU source", 1},
    {OUTPUT, "aluFunc", "ALU operation", 3},
    {OUTPUT, "bitXtend", "Bit extension, 0 = sign extend, 1 = zero extend", 1},
    {OUTPUT, "invOpcode", "Invalid opcode or function", 1},
};

static ElemSignal *elemSignals[] = {
    ejer1_signals, 
};

void ejer1_eval(VEjer1 *elem, uint64_t in[], uint64_t out[]) {
    elem->opc = in[0];
    elem->func = in[1];
    elem->eval();
    out[0] = elem->isJmp;
    out[1] = elem->isBeq;
    out[2] = elem->isBne;
    out[3] = elem->rfWriteDataSel;
    out[4] = elem->rfWriteAddrSel;
    out[5] = elem->rfWriteEnable;
    out[6] = elem->memWrite;
    out[7] = elem->memRead;
    out[8] = elem->aluSrc;
    out[9] = elem->aluFunc;
    out[10] = elem->bitXtend;
    out[11] = elem->invOpcode;
}


/* Exported functions */
EXPORT_C int getElemCount() {
    return ELEM_COUNT;
}

EXPORT_C void getElemInfo(struct ElemInfo outElemInfo[]) {
    for (int i = 0; i < ELEM_COUNT; i++) {
        outElemInfo[i] = elemInfo[i];
    }
}

EXPORT_C int getSignalCount(int elemId) {
    if (elemId >= MIN_ID && elemId <= MAX_ID) {
        return signalCount[elemId];
    }
    return -1;
}

EXPORT_C void *elemCreate(int elemId) {
    void *ptrElem;

    switch (elemId) {
        case EJER1_ID:
            ptrElem = new VEjer1;
            break;
        default:
            return NULL;
    }

    elemInst.insert(ptrElem);
    return ptrElem;
}

EXPORT_C int elemRelease(int elemId, void *ptrElem) {
    if (elemInst.find(ptrElem) != elemInst.end()) {
        elemInst.erase(ptrElem);
        switch (elemId) {
            case EJER1_ID:
                delete ((VEjer1*) ptrElem);
                break;
            default:
                return -1;
        }
        return 0;
    }
    return -1;
}

EXPORT_C int elemEval(int elemId, void *ptrElem, uint64_t in[], uint64_t out[]) {
    if (elemInst.find(ptrElem) != elemInst.end()) {
        switch (elemId) {
            case EJER1_ID:
                ejer1_eval((VEjer1*) ptrElem, in, out);
                break;
            default:
                return -1;
        }
        return 0;
    } else {
        return -1;
    }
}

EXPORT_C int elemSetData(int elemId, void *ptrElem, int index, uint64_t data) {
    return -1;
}

EXPORT_C int elemGetData(int elemId, void *ptrElem, uint64_t outData[]) {
    return -1;
}

EXPORT_C int getElemSignals(int elemId, struct ElemSignal outElemSignals[]) {
   if (elemId >= MIN_ID && elemId <= MAX_ID) {
       struct ElemSignal *signals = elemSignals[elemId];
       int count = signalCount[elemId];

       for (int i = 0; i < count; i++) {
           outElemSignals[i] = signals[i];
       }
       return 0;
   }
   return -1;
}


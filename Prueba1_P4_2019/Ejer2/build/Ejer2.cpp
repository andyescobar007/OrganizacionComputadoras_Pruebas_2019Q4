#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include "Ejer2.h"

using namespace std;

static set<void *> elemInst;

static ElemInfo elemInfo[] = {
    {EJER2_ID, SIMPLE_ELEM, -1, -1, "Ejer2"}, 
};

#define ELEM_COUNT 1
#define MIN_ID 0
#define MAX_ID 0

static int signalCount[] = {
    8, //Ejer2
};

static ElemSignal ejer2_signals[] = {
    {INPUT, "isZero", "", 1},
    {INPUT, "isBEQ", "", 1},
    {INPUT, "isBNE", "", 1},
    {INPUT, "isJmp", "", 1},
    {INPUT, "currentPC", "", 32},
    {INPUT, "jmpTarget32", "", 32},
    {INPUT, "branchTargetAddr", "", 32},
    {OUTPUT, "nextPC", "", 32},
};

static ElemSignal *elemSignals[] = {
    ejer2_signals, 
};

void ejer2_eval(VEjer2 *elem, uint64_t in[], uint64_t out[]) {
    elem->isZero = in[0];
    elem->isBEQ = in[1];
    elem->isBNE = in[2];
    elem->isJmp = in[3];
    elem->currentPC = in[4];
    elem->jmpTarget32 = in[5];
    elem->branchTargetAddr = in[6];
    elem->eval();
    out[0] = elem->nextPC;
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
        case EJER2_ID:
            ptrElem = new VEjer2;
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
            case EJER2_ID:
                delete ((VEjer2*) ptrElem);
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
            case EJER2_ID:
                ejer2_eval((VEjer2*) ptrElem, in, out);
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


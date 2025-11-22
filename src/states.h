//
// Created by Praveen P on 16-11-2025.
//

#ifndef BLEED_STATES_H
#define BLEED_STATES_H

#include <fstream>

struct BleedStates {
    std::ifstream mem_maps;
    int             mem;
    int             client_fd;
};

extern BleedStates currentBleedState;

#endif //BLEED_STATES_H
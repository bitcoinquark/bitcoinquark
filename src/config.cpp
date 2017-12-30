// Copyright (c) 2017 The BitcoinQuark developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "config.h"
#include "consensus/consensus.h"
#include "globals.h"

bool GlobalConfig::SetMaxBlockWeight(uint64_t maxBlockWeight) {
    if (maxBlockWeight < MAX_BLOCK_WEIGHT) {
        return false;
    }

    nMaxBlockWeight = maxBlockWeight;
    return true;
}

uint64_t GlobalConfig::GetMaxBlockWeight() const {
    return nMaxBlockWeight;
}

static GlobalConfig gConfig;

const Config &GetConfig() {
    return gConfig;
}

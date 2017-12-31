// Copyright (c) 2017 The BitcoinQuark developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "config.h"
#include "chainparams.h"
#include "consensus/consensus.h"
#include "globals.h"

bool GlobalConfig::SetMaxBlockWeight(uint64_t maxBlockWeight) {

    if (maxBlockWeight < LEGACY_MAX_BLOCK_SIZE * WITNESS_SCALE_FACTOR) {
        return false;
    }

    nMaxBlockWeight = maxBlockWeight;
    return true;
}

uint64_t GlobalConfig::GetMaxBlockWeight() const {
    return nMaxBlockWeight;
}

const CChainParams &GlobalConfig::GetChainParams() const {
    return Params();
}

static GlobalConfig gConfig;

const Config &GetConfig() {
    return gConfig;
}

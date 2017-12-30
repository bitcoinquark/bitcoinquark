// Copyright (c) 2017 The BitcoinQuark developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONFIG_H
#define BITCOIN_CONFIG_H

#include <boost/noncopyable.hpp>

#include <cstdint>

class Config : public boost::noncopyable {
public:
    virtual bool SetMaxBlockWeight(uint64_t maxBlockWeight) = 0;
    virtual uint64_t GetMaxBlockWeight() const = 0;
};

class GlobalConfig final : public Config {
public:
    bool SetMaxBlockWeight(uint64_t maxBlockWeight);
    uint64_t GetMaxBlockWeight() const;
};

// Temporary woraround.
const Config &GetConfig();


#endif

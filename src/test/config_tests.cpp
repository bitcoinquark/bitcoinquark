// Copyright (c) 2016 The BitcoinQuark developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "config.h"
#include "chainparams.h"
#include "consensus/consensus.h"
#include "test/test_bitcoin.h"

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(config_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(max_block_weight) {
    GlobalConfig config;

    uint64_t LEGACY_MAX_BLOCK_WEIGHT = LEGACY_MAX_BLOCK_SIZE * WITNESS_SCALE_FACTOR;

    // Too small.
    BOOST_CHECK(!config.SetMaxBlockWeight(0));
    BOOST_CHECK(!config.SetMaxBlockWeight(12345));
    BOOST_CHECK(!config.SetMaxBlockWeight(LEGACY_MAX_BLOCK_WEIGHT - 1));

    // MAX_BLOCK_WEIGHT
    BOOST_CHECK(config.SetMaxBlockWeight(LEGACY_MAX_BLOCK_WEIGHT));
    BOOST_CHECK_EQUAL(config.GetMaxBlockWeight(), LEGACY_MAX_BLOCK_WEIGHT);

    // 2MB
    BOOST_CHECK(config.SetMaxBlockWeight(2 * ONE_MEGABYTE * WITNESS_SCALE_FACTOR));
    BOOST_CHECK_EQUAL(config.GetMaxBlockWeight(), 2 * ONE_MEGABYTE * WITNESS_SCALE_FACTOR);

    // 8MB
    BOOST_CHECK(config.SetMaxBlockWeight(8 * ONE_MEGABYTE * WITNESS_SCALE_FACTOR));
    BOOST_CHECK_EQUAL(config.GetMaxBlockWeight(), 8 * ONE_MEGABYTE * WITNESS_SCALE_FACTOR);

    // Invalid size keep config.
    BOOST_CHECK(!config.SetMaxBlockWeight(54321));
    BOOST_CHECK_EQUAL(config.GetMaxBlockWeight(), 8 * ONE_MEGABYTE * WITNESS_SCALE_FACTOR);

    // Setting it back down
    BOOST_CHECK(config.SetMaxBlockWeight(7 * ONE_MEGABYTE * WITNESS_SCALE_FACTOR));
    BOOST_CHECK_EQUAL(config.GetMaxBlockWeight(), 7 * ONE_MEGABYTE * WITNESS_SCALE_FACTOR);
    BOOST_CHECK(config.SetMaxBlockWeight(ONE_MEGABYTE * WITNESS_SCALE_FACTOR));
    BOOST_CHECK_EQUAL(config.GetMaxBlockWeight(), ONE_MEGABYTE * WITNESS_SCALE_FACTOR);
}

BOOST_AUTO_TEST_CASE(chain_params) {
    GlobalConfig config;

    // Global config is consistent with params.
    SelectParams(CBaseChainParams::MAIN);
    BOOST_CHECK_EQUAL(&Params(), &config.GetChainParams());

    SelectParams(CBaseChainParams::TESTNET);
    BOOST_CHECK_EQUAL(&Params(), &config.GetChainParams());

    SelectParams(CBaseChainParams::REGTEST);
    BOOST_CHECK_EQUAL(&Params(), &config.GetChainParams());
}

BOOST_AUTO_TEST_SUITE_END()

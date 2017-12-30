// Copyright (c) 2016 The BitcoinQuark developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "config.h"
#include "consensus/consensus.h"
#include "test/test_bitcoin.h"

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(config_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(max_block_weight) {
    GlobalConfig config;

    // Too small.
    BOOST_CHECK(!config.SetMaxBlockWeight(0));
    BOOST_CHECK(!config.SetMaxBlockWeight(12345));
    BOOST_CHECK(!config.SetMaxBlockWeight(MAX_BLOCK_WEIGHT - 1));

    // MAX_BLOCK_WEIGHT
    BOOST_CHECK(config.SetMaxBlockWeight(MAX_BLOCK_WEIGHT));
    BOOST_CHECK_EQUAL(config.GetMaxBlockWeight(), MAX_BLOCK_WEIGHT);

    // 2MB
    BOOST_CHECK(config.SetMaxBlockWeight(2 * 1000 * 1000 * WITNESS_SCALE_FACTOR));
    BOOST_CHECK_EQUAL(config.GetMaxBlockWeight(), 2 * 1000 * 1000 * WITNESS_SCALE_FACTOR);

    // 8MB
    BOOST_CHECK(config.SetMaxBlockWeight(8 * 1000 * 1000 * WITNESS_SCALE_FACTOR));
    BOOST_CHECK_EQUAL(config.GetMaxBlockWeight(), 8 * 1000 * 1000 * WITNESS_SCALE_FACTOR);

    // Invalid size keep config.
    BOOST_CHECK(!config.SetMaxBlockWeight(54321));
    BOOST_CHECK_EQUAL(config.GetMaxBlockWeight(), 8 * 1000 * 1000 * WITNESS_SCALE_FACTOR);
}

BOOST_AUTO_TEST_SUITE_END()

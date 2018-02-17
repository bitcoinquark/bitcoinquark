#!/usr/bin/env python3
# Copyright (c) 2014-2016 The Bitcoin Quark developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test cases for Bitcoin Quark fork """

import io

#from test_framework.address import *
from test_framework.key import CECKey, CPubKey
from test_framework.script import *
from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import *

class BTQForkTest(BitcoinTestFramework):

    def set_test_params(self):
        self.num_nodes = 1
        self.setup_clean_chain = False 
        
    def sign_tx(self, tx, spend_tx, spend_n, redeem_script, in_n, keys):
        """Sign a P2SH transaction by privkeys."""
        vout = spend_tx.vout[spend_n]        
        (sighash, err) = SignatureHash(redeem_script, tx, in_n, SIGHASH_ALL|SIGHASH_FORKID)
        sigs = [key.sign(sighash) + bytes(bytearray([SIGHASH_ALL|SIGHASH_FORKID])) for key in keys]
        tx.vin[0].scriptSig = CScript([OP_0] + sigs + [redeem_script])
        tx.rehash()        

    def run_test(self):
        node = self.nodes[0]

        hex_funding_raw_tx = '010000000001010000000000000000000000000000000000000000000000000000000000000000ffffffff05033c391300ffffffff020000000000000000266a24aa21a9ede2f61c3f71d1defd3fa999dfa36953755c690689799962b48bebd836974e8cf900b4f9e43000000017a9149992ad8807ae91bb723fbf2c560ff76eeadeb040870120000000000000000000000000000000000000000000000000000000000000000000000000'
        hex_spend_raw_tx = '020000000188b788bce453127387146ccfe14433a5141028249fd335ccee1dfcf6a9e87f8d0100000000feffffff018099f3e4300000001976a91443f32a365f0e4e855f6c2997bd364e6724e8076288acee491300'
        hex_redeem_script = '03ee4913b17552210330ac64a02530018aee75282511ab03ad14afded0de3a7631f859fcc95e7053f52102b1dd3a3d48bae5e8372e896c12fcf1a6a472df03a4e279f1228ea43eb72d7a7621029afac47580783cd5e0fb7b9ef5eb70302e153c02b3880f254eed34e636228fb153ae'
        
        tx0 = CTransaction()
        tx0.deserialize(io.BytesIO(hex_str_to_bytes(hex_funding_raw_tx)))
        tx1 = CTransaction()
        tx1.deserialize(io.BytesIO(hex_str_to_bytes(hex_spend_raw_tx)))
        vout_n = 1
        redeem_script = CScript(hex_str_to_bytes(hex_redeem_script))
        
        privkey1 = 'testprivkey1_hex'
        privkey2 = 'testprivkey2_hex'
        
        rawkeys = []
        raw_key = CECKey()
        raw_key.set_secretbytes(hex_str_to_bytes(privkey1))
        rawkeys.append(raw_key)
        raw_key = CECKey()
        raw_key.set_secretbytes(hex_str_to_bytes(privkey2))
        rawkeys.append(raw_key)
        
        self.sign_tx(tx1, tx0, vout_n, redeem_script, 0, rawkeys[:2])  # Sign with key[0:2]
        
        raw_tx1 = tx1.serialize()
        hex_raw_tx1 = bytes_to_hex_str(raw_tx1)
        
        
        # Basic block generation test.
        # Block #2499.
        #self.log.info("Generating 2499 blocks.")
        #node.generate(2499)
        #tmpl = node.getblocktemplate()
        #assert_equal(tmpl['height'], 2500)

        # Block #2500, Equihash enabled.
        #node.generate(1)
        #tmpl = node.getblocktemplate()
        #assert_equal(tmpl['height'], 1501)


if __name__ == '__main__':
    BTQForkTest().main()

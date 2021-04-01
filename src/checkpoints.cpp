// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 100;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints   =
        boost::assign::map_list_of
        (    1,   uint256("0x6d82fc75145105c260ca61430c463a6a80e77047ad464aeada5164c0aed8e7b8"))
        (  100,   uint256("0x4b59784b429cadbfae2876156842efb6675fd3c7c732dfc104aeb2f79db54ec6"))
        (  200,   uint256("0x9f656aa5aefb46d266c16ff596b027a79f09a60a56b6bb2a0aae760c6f5412a9"))
        (  300,   uint256("0x2bc0cd7dadda5ba0b446433c9f024e7c38b422a6f8c5e9a19a4da917acd6d9ec"))
        (  400,   uint256("0xeff36fe2efc67f3228a9e4e0c12d0fd1f5b9e49ed2954c0ae72e7e62c11338f0"))
        (  500,   uint256("0x649b9edb5ef3b0d7e0ae4ca6bd9c7ce76ab337598268a767935c41d2eef8e127"))
        (  600,   uint256("0x002ad40274ef5aeaea90d41b612be702c5d9fbc661e332df6e860395e02959e9"))
        (  700,   uint256("0x937ffd4a8f5c701f360265785c3d1cafe0d846b9de04705a600363bd5fb76531"))
        (  800,   uint256("0x9d126fe938abc19a70a8250bafa1658221525dc236f8762172bcb676b8a55e27"))
        (  900,   uint256("0xd2cebe283b1aa4ea1af272ffa85fcda7fde22ce22dd5f967fb8462875e015794"))
        ( 1000,   uint256("0xe2c1858577cb2b2716b7955d613ecd94326c4fc1ee57a63f68ed23058b298ba1"))
        ( 1100,   uint256("0xf8cc4fe08ce01f4e1884625ce5f7d70a8599f319feaf6710c2bd03ff33067705"))
        ( 1200,   uint256("0xafbf1ae7bcf3ed310c3a5c235161d3fdb387f351116ad54dbbd1b533d3b63c42"))
        ( 1300,   uint256("0x850881bde6cafaf3bf87fffe66d9effed3d6d737ed1d2be6a4fe4aea11040c02"))
        ( 1400,   uint256("0x2ac1a5e6d92dd06195e6b54e72dd0e6c58a061fe47b73ea504777f5a2759b5cf"))
        ( 1500,   uint256("0x33e00c9d54be115dc5bc6b3e2616c3d461561056575d119c806a422f47bfa029"))
        ( 1600,   uint256("0x8301032ae76dabb43397a77e22326c8744e5513ff997fbbcf3599124f4b30eb2"))
        ( 1700,   uint256("0xf1c158c6101ec15a9a08a17eb74ae1fc63f55bf647562398f19e43f32cecd26c"))
        ( 1800,   uint256("0xd17763255f2d255e7147d1a1da8658409e058a9a315a1d43e418412c699968d2"))
        ( 1900,   uint256("0x664ea3f600b1dd008030385f092ba02232d7438a6bd1c567915d5b39a01f9ce1"))
        ( 2000,   uint256("0x52152b5ec49779a5e866f50e89569f7ecad0e412e8cb441c293f4729efbcd3d3"))
        ( 2100,   uint256("0x64e5190575a66ad9169b77946bef0631705824eeec43ac555f74a0edc169656f"))
        ( 2200,   uint256("0xa8b7570f3a00b14237f8bb651b38cfa205324d58e4e14710f01d72d58b13cbf7"))
        ( 2300,   uint256("0x7351a015609014f37a87f90a35929510c010051c36b9f1b8dace8545c61e5bf0"))




        ;
        


    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();

        if (nHeight <= pindexSync->nHeight)
            return false;
        return true;
    }
}

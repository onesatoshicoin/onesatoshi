// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 200;

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
    static MapCheckpoints mapCheckpoints   = boost::assign::map_list_of 
        
        (    1,   uint256("0xc457c968f33f167cf487979c387adf3bebbe424cda5cd8d6e5bce9219637d5bb"))
        (   10,   uint256("0x4769f615a8ce077198dd34738e808bec06198bcd8b38f86d5b14c123585bda8f")) 
        (   20,   uint256("0x49a22b574feeb390b85152699d7f761d1ea13b4d75f7b472577643e96299a6ce")) 
        (   30,   uint256("0xc226c8c9a162322d5820cff0351ddfcdb217d07ebfb06b37fbeaf5816127139a")) 
        (   40,   uint256("0xa25c2d6e246f87337bbc77f8ed043ffb5bd76debb216ffafd24f0b6853033d46")) 
        (   50,   uint256("0xaf7c52bfa732f1c550227efc2f669ee3e7c7b25d885eee722ce33d4a7213b09a")) 
        (  100,   uint256("0xdb2ceda60b28d297da03e6dc07f836d2797d732ee98d087d256f56084dffa9e8")) 
        (  200,   uint256("0x877f4397f9dbdfe6b3edfd276189b29731502bf041e32b403afe2b727e5273a6")) 
        (  300,   uint256("0x537757a2bf488adb3fb67781866b35cbaf01f0f141d816fa26204f68f5138dc6")) 
        
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

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
    static MapCheckpoints mapCheckpoints   =
        boost::assign::map_list_of
        (    1,   uint256("0x932649123e5fdf7b714bcbb83353b0598caf1abbbfe4a2f0c1bbd76056b29472"))
        (  100,   uint256("0x7892b7c4b1b58f4e47a1c20adb328865be911963062fea9f266736f1e90cbfc1"))
        (  200,   uint256("0x6a235521a5e225124dba2a12c8bfc7331250c55148145aed685722f7b03b4f3b"))
        (  300,   uint256("0x5623164083382c6d1d7abfc66dbcc59d1e5862ace3cb8164f5dd0f9513255efd"))
        (  400,   uint256("0xb50f7276b06cf7de455fcf2b94813d3432b0aff3ef57823e6df27d6b84d6bc8d"))
        (  500,   uint256("0xc132d9efe22672cc2214ac32ce5c12c464b7b07810eda575a44d3489de697526"))
        (  600,   uint256("0x53e2d63fc5ba90bb8b95996d127d43f9008072db85f2897cf0cbdc62b7059b63"))
        (  700,   uint256("0x21aa0fef0e531c63c15f8bdcb1de4ef903c3a3536c8241fa2d399cb3e03da6be"))
        (  800,   uint256("0x7aec8933e64c3d4593dbb1a511807d70a33e90611da31a4328223bd282df86dc"))
        (  900,   uint256("0xd75360811d6ab6cc6c05c159eb26c6ca6431eadaec7d0488ec1d8d00f4a0864a"))
        ( 1000,   uint256("0x296afcf865cdc408027a36dff98c27263ba6bc534bc9e109680ad084a5de242b"))
        ( 1500,   uint256("0x766509e9ab198b3d7b885661cb6beb58a2289ed13b18039c430e1f0523b35f2f"))
        ( 2000,   uint256("0xb61a8481f8298b054254d3f2c226a6fbb6c053d458e99036e7a34936354991a8"))
        ( 2500,   uint256("0x8b833c32f0547466de964cd7cfe9060f9e30b1afdc7729d4273d9082a7dbdf97"))
        ( 3000,   uint256("0xab0c50e1e1afc564af5eb871d6cdceaaac01b1acf61dd1ab0eb8c1f5435afd45"))
        ( 3500,   uint256("0x0422e1ce1c8fee389cff5f23f201e423616330cfece0192c1726cdfcf4a208eb"))
        ( 4000,   uint256("0x7c43d0203149a5e682f6a387c120a4c72c82c3118e113c3a1e4ce1e0ff5fa219"))
        ( 4500,   uint256("0x8ab9e6a7e1211c62e23e5f4813544de06ca1c6650a002e96241ca8d7130fdd30"))
        ( 5000,   uint256("0xc205b3bc0b5735a7fd8fbc91d32ab6aa671accc9667bf63321897b85385ab442"))
        ( 5500,   uint256("0xad4c941345f12179c351553e15716a037b5ffc2f9634ac4edabc10cf2b2d24bd"))
        ( 6000,   uint256("0xab76a129a2f81ce558732ed089d4a3458c750422adce21362a5fbac3ad9dcc12"))
        ( 6500,   uint256("0x2d3bf5db28df3b09eb23be22f90f26e7e40399b524448230c2fb4811c4c16010"))
        ( 7000,   uint256("0xb9ec1675bacd495e85d801c5509925a49c979b2b67e6586f058fd81fd6bcb489"))
        ( 7500,   uint256("0x1e5663dd19fd5b3872e2cf60ef707ae0b97d6c1f6b97bbc40cb997b17bfb3bc2"))
        ( 8000,   uint256("0xe8f41629b40a01b17981ae3dcc0bdad2f8ef9b2daf5b54ddda3a3550971ec700"))
        ( 8500,   uint256("0x0b55bbfeea2cf2aea22abb594663cca38a8be026938130c8dd28a487b78096a3"))
        ( 9000,   uint256("0x2aa70c1f2801f82c30b8b5356567eaa4cea39a5474e44407808282d94fd72d4e"))
        
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

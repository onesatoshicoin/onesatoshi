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
        ( 2400,   uint256("0xe8ac9e249ad7b6e46aa779748f47f9c943f098135a8c85fa096f18ad3180019f"))
        ( 2500,   uint256("0x1d2b23d1ab32985bf034ba127783c19c46bd7c46dfdf98766c77d112f0022989"))
        ( 2600,   uint256("0x8569e5909d1ebc244495cb6b266ec413a9569a2bb415dcf4f625c23164b4686e"))
        ( 2700,   uint256("0x402d6abaffa46ece01bd095f26383fb67040ed95ead23b3b5ab0abd43ae68444"))
        ( 2800,   uint256("0x55ff94d276c7a9c59677878da04daa13c55bdd1ac53e33b17f9c3ede944404cb"))
        ( 2900,   uint256("0xc75ca41fcbbe5f9ba615070f5917d5e6e81a83c41d0c427a7e2b6cac78dc5e39"))
        ( 3000,   uint256("0x6e4758fc0566eb9aece78c193f392994b5ead74b6b234a93e68730a669cec7ba"))
        ( 3100,   uint256("0x883dea8d55937ee021742117cc626e3b99c519a3a72419c632338d820510f6b0"))
        ( 3200,   uint256("0xd234e73458f50605ad8c3baa2b66fdad03858e89ef66751b01652ead6b61c4e0"))
        ( 3300,   uint256("0x923204cf6b90106a909c69a660dba03d871ee6d5e777479887c8472efbe3bae8"))
        ( 3400,   uint256("0xa68d95f8aff66e32cbd446a42631a4d02dc7c90186df12530587c4e7f710f630"))
        ( 3500,   uint256("0x9221018114e49f7b8f38bb0cb47143a364a91d6ac9bcd1ff9cfe7587e40cf54b"))
        ( 3600,   uint256("0xc4eb55d6290e6b07dfc34fb3504f01dc644f1208bb52c700e78b9f943d8ebb80"))
        ( 3700,   uint256("0x7b2b7bcbadc1d2a0f27bc2b2fec4f8dd65ed996058daebe9b1905bcac52f6a6a"))
        ( 3800,   uint256("0xf1cc6453269eba896266bfb0c80335e0caa55908941153b13c921c1b6f79b7c0"))
        ( 3900,   uint256("0x1b382b4b99a0fc05b97199acb28669c4dcf1d1aaeaa84f8696b9f501c05e9c5f"))
        ( 4000,   uint256("0xced4e63571e910eee7126ece2818d2b1873dfe4dc7fc5de414cf2ea675e8d9a0"))
        ( 4100,   uint256("0x860495ab27b59778d0762722f74403f1ee465afa34b7fc08f6d78564dd45419a"))
        ( 4200,   uint256("0x0ee44549fed397cdee1b1c9842c34d27865332131ce03a28e5221f0b2925ba19"))
        ( 4300,   uint256("0x2f09e48fabc97edf8c7463cef267b266131761ef22fbf0309a1af62a2c194b68"))
        ( 4400,   uint256("0x2b8267d62b1042a3c6da17f4b62a8c093f0a3cc96520220a49210794dbb83c87"))
        ( 4500,   uint256("0xe59a3eb8c96eea70ad5f9a0089a93b023fd44442bf21d6cca20d558fdcd96a93"))
        ( 4600,   uint256("0xa46e7569d36e20d3c4b37ec3953d992019dd090228f41c6ded012df94ba12498"))
        ( 4700,   uint256("0x77b248d815796b300f6c595025b673718f30cc91b4c6efc3eb9b91180259a616"))
        ( 4800,   uint256("0x4775dc37998c55a31a04a95ecb37c479f268d117724d45243ee21632d78aa28e"))
        ( 4900,   uint256("0xedad4f03f565d70369466f85334a105fe6b6e92c338044963d773dda620609cc"))
        ( 5000,   uint256("0xd24185188fcf965b9923737d4dff130e4775116042916d9ff412a57db8cc7012")

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

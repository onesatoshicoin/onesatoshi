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
        (    10, uint256("0xead9a74b4769c3cf31021c005be3edcf524aaaeff2ce232b7ffe22cacf7c782a"))
        (    20, uint256("0x4bd06402d31b352211d597bbf5b93227ef78df51095df94dab29881e7b5f2c3a"))
        (    30, uint256("0xf85f5468af56af3add7d7a53d539086aec60dc1eff937398ce44e09491f3198a"))
        (    40, uint256("0x7a1bd8fe3a7b08e9e0d04633fee7f819f2e2ad88efa4148fc282887c74f64a77"))
        (    50, uint256("0xb03d0475606472bdf0973f3b5d884fdc80854941736bbb67d5cb4d250bf77b76"))
        (    60, uint256("0x8c7fa9514e3f3f9a08877aab37ed91ca271a6480780a0023ab49f2677c082f75"))
        (    70, uint256("0x2290566496e17624b815a1ea0403232bea2d0c3ca955b137858d08e52aeaf513"))
        (    80, uint256("0x26623273550ba4c78de066638d6b183e37401625113ac4b5d97dbd5be1f27a29"))
        (    90, uint256("0xc6e5b232d216e6e9337e338aedd38723b075023c845aa1fce133b0c5b5bab57f"))
        (   100, uint256("0xf882eb0b3f9ed00d4928b010a9559394bae49f24b82b8a261ff9a3331d97a921"))
        (   110, uint256("0xd2b2c6957582f9a32d5acff355ec6c79718b1d0407e67e352fbb8218910cb093"))
        (   120, uint256("0x623da334c80ca292fe9f7b3e31c7bef9aecb55d91859562507dc04403a93162d"))
        (   130, uint256("0xa7f527fdcc6fdb9cfd61278c552a3453d1d817cf33c4f11b1076293d5b57e0e2"))
        (   140, uint256("0xe3641338a490774867a0a1ce5b0f568dc5e04aee70c412e2c7ae5ab51368856b"))
        (   150, uint256("0x30ca266a9b591b8488764ded9539ea8c2f57e9d3a7dea01cd907a2bdb1c2329b"))
        (   160, uint256("0x59b786f63b8a2a7b6b7efbfcf4619f89aa87366ab4f487328f677ad60a170f77"))
        (   170, uint256("0x27f8a4eb043f2ec44329b5e9b988559bd9df75c7e657beb18b2885cbf94f642e"))
        (   180, uint256("0x3cd5c0ebd7125a69cc3d59b9f37aafb50dfe4c15f47bf384e43774b9d048a180"))
        (   190, uint256("0xbca1d188d23adf79a7693c5cbead6696f13dfa7fc90ea0bfbdc8a876704c0867"))
        (   200, uint256("0x09c44b195fee5e59c4e1f8d55e748f4af7964d73650bd139cd2c41cd5dd5c150"))
        (   210, uint256("0x0a88236fd5f4c407026ac8e419a6715cad71c20c26e6df02ea6a59ce3769d170"))
        (   220, uint256("0x896dad27dbb0c158830fa60d532bbd79b2c1152f47e70cfac7fd17261b97237a"))
        (   230, uint256("0x7a10cbf6b9fc833a08f22ca29edc26426ae1d3d71b8789ee9ef5da2273906676"))
        (   240, uint256("0x10d64941bd1454b6d5bbbcb0d6b582c7df7363babf3c963cc27650643f03b457"))
        (   250, uint256("0xabc4a58fcbaea708574753bf846e8ae47b1fd5c3aef526faaca320622033ea8c"))
        (   260, uint256("0xcc2ce948f68d07b856caaafde0a677326618e1240302abb6b7c02ff15ab461cd"))
        (   270, uint256("0x73f21b4d606625f00306bec47b76fc346a2fb346a1ac2e32171200bef85e198e"))
        (   280, uint256("0x44602948fcee53941822c07a7ac5fe6f03f7d92897bd70274ab0a0398fa5f869"))
        (   290, uint256("0xfe0825cfc799e6bf54fefbafbc4ba51922f7a2679a5e08fa4caaa6ec91424d0e"))
        (   300, uint256("0x271f94650573eaef893ba0c3be4bca07755eff10f989e8f816f29c6619c6a776"))
        (   310, uint256("0xa3c263d91f981e8894666bfe4228d146f07da3ce9c9e099fec58f8d1ba44c2be"))
        (   320, uint256("0x4683055568c62c9f9f14cad1a9fb72da60c2e42a25b502fd5274a16f92560a2e"))
        (   330, uint256("0x966027ec1b6ab9187a51c3f35a05837c3b76b5e6185595f08ebcc7f744c5ef00"))
        (   340, uint256("0x6e895e7776e0604eab576ab8747fe6a043cddefab8c612fb7623d4e24dd71a8e"))
        (   350, uint256("0x4b1683e94b190aa370170fd9c08fd631125b3f56509db8784e340c4508df078d"))
        (   360, uint256("0xb82c42a0a307be7723f0675f5193ae0f00e209e74b29f971f750a1469f1f594a"))
        (   370, uint256("0x1c4171e38b329dc7c3e049c4bdf99851dab49e84c4af5ad3f494993b6a30e0af"))
        (   380, uint256("0xe472b7aaf5c889d050973497e62428b62e4bb24256db457808966a6975912525"))
        (   390, uint256("0x02b616d9fde548cc95da24a92d7757eea7c4fafcc8e3b96b047a172a3d3a0bc4"))
        (   400, uint256("0x2c67bdfb3040339bbbfdf37836d1b7d9f7d8d7969a5be93b3787de0e7683f9ff"))


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

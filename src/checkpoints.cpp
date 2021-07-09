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
        (   500, uint256("0x3cf484cfa4305d63c35a7768d73ecfb22ddcacbd29e2ca26e63804946238805e"))
        (   600, uint256("0x7fe060ae9669374cce754caadcc12c8e7c3570513c78edf7137ec2e1ac90705a"))
        (   700, uint256("0xcf551514cbc0b49d56e30d577211d5962b88557b9f3e06f04d1bbafd22a6fbd9"))
        (   800, uint256("0x518d5c470ae7a4f98d03178fe8f3e8b902694797ff956191e67a65a6e5f8f675"))
        (   900, uint256("0x95ba0b5917163a4bfacbdbf23a3f131b214509e55d5b851bcbc0a952bbf55307"))
        (  1000, uint256("0x404dc075e68b0d936561eb999a652a5cc22efca8fb0e8fe2f388ec5767108a36"))
        (  1100, uint256("0xbd6b6eb518e1c43b470bbf65fb4c376f463cf0780716ee9fd040c1924e1153c9"))
        (  1200, uint256("0x3b419322cabfdfa64aec627961e191424d605ad2f4b0b96731671b2d94abddd2"))
        (  1300, uint256("0xa0558d10a053ebe10c8499c6776c36f98e1839a1a0f554825b2834b113e0b769"))
        (  1400, uint256("0x98b23522ddecca12fbc6de59079f81b1da5ce0a681ce42183773ecc80db6cfbf"))
        (  1500, uint256("0x7c9d5cb56cfd25bcb044bfe5a504e0e3d421e8c8af44776f1fa0b248d3632254"))
        (  1600, uint256("0x0097c476161e4ea6cc5f81624587e5aa304aabde159b79f1869f170b229f1ae7"))
        (  1700, uint256("0x30965552fbf16c09dcdcdaabfc8d3bf293c92e76b93f10d04d86ae3f82dc9e75"))
        (  1800, uint256("0x01719ffc14754a825a89cb3b7f1de9087bb413451973316462639732b8b85c4c"))
        (  1900, uint256("0xf2e3c624847c7e13a09ad397b2e30fe056810ab655afe12312f38e46d679e92f"))
        (  2000, uint256("0x0eff3eb96230c03529faec77dfcaf869d90cb62e019c19393b7f7b45ad0e1a56"))
        (  2100, uint256("0x0c0b4cb33645b43ebc6f59e5e773137b5303e32b876c4de90eb226b4e77c2865"))
        (  2200, uint256("0x2652665cebfe40828b554a1dee5d837f92df5ef76c20df4258c13d90eb00fbc2"))
        (  2300, uint256("0x4453659d235d165fe6ca773e810588549123984fb1d3c8565d92eb44c6091d5b"))
        (  2400, uint256("0x7fc395e5f401bc3b42275a1e5cb25a52f4ca2ec8dfa0eab192a50aef68c6fb03"))
        (  2500, uint256("0x5e2e523c9e5a02483fa0fffbb80d37a5e3fa1f94c9407348f0e0af6dcd7f7106"))
        (  2600, uint256("0xf57b144466db2a48543da78ac8a318a857c8a38a1d430ffb5a908452dd364968"))
        (  2700, uint256("0xb86abfb7477eee97b08394fa2f67bdbedd7161086d4fe9841e5f8f9df2eff707"))
        (  2800, uint256("0xa8d192685d0f02d2358e7dafe3fe445ff40888b2946ce046f393d524c87e01d4"))
        (  2900, uint256("0xa2d1b108fb5d8adfe7f76e79b53fe772137c9505d788af79f9a2bebb6953bd17"))
        (  3000, uint256("0xe609c8875fa20ff4ac0e5c442a6b023afaabff2db02829faf186fa7050e1677b"))
        (  3100, uint256("0x5ab2b708c11737efe1356e7bc3d5b885377ebb6232176c4c3ddb328e1b6d0684"))
        (  3200, uint256("0xd53475541485c6c5e58bfb371f858e3384127e96b01cc0905f608fd08e628e65"))
        (  3300, uint256("0x056fa04aa7e0bfe638e6ecf4ed8435fcea7c8c871f9e26ed34acf3c5689c362a"))
        (  3400, uint256("0x5f8bdb60cb7feea95494497b54d09e699df24878530fd664dab23f6111e97cc4"))
        (  3500, uint256("0x72c4bc0847eb991b32c2bf48f39e4dd29132c4928462ea0d57c49371543fe73a"))
        (  3600, uint256("0x873517f2b1a6dd5a87b8b4c15ae883514c29a8231de8191269c6160424ed5ce5"))
        (  3700, uint256("0x0e7df4890c7ad7cd26308866760093799c0a43216bb548920d49876dab6220a1"))
        (  3800, uint256("0x08ff189d653f70d6e52f7ed88598a779c028f81ffe5717e59124845abbb02de7"))
        (  3900, uint256("0x7c199332efaf5bd6ea45f7a3d3155a77df25eab5c7ef2dfe1b7afc59b42c2ae8"))
        (  4000, uint256("0x2a8cf20ba2ce886a17dbb07247a8306d25e8c7ad600cb37ecdbfed83da01f26c"))
        (  4100, uint256("0x0c8d242e2fb9a701cd78739f835a5622d5597fd50310a34f6046f9f7a3945f6e"))
        (  4200, uint256("0xe554a8af6ba3b1b5c4a65b2046e9ace31cf8079ccf48f7eba03ee3587afef508"))
        (  4300, uint256("0xf939d6bb199594a6f3c13941e696efd9b89b413aea1b7020b52efb15cb255521"))
        (  4400, uint256("0xe3ab6a7de4e8cd1bfe543f1a8bf267d3e95ff47e3a4561109c00e5dd08b41fce"))
        (  4500, uint256("0x343b0e7f48dd85f70025121a71288afd4bcbcdea5924b9ede693cd1be8eb4824"))
        (  4600, uint256("0x9d673ee518ed1688696dd0388d61df023017fff993945c62201d23e79fd86c71"))
        (  4700, uint256("0x89a5d4520bd24c2cb73175231099e385734a89f776640fba867db932c2ff0cce"))
        (  4800, uint256("0xacd8088bc5b75380f73ef0649775f0b7cbe8520f00b7b97286dd4aa7a09d14c6"))
        (  4900, uint256("0x188a4299f45dc12283d6d719bdfd04418083168af8b7e45691c1ac6d639550d1"))
        (  5000, uint256("0x81b5c90746c9a8fabdea1e516c8c590e91facbdd3d5144b8a158a319b4239231"))
        (  5100, uint256("0x3d40d0305ceb5cd9cad12076c75a988501ffd319a31e2b20f801bbddf8cfb35c"))
        (  5200, uint256("0xac5622adef1a5371ebfc0886eae4ea1da1c2337c2e92f5c87cce5f3a459a5a8b"))


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

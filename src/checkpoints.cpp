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
        ( 5000,   uint256("0xd24185188fcf965b9923737d4dff130e4775116042916d9ff412a57db8cc7012"))
        ( 5100,   uint256("0xd529e05560e599831853ba6b80e93c5e79d439476a711a473d4fc48fa50d4ec4"))
        ( 5200,   uint256("0x1fc15f4314b9837a643819fb6136bea25f9a843c70b52b602d6533fba027b25e"))
        ( 5300,   uint256("0x27572b0f7715410618a5ac96c958d2e23593751918e829cc0a647af8e136b5dc"))
        ( 5400,   uint256("0x80ba36c0ec76c3ba643464020ef2b06f61b1e3a5b5a3c2b47f4aa17922267afc"))
        ( 5500,   uint256("0xc407213981176eaeafa4b48678b1f5068af42b5e55e84233d367b29cccecc4e4"))
        ( 5600,   uint256("0x3597e8a78586b5b265be9f5f4300acbd80444b8707220baba9d73242733c6e8e"))
        ( 5700,   uint256("0xc1d8afb271cd30248a68d1aa485d0fc88b022ae2998ce0cb212145ee6104c62e"))
        ( 5800,   uint256("0xd14b1f3dda38548331104051431ffeca9951d37af3f65d0efb7eef2377113635"))
        ( 5900,   uint256("0xe2e427787eaf806993522fe3f21003463589819f59c78e26aa82dc3e24766d67"))
        ( 6000,   uint256("0x6bb4faa2b16be6125f3753ec5bcf33f8e9ea31c6239c6acb8988d3e8fb4fd2ba"))
        ( 6100,   uint256("0x84294bd0adec1567d786640d5d3e0c6f96969c44f5b8bf6e31ac874ea1c0d959"))
        ( 6200,   uint256("0xe87d74a36e5d8882d39ebe4e7623cb72b58645679ac5a50d35f943f370be1bc1"))
        ( 6300,   uint256("0x77ba357b57eee6d5cfc9169350c757455790191a172b155f52d29d5047297ba2"))
        ( 6400,   uint256("0xe805fb0ed71094c621af0b1ea0a806c9775c7af9ea2bc9ba24d442a00d33905f"))
        ( 6500,   uint256("0xa6b98a45cbe7c32c7cf14bd94c3956879f21405187a713af512a44541b3a626c"))
        ( 6600,   uint256("0xcf5449e79ce930beb2fa3c642ca27739ff05d2b75f6de0a9257d155e0fae2f57"))
        ( 6700,   uint256("0x8df9282ace2beb20c8f90298d85758cfd46dabbc880563fda329a2ef553ec8e2"))
        ( 6800,   uint256("0x6bf4f5cb6c6ad1fa1e050e6a4beccfe4c199abb87734875db7b9d27e4265c683"))
        ( 6900,   uint256("0x7ff465ebc3fedde9310f66035a4f0eaae16d4bb7dc84ec7c668d348a908f7518"))
        ( 7000,   uint256("0x1856a968ef3cf480de91d86580b8bf399256663dcc893a31a4df35efd235030b"))
        ( 7100,   uint256("0x7872c889552f23f9fc0bda8befddfd65c5605410f64d82816dab6c1c0e783622"))
        ( 7200,   uint256("0x18b6a77bb3920308aa1a698a7e62fefe7a134c880d348896f88560c07f3ade2a"))
        ( 7300,   uint256("0xaf5de097b3dad16657d1972e883e127db831ed166903ab2f0b0f89ea5de6036b"))
        ( 7400,   uint256("0x2f880f055227326cea06272f18ba44b20fe78a0b6bbaea611b6b5d98015bd211"))
        ( 7500,   uint256("0xe09e3575eedfd9bcbbcda4e6c4ee32e4cd2d4a7b47625bf3236bdd7b98feb94a"))
        ( 7600,   uint256("0x66b53b29d8eddc2c23dcc195b585e3eb6d3cafb46a94be94a7c660c2a9b77dee"))
        ( 7700,   uint256("0xc130a250f9d5d31a8025077f44bb2cb2191243ce5607f7cd78da4d7df6a341f7"))
        ( 7800,   uint256("0xe585255741d8d194105ea56753763a7c1cc86b15a3d53762f1436c51b03156bc"))
        ( 7900,   uint256("0xe1e3760bfab4dac27f960e1e459ff8c0e2c65e82df64cba38a34aea33db9c0ec"))
        ( 8000,   uint256("0x7b9e8b322b11ea8602a60ae88f153e6ecc9eb5c8b4c124c918f65af0a932a4db"))
        ( 8100,   uint256("0x954c1f6d9ce303a086f2b628c1fdd7bf859bcc4e6655df693fa0c23b0d3aa378"))
        ( 8200,   uint256("0xbbc8d010ee9d5800609cb5ef5f1763d2b517ade9133ee299fefd336dd97bbba3"))
        ( 8300,   uint256("0xe1e71640765659ca9dce3d9f29447d2bf0e6ba437362845cdf1af006a695cd2f"))
        ( 8400,   uint256("0xa90ea936c061836e01cdd50c8241740a324df2aa908bc429f88bfa41d473d929"))
        ( 8500,   uint256("0x903917414d2ba1e179c3405b0b185e12f5a7d03e67cd38999d74719b8793dfad"))
        ( 8600,   uint256("0xd308d126b89e1b1acc37636c9b05707c941fba0a0b5664c4d25280472eb91972"))
        ( 8700,   uint256("0x1ebf924772d44dab2bc90cca37323fafcd9566a17c9306555719e5516b78075d"))
        ( 8800,   uint256("0x588fee8809d9ed67e2f877d70761f6fa09a367cc351407a2296ab7516532d127"))
        ( 8900,   uint256("0x61a57721219ba7109b68b15a98526cb85dc0cc9cb768e9ddf9f70216ceb06be8"))
        ( 9000,   uint256("0xa4392f8e232bd763794bbd2f570913b443e591759d652c7de3610bdd0cf0ad96"))
        ( 9100,   uint256("0xebe83c48fe13201b3b3d979d77c7edb72e4a91e9fb19626967826731665647ee"))
        ( 9200,   uint256("0x5044930273c6c85eed3e925c1cfaefd969d2b0c27784d253915b722e314f67a2"))
        ( 9300,   uint256("0x425ae3fcf2c7f05262c6239cd1a645e611197f3d8670d49c8ea8b534b7136073"))
        ( 9400,   uint256("0x6416592adafe9cfe3ad9696f342de8c7a8d704f3fd0027f7d97ccbf7cc81d04e"))
        ( 9500,   uint256("0x61e2002da2b1770ff7f180c81bc7c7cb9585527122e13c7ebf3c2cac37a2a46d"))
        ( 9600,   uint256("0x6eeb870cfbcfa9efd9b5fcdcf399f65169af42ff8851cf458027d1cd5b7f1c6d"))
        ( 9700,   uint256("0x4020e422e9ca0f8cd30e7c1d14d28f0f580f9e301610d8d8a95345f0c16146b6"))
        ( 9800,   uint256("0xdc4856563ac61366089da2ba2c5a49e42366a704549ab170c8a103d4990bb21c"))
        ( 9900,   uint256("0x5b764ff9862e56343eac681ab5ab3b5c52941623054091cab3532b2b9b08862e"))
        (10000,   uint256("0xb4f907a8904d86a3108cf8c59a2f865187893fe52ccfb2d0112ec229d8bc678a"))
        (10100,   uint256("0x90cb4f2e3be8257a4aae29ffaf5b81188770c9a9f86ed0dcbbcffb4b28e1e17a"))
        (10200,   uint256("0x51bf0672698d45294070c12481757a6d2ff8839f6e1b63c426b7840d6f88ef4c"))
        (10300,   uint256("0xe5c7740ba679fb674908c18b12b3cc22fbf6030090767b683e8749db9b8b35cf"))
        (10400,   uint256("0x219a330abfdf23f9ba5ef8e9c0b120dc9c8d0462ee7460638e693c8b4dc553f4"))
        (10500,   uint256("0x6ffeec4c0ad6f3a10bf2680713d2e01a812631608192cbf968ca70fc9c31aed7"))
        (10600,   uint256("0xdfffab8fb8f8467b4afdd6ef5d5435827c8bab12562e3275c4017a513eb6c2e0"))
        (10700,   uint256("0x22ebf8618612e757220427958e12076411c8bf30db641df7ebc092d9710cc746"))
        (10800,   uint256("0x7b4be022703d0b2268181367d069f67a69a382346b66c8a9577c265738bcfbf5"))
        (10900,   uint256("0xbf4d174a5aae8f06977f2d39d7ec4e450212144199d4b8f572c42e88d78a4098"))
        (11000,   uint256("0x87dcc8385cc48b397ad1343aac70eaa3f051e79b75d49096ac2feb63c214e3ea"))
        (11100,   uint256("0xe70e227ebfe58c3fe1384930c2cd803755ee2baa9d30627287b92e71828de571"))
        (11200,   uint256("0x48750126d8f4534ec2ee178767272b27f4541fd630d98a64e495438e8a68e099"))
        (11300,   uint256("0x168e4a9baf563c2d5be5657eb5dd9f7ad57783d66e6fbd16d739dade143192f1"))
        (11400,   uint256("0x53e919326e7e20ed3b3d8d96ae5b0d2352efb410b995a18b85f2c5f9f97fd1d8"))
        (11500,   uint256("0x800670bd7f2ca4bbc46c33fc943689cf3ca13fb95e31f8627503b626501eeeec"))

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

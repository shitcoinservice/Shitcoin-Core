// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2019 The Shitcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//// * Main network * ////

static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}


static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("0x00000ca4ce4324d11fe3a9f2abadeda5a4caad1620fdf115de8fc176adf9caf7"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1555386789,
    1,
    2
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1555379920,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1555380111,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
     {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        pchMessageStart[0] = 0x8c;
        pchMessageStart[1] = 0xa3;
        pchMessageStart[2] = 0xf3;
        pchMessageStart[3] = 0xfc;
        vAlertPubKey = ParseHex("046808d0db25fc70412eab7f54546f2348376b05a01e0c70888c0327d9707d14ef7e763fb47069e07441c435f710f63f82101105339db8bf1ae11e2647daf735e7");
        nDefaultPort = 4280;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 999999;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 30;
        nTargetSpacing = 1 * 60;
        nMaturity = 9;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 8000000 * COIN;
        nLastPOWBlock = 5000;
        nModifierUpdateBlock = 9999999;
        nZerocoinStartHeight = 5001;
        nAccumulatorStartHeight = 1;
        nZerocoinStartTime = 1555386760;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint


        /*
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *

         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */

        const char* pszTimestamp = "Zelta rudens epicents atrodas Turaida - 2019";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 1546550035 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04970b5dd03f8f86782526be13e95aeb14a3df369311e683b0e9f580e3217aac3b6ee2eac389d3471dbadca1f92d7bd090a59c5f1294cc7ba99ecceccd700612b7") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1555386789;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 19232;
		
	hashGenesisBlock = genesis.GetHash();
          assert(hashGenesisBlock == uint256("7e880814b759209182a7ca55bf905576278e8926993ece448b1b8c1b6194d482"));
          assert(genesis.hashMerkleRoot == uint256("6a9e187e82e4e894b2647b51029d0ba8754a5a310bb7d02f31a3a2ed70ffe073"));
        // SEED NODES //
	

	vSeeds.push_back(CDNSSeedData("seed.shitcoin.cash", "seed1.shitcoin.cash"));
	vSeeds.push_back(CDNSSeedData("seed2.shitcoin.cash", "seed3.shitcoin.cash"));     

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 30);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;  
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "043134177c130f52718ag18888ca572f045e904998b491316cf5d157ac6513efbd512fc2a6e302479g1d84729g74f7142ae9671aec696039f04b02c9a38a736b001";
        strObfuscationPoolDummyAddress = "SHCjpnukBem8zAcGmc6y6ePuny9t6QJmAj";
        nStartMasternodePayments = 1555381010;
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7;
        nMinZerocoinMintFee = 1 * ZCENT;
        nMintRequiredConfirmations = 20;
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100;
        nZerocoinHeaderVersion = 4;
        nBudget_Fee_Confirmations = 3;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/// Testnet parameters ///

class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x43;
        pchMessageStart[1] = 0x71;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xbf;
        vAlertPubKey = ParseHex("04970b5dd03f8f86782526be13e95aeb14a3df369311e683b0e9f580e3217aac3b6ee2eac389d3471dbadca1f92d7bd090a59c5f1294cc7ba99ecceccd700612b7");
        nDefaultPort = 51474;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Shitcoin: 1 day
        nTargetSpacing = 1 * 60;  // Shitcoin: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197;
        nMaxMoneyOut = 8000000 * COIN;
        nZerocoinStartHeight = 201576;
        nZerocoinStartTime = 1524711188;
        nBlockEnforceSerialRange = 1;
        nBlockRecalculateAccumulators = 9908000;
        nBlockFirstFraudulent = 9891737;
        nBlockLastGoodCheckpoint = 9891730;
        
        genesis.nTime = 1555386736;
        genesis.nNonce = 79855;

	hashGenesisBlock = genesis.GetHash();
        ///assert(hashGenesisBlock == uint256(""));

        vFixedSeeds.clear();
        vSeeds.clear();
	vSeeds.push_back(CDNSSeedData("seed.test.shitcoin.cash", "seed1.test.shitcoin.cash"));         

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
        
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2; "0476fcb1fcfbb1b2a2fbba629102689d83dc66c2703d44b1314197ef42e64b6f66b7ec369b6df3d95cf6595c4cdd83907251f4c75d939809dabb17dad3196bf608";
        strObfuscationPoolDummyAddress = "Sp87cds8UvQHzc1B167Yf914C7pnQfAeo7q";
        nStartMasternodePayments = 1420837558;
        nBudget_Fee_Confirmations = 3;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/// Regression test parameters ///
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x66;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0x7l;
        pchMessageStart[3] = 0xa9;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Shitcoin: 1 day
        nTargetSpacing = 1 * 60;        // Shitcoin: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1546087421;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 732084;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51436;

        vFixedSeeds.clear();
        vSeeds.clear();

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/// Unit test ///

class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); 
        vSeeds.clear();

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

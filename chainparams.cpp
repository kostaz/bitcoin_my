#include "chainparams.h"

class CMainParams : public CChainParams
{
public:
	CMainParams()
	{
		pchMessageStart.bytes[0] = 0xf9;
		pchMessageStart.bytes[1] = 0xbe;
		pchMessageStart.bytes[2] = 0xb4;
		pchMessageStart.bytes[3] = 0xd9;
	}

	virtual Network NetworkID() const
	{
		return CChainParams::MAIN;
	}
};

static CMainParams mainParams;

class CTestNetParams : public CChainParams
{
public:
	CTestNetParams()
	{
		pchMessageStart.bytes[0] = 0x0b;
		pchMessageStart.bytes[1] = 0x11;
		pchMessageStart.bytes[2] = 0x09;
		pchMessageStart.bytes[3] = 0x07;
	}

	virtual Network NetworkID() const
	{
		return CChainParams::TESTNET;
	}
};

static CTestNetParams testNetParams;

class CRegTestParams : public CChainParams
{
public:
	CRegTestParams()
	{
		pchMessageStart.bytes[0] = 0xfa;
		pchMessageStart.bytes[1] = 0xbf;
		pchMessageStart.bytes[2] = 0xb5;
		pchMessageStart.bytes[3] = 0xda;
	}

	virtual Network NetworkID() const
	{
		return CChainParams::TESTNET;
	}
};

static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams& Params()
{
	return *pCurrentParams;
}


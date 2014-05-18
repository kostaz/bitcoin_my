#ifndef BITCOIN_CHAIN_PARAMS_H
#define BITCOIN_CHAIN_PARAMS_H

#define MESSAGE_START_SIZE
struct MessageStartChars
{
	unsigned char bytes[MESSAGE_START_SIZE];
};

class CChainParams
{
public:
	enum Network
	{
		MAIN,
		TESTNET,
		REGTEST,
		MAX_NETWORK_TYPES
	};

	const MessageStartChars& MessageStart() const
	{
		return pchMessageStart;
	}

	virtual Network NetworkID() const = 0;

protected:
	CChainParams()
	{
	}

	MessageStartChars pchMessageStart;
};

const CChainParams& Params();

#endif // BITCOIN_CHAIN_PARAMS_H


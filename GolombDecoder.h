#ifndef ICV_GOLOMB_DECODER_H
#define ICV_GOLOMB_DECODER_H

#include "BitStream.h"
#include  "GolombEncoder.h"


class GolombDecoder
{
public:

	GolombDecoder(uint64_t para);

	void setBuffer(uint8_t *buffer, int len);

	BufferState decode(uint64_t& num);
	
	BitInputStream bitStream;

private:
	uint64_t k;
	uint64_t m;
};


GolombDecoder::GolombDecoder(uint64_t para)
{
		k = para;
		m = -1;
}

void GolombDecoder::setBuffer(uint8_t *buffer, int len)
{
	bitStream.setBuffer(buffer, len);
}

BufferState GolombDecoder::decode(uint64_t& num)
{
	auto state = bitStream.check();

	if (state == BufferState::BUFFER_ENGOUGH)
	{
	bool b;
	uint64_t groupID = 0;

	// group id
	b = bitStream.getBit();
	while (!b)
	{
		groupID++;
		b = bitStream.getBit();
	}

	// groupID-1bit
	std::bitset<64> bits;
	bits.reset();
	for (int i = 0; i < groupID; i++)
	{
		b = bitStream.getBit();
		bits.set(i, b);
	}

	num = pow(2, groupID) - 1 + bits.to_ulong();

	if (k != 0)
		num = num - pow(2, k) + 1;
	}

	return state;
}

#endif
#ifndef GOLOMB_ENCODER_H
#define GOLOMB_ENCODER_H

#include "BitStream.h"

class GolombEncoder
{
public:

	GolombEncoder(uint64_t m_);

	bool encode(uint64_t num);

	bool close();

	void resetBuffer();

	void setBuffer(uint8_t *buffer, uint64_t len);

	uint64_t getToalCodeLength()
	{
		return bitStream.getTotalCodeLength();
	}
	
	BitOutputStream bitStream;

private:

	uint64_t m;
	uint64_t k;
};

GolombEncoder::GolombEncoder(uint64_t para)
{
		k = para;
		m = -1;
}

void GolombEncoder::setBuffer(uint8_t *buffer, uint64_t len)
{
	bitStream.setBuffer(buffer, len);
}

void GolombEncoder::resetBuffer()
{
	bitStream.resetBuffer();
}

bool GolombEncoder::encode(uint64_t num)
{
	if (k != 0)
		num = num + pow(2, k) - 1;

	auto m = static_cast<int>(log(num + 1) / log(2)); 
	auto info = static_cast<int>(num + 1 - pow(2, m));

	auto len = 2 * m + 1;

	bitStream.putBit(0, m);

	bitStream.putBit(1);

	for (int i = 0; i < m ; i++)
	{
		bitStream.putBit(static_cast<bool>(info & 0x01));
		info >>= 1;
	}
	
	return bitStream.freeLength() >= len;
}

bool GolombEncoder::close()
{
	return bitStream.flush();
}

#endif
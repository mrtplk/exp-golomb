///////////////////////////////////////////////////////////
// 
// BitBuffer
//
// ByteBuffer
//
// BitOutputStream
//
// BitInputStream
//
//
//////////////////////////////////////////////////////////

#include "BitStream.h"
#include <iostream>

///////////////////////////////////////////////////
// 
// Bit Buffer
//
//////////////////////////////////////////////////

BitBuffer::BitBuffer()
{
	data.set();
	data.flip();
	pos = 0;
	count = 0;
}


bool BitBuffer::getBit()
{
	bool b = data[0];
	count--;
	data >>= 1;
	return b;
}

uint8_t BitBuffer::getByte()
{
	uint8_t b = static_cast<uint8_t>(data.to_ulong());
	count -= 8;
	pos -= 8;
	data >>= 8;
	return b;
}

void BitBuffer::putBit(bool b)
{
	data.set(pos, b);
	pos++;
	count++;
}

void BitBuffer::putByte(uint8_t b)
{
	/*data <<= 8;
	data |= b;
	pos += 8;
	count += 8;*/

	uint64_t tmp = (b << count);
	data |= tmp;
	count += 8;
	pos += 8;
}

///////////////////////////////////////////////////
// 
// Byte Buffer
//
//////////////////////////////////////////////////

ByteBuffer::ByteBuffer()
{
	data = nullptr;
	pos = 0;
	length = 0;
	totalLength = 0;
}

uint8_t ByteBuffer::getByte()
{
	auto b = data[pos];
	pos++;
	return b;
}

void ByteBuffer::putByte(uint8_t b)
{
	data[pos] = b;
	pos++;
	totalLength++;
}

void ByteBuffer::setData(uint8_t *buffer, int len)
{
	data = buffer;
	length = len;
}

///////////////////////////////////////////////////
//
// BitOutputStream
//
//////////////////////////////////////////////////

void BitOutputStream::setBuffer(uint8_t *buffer, int len)
{
	bytes.setData(buffer, len);
}

void BitOutputStream::resetBuffer()
{
	bytes.pos = 0;
}

void BitOutputStream::putBit(bool b)
{
	while(bits.count >= 8 && bytes.pos < bytes.length)
	{
		auto b = bits.getByte();
		bytes.putByte(b);
	}

	bits.putBit(b);
}

void BitOutputStream::putBit(bool b, int num)
{
	for (int i = 0; i < num; i++)
		putBit(b);
}

uint64_t BitOutputStream::freeLength()
{
	return (bytes.length - bytes.pos) * 8 - bits.count;
}

bool BitOutputStream::flush()
{
	if (bits.count > 0)
	{
		auto b = bits.getByte();
		bytes.putByte(b);
	}
	
	for (int i = 0; i < 8; i++)
		bytes.putByte(0x00);

	auto remainder = bytes.totalLength % 8;
	if (remainder != 0)
	{
		for (int i = remainder; i < 8; i++)
			bytes.putByte(0x00);
	}
	std::cout << bytes.totalLength << std::endl;
	return true;
}

///////////////////////////////////////////////
//
// BitInputStream
//
//////////////////////////////////////////////

void BitInputStream::setBuffer(uint8_t *buffer, int len)
{
	bytes.data = buffer;
	bytes.length = len;
}

bool BitInputStream::getBit()
{
	bool b;
	if (bits.count <= 0)
	{
		auto c = bytes.getByte();
		bits.putByte(c);
	}

	b = bits.getBit();

	return b;
}

BufferState BitInputStream::check()
{
	if (bits.count <= 0 && bytes.pos >= bytes.length)
		return BufferState::BUFFER_EMPTY;

	auto count = (bytes.length - bytes.pos) * 8 + bits.count;

	if (count >= 64)
	{
		if (bits.count >= 64)
		{
			if (bits.data.none()) // 64 bits 0
				return BufferState::BUFFER_END_SYMBOL;
			else
				return BufferState::BUFFER_ENGOUGH;
		}
		
		else
		{

			if (!bits.data.none())
				return BufferState::BUFFER_ENGOUGH;

			int count = ((64 - bits.count) / 8 + 1);
			int index = 0;
			while (index < count)
			{
				auto b = bytes.data[bytes.pos + index];
				index++;
				if (b != 0)
					return BufferState::BUFFER_ENGOUGH;
			}

			return BUFFER_END_SYMBOL;
		}
	}

	else
	{
		while (bytes.pos < bytes.length)
		{
			auto b = bytes.getByte();
			bits.putByte(b);
		}
		return BufferState::BUFFER_LACK;
	}
}
#include "BitArray.h"
#include <assert.h>
#include <string.h>
#include <intrin.h>
#include "HeapManager.h"

BitArray * BitArray::CreateBitArray(size_t i_numBits, bool i_bInitToZero, HeapManager * heapAllocator)
{
	BitArray * newBitArray = static_cast<BitArray *>(heapAllocator->_alloc(sizeof(BitArray)));
	const size_t bitsPerBlock = sizeof(BLOCK) * 8; //8 = bits per byte
	newBitArray->m_blockLength = i_numBits / bitsPerBlock;
	if (i_numBits % bitsPerBlock > 0) //round up
		newBitArray->m_blockLength++;
	newBitArray->m_pBits = static_cast<BLOCK *>(heapAllocator->_alloc(sizeof(BLOCK) * newBitArray->m_blockLength));
		//new BLOCK[m_blockLength];
	assert(newBitArray->m_pBits);
	memset(newBitArray->m_pBits, i_bInitToZero ? 0x00 : 0xFF, sizeof(BLOCK) * newBitArray->m_blockLength);
	newBitArray->m_numBits = i_numBits;
	return newBitArray;
}

BitArray::~BitArray()
{
	//need changing into heapmanager
	if (m_pBits)
		delete m_pBits;
	m_pBits = nullptr;
}

void BitArray::ClearAll(void)
{
	assert(m_pBits);
	memset(m_pBits, 0, m_blockLength);
}

void BitArray::SetAll(void)
{
	assert(m_pBits);
	memset(m_pBits, 1, m_blockLength);
}

bool BitArray::AreAllClear(void) const
{
	const size_t bitsPerBlock = sizeof(BLOCK) * 8;
	unsigned int bitArrayEnd = m_numBits % bitsPerBlock;

	for (unsigned int i = 0; i < m_blockLength - (bitArrayEnd == 0 ? 0 : 1); ++i)
	{
		if (m_pBits[i] != 0)
			return false;
	}
	for (unsigned int i = 0; i < bitArrayEnd; ++i)
	{
#ifdef WIN32
		if (_bittest(reinterpret_cast<long *>(&m_pBits[m_blockLength - 1]), i))
#else
		if (_bittest64(reinterpret_cast<long long *>(&m_pBits[m_blockLength - 1]), i))
#endif // WIN32
			return false;
	}
	return true;
}

bool BitArray::AreAllSet(void) const
{
	const size_t bitsPerBlock = sizeof(BLOCK) * 8;
	unsigned int bitArrayEnd = m_numBits % bitsPerBlock;

	for (unsigned int i = 0; i < m_blockLength - (bitArrayEnd == 0 ? 0 : 1); ++i)
	{
		if (m_pBits[i] != 1)
			return false;
	}
	for (unsigned int i = 0; i < bitArrayEnd; ++i)
	{
#ifdef WIN32
		if (!_bittest(reinterpret_cast<long *>(&m_pBits[m_blockLength - 1]), i))
#else
		if (!_bittest64(reinterpret_cast<long long *>(&m_pBits[m_blockLength - 1]), i))
#endif // WIN32
			return false;
	}
	return true;
}



void BitArray::SetBit(size_t i_bitNumber)
{
	assert(i_bitNumber < m_numBits);
	const size_t bitsPerBlock = sizeof(BLOCK) * 8;
#ifdef WIN32
	_bittestandset(reinterpret_cast<long *>(&m_pBits[i_bitNumber / bitsPerBlock]), i_bitNumber % bitsPerBlock);
#else
	_bittestandset64(reinterpret_cast<long long *>(&m_pBits[i_bitNumber / bitsPerBlock]), i_bitNumber % bitsPerBlock);
#endif
}

void BitArray::ClearBit(size_t i_bitNumber)
{
	assert(i_bitNumber < m_numBits);
	const size_t bitsPerBlock = sizeof(BLOCK) * 8;
#ifdef WIN32
	_bittestandreset(reinterpret_cast<long *>(&m_pBits[i_bitNumber / bitsPerBlock]), i_bitNumber % bitsPerBlock);
#else
	_bittestandreset64(reinterpret_cast<long long *>(&m_pBits[i_bitNumber / bitsPerBlock]), i_bitNumber % bitsPerBlock);
#endif
}

bool BitArray::GetFirstClearBit(unsigned long & o_bitNumber) const
{
	size_t index = 0;
	while (m_pBits[index] == 1 && index < m_blockLength)
		index++;
	if (index == m_blockLength)
		return false;
	BLOCK block = m_pBits[index];
	BLOCK i = 0;
	for (i = 0; i < sizeof(BLOCK) * 8; ++i)
	{
#ifdef WIN32
		if ((block & (1U << i)) == 0)
#else
		if ((block & (1ULL << i)) == 0)
#endif // WIN32
			break;
	}
	o_bitNumber = index * sizeof(BLOCK) * 8 + i;
	return true;
}

bool BitArray::GetFirstSetBit(unsigned long & o_bitNumber) const
{
	unsigned char isNonZero;
	const size_t bitsPerBlock = sizeof(BLOCK) * 8;
	size_t index = 0;
	while ((m_pBits[index] == 0) && (index < m_blockLength))
		index++;

#ifdef WIN32
	isNonZero = _BitScanForward(&o_bitNumber, m_pBits[index]);
#else
	isNonZero = _BitScanForward64(&o_bitNumber, m_pBits[index]);
#endif
	o_bitNumber = index * bitsPerBlock + o_bitNumber;
	if (!isNonZero || o_bitNumber >= m_numBits) //all zero or the found bit is beyond the array
		return false;
	else
		return true;
}

bool BitArray::operator[](size_t i_index) const
{
	assert(i_index < m_numBits);
	const size_t bitsPerBlock = sizeof(BLOCK) * 8;
#ifdef WIN32
	return _bittest(reinterpret_cast<long *>(&m_pBits[i_index / bitsPerBlock]), i_index % bitsPerBlock);
#else
	return _bittest64(reinterpret_cast<long long *>(&m_pBits[i_index / bitsPerBlock]), i_index % bitsPerBlock);
#endif
}

#pragma once
#include <stdint.h>
#ifdef WIN32
#define BLOCK uint32_t
#else
#define BLOCK uint64_t
#endif
class HeapManager;
class BitArray
{
public:
	static BitArray * CreateBitArray(size_t i_numBits, bool i_bInitToZero, HeapManager * heapAllocator);
	~BitArray();
	void ClearAll(void);
	void SetAll(void);

	bool AreAllClear(void) const;
	bool AreAllSet(void) const;

	inline bool IsBitSet(size_t i_bitNumber) const;
	inline bool IsBitClear(size_t i_bitNumber) const;

	void SetBit(size_t i_bitNumber);
	void ClearBit(size_t i_bitNumber);

	bool GetFirstClearBit(unsigned long & o_bitNumber) const;
	bool GetFirstSetBit(unsigned long & o_bitNumber) const;

	bool operator[](size_t i_index) const;

private:
	size_t m_numBits;
	size_t m_blockLength;
	BLOCK * m_pBits;
};

inline bool BitArray::IsBitSet(size_t i_bitNumber) const
{
	return operator[] (i_bitNumber);
}

inline bool BitArray::IsBitClear(size_t i_bitNumber) const
{
	return !operator[] (i_bitNumber);
}

#include "janHash.h"

#include <limits.h>
#include <sstream>
#include <iomanip>

uint32_t rotl32(uint32_t value, int count)
{
	const unsigned int mask = CHAR_BIT * sizeof(value) - 1;
	count &= mask;
	return (value << count) | (value >> (-count & mask));
}

uint32_t _4byte_string_to_uint32_t(string data)
{
	if (data.length() == 4)
	{
		return (uint32_t)data[0] | (uint32_t)(data[1] << 8) | (uint32_t)(data[2] << 16) | (uint32_t)(data[3] << 24);
	}
	else
	{
		cout << "Error converting string to uint32_t. String is too long or too short.";
		return 0x0;
	}
}

uint32_t F(const uint32_t X, const uint32_t Y, const uint32_t Z)
{
	//If X then Y else Z.
	return (((X) & (Y)) | ((~X) & (Z)));
}

uint32_t G(const uint32_t X, const uint32_t Y, const uint32_t Z)
{
	return (((X) & (Y)) | ((X) & (Z)) | ((Y) & (Z)));
}

uint32_t H(const uint32_t X, const uint32_t Y, const uint32_t Z)
{
	return ((X) ^ (Y) ^ (Z));
}

void FF(uint32_t &a, const uint32_t b, const uint32_t c, const uint32_t d, const uint32_t k, int s)
{
	a = (a + F(b, c, d) + k);
	a = rotl32(a, s);
}

void GG(uint32_t &a, const uint32_t b, const uint32_t c, const uint32_t d, const uint32_t k, int s)
{
	a = (a + G(b, c, d) + k + 0x5a827999);
	a = rotl32(a, s);
}

void HH(uint32_t &a, const uint32_t b, const uint32_t c, const uint32_t d, const uint32_t k, int s)
{
	a = (a + H(b, c, d) + k + 0x6ed9eba1);
	a = rotl32(a, s);
}

string janHash(string data)
{

	//Padding + appending dataLength
	string dataLength = std::to_string((int)data.length());
	data.append(64 - data.length() % 64, '\0');
	data.append(64 - dataLength.length(), '\0');
	data.append(dataLength);

	uint32_t buffer[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};

	for (int i = 0; i < data.length() / 64; i++)
	{
		uint32_t block[16];
		for (int j = 0; j < 16; j++)
		{
			block[j] = _4byte_string_to_uint32_t(data.substr(64 * i + 4 * j, 4));
		}

		uint32_t A = buffer[0], B = buffer[1], C = buffer[2], D = buffer[3];

		/*
		Round 1.

		Let [abcd k s] denote the operation
			a = (a + F(b,c,d) + X[k]) <<< s.
			Do the following 16 operations.
		[ABCD  0  3][DABC  1  7][CDAB  2 11][BCDA  3 19]
		[ABCD  4  3][DABC  5  7][CDAB  6 11][BCDA  7 19]
		[ABCD  8  3][DABC  9  7][CDAB 10 11][BCDA 11 19]
		[ABCD 12  3][DABC 13  7][CDAB 14 11][BCDA 15 19]
		*/

		FF(A, B, C, D, block[0], 3);
		FF(D, A, B, C, block[1], 7);
		FF(C, D, A, B, block[2], 11);
		FF(B, C, D, A, block[3], 19);

		FF(A, B, C, D, block[4], 3);
		FF(D, A, B, C, block[5], 7);
		FF(C, D, A, B, block[6], 11);
		FF(B, C, D, A, block[7], 19);

		FF(A, B, C, D, block[8], 3);
		FF(D, A, B, C, block[9], 7);
		FF(C, D, A, B, block[10], 11);
		FF(B, C, D, A, block[11], 19);

		FF(A, B, C, D, block[12], 3);
		FF(D, A, B, C, block[13], 7);
		FF(C, D, A, B, block[14], 11);
		FF(B, C, D, A, block[15], 19);

		/*
		Round 2.

		Let [abcd k s] denote the operation
			a = (a + G(b,c,d) + X[k] + 5A827999) <<< s.
			Do the following 16 operations.
		[ABCD  0  3][DABC  4  5][CDAB  8  9][BCDA 12 13]
		[ABCD  1  3][DABC  5  5][CDAB  9  9][BCDA 13 13]
		[ABCD  2  3][DABC  6  5][CDAB 10  9][BCDA 14 13]
		[ABCD  3  3][DABC  7  5][CDAB 11  9][BCDA 15 13]

		*/

		GG(A, B, C, D, block[0], 3);
		GG(D, A, B, C, block[4], 5);
		GG(C, D, A, B, block[8], 9);
		GG(B, C, D, A, block[12], 13);

		GG(A, B, C, D, block[1], 3);
		GG(D, A, B, C, block[5], 5);
		GG(C, D, A, B, block[9], 9);
		GG(B, C, D, A, block[13], 13);

		GG(A, B, C, D, block[2], 3);
		GG(D, A, B, C, block[6], 5);
		GG(C, D, A, B, block[10], 9);
		GG(B, C, D, A, block[14], 13);

		GG(A, B, C, D, block[3], 3);
		GG(D, A, B, C, block[7], 5);
		GG(C, D, A, B, block[11], 9);
		GG(B, C, D, A, block[15], 13);

		/* Round 3.
		Let [abcd k s] denote the operation
				a = (a + H(b,c,d) + X[k] + 6ED9EBA1) <<< s.
				Do the following 16 operations.
		[ABCD  0  3][DABC  8  9][CDAB  4 11][BCDA 12 15]
		[ABCD  2  3][DABC 10  9][CDAB  6 11][BCDA 14 15]
		[ABCD  1  3][DABC  9  9][CDAB  5 11][BCDA 13 15]
		[ABCD  3  3][DABC 11  9][CDAB  7 11][BCDA 15 15]

		*/

		HH(A, B, C, D, block[0], 3);
		HH(D, A, B, C, block[8], 3);
		HH(C, D, A, B, block[4], 3);
		HH(B, C, D, A, block[12], 3);

		HH(A, B, C, D, block[2], 9);
		HH(D, A, B, C, block[10], 9);
		HH(C, D, A, B, block[6], 9);
		HH(B, C, D, A, block[14], 9);

		HH(A, B, C, D, block[1], 11);
		HH(D, A, B, C, block[9], 11);
		HH(C, D, A, B, block[5], 11);
		HH(B, C, D, A, block[13], 11);

		HH(A, B, C, D, block[3], 15);
		HH(D, A, B, C, block[11], 15);
		HH(C, D, A, B, block[7], 15);
		HH(B, C, D, A, block[15], 15);
		;

		buffer[0] += A;
		buffer[1] += B;
		buffer[2] += C;
		buffer[3] += D;
	}

	std::stringstream stream;
	for (int i = 0; i < 4; i++)
	{
		stream << std::hex << std::setw(8) << std::setfill('0') << buffer[i];
	}
	std::string result(stream.str());
	return result;
}

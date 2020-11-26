#include "main.h"
string sha256(string &x)
{
  // holds the padded blocks
  vector<ZZ> blocks;
  makeBlocks(blocks, x);

  // holds values for the compression stage of sha256
  vector<long> registers(8, 0);

  // initialize registers with first 8 constants
  for (int i = 0; i < 8; i++)
    registers[i] = makeConstant(i);

  for (int i = 0; i < blocks.size(); i++)
    processBlock(registers, blocks[i]);

  // final concatenated value to be returned
  ZZ retVal;

  for (int i = 0; i < 8; i++)
  {
    retVal <<= 32;
    retVal += registers[i];
  }

  return toHex(retVal);
}

long makeConstant(int n)
{
  static unsigned short primes[] = {2,
                                    3,
                                    5,
                                    7,
                                    11,
                                    13,
                                    17,
                                    19,
                                    23,
                                    29,
                                    31,
                                    37,
                                    41,
                                    43,
                                    47,
                                    53,
                                    59,
                                    61,
                                    67,
                                    71,
                                    73,
                                    79,
                                    83,
                                    89,
                                    97,
                                    101,
                                    103,
                                    107,
                                    109,
                                    113,
                                    127,
                                    131,
                                    137,
                                    139,
                                    149,
                                    151,
                                    157,
                                    163,
                                    167,
                                    173,
                                    179,
                                    181,
                                    191,
                                    193,
                                    197,
                                    199,
                                    211,
                                    223,
                                    227,
                                    229,
                                    233,
                                    239,
                                    241,
                                    251,
                                    257,
                                    263,
                                    269,
                                    271,
                                    277,
                                    281,
                                    283,
                                    293,
                                    307,
                                    311};

  return (long)(power_long(2, 32) * (sqrtl(primes[n]) - (int)sqrt(primes[n])));
}

void makeBlocks(vector<ZZ> &blocks, string &x)
{
  ZZ digest;
  ZZFromBytes(digest, (unsigned char *)x.c_str(), x.length());
  digest <<= 1;
  digest += 1;

  // the length of current digest and required padding is calculated
  long numBits = NumBits(digest);
  long padding = (512 * ceil(numBits / 512.0)) - numBits;

  // digest is padded to a multiple of 512
  digest <<= padding;

  // length of message is appended at the end of the block
  digest |= trunc_ZZ(Z(x.length() * 8), padding);

  // break up the digest into blocks
  int len = (numBits + padding) / 512;
  blocks.resize(len);
  for (int i = len - 1; i >= 0; i--)
  {
    blocks[i] = trunc_ZZ(digest, 512);
    digest >>= 512;
  }
}

void processBlock(vector<long> &reg, ZZ &block)
{
  long schedule[64];
  initSchedule(schedule, block);

  long initState[8];
  copy(reg.begin(), reg.end(), initState);

  for (int i = 0; i < 64; i++)
  {
    long W = schedule[i];
    long K = makeConstant(i);
    long T1 = trunc_long(Z(big_sig1(reg[4]) + choice(reg[4], reg[5], reg[6]) + reg[7] + K + W), 32);
    long T2 = trunc_long(Z(big_sig0(reg[0]) + maj(reg[0], reg[1], reg[2])), 32);

    reg.pop_back();
    reg.insert(reg.begin(), trunc_long(Z(T1 + T2), 32));
    reg[4] = trunc_long(Z(reg[4] + T1), 32);
  }

  for (int i = 0; i < 8; i++)
    reg[i] = trunc_long(Z(reg[i] + initState[i]), 32);
}

void initSchedule(long *schedule, ZZ &block)
{
  for (int i = 15; i >= 0; i--)
  {
    schedule[i] = trunc_long(block, 32);
    block >>= 32;
  }

  int idx = 16;

  while (idx < 64)
  {
    schedule[idx] = (small_sig1(schedule[idx - 2]) + schedule[idx - 1] + small_sig0(schedule[idx - 15]) + schedule[idx - 16]) % power_long(2, 32);
    idx++;
  }
}
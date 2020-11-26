#include "main.h"

long rotr(long &val, int n)
{
  return (trunc_long(Z(val), n) << (32 - n)) | (val >> n);
}

long shr(long &val, int n)
{
  return val >> n;
}

void choice(long &ans, long &c, long &x, long &y)
{
}

long choice(long &c, long &x, long &y)
{
  long neg = 0xFFFFFFFF ^ c;

  return (c & x) | (neg & y);
}

long small_sig0(long &x)
{
  return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3);
}

long small_sig1(long &x)
{
  return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10);
}

long big_sig0(long &x)
{
  return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

long big_sig1(long &x)
{
  return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

string sha256(string &x)
{
  // holds the padded blocks
  vector<ZZ> blocks;
  makeBlocks(blocks, x);

  // holds values for the compression stage of sha256
  vector<long> registers(8);

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

void processBlock(vector<long> &registers, ZZ &block)
{
  long schedule[64];
  initSchedule(schedule, block);
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

string toHex(long x)
{
  return toHex(Z(x));
}

string toHex(ZZ x)
{
  char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  string retVal = "";
  long iter = NumBits(x) / 4;

  for (int i = 0; i < iter; i++)
  {
    retVal = digits[x % 16] + retVal;
    x >>= 4;
  }

  if (x > 0)
    retVal = digits[x % 16] + retVal;

  return retVal;
}

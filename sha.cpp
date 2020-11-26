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

  // convert text to blocks
  makeBlocks(blocks, x);

  // holds values for the compression stage of sha256
  vector<long> registers;

  // fractional parts of the first 8 prime numbers as starting registers
  registers.push_back(1779033703);
  registers.push_back(3144134277);
  registers.push_back(1013904242);
  registers.push_back(2773480762);
  registers.push_back(1359893119);
  registers.push_back(2600822924);
  registers.push_back(528734635);
  registers.push_back(1541459225);

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

void makeBlocks(vector<ZZ> &blocks, string &x)
{
  ZZ digest;
  ZZFromBytes(digest, (unsigned char *)x.c_str(), x.length());

  long numBits = NumBits(digest);
  long padding = (512 * ceil(numBits / 512.0)) - numBits;
  digest <<= padding;
  digest |= trunc_ZZ(Z(x.length() * 8), padding);

  for (int i = 0; i < ((numBits + padding) / 512); i++)
  {
    blocks.push_back(trunc_ZZ(digest, 512));
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

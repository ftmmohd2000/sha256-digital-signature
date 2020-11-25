#include "main.h"

inline void rotr(ZZ &ans, ZZ &val, int n)
{
  ans = LeftShift(trunc_ZZ(val, n), 32 - n) | RightShift(val, n);
}

ZZ rotr(ZZ &val, int n)
{
  ZZ retVal;
  rotr(retVal, val, n);
  return retVal;
}

inline void shr(ZZ &ans, ZZ &val, int n)
{
  ans = val >> n;
}

ZZ shr(ZZ &val, int n)
{
  ZZ retVal;
  shr(retVal, val, n);
  return retVal;
}

void choice(ZZ &ans, ZZ &c, ZZ &x, ZZ &y)
{
  ZZ neg = 0xFFFFFFFF ^ c;

  ans = (c & x) | (neg & y);
}

ZZ choice(ZZ &c, ZZ &x, ZZ &y)
{
  ZZ retVal;
  choice(retVal, c, x, y);
  return retVal;
}

inline void small_sig0(ZZ &ans, ZZ &x)
{
  ans = rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3);
}

ZZ small_sig0(ZZ &x)
{
  ZZ retVal;
  small_sig0(retVal, x);
  return retVal;
}

inline void small_sig1(ZZ &ans, ZZ &x)
{
  ans = rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10);
}

ZZ small_sig1(ZZ &x)
{
  ZZ retVal;
  small_sig1(retVal, x);
  return retVal;
}

void big_sig0(ZZ &ans, ZZ &x)
{
  ans = rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

ZZ big_sig0(ZZ &x)
{
  ZZ retVal;
  big_sig0(retVal, x);
  return retVal;
}

void big_sig1(ZZ &ans, ZZ &x)
{
  ans = rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

ZZ big_sig1(ZZ &x)
{
  ZZ retVal;
  big_sig1(retVal, x);
  return retVal;
}

ZZ sha256(string x)
{
  // holds values for the compression stage of sha256
  vector<ZZ> registers;

  // hold the blocks containing the digest
  vector<ZZ> blocks;

  makeBlocks(blocks, x);

  // fractional parts of the first 8 prime numbers as starting registers
  registers.push_back(Z(1779033703));
  registers.push_back(Z(3144134277));
  registers.push_back(Z(1013904242));
  registers.push_back(Z(2773480762));
  registers.push_back(Z(1359893119));
  registers.push_back(Z(2600822924));
  registers.push_back(Z(4823701931));
  registers.push_back(Z(5836426521));

  while (!blocks.empty())
  {
    processBlock(registers, blocks[0]);
    blocks.pop_back();
  }

  // final concatenated value to be returned
  ZZ retVal;

  while (!registers.empty())
  {
    retVal <<= 32;
    retVal = retVal + registers[0];
    registers.pop_back();
  }

  return retVal;
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
    ZZ temp = digest;
    blocks.push_back(trunc_ZZ(temp,512));
    digest >>= 512;
  }
}

void processBlock(vector<ZZ> &registers, ZZ &block)
{

}
#include "main.h"

long maj(long &a, long &b, long &c)
{
  unsigned long ret = a;
  if (b > ret)
    ret = b;
  if (c > ret)
    ret = c;

  return ret;
}

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

string toBin(long x)
{
  return toBin(Z(x));
}

string toBin(ZZ x)
{
  string retVal = "";
  for (int i = 0; i < 32; i++)
  {
    retVal += IsOdd(x) ? '1' : '0';
    x >>= 1;
  }
  return retVal;
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

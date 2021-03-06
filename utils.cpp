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

ZZ ZZFromHex(string x)
{
  ZZ retVal;
  for (const char c : x)
  {
    retVal <<= 4;
    switch (c)
    {
    case '0':
      retVal |= 0;
      break;
    case '1':
      retVal |= 1;
      break;
    case '2':
      retVal |= 2;
      break;
    case '3':
      retVal |= 3;
      break;
    case '4':
      retVal |= 4;
      break;
    case '5':
      retVal |= 5;
      break;
    case '6':
      retVal |= 6;
      break;
    case '7':
      retVal |= 7;
      break;
    case '8':
      retVal |= 8;
      break;
    case '9':
      retVal |= 9;
      break;
    case 'a':
      retVal |= 10;
      break;
    case 'b':
      retVal |= 11;
      break;
    case 'c':
      retVal |= 12;
      break;
    case 'd':
      retVal |= 13;
      break;
    case 'e':
      retVal |= 14;
      break;
    case 'f':
      retVal |= 15;
      break;
    }
  }

  return retVal;
}
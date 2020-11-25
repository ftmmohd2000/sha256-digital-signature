#include "main.h"

inline void encrypt(ZZ &ct, ZZ &pt, ZZ &e, ZZ &n)
{
  PowerMod(ct, pt, e, n);
}

inline void decrypt(ZZ &pt, ZZ &ct, ZZ &d, ZZ &n)
{
  PowerMod(pt, ct, d, n);
}

void genPair(ZZ &p, ZZ &q, long numBits)
{
  GenPrime(p, numBits);
  GenPrime(q, numBits);
}

void genKeys(ZZ &e, ZZ &d, ZZ &totient, ZZ &p, ZZ &q)
{
  e = 65537;
  totient = (p - 1) * (q - 1);
  InvMod(d,e,totient);
}

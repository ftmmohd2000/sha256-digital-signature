#include "main.h"

void sign(ZZ &ct, ZZ &pt, ZZ &priv, ZZ &n)
{
  PowerMod(ct, pt, priv, n);
}

bool verify(string &message, ZZ &signature, ZZ &pub, ZZ &n)
{
  string hashedMsg = sha256(message);
  ZZ hash = ZZFromHex(hashedMsg);
  ZZ plaintext;
  PowerMod(plaintext, signature, pub, n);
  return (plaintext == hash);
}

void genKeys(ZZ &e, ZZ &d, ZZ &N, long primeBitLength)
{
  ZZ p, q;
  GenPrime(p, primeBitLength);
  GenPrime(q, primeBitLength);
  e = 65537;
  N = p * q;
  InvMod(d, e, (p - 1) * (q - 1));
}

#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <NTL/ZZ.h>
#include <time.h>
#define Z to_ZZ

NTL_CLIENT

#ifndef RSA_H
#define RSA_H

void encrypt(ZZ &ct, ZZ &pt, ZZ &e, ZZ &n);
void decrypt(ZZ &pt, ZZ &ct, ZZ &d, ZZ &n);
void genPair(ZZ &p, ZZ &q, long numBits = 400);
void genKeys(ZZ &e, ZZ &d, ZZ &totient, ZZ &p, ZZ &q);

#endif

#ifndef SHA_H
#define SHA_H

void rotr(ZZ &ans, ZZ &val, int n);
ZZ rotr(ZZ &val, int n);

void shr(ZZ &ans, ZZ &val, int n);
ZZ shr(ZZ &val, int n);

void choice(ZZ &ans, ZZ &c, ZZ &x, ZZ &y);
ZZ choice(ZZ &c, ZZ &x, ZZ &y);

void small_sig0(ZZ &ans, ZZ &x);
ZZ small_sig0(ZZ &x);

void small_sig1(ZZ &ans, ZZ &x);
ZZ small_sig1(ZZ &x);

void big_sig0(ZZ &ans, ZZ &x);
ZZ big_sig0(ZZ &x);

void big_sig1(ZZ &ans, ZZ &x);
ZZ big_sig1(ZZ &x);

string sha256(string &s);

void makeBlocks(vector<ZZ> &blocks,string &x);
void processBlock(vector<long> &registers, ZZ &block);

string toHex(ZZ &T);

#endif
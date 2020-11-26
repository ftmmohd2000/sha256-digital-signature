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

long rotr(long &val, int n);
long shr(long &val, int n);
long choice(long &c, long &x, long &y);
long small_sig0(long &x);
long small_sig1(long &x);
long big_sig0(long &x);
long big_sig1(long &x);

string sha256(string &s);

void initSchedule(long *schedule, ZZ &block);
void makeBlocks(vector<ZZ> &blocks,string &x);
void processBlock(vector<long> &registers, ZZ &block);

string toHex(long T);
string toHex(ZZ T);

#endif
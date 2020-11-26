#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <NTL/ZZ.h>
#include <time.h>
#define Z to_ZZ

NTL_CLIENT

#ifndef PROJECT_H
#define PROJECT_H

void sign(ZZ &ct, ZZ &pt, ZZ &priv, ZZ &n);
bool verify(string &message, ZZ &signature, ZZ &pub, ZZ &n);
void genKeys(ZZ &e, ZZ &d, ZZ &N, long numBits = 400);

long maj(long &a, long &b, long &c);
long rotr(long &val, int n);
long shr(long &val, int n);
long choice(long &c, long &x, long &y);
long small_sig0(long &x);
long small_sig1(long &x);
long big_sig0(long &x);
long big_sig1(long &x);

string sha256(string &s);

long makeConstant(int n);
void initSchedule(long *schedule, ZZ &block);
void makeBlocks(vector<ZZ> &blocks,string &x);
void processBlock(vector<long> &registers, ZZ &block);

string toBin(long x);
string toBin(ZZ x);
string toHex(long x);
string toHex(ZZ x);
ZZ ZZFromHex(string x);
#endif
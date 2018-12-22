#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <algorithm>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

// debugging stuff {{{
#ifdef DEBUG
  #define bDebug 1
  #define bDebug2 0
#else
  #define bDebug 0
  #define bDebug2 0
#endif
#define deb(a) #a << "=" << (a) << " "
#ifndef HOME
  #define assert(a) {}
#endif

template<class T> ostream& operator<<(ostream& os, vector<T> v) //{{{
{
  for(int i=0; i<v.size(); i++)
    os << v[i] << " ";
  os << endl;
  return os;
}  //}}}
// }}} end of debugging stuff

//c++11
#define typeof __typeof__

#define array(a, type, count) type *a = (type*)calloc(sizeof(type), count)
#define eps 1e-9
#define eq(a, b) ( (a) > (b) - eps && (a) < (b) + eps )
#define eraseAll(v) v.erase(v.begin(), v.end())
#define fi first
#define rep(i,n) for(long i=0; i<(n); i++)
#define rep2(i,a,b) for(long i=(a); i<=(b); i++)
#define rep2d(i,a,b) for(long i=(a); i>=(b); i--)
#define zeroMem(a) memset(a, 0, sizeof(a))
#define zeroMem2(a, n) memset(a, 0, sizeof(*a) * n)
#define fore(it,L) for(typeof(L.begin()) it=L.begin(); it!=L.end(); it++)
#define eraseAll(v) v.erase(v.begin(), v.end())
#define se second
#define setMin(a,b) { typeof(a) rv = (b); if (rv < a) a = rv; }
#define setMinP(a,b) { typeof(a) rv = (b); \
                       if (rv >= 0 && (a < 0 || rv < a)) a = rv; }
#define setMax(a,b) { typeof(a) rv = (b); if (rv > a) a = rv; } 
#define swap(a,b) { typeof(a) swapVar = a; a = b; b = swapVar; }
#define Int long long

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(suppress : 4996)

//*********************** SOLUTION    ******************************
#define N 20000000L
#define A 27
#define C 2
Int asum1[C];
Int asum2[C];
Int ap[C] = { 179426173LL, 179426363LL };
Int apot[C];

int main (int argc, char **args)
{
  #ifdef HOME
  if (argc > 1) {
    freopen("testy/pal/0", "r", stdin);
  }
  #endif
  cin.sync_with_stdio(false);
  cout.sync_with_stdio(false);
  char buf[50];
  scanf("%s", buf);
  rep(i, C) {
    asum1[i] = asum2[i] = (Int)0;
    apot[i] = 1;
  }
  long n = 0;
  while (true) {
    char ch;
    if (scanf("%c", &ch) != 1)
      break;
    if (!(ch >= 'a' && ch <= 'z'))
      continue;
    Int d = ch - 'a';
    n++;
    rep(i, C) {
      asum1[i] = (asum1[i] * A + d) % ap[i];
      asum2[i] = (apot[i] * d + asum2[i]) % ap[i];
      apot[i] = (apot[i] * A) % ap[i];
    }
  }
  bool ok = true;
  rep(i, C) {
    if (asum1[i] != asum2[i])
      ok = false;
  }
  cout << (ok ? "TAK" : "NIE") << endl;
}

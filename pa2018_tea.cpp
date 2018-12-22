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

#ifdef MIKROSOFT
#define typeof decltype
#else
//c++11
#define typeof __typeof__
#endif

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
#pragma warning(disable : 4996)

//*********************** SOLUTION    ******************************
#define M 1000010
#define N 2500000L
long ac[2][M];
long *ad[2];
long nGlobal = 0;
bool wczytane = false;
Int resGlobal = 0;
Int cop = 0;

//#define INPUTSTDIN
//#define SINGLEINSTANCE
#define TYLKODUZE false

#ifdef INPUTSTDIN
  long ain[N];
  void wczytaj() {
    cin >> nGlobal;
    rep(i, nGlobal)
      cin >> ain[i];
  }
  long myGetN() {
    if (!wczytane) {
      wczytane = true;
      wczytaj();
    }
    return nGlobal;
  }
  long myGetElem(long i) { return ain[i]; }
#else
  unsigned long long mge_n, mge_type, mge_a, mge_b, mge_mod, mge_mul;
  bool initDone = false;
  void init() {
    if (!initDone) {
      //cin >> n >> type >> a >> b >> mod >> mul;
      //2a
      //mge_n = 100000000, mge_type = 0, mge_a = -1, mge_b = -1, mge_mod = 5, mge_mul = 2906159023179899071;
      //3a mge_n = 80000000, mge_type = 0, mge_a = -1, mge_b = -1, mge_mod = 1000000, mge_mul = 6881491782827497215LL;
      //4a
      //mge_n = 90000000, mge_type = 0, mge_a = -1, mge_b = -1, mge_mod = 1000000, mge_mul = 17318417819340455879;
      //8a mge_n = 100000000, mge_type = 3, mge_a = 32, mge_b = 19, mge_mod = 1000000, mge_mul = 7419359541164124855;
      //10a
      mge_n = 99999999, mge_type = 0, mge_a = -1, mge_b = -1, mge_mod = 1000000, mge_mul = 8100225648422384477LL;

      //2a krotki
      //mge_n = 4 * 1000000, mge_type = 0, mge_a = -1, mge_b = -1, mge_mod = 5, mge_mul = 2906159023179899071;
      //4a krotki
      //mge_n = 4 * 1000000, mge_type = 0, mge_a = -1, mge_b = -1, mge_mod = 1000000, mge_mul = 17318417819340455879;
      //10a krotki
      //mge_n = 4 * 1000000, mge_type = 0, mge_a = -1, mge_b = -1, mge_mod = 1000000, mge_mul = 8100225648422384477;
      initDone = true;
    }
  }
  long myGetElem(long i) {
    init();
    if (i < 0) return mge_n;
    cop++;
    //return 1000000 - (i % 1000000);
    assert(0 <= i and i < mge_n);
    assert(0 <= i && i < mge_n);
    unsigned long long x = i + 1;
    x = ((x + 1) * mge_mul) >> 32;
    bool done = false;
    if (mge_type == 1 || mge_type == 2) {
      if (x % 100 < (unsigned)mge_a) {
        x = (long long)i * mge_mod / mge_n;
        if (mge_type == 2) {
          x = mge_mod - 1 - x;
        }
        done = true;
      }
    }
    if (!done) { // fake time consumption, to make running times equal
      for (int asdf = 1; asdf <= 2 - (mge_type == 3); ++asdf) {
        x += mge_n / (i / asdf + 1);
      }
    }
    if (mge_type == 3) {
      if ((i + mge_a / 3) % mge_a < mge_b) {
        x = mge_mod * 9LL / 10;
      }
    }
    return 1 + x % mge_mod;
  }
  long myGetN() { return myGetElem(-1); }
#endif

#ifdef SINGLEINSTANCE
  long myMyNodeId() { return 0; }
  long myNumberOfNodes() { return 1; }
  deque<int> intMsg;
  void PutInt(int dst, int a) { intMsg.push_back(a); }
  int GetInt(int src) { int a = *intMsg.begin(); intMsg.pop_front(); return a; }
  deque<Int> llMsg;
  void PutLL(int dst, Int a) { llMsg.push_back(a); }
  Int GetLL(int src) { Int a = *llMsg.begin(); llMsg.pop_front(); return a; }
  void Send(int dst) {}
  int Receive(int dst) { return 0; }
#else
  #include "message.h"
  #include "teatr.h"

  long myMyNodeId() { return MyNodeId(); }
  long myNumberOfNodes() { return NumberOfNodes(); }
#endif

inline long myGetElemSafe(long i) {
  if (i >= nGlobal)
    return M - 1;
  else
    return myGetElem(i);
}

Int scalajMale(long w, long poz, long src[], long dst[]) {
  long x1 = poz;
  long x2 = poz + w;
  long x1stop = x1 + w;
  long x2stop = x2 + w;
  long y = poz;
  Int res = 0;
  if (bDebug2) cerr << "scalaj " << deb(w) << deb(poz) << endl;

  rep(i, 2*w) {
    if (x1 >= x1stop || (x2 < x2stop && src[x1] > src[x2])) {
      res += x1stop - x1;
      if (bDebug2) cerr << "przep2 " << deb(src[x2]) << deb(x1) << deb(x2) << deb(y) << deb(res) << endl;
      dst[y] = src[x2];
      x2++;
    } else {
      if (bDebug2) cerr << "przep1 " << deb(src[x1]) << deb(x1) << deb(x2) << deb(y) << deb(res) << endl;
      dst[y] = src[x1];
      x1++;
    }
    y++;
  }
  return res;
}

void zbierzCzestosci(long istart, long istop, long ac[M]) {
  memset(ac, 0, M * sizeof(long));
  cerr << sizeof(unsigned char) << endl;
  array(ac1, unsigned char, M);
  if (istop > nGlobal)
    istop = nGlobal;
  rep2(i, istart, istop - 1) {
    int e = myGetElem(i);
    ac1[e]++;
    if (ac1[e] == 0) {
      ac[e]++;
    }
  }
  rep(j, M) {
    ac[j] = 256 * ac[j] + ac1[j];
  }
  if (false && bDebug2) {
    cerr << "zebrane " << deb(istart) << deb(istop) << endl;
    rep(i, M) {
      if (ac[i])
        cerr << deb(i) << deb(ac[i]) << endl;
    }
  }
}

Int scalajDuze(long w, long poz) {
  long x1 = poz;
  long x2 = poz + w;
  long x1stop = min(x1 + w, nGlobal);
  long x2stop = min(x2 + w, nGlobal);
  Int res = 0;
  if (bDebug) cerr << "scalajDuze start " << deb(w) << deb(poz) << endl;
  zbierzCzestosci(x1, x1stop, ac[0]);
  zbierzCzestosci(x2, x2stop, ac[1]);

  long i1 = 0;
  long i2 = 1;
  long c1 = x1stop - x1;
  while (true) {
    while (i1 < M && ac[0][i1] == 0) i1++;
    while (i2 < M && ac[1][i2] == 0) i2++;
    if (i1 >= M && i2 >= M)
      break;
    if (i1 >= M || (i2 < M && i1 > i2)) {
      res += ((Int)ac[1][i2]) * (Int)c1;
      if (bDebug2) cerr << "przep2 " << deb(i2) << deb(i1) << deb(i2) << deb(c1) << deb(res) << endl;
      i2++;
    } else {
      c1 -= ac[0][i1];
      if (bDebug2) cerr << "przep1 " << deb(i1) << deb(i1) << deb(i2) << deb(c1) << deb(res) << endl;
      i1++;
    }
  }
  assert(c1 == 0);
  if (bDebug) cerr << "scalajDuze end " << deb(w) << deb(poz) << deb(res) << endl;
  return res;
}

int main (int argc, char **args)
{
  #ifdef HOME
  if (argc > 1) {
    freopen("tea/testy_moje/01.in", "r", stdin);
  }
  #endif
  cin.sync_with_stdio(false);
  cout.sync_with_stdio(false);

  array(a1, long, N);
  array(a2, long, N);
  ad[0] = a1;
  ad[1] = a2;
  nGlobal = myGetN();
  long wSent = 0;

  if (bDebug) cerr << "my name is " << myMyNodeId() << endl;

  // Rozsylamy kazdemu rowny kawalek.
  if (true) {
    long d = 2;
    while (d < 1000000 && myNumberOfNodes() * d < nGlobal) d *= 2;
    if (!TYLKODUZE && myMyNodeId() == 0) {
      rep(i, myNumberOfNodes()) {
        if (bDebug) cerr << "Do " << i << " wysylamy " << deb(d) << endl;
        PutInt(i, i * d);
        PutInt(i, i * d + d);
        Send(i);
      }
    }
    wSent = d;
  }

  // Przetwarzamy swoj kawalek.
  if (!TYLKODUZE) {
    Int resLocal = 0;
    int src = Receive(-1);
    long istart = GetInt(src);
    long istop = GetInt(src);
    rep(i, N)
      ad[0][i] = ad[1][i] = M - 1;
    rep(i, istop - istart)
      ad[0][i] = myGetElemSafe(istart + i);

    long w = 1, j = 0;
    while (w < istop - istart) {
      if (bDebug2)
        cerr << "instancja " << myMyNodeId() << " scala " << deb(w) << endl;
        long x = 0;
        while (x < istop - istart) {
          resLocal += scalajMale(w, x, ad[j], ad[!j]);
          x += 2 * w;
        }
        j = !j;
      w *= 2;
    }
    if (bDebug) cerr << "instancja " << myMyNodeId() << " zwraca wynik malego " << deb(resLocal) << endl;
    PutLL(src, resLocal);
    Send(src);
    if (bDebug) cerr << "instancja " << myMyNodeId() << " zwrocila malego do " << deb(src) << endl;
  }

  if (!TYLKODUZE && myMyNodeId() == 0) {
    if (bDebug) cerr << "Odbieramy od kazdego jego kawalek." << endl;
    rep(i, myNumberOfNodes()) {
      if (bDebug) cerr << "Czekamy na malego od " << i << endl;
      int src = Receive(i);
      Int c = GetLL(src);
      resGlobal += c;
      if (bDebug) cerr << "Od " << src << " dostalismy " << c << endl;
    }
  }

  int cMsg = 0;
  int cMsgForMe = 0;
  if (true) {
    if (myMyNodeId() == 0 && bDebug) cerr << "Rozsylamy duze kawalki do przetworzenia." << deb(wSent) << deb(nGlobal) << endl;
    int dst = 0;
    long w = wSent;
    while (w < nGlobal) {
      long x = 0;
      while (x < nGlobal) {
        if (myMyNodeId() == 0) {
          if (bDebug) cerr << "Wysylamy z " << myMyNodeId() << " -> " << deb(dst) << deb(w) << deb(x) << endl;
          PutInt(dst, w);
          PutInt(dst, x);
          Send(dst);
        } else {
          if (bDebug2) cerr << "A " << myMyNodeId() << " nie wysyla " << deb(dst) << deb(w) << deb(x) << endl;
        }
        if (dst == myMyNodeId())
          cMsgForMe++;
        dst = (dst + 1) % myNumberOfNodes();
        cMsg++;
        x += 2 * w;
      }
      w *= 2;
    }
  }
  if (bDebug) cerr << "ja to " << myMyNodeId() << ": " << deb(cMsg) << deb(cMsgForMe) << endl;

  // Przetwarzamy duze kawalki.
  vector<Int> ans;
  rep(i, cMsgForMe) {
    int src = Receive(-1);
    if (bDebug) cerr << "Odbieramy duzy kawalek do zrobienia " << myMyNodeId() << "... ";
    long w = GetInt(src);
    long x = GetInt(src);
    if (bDebug) cerr << deb(w) << deb(x) << endl;
    ans.push_back(scalajDuze(w, x));
  }
  fore(it, ans) {
    PutLL(0, *it);
    Send(0);
  }

  // Odbieramy duze kawalki.
  if (myMyNodeId() == 0) {
    rep(i, cMsg) {
      int src = Receive(-1);
      if (bDebug) cerr << "Odbieramy duzy " << deb(i);
      Int y = GetLL(src);
      resGlobal += y;
      if (bDebug) cerr << deb(y) << deb(resGlobal) << endl;
    }
  }

  // Sprawdzamy liczbê operacji.
  if (false) {
    if (myMyNodeId() == 0) {
      if (bDebug) cerr << "node 0 " << deb(cop) << endl;
      rep2(i, 1, myNumberOfNodes() - 1) {
        PutInt(i, -1);
        Send(i);
        Receive(i);
        Int cOper = GetLL(i);
        if (bDebug) cerr << deb(i) << deb(cOper) << endl;
      }
    }
    else {
      Receive(0);
      PutLL(0, cop);
      Send(0);
    }
  }

  if (myMyNodeId() == 0)
    cout << resGlobal << endl;
}

/*
Mam algorytm chyba dobry. Najpierw przetwarza 100 * 1 mln w czasie n logn, potem ka¿dy nod przetwarza <100mln w czasie liniowym. Liczba odczytów GetElem jest niewiele wiêksza od 100 mln. Podczas prób na zadaniu testowym mia³em czasy poni¿ej 1 sekundy (przy natychmiastowym odczycie typu i % 1000000.

Jak puszczê u mnie test 10a, to owszem, mam komunikat:

Duration: 9.1105s (longest running instance: 73)

Wydaje mi siê jednak, ¿e na fizycznych 100 komputerach nie jest to mo¿liwe. ¯eby by³o œmieszniej, wskazany nod przetwarza³ liniowo tylko 1/10 danych (licz¹c po GetElem). To, ¿e wskazany jest jako najwolniejszy, zakrawa na absurd. Mo¿na jeszcze upatrywaæ problemów w synchronizacji, ale wykonujê j¹ tylko raz, po tym jak ka¿dy z nodów przetworzy swoj¹ czêœæ. A np. test 4a, który na sprawdzarce wykaza³ czas 4,98s i przeszed³ - u mnie pokazuje 8,64s. Wygl¹da wiêc na to, ¿e wariancja wyników pomiarów jest tu znaczna.

Pytanie brzmi: czy nie ma przypadkiem takiej mo¿liwoœci, ¿e klaster 100 komputerów by³ dociœniêty w czasie testowania i z tego powodu nie osi¹gn¹³ maksymalnej wydajnoœci?

Nie umiem inaczej tego wyt³umaczyæ. Gdyby tak by³o, to poprosi³bym o retest na nieobci¹¿onym klastrze.

8a 4.23s

*/

/** \file MtRand.cxx Mersenne Twister pseudo-random number generator.
    The code used to develop this class contained the following copyright notice:

    A C-program for MT19937, with initialization improved 2002/1/26.
    Coded by Takuji Nishimura and Makoto Matsumoto.

    Before using, initialize the state by using init_genrand(seed)  
    or init_by_array(init_key, key_length).

    Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
    All rights reserved.                          

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    3. The names of its contributors may not be used to endorse or promote 
    products derived from this software without specific prior written 
    permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    Any feedback is very welcome.
    http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
    email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/
#include "MtRand.hh"

//_____________________________________________________________________________
/** Default constructor from single seed. */
MtRand::MtRand(ULong_t seed)
  : _mtCntr(kN+1),
    _nCalls(0)
{
  // _mtCntr==kN+1 means _mt[kN] is not initialized
  setSeed(seed);
}

//_____________________________________________________________________________
/** Constructor from seed keys. */
MtRand::MtRand(const ULong_t* seed, UInt_t seedLength)
  : _mtCntr(kN+1),
    _nCalls(0)
{
  // _mtCntr==kN+1 means _mt[kN] is not initialized
  setSeed(seed, seedLength);
}

//_____________________________________________________________________________
/** Copy constructor. */
MtRand::MtRand(const MtRand& other)
{
  for(UInt_t i=0; i<kN; i++) _mt[i] = other._mt[i];
  _mtCntr = other._mtCntr;
  _nCalls = other._nCalls;
}

//_____________________________________________________________________________
/** Assignment operator. */
void MtRand::operator=(const MtRand& rhs)
{
  for(UInt_t i=0; i<kN; i++) _mt[i] = rhs._mt[i];
  _mtCntr = rhs._mtCntr;
  _nCalls = rhs._nCalls;  
}

//_____________________________________________________________________________
/** Constructor from seed keys. */
MtRand::~MtRand()
{
  // over write state with zeros
  for(UInt_t i=0; i<kN; i++) _mt[i] = 0x00000000UL;
  _mtCntr = 0;
  _nCalls = 0;  
}

//_____________________________________________________________________________
/** Seed from single number. 
    Initializes _mt[kN] with a seed.
*/
void MtRand::setSeed(ULong_t seed)
{
  // reset rndm call counter
  _nCalls = 0;

  // seed and fill array
  _mt[0]= seed & 0xffffffffUL;
  for (_mtCntr=1; _mtCntr<kN; _mtCntr++) {
    // See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
    // 2002/01/09 modified by Makoto Matsumoto
    _mt[_mtCntr] = (1812433253UL * (_mt[_mtCntr-1] ^ (_mt[_mtCntr-1] >> 30)) + _mtCntr); 
    _mt[_mtCntr] &= 0xffffffffUL; // for >32 bit machines
  }
}

//_____________________________________________________________________________
/** Seed by an array with array-length.
    \param seed The array for initializing keys. 
    \param seedLength Length of the seed array.
*/
void MtRand::setSeed(const ULong_t* seed, UInt_t seedLength)
{
  // set default single seed
  setSeed(kDefaultSeed);

  Int_t i = 1;
  Int_t j = 0;
  Int_t k = (kN>seedLength ? kN : seedLength);

  for(; k; k--) {
    // non linear
    _mt[i] = (_mt[i] ^ ((_mt[i-1] ^ (_mt[i-1] >> 30)) * 1664525UL)) + seed[j] + j;
    _mt[i] &= 0xffffffffUL; // for WORDSIZE > 32 machines
    i++; j++;
    if (i>=kN) { _mt[0] = _mt[kN-1]; i=1; }
    if (j>=seedLength) j=0;
  }

  for(k=kN-1; k; k--) {
    // non linear
    _mt[i] = (_mt[i] ^ ((_mt[i-1] ^ (_mt[i-1] >> 30)) * 1566083941UL)) - i;
    _mt[i] &= 0xffffffffUL; // for WORDSIZE > 32 machines
    i++;
    if (i>=kN) { _mt[0] = _mt[kN-1]; i=1; }
  }

  // MSB is 1; assuring non-zero initial array
  _mt[0] = 0x80000000UL;
}

//_____________________________________________________________________________
/** Generate a random number (32-bit integer) on the [0, 2^32 - 1] interval. */
ULong_t MtRand::rndm()
{
  ULong_t val; // returned value
  static ULong_t kMag01[2] = {0x0UL, kMatrixA};  // x * kMatrixA for x=0,1

  // generate kN words at a time
  if(_mtCntr >= kN) {
    Int_t kk(0);
    for(kk=0; kk<kN-kM; kk++) {
      val = (_mt[kk] & kUpperMask) | (_mt[kk+1] & kLowerMask);
      _mt[kk] = _mt[kk+kM] ^ (val >> 1) ^ kMag01[val & 0x1UL];
    }

    for(; kk<kN-1; kk++) {
      val = (_mt[kk] & kUpperMask) | (_mt[kk+1] & kLowerMask);
      _mt[kk] = _mt[kk+(kM-kN)] ^ (val >> 1) ^ kMag01[val & 0x1UL];
    }

    val = (_mt[kN-1] & kUpperMask) | (_mt[0] & kLowerMask);
    _mt[kN-1] = _mt[kM-1] ^ (val >> 1) ^ kMag01[val & 0x1UL];

    _mtCntr = 0;
  }

  // set value
  val = _mt[_mtCntr++];

  // Tempering
  val ^= (val >> 11);
  val ^= (val <<  7) & kTemperMaskB;
  val ^= (val << 15) & kTemperMaskC;
  val ^= (val >> 18);

  // warn for crypto security
  if(_nCalls > kN-1){
    WARN << "******************************************************" << std::endl;
    WARN << "To many rndm calls; generator much less crypto-secure!" << std::endl;
    WARN << "******************************************************" << std::endl;
    _nCalls = 0;
  }

  // increment rndm call counter
  _nCalls++;

  return val;  
}

//_____________________________________________________________________________
/** Generate a random number (double) on [min,max) real interval. */
Double_t MtRand::uniform(Double_t min, Double_t max)
{
  return static_cast<Double_t>(min + (max-min) * rndm() * kInvTwoPow32);
}

//_____________________________________________________________________________
/** Generate a random nSided die role.  */
UInt_t MtRand::dieRole(UInt_t nSides)
{
  return static_cast<UInt_t>(uniform(1,nSides+1));
}

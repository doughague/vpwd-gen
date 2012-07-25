/** \file MtRand.hh Mersenne Twister pseudo-random number generator. */
#ifndef MTRAND
#define MTRAND

#include "Globals.hh"

/** \class MtRand 
    \brief Mersenne Twister pseudo-random number generator.
    \warning This generator is NOT cryptographically secure since the random numbers 
    can be perfectly reproduced given the seed value or about 624 sequential values!
*/
class MtRand { 
public:
  MtRand(ULong_t seed = kDefaultSeed);
  MtRand(const ULong_t* seed, UInt_t seedLength);
  MtRand(const MtRand& other);
  void operator=(const MtRand& rhs);
  virtual ~MtRand();

  // seed setters
  void setSeed(ULong_t seed);
  void setSeed(const ULong_t* seed, UInt_t seedLength);

  // generators
  ULong_t rndm();
  Double_t uniform(Double_t min=0., Double_t max=1.);
  UInt_t dieRole(UInt_t nSides=6);

private:
  // period parameters
  static const UInt_t kN = 624;                     //<! state size
  static const UInt_t kM = 397;                     //<! coefcient 'm'
  static const ULong_t kMatrixA = 0x9908b0dfUL;     //<! constant vector 'a'
  static const ULong_t kUpperMask = 0x80000000UL;   //<! most significant 'w-r' bits
  static const ULong_t kLowerMask = 0x7fffffffUL;   //<! least significant 'r' bits
  static const ULong_t kTemperMaskB = 0x9d2c5680UL; //<! Tempering Mask 'B'
  static const ULong_t kTemperMaskC = 0xefc60000UL; //<! Tempering Mask 'C'

  // state parameters
  ULong_t _mt[kN];  //<! array for the state vector
  UInt_t  _mtCntr;  //<! state array counter

  // crypto helpers
  UInt_t  _nCalls;  //<! to track the number of rndm calls
};

#endif // MTRAND

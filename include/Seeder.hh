/** \file Seeder.hh */
#ifndef SEEDER
#define SEEDER

#include "Globals.hh"

/** \class Seeder 
    \brief Generating seeds/keys for PRNG.
*/
class Seeder { 
public:
  Seeder();
  Seeder(String_t type, Double_t entropy=10.);
  Seeder(const Seeder& other);
  void operator=(const Seeder& rhs);
  virtual ~Seeder();

  // getters
  ULong_t* key() const { return _key;}  
  UInt_t keyLength() const { return _keyLength;}  

  // enum SeedType { eTime=0, eNumber=1, eDevRand=2, ePass=3 };
  Bool_t setKey(const ULong_t* key, UInt_t keyLength);
  Bool_t setKey(ULong_t key);
  Bool_t setFromTime();
  Bool_t setFromPhrase(const Char_t* phrase);
  Bool_t setFromDevUrandom(Double_t entropy);

  // print info
  void printKey(std::ostream& os);

private:
  ULong_t* _key;
  UInt_t _keyLength;

  void clearKey();
  void allocKey(UInt_t size);
};

#endif // SEEDER

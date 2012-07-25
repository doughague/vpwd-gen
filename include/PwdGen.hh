/** \file PwdGen.hh */
#ifndef PWDGEN
#define PWDGEN

#include "Globals.hh"
#include "PwdOpts.hh"
#include "MtRand.hh"

/** \class PwdGen 
    \brief Generating pass-words/-phrases.
*/
class PwdGen { 
public:
  PwdGen();
  PwdGen(const PwdOpts& options, const MtRand& random);
  PwdGen(const PwdGen& other);
  void operator=(const PwdGen& rhs);
  inline virtual ~PwdGen() {}

  // entropy estimator
  static Double_t calcPossibleEntropy(const PwdOpts opts);
  static Double_t calcObservedEntropy(const String_t pwd);

  // pass generators
  String_t generate();
  String_t genPassAscii();
  String_t genPassPhrase();
  String_t genPassFromCode(UInt_t length, String_t code);
  String_t genPassFromChars(UInt_t length, String_t chars);
  void insertPadding(String_t& pwd);

  // printers
  void printLength(std::ostream& os);
  void printUnits(std::ostream& os);

private:
  //! types of pwd units
  enum UnitType { eLower=0, eUpper=1, eDigit=2, eSpecial=3, 
		  eKoremut=4, eDice=5, eSkey=6 };
  PwdOpts   _pwdOpts;  //<! pwd options
  MtRand    _random;   //<! generator
  UnitType* _units;    //<! pwd units to choose from
  UInt_t    _nUnits;   //<! number of pwd units to choose from
  
  // pwd units
  void allocUnits(UInt_t size);
  void buildUnits();
  const Char_t* unitName(UnitType ut);
  PwdGen::UnitType chooseUnit();
  const Char_t* genPwdUnit(UnitType ut);
  const Char_t* genPwdUnit();
};

#endif // PWDGEN

/** \file PwdOpts.hh */
#ifndef PWDOPTS
#define PWDOPTS

#include "Globals.hh"

/** \class PwdOpts 
    \brief Holding password options.
*/
class PwdOpts { 
public:
  PwdOpts();
  PwdOpts(Int_t argc, Char_t** argv);
  PwdOpts(const PwdOpts& other);
  void operator=(const PwdOpts& rhs);
  virtual ~PwdOpts();

  void parseCmdLine(Int_t argc, Char_t** argv);

  void setAllAscii(Bool_t val = kTRUE);
  void setAllWords(Bool_t val = kTRUE);
  void setAll(Bool_t val = kTRUE);
  
  Bool_t none();
  Bool_t onlyAscii();
  Bool_t onlyWords();

public:
  Bool_t    help;       //<! print program help
  Int_t     pLevel;     //<! print level
  String_t  seedType;   //<! seeding options

  UInt_t    length;     //<! length of requested password
  Bool_t    all;        //<! use all available for each password unit

  Bool_t    ascii;      //<! use all ascii charcters
  Bool_t    lower;      //<! use lower-case letters
  Bool_t    upper;      //<! use upper-case letters
  Bool_t    digit;      //<! use digits
  Bool_t    special;    //<! use special characters

  Bool_t    words;      //<! use all words
  Bool_t    koremut;    //<! use Koremutake syllables
  Bool_t    dice;       //<! use DiceWare words
  Bool_t    skey;       //<! use SKey words
  Bool_t    noSpace;    //<! do not put spaces between words
  Bool_t    proper;     //<! capitalize first letter of words

  String_t  pad;        //<! user input padding characters
  Int_t     padPos;     //<! possition of padding (-1,0,1)

  String_t  code;       //<! user code for password units
  String_t  chars;      //<! user characters for password
};

#endif // PWDOPTS

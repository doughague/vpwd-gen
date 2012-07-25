/** \file Characters.hh */
#ifndef CHARACTERS
#define CHARACTERS

#include "Globals.hh"

static const UInt_t nLetters = 26;
static const Double_t entropyLetter = 4.700;
const Char_t* getLetterLower(UInt_t n);
const Char_t* getLetterUpper(UInt_t n);

static const UInt_t nDigits = 10;
static const Double_t entropyDigit = 3.322;
const Char_t* getDigit(UInt_t n);

static const UInt_t nSpecials = 32;
static const Double_t entropySpecial = 5.000;
const Char_t* getSpecial(UInt_t n);

static const UInt_t nConsonants = 36;
static const Double_t entropyConsonant = 5.170;
const Char_t* getConsonant(UInt_t n);

static const UInt_t nVowels = 6;
static const Double_t entropyVowel = 2.585;
const Char_t* getVowel(UInt_t n);

#endif // CHARACTERS

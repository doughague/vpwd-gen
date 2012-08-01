/** \file PwdGen.cxx */
/*  vpwd-gen for for versatile generation of a password
    Copyright (C) 2012 Doug Hague

    vpwd-gen is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    vpwd-gen is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with vpwd-gen.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <cmath>   // for log2
#include <ctype.h> // for toupper
#include "Characters.hh"
#include "Koremutakes.hh"
#include "DiceWords.hh"
#include "SkeyWords.hh"
#include "PwdGen.hh"

using std::endl;

//_____________________________________________________________________________
/** Default constructor. */
PwdGen::PwdGen()
  : _pwdOpts(),
    _random(),
    _units(0),
    _nUnits(0)
{}

//_____________________________________________________________________________
/** Constructor. */
PwdGen::PwdGen(const PwdOpts& options, const MtRand& random)
  : _pwdOpts(options),
    _random(random),
    _units(0),
    _nUnits(0)
{
  buildUnits();
}

//_____________________________________________________________________________
/** Copy constructor. */
PwdGen::PwdGen(const PwdGen& other)
  : _pwdOpts(other._pwdOpts),
    _random(other._random),
    _nUnits(other._nUnits)
{
  allocUnits(other._nUnits);
  for(UInt_t u=0; u<_nUnits; u++) _units[u] = other._units[u];
}

//_____________________________________________________________________________
/** Assignment operator. */
void PwdGen::operator=(const PwdGen& rhs)
{
  _pwdOpts = rhs._pwdOpts;
  _random = rhs._random;
  _nUnits = rhs._nUnits;
  allocUnits(rhs._nUnits);
  for(UInt_t u=0; u<_nUnits; u++) _units[u] = rhs._units[u];
}

//_____________________________________________________________________________
/** Allocate unit-type array. */
void PwdGen::allocUnits(UInt_t size)
{
  _nUnits = size;
  _units = new UnitType[_nUnits];  
}

//_____________________________________________________________________________
/** Build the array containing possible password units. */
void PwdGen::buildUnits()
{
  // calculate
  UInt_t nu(0);
  if(_pwdOpts.lower) nu++;
  if(_pwdOpts.upper) nu++;
  if(_pwdOpts.digit) nu++;
  if(_pwdOpts.special) nu++;
  if(_pwdOpts.koremut) nu++;
  if(_pwdOpts.dice) nu++;
  if(_pwdOpts.skey) nu++;

  // allocate
  allocUnits(nu);

  // build
  UInt_t un(0);
  if(_pwdOpts.lower){   _units[un] = eLower;   un++; } 
  if(_pwdOpts.upper){   _units[un] = eUpper;   un++; } 
  if(_pwdOpts.digit){   _units[un] = eDigit;   un++; } 
  if(_pwdOpts.special){ _units[un] = eSpecial; un++; } 
  if(_pwdOpts.koremut){ _units[un] = eKoremut; un++; } 
  if(_pwdOpts.dice){    _units[un] = eDice;    un++; } 
  if(_pwdOpts.skey){    _units[un] = eSkey;    un++; } 
}

//_____________________________________________________________________________
/** Get a pwd unit name. */
const Char_t* PwdGen::unitName(UnitType ut)
{
  switch(ut){
  case eLower:   return "Lower";
  case eUpper:   return "Upper";
  case eDigit:   return "Digit";
  case eSpecial: return "Special";
  case eKoremut: return "Koremutake";
  case eDice:    return "DiceWord";
  case eSkey:    return "SkeyWord";
  }
}

//_____________________________________________________________________________
/** Allocate unit-type array. */
PwdGen::UnitType PwdGen::chooseUnit()
{
  UInt_t u = _random.dieRole(_nUnits) - 1;
  return _units[u];
}

//_____________________________________________________________________________
/** Get a pwd unit (character or word). */
const Char_t* PwdGen::genPwdUnit(UnitType ut)
{
  UInt_t n = _random.rndm();
  switch(ut){
  case eLower:   return getLetterLower(n);
  case eUpper:   return getLetterUpper(n);
  case eDigit:   return getDigit(n);
  case eSpecial: return getSpecial(n);
  case eKoremut: return getKoremutake(n);
  case eDice:    return getDiceWord(n);
  case eSkey:    return getSkeyWord(n);
  }
}

//_____________________________________________________________________________
/** Get a pwd unit (character or word). */
const Char_t* PwdGen::genPwdUnit()
{
  return genPwdUnit(chooseUnit());
}

//_____________________________________________________________________________
/** Extimate the possible entropy from the options. */
Double_t PwdGen::calcPossibleEntropy(const PwdOpts opts)
{
  UInt_t choicesPerUnit(0);
  if(opts.lower)   choicesPerUnit += nLetters;
  if(opts.upper)   choicesPerUnit += nLetters;
  if(opts.digit)   choicesPerUnit += nDigits;
  if(opts.special) choicesPerUnit += nSpecials;
  if(opts.koremut) choicesPerUnit += nKoremuts;
  if(opts.dice)    choicesPerUnit += nDiceWords;
  if(opts.skey)    choicesPerUnit += nSkeyWords;

  // std::cout << "choicesPerUnit = " << choicesPerUnit << std::endl;
  return opts.length * log2(1.*choicesPerUnit);
}

//_____________________________________________________________________________
/** Extimate the observed entropy of the password. */
Double_t PwdGen::calcObservedEntropy(const String_t pwd)
{
  UInt_t choicesPerUnit(0);
  
  // check for lower-case letters
  for(UInt_t k=0; k<nLetters; k++){
    String_t c(getLetterLower(k));
    if(pwd.find(c)!=std::string::npos){
      choicesPerUnit += nLetters;
      break;
    }
  }

  // check for upper-case letters
  for(UInt_t k=0; k<nLetters; k++){
    String_t c(getLetterUpper(k));
    if(pwd.find(c)!=std::string::npos){
      choicesPerUnit += nLetters;
      break;
    }
  }

  // check for digits
  for(UInt_t k=0; k<nDigits; k++){
    String_t c(getDigit(k));
    if(pwd.find(c)!=std::string::npos){
      choicesPerUnit += nDigits;
      break;
    }
  }

  // check for specials
  for(UInt_t k=0; k<nSpecials; k++){
    String_t c(getSpecial(k));
    if(pwd.find(c)!=std::string::npos){
      choicesPerUnit += nSpecials;
      break;
    }
  }

  return pwd.size() * log2(1.*choicesPerUnit);
}

//_____________________________________________________________________________
/** Generate a pass- word/phrase. */
String_t PwdGen::generate()
{

  String_t pwd("");

  if(_pwdOpts.code!="") 
    pwd = genPassFromCode(_pwdOpts.length, _pwdOpts.code);
  else if(_pwdOpts.chars!="") 
    pwd = genPassFromChars(_pwdOpts.length, _pwdOpts.chars);
  else{
    if(_pwdOpts.onlyWords()) 
      pwd = genPassPhrase();
    else if(_pwdOpts.onlyAscii()) 
      pwd = genPassAscii();
    else{
      for(UInt_t u=0; u<_pwdOpts.length; u++)
	pwd += genPwdUnit();
    }
  }

  // insert padding if requested
  if(_pwdOpts.pad!="") 
    insertPadding(pwd);

  return pwd;
}

//_____________________________________________________________________________
/** Generate an ascii pass-word. */
String_t PwdGen::genPassAscii()
{
  String_t pwd("");
  for(UInt_t u=0; u<_pwdOpts.length; u++)
    pwd += genPwdUnit();
  return pwd;
}

//_____________________________________________________________________________
/** Generate a pass-phrase. */
String_t PwdGen::genPassPhrase()
{
  String_t pwd("");
  Bool_t first = kFALSE;  
  for(UInt_t u=0; u<_pwdOpts.length; u++){
    String_t phold("");
    if(!first){
      if(!_pwdOpts.noSpace) phold = (genPwdUnit() + String_t(" "));
      else phold = genPwdUnit();
    } 
    else phold += genPwdUnit();

    if(_pwdOpts.proper){
      // capitolize first letter of word
      Char_t fl = phold[0];
      Char_t fL = (Char_t)toupper(fl);
      phold.replace(0,1,String_t(&fL));
      pwd += phold;
    }
    else pwd += phold;
    
    // overwrite phold in memory
    for(UInt_t k=0; k<phold.size(); k++) phold[k] = '0';
  }
  return pwd;
}

//_____________________________________________________________________________
/** Generate a pass-word from user code. */
String_t PwdGen::genPassFromCode(UInt_t length, String_t code)
{
  UInt_t codeLength = code.size();
  String_t pwd("");

  UInt_t codePos(0), codeInt(0), n(0), nunits(0);
  while(nunits<length){
    codePos = nunits % codeLength;
    codeInt = UInt_t(code[codePos]);
    n = _random.rndm();
    nunits++;
    
    switch(codeInt){
    case 'l': pwd += getLetterLower(n); break;
    case 'u': pwd += getLetterUpper(n); break;
    case 'g': pwd += getDigit(n); break;
    case 's': pwd += getSpecial(n); break;
    case 'k': pwd += getKoremutake(n); break;
    case 'd': pwd += getDiceWord(n); break;
    case 'y': pwd += getSkeyWord(n); break;
    default:  pwd += getLetterLower(n); break;
    }
  }

  return pwd;
}

//_____________________________________________________________________________
/** Generate a pass-word from user characters. */
String_t PwdGen::genPassFromChars(UInt_t length, String_t chars)
{
  UInt_t charsLength = chars.size();
  String_t pwd("");

  UInt_t charsPos(0);
  while(pwd.size()<length){
    charsPos = _random.rndm() % charsLength;
    pwd += _pwdOpts.chars[charsPos];
  }

  return pwd;
}

//_____________________________________________________________________________
/** Insert padding from user characters. */
void PwdGen::insertPadding(String_t& pwd)
{
  if(_pwdOpts.padPos<0)
    pwd.insert(0,_pwdOpts.pad);
  else if(_pwdOpts.padPos>0)
    pwd.insert(pwd.size(),_pwdOpts.pad);
  else{
    UInt_t mid(pwd.size()/2);
    pwd.insert(mid,_pwdOpts.pad);
  }
}

//_____________________________________________________________________________
/** Print the used options to the stream. */
void PwdGen::printLength(std::ostream& os)
{
  os << "Length = " << _pwdOpts.length << std::endl;
}

//_____________________________________________________________________________
/** Print the used options to the stream. */
void PwdGen::printUnits(std::ostream& os)
{
  os << "Unit-Type(s) = ";
  Bool_t first = kTRUE;
  for(UInt_t u=0; u<_nUnits; u++){
    const Char_t* uname = unitName(_units[u]);
    if(first){ os << uname; first = kFALSE; } 
    else  os << ", " << uname;
  }
  os << std::endl;
}

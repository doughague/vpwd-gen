/** \file Characters.cxx */
#include "Characters.hh"

//_____________________________________________________________________________
/** List of 26 lower-case English letters. */
static const Char_t* lettersLower[] = {
  "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l",
  "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x",
  "y", "z"
};

//_____________________________________________________________________________
/** Get English letter. */
const Char_t* getLetterLower(UInt_t n) 
{
  return lettersLower[n & 0x19];
}

//_____________________________________________________________________________
/** List of 26 upper-case English letters. */
static const Char_t* lettersUpper[] = {
  "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
  "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
  "Y", "Z"
};

//_____________________________________________________________________________
/** Get English letter. */
const Char_t* getLetterUpper(UInt_t n) 
{
  return lettersUpper[n & 0x19];
}

//_____________________________________________________________________________
/** List of 10 digits. */
static const Char_t* digits[] = {
  "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
};

//_____________________________________________________________________________
/** Get digit. */
const Char_t* getDigit(UInt_t n) 
{
  return digits[n & 0x09];
}

//_____________________________________________________________________________
/** List of 32 special characters. */
static const Char_t* specials[] = {
  "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "_",
  "+", "=", "[", "]", "{", "}", ";", ":", "'", "\"", ",", ".",
  "<", ">", "/", "?", "`", "~", "|", "\\"
};

//_____________________________________________________________________________
/** Get digit. */
const Char_t* getSpecial(UInt_t n) 
{
  return specials[n & 0x1F];
}

//_____________________________________________________________________________
/** List of 36 consonants. */
static const Char_t* consonants[] = {
  "b", "c", "d", "f", "g", "h",
  "j", "k", "l", "m", "n", "p",
  "qu", "r", "s", "t", "v", "w",
  "x", "z", "ch", "cr", "fr", "nd",
  "ng", "nk", "nt", "ph", "pr", "rd",
  "sh", "sl", "sp", "st", "th", "tr"
};

//_____________________________________________________________________________
/** Get consonant. */
const Char_t* getConsonant(UInt_t n) 
{
  return consonants[n & 0x23];
}

//_____________________________________________________________________________
/** List of 6 vowels. */
static const Char_t* vowels[] = {
  "a", "e", "i", "o", "u", "y"
};

//_____________________________________________________________________________
/** Get vowel. */
const Char_t* getVowel(UInt_t n) 
{
  return vowels[n & 0x05];
}

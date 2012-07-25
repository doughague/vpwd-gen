/** \file Koremutakes.cxx */
#include "Koremutakes.hh"

//_____________________________________________________________________________
/** List of 128 Koremutake syllables. */
static const char *koremutakes[] = {
  "ba", "be", "bi", "bo", "bu", "by", "da", "de",
  "di", "do", "du", "dy", "fa", "fe", "fi", "fo",
  "fu", "fy", "ga", "ge", "gi", "go", "gu", "gy",
  "ha", "he", "hi", "ho", "hu", "hy", "ja", "je",
  "ji", "jo", "ju", "jy", "ka", "ke", "ki", "ko",
  "ku", "ky", "la", "le", "li", "lo", "lu", "ly",
  "ma", "me", "mi", "mo", "mu", "my", "na", "ne",
  "ni", "no", "nu", "ny", "pa", "pe", "pi", "po",
  "pu", "py", "ra", "re", "ri", "ro", "ru", "ry",
  "sa", "se", "si", "so", "su", "sy", "ta", "te",
  "ti", "to", "tu", "ty", "va", "ve", "vi", "vo",
  "vu", "vy", "bra", "bre", "bri", "bro", "bru", "bry",
  "dra", "dre", "dri", "dro", "dru", "dry", "fra", "fre",
  "fri", "fro", "fru", "fry", "gra", "gre", "gri", "gro",
  "gru", "gry", "pra", "pre", "pri", "pro", "pru", "pry",
  "sta", "ste", "sti", "sto", "stu", "sty", "tra", "tre"
};

//_____________________________________________________________________________
/** Get Koremutake. */
const Char_t* getKoremutake(UInt_t n) 
{
  return koremutakes[n & 0x7F];
}

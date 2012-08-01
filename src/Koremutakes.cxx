/** \file Koremutakes.cxx */
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

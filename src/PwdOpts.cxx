/** \file PwdOpts.cxx */
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
#include <getopt.h>
#include "PwdOpts.hh"

//_____________________________________________________________________________
/** Default constructor. */
PwdOpts::PwdOpts()
  : help(kFALSE), pLevel(0),
    seedType("random"),
    length(8),
    all(kFALSE), ascii(kFALSE), lower(kFALSE), upper(kFALSE), digit(kFALSE), special(kFALSE),
    words(kFALSE), koremut(kFALSE), dice(kFALSE), skey(kFALSE), 
    noSpace(kFALSE), proper(kFALSE),
    pad(""), padPos(0), code(""), chars("")
{}

//_____________________________________________________________________________
/** Constructor from commend-line inputs. */
PwdOpts::PwdOpts(Int_t argc, Char_t** argv)
  : help(kFALSE), pLevel(0),
    seedType("random"),
    length(8),
    all(kFALSE), ascii(kFALSE), lower(kFALSE), upper(kFALSE), digit(kFALSE), special(kFALSE),
    words(kFALSE), koremut(kFALSE), dice(kFALSE), skey(kFALSE), 
    noSpace(kFALSE), proper(kFALSE),
    pad(""), padPos(0), code(""), chars("")
{
  parseCmdLine(argc, argv);
}

//_____________________________________________________________________________
/** Copy constructor. */
PwdOpts::PwdOpts(const PwdOpts& other)
  : help(other.help),
    pLevel(other.pLevel), seedType(other.seedType),
    length(other.length),
    all(other.all), ascii(other.ascii),
    lower(other.lower), upper(other.upper), digit(other.digit), special(other.special),
    words(other.words), koremut(other.koremut), dice(other.dice), skey(other.skey), 
    noSpace(other.noSpace), proper(other.proper),
    pad(other.pad), padPos(other.padPos), code(other.code), chars(other.chars)
{}

//_____________________________________________________________________________
/** Assignment operator. */
void PwdOpts::operator=(const PwdOpts& rhs)
{
  help = rhs.help;
  pLevel = rhs.pLevel; seedType = rhs.seedType;

  length = rhs.length;
  all = rhs.all;
  ascii = rhs.ascii; lower = rhs.lower; upper = rhs.upper; digit = rhs.digit; special = rhs.special; 
  words = rhs.words; koremut = rhs.koremut; dice = rhs.dice; skey = rhs.skey; 
  noSpace = rhs.noSpace; proper = rhs.proper; 
  pad = rhs.pad; padPos = rhs.padPos; code = rhs.code; chars = rhs.chars;
}

//_____________________________________________________________________________
/** Destructor. */
PwdOpts::~PwdOpts()
{
  for(UInt_t k=0; k<pad.size(); k++) pad[k] = '0';
  for(UInt_t k=0; k<code.size(); k++) code[k] = '0';  
  for(UInt_t k=0; k<chars.size(); k++) chars[k] = '0';  
}

//_____________________________________________________________________________
/** Set to all available. */
void PwdOpts::setAll(Bool_t val)
{
  all = val;
  setAllAscii(val);
  setAllWords(val);
}

//_____________________________________________________________________________
/** Set to all available. */
void PwdOpts::setAllAscii(Bool_t val)
{
  ascii = val;
  lower = val;
  upper = val;
  digit = val;
  special = val;
}

//_____________________________________________________________________________
/** Set to all available. */
void PwdOpts::setAllWords(Bool_t val)
{
  words = val;
  koremut = val;
  dice = val;
  skey = val;
}

//_____________________________________________________________________________
/** No available unit types. */
Bool_t PwdOpts::none()
{
  if(!all && 
     !ascii && !lower && !upper && !digit && !special && 
     !words && !koremut && !dice && !skey)
    return kTRUE;
  else return kFALSE;
}

//_____________________________________________________________________________
/** Is only ascii. */
Bool_t PwdOpts::onlyAscii()
{
  if(!all && !words && 
     !koremut && !dice && !skey)
    return kTRUE;
  else return kFALSE;
}

//_____________________________________________________________________________
/** Is only words; e.g. a pass-phrase. */
Bool_t PwdOpts::onlyWords()
{
  if(!all && !ascii && 
     !lower && !upper && !digit && !special)
    return kTRUE;
  else return kFALSE;
}

//_____________________________________________________________________________
/** Parse the command-line options
    See gnu.org/software/libc/manual/html_node/Getopt.html for how to use GNU getopt.
*/
void PwdOpts::parseCmdLine(Int_t argc, Char_t** argv)
{
  while(1){

    // struct array for feeding to getopt
    static struct option long_options[] =
      {
	{"help",         no_argument,       0, 'h'},
	{"print-level",  required_argument, 0, 'p'},
	{"seed",         required_argument, 0, 's'},
	{"all",          no_argument,       0, 'a'},
	{"ascii",        no_argument,       0, 'c'},
	{"lower-case",   no_argument,       0, 'l'},
	{"upper-case",   no_argument,       0, 'u'},
	{"digit",        no_argument,       0, 'g'},
	{"special",      no_argument,       0, 'i'},
	{"words",        no_argument,       0, 'w'},
	{"koremutake",   no_argument,       0, 'k'},
	{"dice-words",   no_argument,       0, 'd'},
	{"skey-words",   no_argument,       0, 'y'},
	{"no-space",     no_argument,       0, 'j'},
	{"proper",       no_argument,       0, 'v'},
	{"padding",      required_argument, 0, 'e'},
	{"pad-pos",      required_argument, 0, 'f'},
	{"code",         required_argument, 0, 'o'},
	{"characters",   required_argument, 0, 'r'},
	{0, 0, 0, 0}
      };

    // getopt_long stores the option index here.
    Int_t option_index(0);
    // '' = no argument, ':' = required argument, '::' = optional argument
    Int_t c = getopt_long(argc, argv, "hp:g:s:acludgwkdyjve:o:r:", 
			  long_options, &option_index);
    // Detect the end of the options.
    if (c == -1) break;
     
    // Detect the options.
    switch(c){
    case 'h': help = kTRUE; break;
    case 'p': pLevel = atoi(optarg); break;

    case 's': seedType = String_t(optarg); break;
    case 'a': setAll(kTRUE); break;
    case 'c': setAllAscii(kTRUE); break;
    case 'l': lower = kTRUE; break;
    case 'u': upper = kTRUE; break;
    case 'g': digit = kTRUE; break;
    case 'i': special = kTRUE; break;
    case 'w': setAllWords(kTRUE); break;
    case 'k': koremut = kTRUE; break;
    case 'd': dice = kTRUE; break;
    case 'y': skey = kTRUE; break;
    case 'j': noSpace = kTRUE; break;
    case 'v': proper = kTRUE; break;

    case 'e': pad = String_t(optarg); break;
    case 'f': padPos = atoi(optarg); break;

    case 'o': code = String_t(optarg); break;
    case 'r': chars = String_t(optarg); break;

    case '?': help = kTRUE; break;
    default:  abort();
    } // end switch

  } // end while read opts

  // first non-option is taken as length of pass-word/-phrase
  if(optind < argc)
    length = (UInt_t)atoi(argv[optind++]);
}

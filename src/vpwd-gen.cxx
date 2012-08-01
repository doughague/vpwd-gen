/** \file vpwd-gen.cxx */
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
#include "Globals.hh"
#include "PwdOpts.hh"
#include "Seeder.hh"
#include "MtRand.hh"
#include "PwdGen.hh"

void printUsage(std::ostream& os);

//_____________________________________________________________________________
//! vpwd-gen executable
Int_t main(Int_t argc, Char_t** argv)
{
  // --------------------------------------------
  // get options
  PwdOpts opt(argc, argv);

  // --------------------------------------------
  // print help message
  if(opt.help){
    printUsage(std::cout);
    return 0;
  }      

  // --------------------------------------------
  // check for reasonable options
  if(opt.length <= 0){
    WARN << "Cannot create password with length " << opt.length << std::endl;
    printUsage(std::cout);
    return -1;
  }
  if(opt.none())
    opt.setAll(kTRUE);

  // --------------------------------------------
  // calculate possible entropy
  Double_t posEntropy = PwdGen::calcPossibleEntropy(opt);
  
  // --------------------------------------------
  // create seeder
  Seeder seed(opt.seedType, posEntropy);

  // --------------------------------------------
  // create random generator
  MtRand mt(seed.key(), seed.keyLength());

  // --------------------------------------------
  // create pwd generator
  PwdGen pg(opt, mt);

  // --------------------------------------------
  // generate pass word
  String_t pwd = pg.generate();
  if(opt.pLevel<0){
    std::cout << pwd.c_str() << std::endl;
  } else {
    PASS << pwd.c_str() << std::endl;
    INFO << "--------------------------------------------" << std::endl;    
    INFO << "Possible Entropy = " << posEntropy << " bits" << std::endl;
    INFO << "Observed Entropy = " << PwdGen::calcObservedEntropy(pwd) << " bits" << std::endl;
  }

  // --------------------------------------------
  // overwrite pwd memory
  for(UInt_t k=0; k<pwd.size(); k++) pwd[k] = '0';

  // --------------------------------------------
  // print some infos
  if(opt.pLevel>0){
    pg.printLength(INFO);
    pg.printUnits(INFO);
    INFO << "Seed = " << opt.seedType.c_str() << std::endl;
    seed.printKey(INFO);
  }

  // --------------------------------------------
  // return (success)
  return 0;
}

//_____________________________________________________________________________
//! print program usage to stream
void printUsage(std::ostream& os)
{
  os << "Usage: vpwd-gen [length] [options]" << std::endl;
  os << std::endl;

  os << "Example: vpwd-gen" << std::endl;
  os << "         Will generate an 8 unit password using all possible unit types, " << std::endl;
  os << "         e.g. Ascii characters (upper/lower-case, digits, special) and " << std::endl;
  os << "              Words (koremutakes, DiceWare, SKey)." << std::endl;
  // os << std::endl;

  os << "Example: vpwd-gen 4 --dice-words" << std::endl;
  os << "         Will generate a 4 word DiceWare passphrase" << std::endl;
  os << std::endl;

  os << "WARNING: This software uses a deterministic random number generator (Mersenne Twister)!" << std::endl;
  os << "         Which means that is is NOT suitable for key-generation. The passwords generated" << std::endl;
  os << "         can be reproduced given the seed and, thus, the seed value is as valuable as "  << std::endl;
  os << "         the password itself. However, this alows for \"pretty good\" passwords " << std::endl;
  os << "         and portability (e.g. few dependencies). If the generator can be comprimised based " << std::endl;
  os << "         on the generated password, a warning is issued." << std::endl;
  os << "         Attempts are made to destroy sensitive data when this program exits." << std::endl;
  os << std::endl;

  os << "Documentation: Code (API) can be found at vpwdgen/doc/html/index.html" << std::endl;
  //os << "               other refs??!!" << std::endl;
  os << std::endl;
  
  os << "Options:" << std::endl;
  os << "  [long], [short]    [example] [description]" << std::endl;
  os << "  --help, -h                   show this help message and exit" << std::endl;
  os << "  --print-level, -p  0         amount of info. printed to cout; -1, 0, 1" << std::endl;
  os << "                               -1: only password is printed" << std::endl;
  os << "                               0: (default) password and entropy estimates" << std::endl;
  os << "                               1: password, entropy estimates, and extra info" << std::endl;

  os << "  --seed, -s          random   seed value to use; 0, [integer], random, \"passphrase\"" << std::endl;
  os << "                               0: create from wall-time, system up-time and PID" << std::endl;
  os << "                               [integer]: use input (unsigned long) integer" << std::endl;
  os << "                               random: (default) read sufficient bytes from /dev/urandom" << std::endl;
  os << "                               \"passphrase\": interprete user input passphrase as seed" << std::endl;

  os << "  --all, -a                    flag to include all available password units (default)" << std::endl;
  os << "  --ascii, -c                  flag to include all ASCII characters" << std::endl;
  os << "  --lower-case, -l             flag to include lower case letters" << std::endl;
  os << "  --upper-case, -u             flag to include upper case letters" << std::endl;
  os << "  --digit, -g                  flag to include digits" << std::endl;
  os << "  --special, -i                flag to include special characters" << std::endl;

  os << "  --words, -w                  flag to include all words" << std::endl;
  os << "  --koremutake, -k             flag to include koremutake \"words\"" << std::endl;
  os << "  --dice-words, -d             flag to include DiceWare words" << std::endl;
  os << "  --skey-words, -y             flag to include SKey \"words\"" << std::endl;
  os << "  --no-space, -j               flag to not include spaces between words" << std::endl;
  os << "  --proper, -v                 flag to capitolize the first letter of each word" << std::endl;

  os << "  --padding, -e       asdf%    include (verbose) user input padding in password" << std::endl;
  os << "  --pad-pos, -f       0        where to place the padding; -1, 0, 1 " << std::endl;
  os << "                               -1: place at begining of password" << std::endl;
  os << "                               0: (default) place in middle of password" << std::endl;
  os << "                               1: place at end of password" << std::endl;

  os << "  --code, -o          lugskdy  pattern code for generation (looped until length is satisfied);" << std::endl;
  os << "                               l: lower-case, u: upper-case, g: digit, s: special" << std::endl;
  os << "                               k: koremutake, d: DiceWare word, k: SKey word" << std::endl;

  os << "  --characters, -r    chars    only use these characters in the password" << std::endl;
}

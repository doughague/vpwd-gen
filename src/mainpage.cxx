/** \file src/mainpage.cxx \brief Documentation overview. */

/*! \mainpage
  \author Doug Hague
  \date 24.07.2012

  \section Overview
  This package includes tools for versitile generation of a password.

  \section Install

  0) modify Makefile appropriately

  1) > make

  \section Help

  \code 

Usage: vpwd-gen [length] [options]

Example: vpwd-gen
         Will generate an 8 unit password using all possible unit types, 
         e.g. Ascii characters (upper/lower-case, digits, special) and 
              Words (koremutakes, DiceWare, SKey).
Example: vpwd-gen 4 --dice-words
         Will generate a 4 word DiceWare passphrase

WARNING: This software uses a deterministic random number generator (Mersenne Twister)!
         Which means that is is NOT suitable for key-generation. The passwords generated
         can be reproduced given the seed and, thus, the seed value is as valuable as 
         the password itself. However, this alows for "pretty good" passwords 
         and portability (e.g. few dependencies). If the generator can be comprimised based 
         on the generated password, a warning is issued.
         Attempts are made to destroy sensitive data when this program exits.

Documentation: Code (API) doc can be found at vpwdgen/doc/html/index.html

Options:
  [long], [short]    [example] [description]
  --help, -h                   show this help message and exit
  --print-level, -p  0         amount of info. printed to cout; -1, 0, 1
                               -1: only password is printed
                               0: (default) password and entropy estimates
                               1: password, entropy estimates, and extra info
  --seed, -s          random   seed value to use; 0, [integer], random, "passphrase"
                               0: create from wall-time, system up-time and PID
                               [integer]: use input (unsigned long) integer
                               random: (default) read sufficient bytes from /dev/urandom
                               "passphrase": interprete user input passphrase as seed
  --all, -a                    flag to include all available password units (default)
  --ascii, -c                  flag to include all ASCII characters
  --lower-case, -l             flag to include lower case letters
  --upper-case, -u             flag to include upper case letters
  --digit, -g                  flag to include digits
  --special, -i                flag to include special characters
  --words, -w                  flag to include all words
  --koremutake, -k             flag to include koremutake "words"
  --dice-words, -d             flag to include DiceWare words
  --skey-words, -y             flag to include SKey "words"
  --no-space, -j               flag to not include spaces between words
  --proper, -v                 flag to capitolize the first letter of each word
  --padding, -e       asdf%    include (verbose) user input padding in password
  --pad-pos, -f       0        where to place the padding; -1, 0, 1 
                               -1: place at begining of password
                               0: (default) place in middle of password
                               1: place at end of password
  --code, -o          lugskdy  pattern code for generation (looped until length is satisfied);
                               l: lower-case, u: upper-case, g: digit, s: special
                               k: koremutake, d: DiceWare word, k: SKey word
  --characters, -r    chars    only use these characters in the password
  
  \endcode
*/

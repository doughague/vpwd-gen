/** \file Seeder.cxx */
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
#include <fstream> // for reading files
#include <string.h> // character string methods
#include <iomanip>   // for fixed and setprecision
#include <time.h> // for wall time
#include <sys/sysinfo.h> // for up time
#include <sys/types.h> // for pid_t
#include <unistd.h> // for getpid

#include "Seeder.hh"

//_____________________________________________________________________________
/** Default constructor. */
Seeder::Seeder()
  : _key(0),
    _keyLength(0)
{}

//_____________________________________________________________________________
/** Constructor. */
Seeder::Seeder(String_t type, Double_t entropy)
  : _key(0),
    _keyLength(0)
{
  if(type=="0")
    setFromTime();
  else if(isdigit(type[0]))
    setKey(atol(type.c_str()));
  else if(type=="random")
    setFromDevUrandom(entropy);
  else if(type!="")
    setFromPhrase(type.c_str());
  else
    setKey(kDefaultSeed);
}

//_____________________________________________________________________________
/** Copy constructor. */
Seeder::Seeder(const Seeder& other)
  : _key(0),
    _keyLength(0)
{
  // destroy this key
  allocKey(other._keyLength);
  for(UInt_t k=0; k<other._keyLength; k++) _key[k] = other._key[k];
}

//_____________________________________________________________________________
/** Assignment operator. */
void Seeder::operator=(const Seeder& rhs)
{
  allocKey(rhs._keyLength);
  for(UInt_t k=0; k<rhs._keyLength; k++) _key[k] = rhs._key[k];
}

//_____________________________________________________________________________
/** Destructor. */
Seeder::~Seeder()
{
  // destroy seed (overwrite with zeros)
  clearKey();
  if(_key){ delete [] _key; _key = 0; }
  _keyLength = 0;
}

//_____________________________________________________________________________
/** Destroy (clear) seed key. Overwrite with zeros. */
void Seeder::clearKey()
{
  if(_key) 
    for(UInt_t k=0; k<_keyLength; k++) _key[k] = 0x00000000UL;  
}

//_____________________________________________________________________________
/** Allocate memory for key. */
void Seeder::allocKey(UInt_t size)
{
  clearKey();
  _keyLength = size;
  _key = new ULong_t[_keyLength];
}

//_____________________________________________________________________________
/** Set the key generically. */
Bool_t Seeder::setKey(const ULong_t* key, UInt_t keyLength)
{
  allocKey(keyLength);
  for(UInt_t k=0; k<_keyLength; k++) _key[k] = key[k];
  return kFALSE;
}

//_____________________________________________________________________________
/** Set the key froma single 64bit integer. */
Bool_t Seeder::setKey(ULong_t key)
{
  allocKey(1);
  _key[0] = key;
  return kFALSE;
}

//_____________________________________________________________________________
/** Generate a key-seed based on wall-time, system-up-time and PID. */
Bool_t Seeder::setFromTime()
{
  // Get current time
  time_t curtime;
  time(&curtime);
  ULong_t ct(curtime);

  // Get uptime
  struct sysinfo sys_info;
  Int_t infoerr = sysinfo(&sys_info);
  ULong_t ut = 0;
  if(infoerr == 0) ut = ULong_t(sys_info.uptime);
  else ut = ct;

  // get process ID
  ULong_t pid(getpid());

  // allocate and fill
  allocKey(3);
  _key[0] = ct;
  _key[1] = ut;
  _key[2] = pid;

  // return "failed"
  return kFALSE;
}

//_____________________________________________________________________________
/** Set the key-seed from a pass-phrase. */
Bool_t Seeder::setFromPhrase(const Char_t* phrase)
{
  // Each character of the phrase is represented as a 3-digit number
  // between 0 and 256. Thus, 3 characters can be concatenated into 
  // a 9-digit number and can be held in one "unsigned long" integer
  UInt_t pSize = strlen(phrase);
  UInt_t nLongs(1.*pSize/3);
  if(pSize % 3) nLongs++;
  allocKey(nLongs);

  UInt_t j(0), k(0);
  while(j<pSize){
    // get the char int code as characters
    Char_t cdig[10];
    if(j<pSize-2){
      sprintf(cdig,"%d%d%d",phrase[j],phrase[j+1],phrase[j+2]);
      j += 3;
    }
    else if(j<pSize-1){
      sprintf(cdig,"%d%d",phrase[j],phrase[j+1]);
      j += 2;
    }
    else{
      sprintf(cdig,"%d",phrase[j]);
      j += 1;
    }

    // write to keys as unsigned long
    _key[k] = strtol(cdig,NULL,10); // keep it off the heep?
    // _key[k] = atol(cdig);
    k++;

    // clear memory, since phrase is sensitive
    memset(cdig,0,sizeof(*cdig));
  }

  // clear, since phrase is sensitive
  pSize = 0;
  nLongs = 0;

  // return "failed"
  return kFALSE;
}

//_____________________________________________________________________________
/** Generate a key-seed from entropy read from /dev/urandom. */
Bool_t Seeder::setFromDevUrandom(Double_t entropy)
{
  // claculate number of UInt_t's required
  UInt_t size = 4;
  UInt_t n((entropy+1.)/size);
  allocKey(n);  

  // read /dev/urandom
  std::ifstream fin("/dev/urandom", std::ios::binary);
  if(fin.is_open()){
    UInt_t k(0);
    Char_t* mem = new Char_t[size];
    // get random numbers
    while(k<n){
      fin.read(mem, size);
      _key[k] = *reinterpret_cast<ULong_t*>(mem);
      //std::cout << mem << std::endl;
      k++;      
    }
    // clear memory, since key is sensitive
    memset(mem,0,sizeof(*mem));
    if(mem) delete [] mem;
    // close file
    fin.close();
  }
  else{
    WARN << "Could not open '/dev/urandom'; using time seeder" << std::endl;
    return setFromTime();
  }

  // return "failed"
  return kFALSE;  
}

//_____________________________________________________________________________
/** Print the used options to the stream. */
void Seeder::printKey(std::ostream& os)
{
  os << "Key(s) = ";
  Bool_t first = kTRUE;
  for(UInt_t i=0; i<_keyLength; i++){
    if(first){
      os << _key[i];
      first = kFALSE;
    } else  os << ", " << _key[i];
  }
  os << std::endl;
}

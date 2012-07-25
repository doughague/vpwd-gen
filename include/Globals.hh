/** \file Globals.hh */
#ifndef GLOBALS
#define GLOBALS

//---- includes ----------------------------------------------------------------
#include <stdlib.h> // general utilities
#include <stdio.h>  // for printf, etc.
#include <iostream> // for cout, cerr, clog
#include <string>   // for std::string

//---- types -------------------------------------------------------------------
typedef bool           Bool_t;      //!< Boolean (0=false, 1=true) (bool)
typedef unsigned char  Byte_t;      //!< Byte (8 bits) (unsigned char)

typedef char           Char_t;      //!< Signed Character 1 byte (char)
typedef unsigned char  UChar_t;     //!< Unsigned Character 1 byte (unsigned char)

typedef short          Short_t;     //!< Signed Short integer 2 bytes (short)
typedef unsigned short UShort_t;    //!< Unsigned Short integer 2 bytes (unsigned short)

typedef int            Int_t;       //!< Signed integer 4 bytes (int)
typedef unsigned int   UInt_t;      //!< Unsigned integer 4 bytes (unsigned int)

typedef long           Long_t;      //!< Signed long integer 8 bytes (long)
typedef unsigned long  ULong_t;     //!< Unsigned long integer 8 bytes (unsigned long)

typedef float          Float_t;     //!< Float 4 bytes (float)
typedef double         Double_t;    //!< Double 8 bytes (double)

typedef std::string    String_t;    //!< std::string

//---- constants ---------------------------------------------------------------
const Bool_t kFALSE = false; //!< false (=0)
const Bool_t kTRUE  = true;  //!< true (=1)

const size_t    kBitsPerByte = 8;

const Int_t     kMaxUChar    = 256;
const Int_t     kMaxChar     = kMaxUChar >> 1;
const Int_t     kMinChar     = -kMaxChar - 1;

const Int_t     kMaxUShort   = 65534;
const Int_t     kMaxShort    = kMaxUShort >> 1;
const Int_t     kMinShort    = -kMaxShort - 1;

const UInt_t    kMaxUInt     = UInt_t(~0);
const Int_t     kMaxInt      = Int_t(kMaxUInt >> 1);
const Int_t     kMinInt      = -kMaxInt - 1;

const ULong_t   kMaxULong    = ULong_t(~0);
const Long_t    kMaxLong     = Long_t(kMaxULong >> 1);
const Long_t    kMinLong     = -kMaxLong - 1;

const ULong_t     kTwoPow32 = 4294967296;              //!< 2^32
const Double_t kInvTwoPow32 = 2.3283064365386963e-10;  //!< 2^-32
const ULong_t  kDefaultSeed = 19650218UL;              //<! Default seed value for random generator

//---- outputs -----------------------------------------------------------------
#define RESETCOLOR "\033[0m"        //!< reset color
#define WARNCOLOR "\033[31;01m"     //!< warning color (red)
#define WARN std::cerr << WARNCOLOR << "WARNING: " << RESETCOLOR //!< warning output tag streamer
#define INFOCOLOR "\033[32;01m"     //!< info color (green)
#define INFO std::cout << INFOCOLOR << "Info: " << RESETCOLOR //!< info output tag streamer
#define PASSCOLOR "\033[36;01m"     //!< password color (blue)
#define PASS std::cout << PASSCOLOR << "Pass: " << RESETCOLOR //!< password output tag streamer

//---- methods -----------------------------------------------------------------
void printGlobals(std::ostream& os);

#endif // GLOBALS

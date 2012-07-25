/** \file Globals.cxx */
#include "Globals.hh"

using std::endl;

/** Print globals to the out-stream. */
void printGlobals(std::ostream& os)
{
  os << "Type Definitions:" << endl;
  os << "    Bool_t = bool           (1 bit)" << endl;
  os << "    Byte_t = unsigned char  (8 bits)" << endl;
  os << "    Char_t = char           (1 byte)" << endl;
  os << "   UChar_t = unsigned char  (1 byte)" << endl;
  os << "   Short_t = short          (2 bytes)" << endl;
  os << "  UShort_t = unsigned short (2 bytes)" << endl;
  os << "     Int_t = int            (4 bytes)" << endl;
  os << "    UInt_t = unsigned int   (4 bytes)" << endl;
  os << "    Long_t = long           (8 bytes)" << endl;
  os << "   ULong_t = unsigned long  (8 bytes)" << endl;
  os << "   Float_t = float          (4 bytes)" << endl;
  os << "  Double_t = double         (8 bytes)" << endl;
  os << "  String_t = std::string" << endl;

  os << "Constants:" << endl;
  os << "        kFALSE = " << kFALSE << " (false)" << endl;
  os << "         kTRUE = " << kTRUE << " (true)" << endl;
  os << "  kBitsPerByte = " << kBitsPerByte << endl;
  os << "     kMaxUChar = " << kMaxUChar << endl;
  os << "      kMaxChar = " << kMaxChar << endl;
  os << "      kMinChar = " << kMinChar << endl;
  os << "    kMaxUShort = " << kMaxUShort << endl;
  os << "     kMaxShort = " << kMaxShort << endl;
  os << "     kMinShort = " << kMinShort << endl;
  os << "      kMaxUInt = " << kMaxUInt << endl;
  os << "       kMaxInt = " << kMaxInt << endl;
  os << "       kMinInt = " << kMinInt << endl;
  os << "     kMaxULong = " << kMaxULong << endl;
  os << "      kMaxLong = " << kMaxLong << endl;
  os << "      kMinLong = " << kMinLong << endl;
  os << "     kTwoPow32 = " << kTwoPow32 << endl;
  os << "  kInvTwoPow32 = " << kInvTwoPow32 << endl;

  os << "Output Tags:" << endl;
  os << "  " << WARNCOLOR << "WARNING: " << RESETCOLOR << " (std::cerr)" << endl;
  os << "  " << INFOCOLOR << "INFO: " << RESETCOLOR << " (std::cout)" << endl;
}

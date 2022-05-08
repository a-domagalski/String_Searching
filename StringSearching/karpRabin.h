//
// Created by Adrian on 19.12.2021.
//

#ifndef STRING_SEARCHING_STRINGSEARCHING_KARPRABIN_H_
#define STRING_SEARCHING_STRINGSEARCHING_KARPRABIN_H_
#include "StringSearchingBase.h"
namespace str_search {
typedef unsigned long long ULLONG;
class karpRabin : public StringSearchingBase {
 private:
  ULLONG conv_ptrn;
  ULLONG last_conv_slice;
  ULLONG q_factor;
  ULLONG convertSlice(const std::string &sliceToConv);
  ULLONG convertSliceConst(const std::string &strToConv, const unsigned int &sliceIdx);
 public:
  karpRabin();
  bool findMatch(const unsigned int &, const unsigned int &, Coords &);
  bool findNext(Coords &);
  void setPattern(const std::string &);
};
}

#endif //STRING_SEARCHING_STRINGSEARCHING_KARPRABIN_H_

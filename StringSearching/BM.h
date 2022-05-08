//
// Created by Adrian on 29.12.2021.
//

#ifndef STRING_SEARCHING_STRINGSEARCHING_BM_H_
#define STRING_SEARCHING_STRINGSEARCHING_BM_H_
#include "StringSearchingBase.h"

namespace str_search {
class BM : public StringSearchingBase {
 protected:
  unsigned int shift;
  void setStartShift(const unsigned int &, const unsigned int &);
  void shiftToCoords(Coords &coords);
	public:
  BM();
  void heuristics(const std::string &);
  void basicBM();
  bool findMatch(const unsigned int &, const unsigned int &, Coords &) override;
};
}

#endif //STRING_SEARCHING_STRINGSEARCHING_BM_H_

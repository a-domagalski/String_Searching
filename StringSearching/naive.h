//
// Created by Adrian on 12.12.2021.
//

#ifndef NAIVE_H_
#define STRINGSEARCHING_H_
#include "StringSearchingBase.h"
namespace str_search {
class Naive : public StringSearchingBase {
 public:
  Naive();
  bool findMatch(const unsigned int &, const unsigned int &, Coords &) override;
  bool findNext(Coords &) override;
  bool findPatternInWord(const std::string &, unsigned int &) override;
};
}
#endif //NAIVE_H_

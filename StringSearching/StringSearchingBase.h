//
// Created by Adrian on 06.12.2021.
//
#ifndef STRINGSEARCHINGBASE_H_
#define STRINGSEARCHINGBASE_H_
#include <string>
#include <vector>
#include <array>
#include <set>
namespace str_search {
typedef std::array<unsigned int, 2> Coords;

class StringSearchingBase {
 protected:
  std::string pattern;
  std::vector<Coords> patternCoords;
  std::vector<std::string> lines;
  std::string text;
  unsigned int current_pos_row;
  unsigned int current_pos_col;
  std::set<char> alphabet;

  void getAlphabet(const std::string &);
 public:
  unsigned int ops_counter;

  StringSearchingBase();
  bool operator==(const StringSearchingBase &) const;
  bool operator!=(const StringSearchingBase &) const;

  void SetCurrentPosRow(const unsigned int &);
  void SetCurrentPosCol(const unsigned int &);
  virtual void setPattern(const std::string &);

  void readFile(const std::string &);
  void linesToText();
  virtual bool findMatch(const unsigned int &, const unsigned int &, Coords &) = 0;
  std::string findByCoords(const unsigned int &, const unsigned int &);
  virtual bool findPatternInWord(const std::string &, unsigned int &);
  virtual bool findNext(Coords &);
  std::vector<std::string> getLines();
};
std::string sliceString(const std::string &, const unsigned int &, const unsigned int &);
std::string strToLower(const std::string &);
}

#endif //STRINGSEARCHINGBASE_H_

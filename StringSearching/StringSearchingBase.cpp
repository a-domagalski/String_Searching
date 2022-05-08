//
// Created by Adrian on 06.12.2021.
//

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <algorithm>
#include "StringSearchingBase.h"
namespace str_search {
StringSearchingBase::StringSearchingBase() :
	current_pos_row(0),
	current_pos_col(0),
	ops_counter(0){}

void StringSearchingBase::setPattern(const std::string &StrToSetFrom) {
  pattern = StrToSetFrom;
}

std::vector<std::string> StringSearchingBase::getLines() {
  return lines;
}

unsigned int CountLinesInFile(std::fstream &fileHandle) {
  unsigned int lines_counter = std::count(
	  std::istreambuf_iterator<char>(fileHandle),
	  std::istreambuf_iterator<char>(), '\n');
  lines_counter++;
  fileHandle.seekg(0, std::ios::beg);
  return lines_counter;
}

void StringSearchingBase::getAlphabet(const std::string &text) {
  for (const char &letter: text) {
	alphabet.insert(letter);
  }
}

void StringSearchingBase::readFile(const std::string &FileName) {
  std::fstream file(FileName, std::ios::out | std::ios::in);
  if (file.good()) {
	lines.resize(CountLinesInFile(file));
	unsigned int idx = 0;
	while (file.good()) {
	  std::getline(file, lines[idx]);
	  getAlphabet(lines[idx]);
	  idx++;
	}
  } else {
	std::cout << "file bad\n";
  }
  linesToText();
  file.close();
}

//TODO Make either lines or text (not both) and adjust algorithms implementations.
void StringSearchingBase::linesToText() {
  for (std::string &line: lines) {
	text += line;
  }
}

std::string strToLower(const std::string &strToConvert) {
  std::string converted = strToConvert;
  std::transform(converted.begin(), converted.end(), converted.begin(),
				 [](unsigned char chr) { return std::tolower(chr); });
  return converted;
}

std::string sliceString(const std::string &strToGetSliceFrom,
						const unsigned int &beg_idx,
						const unsigned int &end_idx) {
  std::string slice;
  unsigned int end_idx_cpy = end_idx;
  if (end_idx > strToGetSliceFrom.size()) {
	end_idx_cpy = strToGetSliceFrom.size();
  }
  //Loop len. is slice size
  for (unsigned int i = 0; i < end_idx_cpy - beg_idx; i++) {
	slice += strToGetSliceFrom[beg_idx + i];
  }
  return slice;
}

bool StringSearchingBase::findPatternInWord(const std::string &word, unsigned int &patternCoords) {
  for (unsigned int i = 0; i < word.size(); i++) {
	if (pattern.size() + i < word.size()) {
	  if (strToLower(sliceString(word, 0 + i, pattern.size() + i)) != strToLower(pattern)) {
		continue;
	  } else {
		patternCoords = i;
		return true;
	  }
	} else {
	  break;
	}
  }
  return false;
}

std::string StringSearchingBase::findByCoords(const unsigned int &x, const unsigned int &y) {
  unsigned int y_cpy = y;
  std::string returnWord;
  unsigned int returnWordLine = x;
  for (unsigned int l_iter = x; l_iter < lines.size(); l_iter++) {
	for (unsigned int c_iter = y_cpy; c_iter < lines[l_iter].size(); c_iter++) {
	  if (lines[l_iter][c_iter] != ' ' &&
		  lines[l_iter][c_iter] != '\n' &&
		  returnWordLine == l_iter) {
		returnWord += lines[l_iter][c_iter];
	  } else {
		return returnWord;
	  }
	}
	y_cpy = 0;
  }
  return returnWord;
}

bool StringSearchingBase::operator==(const StringSearchingBase &rhs) const {
  return pattern == rhs.pattern &&
	  patternCoords == rhs.patternCoords &&
	  lines == rhs.lines &&
	  current_pos_row == rhs.current_pos_row &&
	  current_pos_col == rhs.current_pos_col;
}

bool StringSearchingBase::operator!=(const StringSearchingBase &rhs) const {
  return !(rhs == *this);
}

bool StringSearchingBase::findNext(Coords &matchCoords){
  return findMatch(current_pos_row, current_pos_col + pattern.size(), matchCoords);
}

void StringSearchingBase::SetCurrentPosRow(const unsigned int &rowPosToSetFrom) {
  StringSearchingBase::current_pos_row = rowPosToSetFrom;
}
void StringSearchingBase::SetCurrentPosCol(const unsigned int &colPosToSetFrom) {
  StringSearchingBase::current_pos_col = colPosToSetFrom;
}
}

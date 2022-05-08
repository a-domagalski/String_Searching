//
// Created by Adrian on 12.12.2021.
//
#include <iostream>
#include <algorithm>
#include "naive.h"

namespace str_search {
Naive::Naive() : StringSearchingBase() {}

bool Naive::findPatternInWord(const std::string &word, unsigned int &patternCoords) {
  std::string match;
  if (pattern.size() > word.size()){
	return false;
  }
	if(word == pattern){
	  return true;
  }
  return false;
}

bool Naive::findMatch(const unsigned int &lineIdx, const unsigned int &columnIdx, Coords &matchCoords) {
  unsigned int ptrn_in_word_coords = 0;
  unsigned int col_idx = columnIdx;
  for (unsigned int l_idx = lineIdx; l_idx < lines.size(); l_idx++) {
	if (l_idx > lineIdx) {
	  col_idx = 0;
	}
	for (col_idx; col_idx < lines[l_idx].size() - pattern.size(); col_idx++) {
	  if (lines[l_idx].size() < pattern.size()) {
		break;
	  } else if (findPatternInWord(sliceString(lines[l_idx], col_idx, col_idx + pattern.size()),
								   ptrn_in_word_coords)) {
		current_pos_row = l_idx;
		current_pos_col = col_idx;
		matchCoords[0] = l_idx;
		matchCoords[1] = col_idx;
		patternCoords.push_back(matchCoords);
		return true;
	  }
	}
  }
  return false;
}

bool Naive::findNext(Coords &matchCoords) {
  return findMatch(current_pos_row, current_pos_col + pattern.size(), matchCoords);
}

}


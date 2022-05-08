//
// Created by Adrian on 29.12.2021.
//
#include <iostream>
#include "BM.h"

namespace str_search {
BM::BM() : shift(0) {}

void BM::setStartShift(const unsigned int &lineIdx, const unsigned int &columnIdx) {
  unsigned int startShift = 0;
  for (unsigned int l_idx = 0; l_idx < lineIdx; l_idx++) {
	startShift += lines[l_idx].size();
  }
  shift = startShift + columnIdx;
}

void BM::shiftToCoords(Coords &coords) {
  unsigned int shiftCpy = shift;
  for (unsigned int l_idx = 0; l_idx < lines.size(); l_idx++) {
	if (shiftCpy < lines[l_idx].size()) {
	  coords[0] = l_idx;
	  coords[1] = shiftCpy;
	  break;
	}
	shiftCpy -= lines[l_idx].size();
  }
}

void BM::heuristics(const std::string &suffix) {
  std::string patternSlice = sliceString(pattern, 0, pattern.size() - suffix.size());
  std::size_t foundPos = 0;
  foundPos = patternSlice.rfind(suffix);
  if (foundPos != std::string::npos) {
	shift += patternSlice.size() - foundPos;
  } else {
	foundPos = patternSlice.rfind(text[shift + patternSlice.size() - 1 - suffix.size()]);
	if (foundPos != std::string::npos) {
	  shift += patternSlice.size() - foundPos;
	} else {
	  shift += pattern.size();
	}
  }
}

void BM::basicBM() {
  for (unsigned int p_idx = 1; p_idx < pattern.size(); p_idx++) {
	if (text[shift + pattern.size() - 1] == pattern[pattern.size() - 1 - p_idx]) {
	  shift += p_idx;
	  return;
	}
  }
  shift += pattern.size();
}

bool BM::findMatch(const unsigned int &lineIdx, const unsigned int &columnIdx, Coords &matchCoords) {
  setStartShift(lineIdx, columnIdx);
  if (text.size() < pattern.size()) {
	return false;
  }
  while (shift <= text.size() - pattern.size()) {
	ops_counter++;
	if (pattern[pattern.size() - 1] == text[shift + pattern.size() - 1]) {
	  unsigned int controlFlag = 1;
	  for (unsigned int p_idx = 1; p_idx < pattern.size(); p_idx++) {
		if (pattern[pattern.size() - 1 - p_idx] != text[shift + pattern.size() - 1 - p_idx]) {
		  heuristics(sliceString(pattern, pattern.size() - p_idx, pattern.size()));
		  controlFlag = 0;
		  break;
		} else {
		  continue;
		}
	  }
	  if (controlFlag == 1) {
		shiftToCoords(matchCoords);
		current_pos_row = matchCoords[0];
		current_pos_col = matchCoords[1];
		return true;
	  }
	} else {
	  basicBM();
	}
  }
  return false;
}

}
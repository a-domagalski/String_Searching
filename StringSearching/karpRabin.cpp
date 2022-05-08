//
// Created by Adrian on 19.12.2021.
//

#include <iostream>
#include "karpRabin.h"
namespace str_search {

karpRabin::karpRabin() : StringSearchingBase(),
						 conv_ptrn(0),
						 last_conv_slice(0),
						 q_factor((ULLONG)pow(256, 7) - 1) {}

void karpRabin::setPattern(const std::string &strToSetFrom) {
  pattern = strToSetFrom;
  conv_ptrn = convertSlice(pattern);
}

ULLONG karpRabin::convertSlice(const std::string &sliceToConv) {
  std::string copyToConv = sliceToConv;
  copyToConv = strToLower(copyToConv);
  ULLONG convSlice = copyToConv[0] * alphabet.size();
  for (unsigned int i = 1; i < copyToConv.size() - 1; i++) {
	convSlice = (alphabet.size() * (copyToConv[i] + convSlice)) % q_factor;
  }
  convSlice += copyToConv[copyToConv.size() - 1];
  last_conv_slice = convSlice;
  return convSlice;
}

ULLONG karpRabin::convertSliceConst(const std::string &strToConv, const unsigned int &sliceIdx) {
  if (sliceIdx == 0) {
	last_conv_slice = convertSlice(sliceString(strToConv, 0, pattern.size()));
	return last_conv_slice;
  }
  ULLONG convSlice = 0;
  convSlice = ((last_conv_slice -
	  (strToConv[sliceIdx - 1] *
		  (ULLONG)pow(alphabet.size(), pattern.size() - 1)) % q_factor) *
	  alphabet.size()) % q_factor
	  + strToConv[pattern.size() + sliceIdx - 1];
  last_conv_slice = convSlice;
  return convSlice;
}

bool karpRabin::findMatch(const unsigned int &lineIdx,
						  const unsigned int &columnIdx,
						  Coords &matchCoords) {
  unsigned int colIdxCpy = columnIdx;
  for (unsigned int l_iter = lineIdx; l_iter < lines.size(); l_iter++) {
	if (lines[l_iter].size() < pattern.size()){
	  continue;
	}
	for (unsigned int c_iter = colIdxCpy; c_iter < lines[l_iter].size() - (pattern.size() - 1); c_iter++) {
	  current_pos_row = l_iter;
	  current_pos_col = c_iter;
	  ULLONG conv_str = 0;
	  if(pattern.size() > 1){
		conv_str = convertSliceConst(strToLower(lines[l_iter]), c_iter);
	  }
	  else{
		conv_str = convertSlice(sliceString(lines[l_iter], c_iter, c_iter + pattern.size()));
	  }
	  if (conv_str == conv_ptrn) {
		matchCoords[0] = l_iter;
		matchCoords[1] = c_iter;
		return true;
	  }
	}
	colIdxCpy = 0;
  }
  return false;
}

bool karpRabin::findNext(Coords &matchCoords) {
unsigned int columnIdx = current_pos_col + pattern.size() - 1;
if(pattern.size() == 1){
  columnIdx++;
}
  return findMatch(current_pos_row, columnIdx, matchCoords);
}

}


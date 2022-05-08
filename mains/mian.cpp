#include <iostream>
#include <chrono>
#include <windows.h>
#include "../StringSearching/naive.h"

int main() {
  SetConsoleOutputCP( 65001 );
  str_search::Naive ssInstance;
  ssInstance.readFile("potter.txt");
  ssInstance.setPattern("Fancy seeing you here, Professor McGonagall.");

  str_search::Coords matchCoords{0,0};
  std::vector<str_search::Coords> CoordsVec;

  auto start = std::chrono::high_resolution_clock::now();
  if(ssInstance.findMatch(0, 0, matchCoords)){
	CoordsVec.push_back(matchCoords);
  }
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time of search: " <<duration.count() << std::endl;

  while(ssInstance.findNext(matchCoords)){
	CoordsVec.push_back(matchCoords);
  }

  for(const str_search::Coords coords: CoordsVec){
	std::cout<<"found in: "<<coords[0]<<", "<<coords[1]<<std::endl;
  }
  return 0;
}

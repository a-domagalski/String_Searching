//
// Created by Adrian on 30.12.2021.
//

//
// Created by Adrian on 16.12.2021.
//
#include <iostream>
#include <chrono>
#include "../StringSearching/BM.h"

int main() {
  str_search::StringSearchingBase *ssbInstance;
  ssbInstance = new str_search::BM();

  ssbInstance->readFile("short_test_text.txt");
  ssbInstance->setPattern("internet conglomerate, on 2 June 2021 for $18");
  str_search::Coords matchCoords{0, 0};

  auto start = std::chrono::high_resolution_clock::now();

  if (ssbInstance->findMatch(0, 0, matchCoords)) {
	std::cout <<"found in: "<<matchCoords[0]<<", " <<matchCoords[1]<<std::endl;
  }
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time of search: " <<duration.count() << std::endl;

  while (ssbInstance->findNext(matchCoords)) {
	std::cout <<"found in: "<<matchCoords[0]<<", " <<matchCoords[1]<<std::endl;
  }
  std::cout<<ssbInstance->ops_counter<<std::endl;
  return 0;
}

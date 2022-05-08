//
// Created by Adrian on 16.12.2021.
//
#include <iostream>
#include <chrono>
#include "../StringSearching/naive.h"
#include "../StringSearching/karpRabin.h"

int main() {
  str_search::StringSearchingBase *ssbInstance;
  ssbInstance = new str_search::karpRabin();
  ssbInstance->readFile("short_test_text.txt");
  ssbInstance->setPattern("internet conglomerate, on 2 June 2021 for $18");
  unsigned int ii = 0;
  str_search::Coords c{0, 0};

  auto start = std::chrono::high_resolution_clock::now();
  if(ssbInstance->findMatch(0, 0, c)){

	std::cout << "found in: " << c[0] << ", " << c[1] << "\n\n";
  }
  auto stop = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time of search: " <<duration.count() << std::endl;

  return 0;
}

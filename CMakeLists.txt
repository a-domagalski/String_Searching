cmake_minimum_required(VERSION 3.20)
project(string_searching)

set(CMAKE_CXX_STANDARD 14)

set(glob StringSearching/StringSearchingBase.cpp StringSearching/StringSearchingBase.h
        StringSearching/naive.cpp StringSearching/naive.h
        StringSearching/karpRabin.cpp StringSearching/karpRabin.h
        StringSearching/BM.cpp StringSearching/BM.h)


add_executable(string_searching mains/mian.cpp ${glob})
add_executable(kr_test mains/kr_test.cpp ${glob})
add_executable(bm_test mains/bm_test.cpp ${glob})
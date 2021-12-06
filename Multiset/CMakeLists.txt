# CMakeList.txt : CMake project for Multiset, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Multiset "Multiset.cpp" "Multiset.h" "Multiset_implement.h" "RB_Iterator.h" "RBIterator_impl.h" "Node.h")

# TODO: Add tests and install targets if needed.

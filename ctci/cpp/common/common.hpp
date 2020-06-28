#pragma once

#include <vector>

template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v);

#include "common.cpp"




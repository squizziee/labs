#pragma once

template <int rows, int cols>
std::vector<int> createVector(int(&matrix)[rows][cols]);
int multOfElements(std::vector<int> vect);
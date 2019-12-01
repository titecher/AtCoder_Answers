#ifndef CONSTRAINTS_HPP
#define CONSTRAINTS_HPP

#include <cstdint>
#include <cstddef>

const size_t MIN_N = 200;
const size_t MAX_N = 400;

const size_t MIN_C = 1;
const size_t MAX_C = 100;

const size_t TIME_LIMIT = 10000;
const size_t TIME_LAST = static_cast<size_t>(TIME_LIMIT * 0.95);

const size_t INDEXED = 1;

const size_t MAX_DEGREE = 5;

const size_t MIN_N_ORDER = 0;
const size_t MAX_N_ORDER = 1;

const size_t MIN_ID = 1;
const size_t MAX_ID = TIME_LAST + 1;

const size_t MIN_FREQ = 1;
const size_t MAX_FREQ = 2;

const size_t SCALE_HIGHWAY = 2;
const size_t SCALE_ROAD = 4;

const size_t NUM_OF_CASE = 2;

#endif

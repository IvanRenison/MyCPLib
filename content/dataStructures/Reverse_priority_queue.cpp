#pragma once

#include <IncludeTemplate.hpp>

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

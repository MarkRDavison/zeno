#define CATCH_INTERNAL_UNSUPPRESS_PARENTHESES_WARNINGS

#include <fakeit.hpp>

#ifdef __GNUG__

// Fakeit does not work with GCC's devirtualization
// which is enabled with -O2 (the default) or higher.
#pragma GCC optimize("no-devirtualize")

#endif
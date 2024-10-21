#pragma once

#include "MemLeakDetector.h"//Contains overloads for new and delete to check for memory leaks
#include "new_macro.h"//Contains macros for getting line file and line info from new and delete, MUST BE #included AFTER MemLeakDetector.h
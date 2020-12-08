#pragma once

#ifdef DEMODLL_EXPORTS //Visual Studio specifies this name.
#define FUNC_API __declspec(dllexport)
#else
#define FUNC_API __declspec(dllimport)
#endif


extern "C" FUNC_API float** transform_matrix(
    float** matrix, const size_t rows, const size_t cols);

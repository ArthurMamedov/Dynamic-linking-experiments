#include <windows.h> 
#include <iostream>

//Functions pointer prototype we want to import to our application
typedef float** (__cdecl* FUNC)(float**, const size_t, const size_t);

void print_matrix(float** matrix, const size_t rows, const size_t cols) {
    for (size_t c = 0; c < rows; c++) {
        for (size_t p = 0; p < cols; p++) {
            std::cout << matrix[c][p] << ' ';
        } std::cout << std::endl;
    }
}

auto main() -> int {
    HINSTANCE hinstLib;  //Descriptor of our dynamic library.
    FUNC ProcAdd;  //Pointer to our function. Here and now it is empty.
    BOOL fFreeResult;  //Some checks we will describe further.

    const size_t ROWS = 5;
    const size_t COLS = 3;
    float** matrix = new float* [ROWS];
    float** new_matrix = nullptr;
    for (size_t c = 0; c < ROWS; c++) {
        matrix[c] = new float[COLS];
        for (size_t p = 0; p < COLS; p++) {
            matrix[c][p] = static_cast<float>(rand() % 100);
        }
    }
    print_matrix(matrix, ROWS, COLS);
    
    //Here we loading our library to the current executable binary and saving the descriptor to 'hinstLib'
    hinstLib = LoadLibrary(TEXT("demodll.dll"));

    //Here we check if the library was loaded.
    if (hinstLib != NULL) {
        //Here we seeking for the address of needed function from dll.
        ProcAdd = (FUNC)GetProcAddress(hinstLib, "transform_matrix");
        //Check if we've found it.
        if (NULL != ProcAdd) {
            new_matrix = (ProcAdd)(matrix, ROWS, COLS);
        } else {
            std::cerr << "Didn't manage to find the function" << std::endl;
        }
        //Detaching the dll and writing the result (did we manage to detach) to 'fFreeResult'
        fFreeResult = FreeLibrary(hinstLib);
    } else {
        //Printing error message if we didn't manage to find the dll.
        std::cerr << "Error: didn't manage to find demodll.dll!" << std::endl;
    }

    print_matrix(new_matrix, COLS, ROWS);

    for (size_t c = 0; c < ROWS; c++)
        delete[] matrix[c];
    for (size_t c = 0; c < COLS; c++)
        delete[] new_matrix[c];
    delete[] new_matrix;
    delete[] matrix;

    return 0;
}
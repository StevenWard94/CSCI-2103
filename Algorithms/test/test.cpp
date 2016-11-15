#include "search_sort.cpp"

#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>

template<class T>
std::string show(T* arr, size_t n) {
    std::string arr_str{ "[ " };
    for (size_t i = 0; i < n; i++) {
        std::string buf = std::to_string(*(arr + i));
        arr_str.append(buf).append(" ");
    }
    return arr_str.append("]");
}


template<class Iterator>
std::string show(Iterator const fst, Iterator const last) {
    std::string cntnr_str{ "{ " };
    for (Iterator it = fst; it != last; it++) {
        std::string buf = std::to_string(*it);
        cntnr_str.append(buf).append(" ");
    }
    return cntnr_str.append("}");
}

int main(int argc, char** argv) {
    int* arr_A = new int[5] { 3, 9, 1, 4, 7 };
    int arr_B[] = { 23, 14, 15, 3, 62, 21, 17, 9 };

    std::vector<double> vec_A { 1.7, 9.2, 3.0, 12.6, 12.7, 12.8, 4.3 };
    std::vector<double> vec_B { 7.1, 2.9, 0.3, 62.1, 72.1, 82.1, 3.4 };

    std::cout << "ARRAY TEST 1: " << show(arr_A, 5) << std::endl;
    sort::bubble(arr_A, 5);
    std::cout << "RESULT: " << show(arr_A, 5) << std::endl << std::endl;

    return 0;
}

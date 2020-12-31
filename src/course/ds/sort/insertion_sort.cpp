#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace sorting {

template <typename T>
void insertion_sort(T *array, int n){
    for (int i = 1; i < n; ++i)
    {
        T temp = array[i];
        int j = i - 1;

        // find the first element which bigger or equal than temp
        while(j >= 0 && temp < array[j]){
            array[j + 1] = array[j];
            --j;
        }

        array[j + 1] = temp;
    }
}

// vector version
template <typename T>
void insertion_sort(std::vector<T> *array){
    size_t n = array->size();

    for (size_t i = 1; i < n; ++i){
        T temp = array[0][i];
        int32_t j = i - 1;
        while(j >= 0 && temp < array[0][j]){
            array[0][j+1] = array[0][j];
            j--;
        }

        array[0][j + 1] = temp;
    }
}
} // end of namespace


// test cases
template <typename T>
static void  create_random_array(T *array, int n)
{
    while (n--){
        double r = (std::rand() % 10000 - 5000) / 100.f;
        array[n] = static_cast<T>(r);
    }
}


int main(){
    float array[50];
    create_random_array(array, 50);
    sorting::insertion_sort(array, 50);
    
    for (int i = 0; i < 50; ++i)
        std::cout << array[i] << " ";
    
    std::cout << std::endl;
}
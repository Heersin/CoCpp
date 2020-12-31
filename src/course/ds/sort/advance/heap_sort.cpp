#include <algorithm>
#include <cassert>
#include <iostream>

template <typename T>
void print_array(T *array, int size)
{
    for (int i = 0; i < size; ++i)
        std::cout << array[i] << " ";
    std::cout << "\n";
}

template <typename T>
void heapify(T *array, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && array[l] > array[largest])
        largest = l;

    if (r < n && array[r] > array[largest])
        largest = r;
    
    if (largest != i){
        std::swap(array[i], array[largest]);
        heapify(array, n, largest);
    }
}


template <typename T>
void heap_sort(T *array, int n)
{
    for (int i = n - 1; i >= 0; --i)
        heapify(array, n, i);
    
    for (int i = n - 1; i >= 0; --i)
    {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}


void test(){
    int array[] = {-10, 78, -1, -6, 7, 4, 94, 5, 99, 0};
    int size = sizeof(array) / sizeof(array[0]);

    print_array(array, size);
    heap_sort(array, size);
    print_array(array, size);
}

int main(){
    test();
    return 0;
}
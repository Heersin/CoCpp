#include <iostream>

using namespace std;

int main()
{
    int array[6];
    cout << "Enter 6 Number : ";

    // Input 
    for (int i = 0; i < 6; ++i)
        cin >> array[i];
    

    for (int i = 0; i < 6; ++i){
        int min = i;
        for (int j = i + 1; j < 6; ++j){
            if ( array[j] < array[min] )
                min = j;
        }

        int temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }


    // output
    cout << "sorted array : ";
    for (int i = 0; i < 6; ++i)
        cout << array[i] << "\t";
    
    return 0;
}
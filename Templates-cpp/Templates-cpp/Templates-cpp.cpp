#include "Templates-cpp.h"
#include <iostream>


int main()
{
    Deque<int> dInt;
    Deque<int> dInt2;
    if (dInt2.isEmpty()) {
        printf("empty\n");
    }

    dInt.pushFront(5);
    dInt.pushFront(6);
    dInt.pushFront(6);

    dInt2.pushFront(5);
    dInt2.pushFront(6);
    dInt2.pushFront(6);

    if (dInt == dInt2) {
        printf("equal\n");
    }
    else {
        printf("not equal\n");
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include "Templates-cpp.h"
#include <iostream>


int main()
{
    Deque<int> dInt;
    dInt.pushBack(3);
    dInt.pushBack(4);
    dInt.pushBack(5);
    printf("%d->", dInt[0]);
    printf("%d->", dInt[1]);
    printf("%d->", dInt[2]);
    Deque<int> dInt2 = dInt;
    printf("\n%d->", dInt2[0]);
    printf("%d->", dInt2[1]);
    printf("%d->", dInt2[2]);
    dInt.pushFront(8);
    dInt2 = dInt; 
    printf("\n%d->",dInt2[0]);
    printf("%d->", dInt2[1]);
    printf("%d->", dInt2[2]);
    printf("%d->", dInt2[3]);
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

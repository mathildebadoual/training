#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

void value(int a, int b)
{
    clock_t tStart = clock();
    int temp;
    temp=a;
    a=b;
    b=temp;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}

void reference(int &x, int &y) {
    clock_t tStart = clock();
    int temp;
    temp = x;
    x = y;
    y = temp;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}


int main(int argc, const char* argv[]) {
    int a=100, b=200;
    cout << "Before value function, value of a :" << a << endl;
    cout << "Before value function, value of b :" << b << endl;
    value(a, b);
    cout << "After value function, value of a :" << a << endl;
    cout << "After value function, value of b :" << b << endl;
    reference(a, b);
    cout << "After reference function, value of a : " << a << endl;
    cout << "After reference function, value of b : " << b << endl;
    return 0;
}

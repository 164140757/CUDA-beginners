#include <math.h>
#include <stdlib.h>
#include <iostream> 

// (Pi*R^2)/(2R*2R)=Pi/4
int main(int argc, char const *argv[])
{
    int runs=0;
    int inside_circle=0;
    while(true){
        runs++;
        float x = 2*drand48()-1; //[-1, 1]
        float y = 2*drand48()-1;
        if (x*x + y*y < 1)
            inside_circle++;
        if (runs % 100000 == 0)
            std::cout << "Estimate of Pi = " << 4*float(inside_circle)/runs << "\n";
    }
}


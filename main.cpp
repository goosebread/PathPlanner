//Team Sombrero

#include "SinglePair.h"
#include "A_star.h"
#include "Wavefront.h"



int main()
{
    try
    {
        runBasic();

        //still need a way to print the sequence for dijkstra and bellman-ford

        //runWavefront();
        //runAStar();
    }
    catch (const char* msg) {
        std::cerr << msg << "\n";
    }
    return 0;
}

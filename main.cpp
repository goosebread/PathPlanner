//Team Sombrero

#include "SinglePair.h"
#include "SingleSource.h"
#include "A_star.h"
#include "Wavefront.h"



int main()
{
    try
    {
        //runBasic();

        //runBFDijkstra();

        //runWavefront();
        runAStar();
    }
    catch (const char* msg) {
        std::cerr << msg << "\n";
    }
    return 0;
}

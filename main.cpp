//Team Sombrero

#include "SinglePair.h"
#include "A_star.h"
#include "Wavefront.h"

int main()
{
    try
    {
        //parts b-e
        runWavefront();
    }
    catch (const char* msg) {
        std::cerr << msg << "\n";
    }
    return 0;
}

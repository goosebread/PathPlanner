//Team Sombrero

#include "SinglePair.h"
#include "A_star.h"

int main()
{
    try
    {
        //parts b-e
        runAStar();
    }
    catch (const char* msg) {
        std::cerr << msg << "\n";
    }
    return 0;
}

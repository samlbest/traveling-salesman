#include "city.h"
#include "algorithms.h"
#include <iostream>
#include <deque>
#include <cstdlib>

using namespace std;

int main(int argc, char * argv[])
{
    srand(time(0));  
    
    tsp test(argv[1]);              //read in command line input
    test.nearest_neighbor();        //run nearest neighbor function
    return 0;
}

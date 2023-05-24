#include <iostream>
#include "Tests/Test.h"
#include "Tests/ParticleTest.h"
#include "Tests/ForceTest.h"
#include "Tests/JointTest.h"
#include "Tests/ShapeTest.h"

int main(int argc, char* argv[])
{
    Test* test = new ForceTest();
    test->Initialize();

    while (!(test->IsQuit()))
    {
        test->Run();
    }
    
    delete test;
    return 0;
}
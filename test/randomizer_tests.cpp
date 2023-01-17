#include <unity.h>
#include <stdio.h>
#include "../src/services/randomizer.h"


Randomizer _randomizer;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

int main() {
    UNITY_BEGIN();

    for (auto i = 0; i < 1000; i++)
    {
        auto r = _randomizer.GetDirection();
        // printf("%d\n", r);
    }
    _randomizer.Dump();
    

    UNITY_END();
}

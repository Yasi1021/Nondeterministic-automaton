#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <fstream>
#include "fileManager.h"
#include "tests.h";

int main()
{
    TestDeterministic();
    TestDeterministicWithEpsilonTranzitions();
    TestFunctions();
    TestRecognize();
    TestRegularExpression();
    TestUn();
    TestConcat();
    TestUnion();

  return 0;
}

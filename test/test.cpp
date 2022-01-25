#include "../Logger/Logger.h"
#include <thread>
#include <iostream>
#include <memory>

using namespace std;

int main()
{
    Logger::Logger log;
    for(int i = 0; i < 100; i++)
        log.printLog(0, "sex", "ee");
    return 0;
}
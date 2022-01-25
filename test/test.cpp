#include "../Logger/Logger.h"
#include <thread>
#include <iostream>
#include <memory>

using namespace std;

int main()
{
    Logger::Logger log;

    log.setMsecOpt(true);
    log.setWdayOpt(true);

    // test
    log.printLog(0, "127.0.0.1", "Hello", "Logger!");
    return 0;
}
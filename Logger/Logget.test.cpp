#include <Logger/Logger.hpp>
#include <thread>
#include <iostream>
#include <memory>
#include <ctime>
#include <unistd.h>

using namespace std;

int main()
{
    Logger::Logger log;

    log.setMsecOpt(true);
    log.setWdayOpt(true);

    // test
    for(int i = 0; i < 20; i++) {
        log.printLog(2, "127.0.0.1", "Hello", "Logger!");
        usleep(100000);
    }
    return 0;
}
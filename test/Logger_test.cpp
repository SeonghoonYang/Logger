#include "../src/Logger.hpp"
#include <thread>
#include <iostream>
#include <memory>
#include <ctime>
#include <unistd.h>
#include <vector>
#include <string>

enum MyLogLevel { I, T, W, E, D };
    

void testFunc1(int logLevel, log::Logger plog)
{
    for(int i = 0; i < 20; i++)
        plog.printLog(logLevel, "I'm ", "logging..");
}

int main()
{
    using namespace std;

    log::Logger log("Logger_ex.txt");

    log.setMsecOpt(true);
    log.setWdayOpt(true);

    log.printLog(T, "trace", "127.0.0.1!!");
    log.printLog(I, "test");
    log.addLevel(D, "DEBUG", log::Color::B_CYAN);
    log.printLog(D, "This is Debug");
    log.printLog(E, "Funny", "Error");

    // multi threads
    std::vector<std::thread> threads;
    threads.reserve(5);

    log.setFileOpt(true);

    for(int i = 0; i < 5; i++)
    {
        threads.push_back(std::thread(testFunc1, i, log));
    }

    for(auto& th : threads)
        th.join();

    return 0;
}
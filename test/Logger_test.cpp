#include "../src/Logger.hpp"
#include <thread>
#include <iostream>
#include <memory>
#include <ctime>
#include <unistd.h>
#include <vector>
#include <string>

void testFunc1(int logLevel, log::Logger plog)
{
    enum MyLogLevel { I, T, W, E, D };
    
    for(int i = 0; i < 20; i++)
        plog.printLog(logLevel, "I'm ", "logging..");
}

int main()
{

    /* TODO:
        1. cout, cerr 처리 o
        2. 파일입출력 처리 o
        3. 터미널 색상처리 o
        4. options함수 오버로딩 구현 o
        5. 레벨 만들기 구현 o
        6. 멀티스레딩환경 테스트 o
        7. 복사생성자 할당자 통해 옵션복사 o
    */

    using namespace std;

    log::Logger log("Logger_ex.txt");

    log.setMsecOpt(true);
    log.setWdayOpt(true);

    enum MyLogLevel { I, T, W, E, D };

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
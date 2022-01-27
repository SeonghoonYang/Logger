#include "../src/Logger.hpp"
#include <thread>
#include <iostream>
#include <memory>
#include <ctime>
#include <unistd.h>

using namespace std;

int main()
{

    /* TODO:
        1. cout, cerr 처리 o
        2. 파일입출력 처리 o
        3. 터미널 색상처리 o
        4. options함수 오버로딩 구현 o
        5. 레벨 만들기 구현 o
        6. 멀티스레딩환경 테스트
    */
    log::Logger log("Logger_ex.txt");

    log.setMsecOpt(true);
    log.setWdayOpt(true);

    enum MyLogLevel {
        I,
        T,
        W,
        E,
        D
    };

    log.printLog(T, "trace", "127.0.0.1!!");
    log.printLog(I, "test");
    log.addLevel(D, "debug..", log::Color::B_CYAN);
    log.printLog(D, "This is Debug");
    log.printLog(E, "Funny", "Error");

    return 0;
}
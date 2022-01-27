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
        1. cout, cerr 처리
        2. 파일입출력 처리
        3. 터미널 색상처리
        4. options함수 오버로딩 구현
        5. 레벨 만들기 구현
        6. 멀티스레딩환경 테스트
    */
    Logger::Logger log("Logger_ex.txt");

    log.setMsecOpt(true);
    log.setWdayOpt(true);


    log.setWdayOpt(false);
    log.setFileOpt(true);
    // test
    for(int i = 0; i < 10; i++) {
        log.printLog(2, "127.0.0.1", "Hello", "Logger!");
    }
    
    log.setFileOpt(false);

    return 0;
}
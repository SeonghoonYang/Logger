#pragma once

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <stack>
#include <map>
#include <string>
#include <cstring>

#include <chrono>
#include <ctime>

#include <iostream>
#include <fstream>

namespace Logger 
{
    constexpr unsigned int TIME_INFO_NUM = 4;

    constexpr uint8_t COUT_FLAG = 1;
    constexpr uint8_t MSEC_FLAG = 2;
    constexpr uint8_t WDAY_FLAG = 4;
    constexpr uint8_t TIME_FLAG = 8;
    constexpr uint8_t DATE_FLAG = 16;
    constexpr uint8_t FILE_FLAG = 128;

    class Logger
    {
    private:
    
        unsigned int        m_max_len;

        uint8_t             m_options;
    
        std::string         m_file_name;
        std::string         m_log_statement;
        std::map
        <int, std::string>  m_levels;
        
        void switchOnOff(bool, uint8_t);
        

        void concatLog() { return; }
        template<typename String, typename... Strings>
        void concatLog(const String& log, Strings... logs);

    public:
        Logger(unsigned int max_len = 128, uint8_t options = 24);

        void setOptions(uint8_t options);
        void setDateOpt(bool);
        void setTimeOpt(bool);
        void setWdayOpt(bool);
        void setMsecOpt(bool);
        void setCoutOpt(bool);
        void setFileOpt(bool);
        void setFileName(const std::string& file_name);

        void setLevels(unsigned int level_num, const std::string& level_name);

        template<typename String, typename... Strings>
        void printLog(unsigned int level_num, const String& log, Strings... logs);
    };

    // enum class?


    //////////////////////////////////////////////////////////////////////////////////////////

    // size_t getStringSize(const char* s) { return strlen(s); }

    // size_t getStringSize(const std::string& s) { return s.size(); }

    // template <typename String, typename... Strings>
    // size_t getStringSize(const String& s, Strings... strs)
    // {
    //     return getStringSize(s) + getStringSize(strs...);
    // }

}

#include "Logger.hpp"

#endif
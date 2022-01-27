#pragma once

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <map>
#include <string>
#include <cstring>
#include <utility>

#include <chrono>
#include <ctime>
#include <mutex>

#include <iostream>
#include <fstream>
#include <stdexcept>


namespace log
{
    constexpr unsigned int TIME_INFO_NUM = 4;

    constexpr uint8_t COUT_FLAG = 1;
    constexpr uint8_t MSEC_FLAG = 2;
    constexpr uint8_t WDAY_FLAG = 4;
    constexpr uint8_t TIME_FLAG = 8;
    constexpr uint8_t DATE_FLAG = 16;
    constexpr uint8_t FILE_FLAG = 128;

    enum class Color
    {
        RED, BLUE, GREEN, YELLOW, PURPLE, CYAN, GRAY,
        B_RED, B_BLUE, B_GREEN, B_YELLOW, B_PURPLE, B_CYAN, B_GRAY,
        WHITE
    };

    class Logger
    {
    private:
        static std::mutex   s_log_mtx;
        static const std::map<Color, std::string>  s_color_map;
    
        unsigned int        m_max_len;
        uint8_t             m_options;
    
        std::string         m_file_name;
        std::string         m_log_statement;
        std::map<int, std::pair<std::string, Color> >  m_levels;
        
        void switchOnOff(bool, uint8_t);

        void concatLog() { return; }

        template<typename String, typename... Strings>
        void concatLog(const String& log, Strings... logs);

    public:
        Logger(const std::string& file_name, unsigned int max_len = 128);
        Logger(const Logger& rhs);
        Logger& operator= (const Logger& rhs);
        ~Logger();

        void setOptions(
            bool on_date = true,
            bool on_time = true,
            bool on_msec = false,
            bool on_wday = false,
            bool on_cout = false,
            bool on_file = false
            );
        void setDateOpt(bool);
        void setTimeOpt(bool);
        void setWdayOpt(bool);
        void setMsecOpt(bool);
        void setCoutOpt(bool);
        void setFileOpt(bool);

        void setFileName(const std::string& file_name = "Logger_log.txt");

        void addLevel(
            unsigned int        level_num, 
            const std::string&  level_name,
            Color               levle_color = Color::WHITE
            );

        template<typename String, typename... Strings>
        void printLog(unsigned int level_num, const String& log, Strings... logs);
    };

    template<typename String, typename... Strings>
    void Logger::concatLog(const String& log, Strings... logs)
    {
        m_log_statement.append(" ");
        m_log_statement.append(log);
        concatLog(logs...);
    }

    template<typename String, typename... Strings>
    void Logger::printLog(unsigned int level_num, const String& log, Strings... logs)
    {
        
        // order safe
        std::lock_guard<std::mutex> lock(s_log_mtx);
        
        // get very first currenttime
        auto _time = std::chrono::system_clock::now();
        
        // Level
        m_log_statement.append("[");
        try 
        {
            if (!(m_options & FILE_FLAG)) 
                m_log_statement.append(s_color_map.at(m_levels.at(level_num).second));
            m_log_statement.append(m_levels[level_num].first);
            if (!(m_options & FILE_FLAG)) 
                m_log_statement.append(s_color_map.at(Color::WHITE));
        
        }
        catch (std::exception& e)
        {
            m_log_statement.append("???");
        }
        m_log_statement.append("] ");

        // C-style
        char prefix_infos[TIME_INFO_NUM][16];
        unsigned int index = 0;
        
        // Msec
        if (m_options & MSEC_FLAG) 
        {
            int msec = std::chrono::duration_cast<std::chrono::milliseconds>
                (_time.time_since_epoch()).count() % 1000;
            sprintf(prefix_infos[index++], "%03dms", msec);
        }

        // for Time, Date, WDay
        auto event_time = std::chrono::system_clock::to_time_t(_time);
        struct tm time_info;
        localtime_r(&event_time, &time_info);   
        
        // Time
        if (m_options & TIME_FLAG)
            sprintf(prefix_infos[index++], "%02d:%02d:%02d", time_info.tm_hour, time_info.tm_min, time_info.tm_sec);

        // Wday
        if (m_options & WDAY_FLAG)
        {
            switch(time_info.tm_wday)
            {
            case 0: prefix_infos[index][0] = 'S'; prefix_infos[index][1] = 'u'; prefix_infos[index][2] = 'n'; break;
            case 1: prefix_infos[index][0] = 'M'; prefix_infos[index][1] = 'o'; prefix_infos[index][2] = 'n'; break;
            case 2: prefix_infos[index][0] = 'T'; prefix_infos[index][1] = 'u'; prefix_infos[index][2] = 'e'; break;
            case 3: prefix_infos[index][0] = 'W'; prefix_infos[index][1] = 'e'; prefix_infos[index][2] = 'd'; break;
            case 4: prefix_infos[index][0] = 'T'; prefix_infos[index][1] = 'h'; prefix_infos[index][2] = 'u'; break;
            case 5: prefix_infos[index][0] = 'F'; prefix_infos[index][1] = 'r'; prefix_infos[index][2] = 'i'; break;
            case 6: prefix_infos[index][0] = 'S'; prefix_infos[index][1] = 'a'; prefix_infos[index][2] = 't'; break;
            default: prefix_infos[index][0] = 'X'; prefix_infos[index][1] = 'X'; prefix_infos[index][2] = 'X'; break;
            }
            prefix_infos[index++][3] = '\0';
        }

        // Date
        if (m_options & DATE_FLAG)
            sprintf(prefix_infos[index++], "%04d-%02d-%02d", time_info.tm_year + 1900, time_info.tm_mon + 1, time_info.tm_mday);
 
        m_log_statement.append("(");
        
        if (index != 0) 
            m_log_statement.append(prefix_infos[index - 1]);

        for (int i = index - 2; i >= 0; i--) 
        {
            m_log_statement.append(" ");
            m_log_statement.append(prefix_infos[i]);
        }

        m_log_statement.append(") ");
        m_log_statement.append(log);

        concatLog(logs...);

        m_log_statement.append("\n");

        if (m_options & FILE_FLAG)
        {
            try
            {
                // slow
                std::ofstream fout(m_file_name, std::ios::app);
                if (!fout.is_open())
                {
                    throw std::string("Logger: ")
                        + m_file_name 
                        + " file ostream error. log-";
                }
                fout << m_log_statement;
            }
            catch (const std::string& msg)
            {
                std::cerr << msg + m_log_statement;
                setFileOpt(true); // recover
            }
        }
        else 
        {
            if (m_options & COUT_FLAG)
                std::cout << m_log_statement << std::flush;
            else
                std::cerr << m_log_statement;
        }

        m_log_statement.clear();
    }
}

#endif
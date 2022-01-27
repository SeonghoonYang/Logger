#include "Logger.hpp"

namespace log
{
    std::mutex Logger::s_log_mtx;
    const std::map<Color, std::string> Logger::s_color_map = {
        { Color::RED,       "\033[0;31m" },
        { Color::BLUE,      "\033[0;34m" },
        { Color::GREEN,     "\033[0;32m" },
        { Color::YELLOW,    "\033[0;33m" },
        { Color::PURPLE,    "\033[0;35m" },
        { Color::CYAN,      "\033[0;36m" },
        { Color::GRAY,      "\033[0;30m" },
        { Color::B_RED,     "\033[1;31m" },
        { Color::B_BLUE,    "\033[1;34m" },
        { Color::B_GREEN,   "\033[1;32m" },
        { Color::B_YELLOW,  "\033[1;33m" },
        { Color::B_PURPLE,  "\033[1;35m" },
        { Color::B_CYAN,    "\033[1;36m" },
        { Color::B_GRAY,    "\033[1;30m" },
        { Color::WHITE,     "\033[0;0m"  }
    };

    Logger::Logger(const std::string& file_name, unsigned int max_len)
     : m_max_len(max_len), m_options(0), m_file_name(file_name)
    {
        setOptions(true, true, false, false, false, false);
        m_log_statement.reserve(m_max_len);
        m_levels[0] = std::make_pair("INFO", Color::WHITE);
        m_levels[1] = std::make_pair("TRACE", Color::BLUE);
        m_levels[2] = std::make_pair("WARN", Color::YELLOW);
        m_levels[3] = std::make_pair("ERROR", Color::B_RED);
    }
    
    void Logger::addLevel(
        unsigned int        level_num,
        const std::string&  level_name,
        Color               level_color
        )
    {
        m_levels[level_num] = std::make_pair(level_name, level_color);
    }

    void Logger::setOptions(
        bool on_date,
        bool on_time,
        bool on_msec,
        bool on_wday,
        bool on_cout,
        bool on_file
        )
    {
        setDateOpt(on_date);
        setTimeOpt(on_time);
        setWdayOpt(on_wday);
        setMsecOpt(on_msec);
        setCoutOpt(on_cout);
        setFileOpt(on_file);
    }

    void Logger::switchOnOff(bool onOff, uint8_t flag) 
    {
        if (onOff)
            m_options |= flag;
        else
            m_options &= ~flag;
    }

    void Logger::setDateOpt(bool onOff) { switchOnOff(onOff, DATE_FLAG); }
    void Logger::setTimeOpt(bool onOff) { switchOnOff(onOff, TIME_FLAG); }
    void Logger::setWdayOpt(bool onOff) { switchOnOff(onOff, WDAY_FLAG); }
    void Logger::setMsecOpt(bool onOff) { switchOnOff(onOff, MSEC_FLAG); }
    void Logger::setCoutOpt(bool onOff) { switchOnOff(onOff, COUT_FLAG); }
    void Logger::setFileOpt(bool onOff) { switchOnOff(onOff, FILE_FLAG); }
    void Logger::setFileName(const std::string& file_name) 
    {
        m_file_name = file_name;
    }
}

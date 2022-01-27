#include "Logger.hpp"

namespace Logger{
    std::mutex Logger::s_log_mtx;

    Logger::Logger(const std::string& file_name, unsigned int max_len)
     : m_max_len(max_len), m_options(0), m_file_name(file_name)
    {
        setOptions(true, true, false, false, false, false);
        m_log_statement.reserve(m_max_len);
        m_levels[0] = "INFO";
        m_levels[1] = "TRACE";
        m_levels[2] = "ERROR";
    }
    
    void Logger::setLevels(unsigned int level_num, const std::string& level_name)
    {
        m_levels[level_num] = level_name;
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

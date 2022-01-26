#include "Logger.hpp"

namespace Logger{

    Logger::Logger(unsigned int max_len, uint8_t options)
     : m_options(options), m_max_len(max_len), m_file_name("logger_default.txt")
    {
        m_log_statement.reserve(m_max_len);
        m_levels[0] = "INFO";
        m_levels[1] = "TRACE";
        m_levels[2] = "ERROR";
    }
    
    void Logger::setLevels(unsigned int level_num, const std::string& level_name)
    {
        m_levels[level_num] = level_name;
    }

    void Logger::setOptions(uint8_t options) { m_options = options; }

    void Logger::switchOnOff(bool onOff, uint8_t flag) 
    {
        if (flag)   m_options |= flag;
        else        m_options &= flag;
    }

    void Logger::setDateOpt(bool onOff) { switchOnOff(onOff, DATE_FLAG); }
    void Logger::setTimeOpt(bool onOff) { switchOnOff(onOff, TIME_FLAG); }
    void Logger::setWdayOpt(bool onOff) { switchOnOff(onOff, WDAY_FLAG); }
    void Logger::setMsecOpt(bool onOff) { switchOnOff(onOff, MSEC_FLAG); }
    void Logger::setCoutOpt(bool onOff) { switchOnOff(onOff, COUT_FLAG); }
    void Logger::setFileOpt(bool onOff) { switchOnOff(onOff, FILE_FLAG); }
    void Logger::setFileName(const std::string& file_name) { m_file_name = file_name; }
        
}
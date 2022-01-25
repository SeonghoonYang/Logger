namespace Logger
{    
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
        // get very first currenttime
        auto _time = std::chrono::system_clock::now();

        // Level
        m_log_statement.append("[");
        m_log_statement.append(m_levels[level_num]);
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
        {
            sprintf(prefix_infos[index++], "%02d:%02d:%02d", time_info.tm_hour, time_info.tm_min, time_info.tm_sec);
        }

        // Wday
        if (m_options & WDAY_FLAG)
        {
            switch(time_info.tm_wday)
            {
            case 0: prefix_infos[index][0] = 'S'; prefix_infos[index][1] = 'u'; prefix_infos[index][2] = 'n'; break;
            case 1: prefix_infos[index][0] = 'M'; prefix_infos[index][1] = 'o'; prefix_infos[index][2] = 'n'; break;
            case 2: prefix_infos[index][0] = 'T'; prefix_infos[index][1] = 'u'; prefix_infos[index][2] = 'e'; break;
            case 3: prefix_infos[index][0] = 'W'; prefix_infos[index][1] = 'e'; prefix_infos[index][2] = 'd'; break;
            case 4: prefix_infos[index][0] = 'T'; prefix_infos[index][1] = 'h'; prefix_infos[index][2] = 't'; break;
            case 5: prefix_infos[index][0] = 'F'; prefix_infos[index][1] = 'r'; prefix_infos[index][2] = 'i'; break;
            case 6: prefix_infos[index][0] = 'S'; prefix_infos[index][1] = 'a'; prefix_infos[index][2] = 't'; break;
            default: prefix_infos[index][0] = 'X'; prefix_infos[index][1] = 'X'; prefix_infos[index][2] = 'X'; break;
            }
            prefix_infos[index++][3] = '\0';
        }

        // Date
        if (m_options & DATE_FLAG)
        {
            sprintf(prefix_infos[index++], "%04d-%02d-%02d", time_info.tm_year + 1900, time_info.tm_mon + 1, time_info.tm_mday);
        }
 
        m_log_statement.append("(");
        for(int i = index - 1; i >= 0; i--) 
        {
            m_log_statement.append(prefix_infos[i]);
            if (i != 0) m_log_statement.append(" ");
        }
        m_log_statement.append(") ");
        m_log_statement.append(log);

        concatLog(logs...);
        m_log_statement.append("\n");

        // ?
        std::cerr << m_log_statement;

        m_log_statement.clear();
        if(m_log_statement.size() > m_max_len)
            m_log_statement.reserve(m_max_len);
    }
}
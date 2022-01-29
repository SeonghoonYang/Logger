# Logger
logging lib

this is thread safe logging library.

Actually, for thread safety, because of lock, the speed of logging is little slow.
But I guess this logging library can guarantee time interval at least 0.1ms.

Each log instance can have different options, so you can write various log, just instantiate them. 

This has small options.
1. setFile ( when write log, Instance write log to specific file(mode append), 
             the file name is in the instance's member var(string).)
             
2. setCout ( convert Cerr -> Cout. NO BUFFERING directly flush.
             default output is Cerr.)
             
3. setDate, Time, Wday, Msec ( detail of log's time prefix. )

4. setFileName ( literally, put string )

5. addLevel ( this lib can customize log level.
              just Add level num, level's string,
              and built in enum class Color:: colors~~. )
              
+) copy constructor and assignment operator are implemented. they copy whole rhs' options.

You can check testfile.
thanks.

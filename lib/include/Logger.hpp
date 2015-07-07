#ifndef _LOGGER_H_
#define _LOGGER_H_

#define LOGGING_SIZE               1024*1024
#define _ERROR                     (1 << 0)
#define _WARN                      (_ERROR | (1 << 1))
#define _INFO                      (_WARN | (1 << 2))
#define _DEBUG                     (1 << 3)
#define _NODEBUG                   0

#define LOGGING_LEVEL              (_ERROR | _DEBUG)
#define LOG(lvl,msg)               Logger::getInstance()->addMsg(LOG_LEVEL::lvl,msg)

#include "Singleton.hpp"

#include <list>
#include <mutex>
#include <thread>
#include <string>
#include <atomic>
#include <memory>
#include <fstream>
#include <condition_variable>

#include <iostream>
#include <sstream>

enum LOG_LEVEL {INFO, WARN, ERROR, DEBUG};

class Logger : public Singleton<Logger>
{
    friend class Singleton<Logger>;

public:
     void addMsg(LOG_LEVEL lvl, const std::string &msg);

     ~Logger();

private:
     Logger();
     Logger(Logger const&) = delete;
     void operator=(Logger const&) = delete;

     void loggingThread(void);
     inline void addMsg(const std::string &msg);

     std::atomic<bool> m_endThread;
     std::atomic<unsigned int> m_size;

     std::mutex m_mutex;
     std::mutex m_addMutex;
     std::condition_variable m_cv;

     std::thread m_loggingThread;
     std::list<std::string> m_messages;

     std::fstream m_file;

};

#endif // _LOGGER_H_

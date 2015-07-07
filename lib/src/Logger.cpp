#include <pthread.h>
#include <ratio>
#include <ctime>
#include <chrono>
#include <thread>
#include <sstream>
#include "../include/Logger.hpp"


const std::string currentDateTime();
const std::string getTimeInNs();

Logger::Logger() : m_endThread(false), m_size(0), m_mutex(), m_addMutex(), m_cv()
{
     std::string fileName = currentDateTime() + ".log";
     m_file.open(fileName, std::fstream::app | std::fstream::out);
     m_loggingThread = std::thread(&Logger::loggingThread, this);
     sched_param sch;
     sch.sched_priority = 0;
     pthread_setschedparam(m_loggingThread.native_handle(),SCHED_OTHER,&sch);
}

Logger::~Logger()
{
     m_endThread = true;
     m_cv.notify_one();
     m_loggingThread.join();

     if(m_size > 0)
     {
          for(auto &str : m_messages)
               m_file << str << std::endl;
     }

     m_file.close();
}

void Logger::loggingThread(void)
{
     std::unique_lock<std::mutex> lock(m_mutex);
     std::list<std::string> msg;

     while(!m_endThread)
     {
          if(m_size < LOGGING_SIZE)
               m_cv.wait(lock);
          else
          {
               msg.swap(m_messages);
               m_size = 0;

               for(auto &str : msg)
                    m_file << str << std::endl;

               msg.clear();
          }
     }
}

void Logger::addMsg(LOG_LEVEL lvl, const std::string &msg)
{
     std::string str;

     switch (lvl)
     {
          #if ((LOGGING_LEVEL & _DEBUG) == _DEBUG)
     case LOG_LEVEL::DEBUG:
          str = " | DEBUG | " + msg;
          break;
          #endif

          #if ((LOGGING_LEVEL & _ERROR) == _ERROR)
     case LOG_LEVEL::ERROR:
          str = " | ERROR | " + msg;
          break;
          #endif

          #if ((LOGGING_LEVEL & _WARN) == _WARN)
     case LOG_LEVEL::WARN:
          str = " | WARN | " + msg;
          break;
          #endif

          #if ((LOGGING_LEVEL & _INFO) == _INFO)
     case LOG_LEVEL::INFO:
          str = " | INFO | " + msg;
          break;
          #endif
     }

     if(str.size())
     {
          str = getTimeInNs() + str;
          addMsg(str);
     }
}

void Logger::addMsg(const std::string& msg)
{
     m_addMutex.lock();
     m_size += msg.length();
     m_messages.push_back(msg);
     m_addMutex.unlock();
     m_cv.notify_one();
}

const std::string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%H-%M", &tstruct);
    //buf[13] = '-';
    //buf[16] = '-';

    return buf;
}

const std::string getTimeInNs()
{
     static std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
     std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

     std::chrono::microseconds ns = std::chrono::duration_cast<std::chrono::microseconds>(now-start);

     return std::to_string(ns.count());
}


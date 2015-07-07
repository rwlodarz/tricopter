#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <memory>
#include <mutex>

template<class T>

class CSingleton
{
public:
    static std::shared_ptr<T>& getInstance()
    {
        if(m_instance == nullptr)
        {
            std::unique_lock<std::mutex> l_lock(m_mutex);

            if(m_instance == nullptr)
                m_instance = std::shared_ptr<T>(new T);
        }

        return m_instance;
    }

protected:
    CSingleton() {};
    CSingleton(CSingleton const&) = delete;
    CSingleton& operator=(CSingleton const&) = delete;

    virtual ~CSingleton()
    {
        m_instance = nullptr;
    }

private:
    static std::shared_ptr<T> m_instance;
    static std::mutex m_mutex;
};

template<class T>
std::shared_ptr<T> CSingleton<T>::m_instance = nullptr;

template<class T>
std::mutex CSingleton<T>::m_mutex;

#endif // _SINGLETON_H_

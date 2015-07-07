#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <memory>
#include <mutex>

template<class T>

class Singleton
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
    Singleton() {};
    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;

    virtual ~Singleton()
    {
        m_instance = nullptr;
    }

private:
    static std::shared_ptr<T> m_instance;
    static std::mutex m_mutex;
};

template<class T>
std::shared_ptr<T> Singleton<T>::m_instance = nullptr;

template<class T>
std::mutex Singleton<T>::m_mutex;

#endif // _SINGLETON_H_

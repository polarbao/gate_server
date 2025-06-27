#pragma once
#include "global.h"


template <typename T>
class CSingleton
{
public:

	static std::shared_ptr GetInstance()
	{
		static std::once_flag s_flag;
		std::call_once(s_flag, [&]() 
			{
				m_instance = shared_ptr<T>(new T);
			});
		return m_instance;
	}

	~CSingleton()
	{

	}

	void PrintAddres();

protected:
	CSingleton() = default;

	CSingleton(const CSingleton<T>&) = delete;

	CSingleton& operator= (const CSingleton<T>& st) = delete;

protected:
	static std::shared_ptr<T> m_instance;
};

template <typename T>
std::shared_ptr<T> CSingleton<T>::m_instance = nullptr;
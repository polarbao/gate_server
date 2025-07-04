#pragma once

#include <functional>
#include <map>

#include "global.h"


struct SectionInfo
{
	SectionInfo() {}

	~SectionInfo()
	{
		m_section_datas.clear();
	}

	SectionInfo& operator = (const SectionInfo& other)
	{
		if (&other == this)
		{
			return *this;
		}
		this->m_section_datas = other.m_section_datas;
	}

	std::string operator[] (const std::string& key)
	{
		if (m_section_datas.find(key) == m_section_datas.end())
		{
			return "";
		}
		return m_section_datas[key];
	}


	std::map<std::string, std::string> m_section_datas;
};

class ConfigMgr
{
public:
	
	ConfigMgr();

	~ConfigMgr()
	{
		m_config_map.clear();
	}

	ConfigMgr(const ConfigMgr& other)
	{
		this->m_config_map = other.m_config_map;
	}

	ConfigMgr& operator= (const ConfigMgr& other)
	{
		if (&other == this)
		{
			return *this;
		}

		this->m_config_map = other.m_config_map;
	}

	SectionInfo operator[] (const std::string& section)
	{

		return m_config_map[section];
	}



private:
	//
	std::map<std::string, SectionInfo> m_config_map;

};
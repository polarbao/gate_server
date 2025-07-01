// gate_ser.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>

#include "glog/logging.h"
#include "global.h"
#include "CServer.h"

int main(int argc, char* argv[])
{
	//google::InitGoogleLogging(argv[0]);  //括号内是程序名
	//LOG(INFO) << "This is an INFO message";
	//LOG(WARNING) << "This is a WARNING message";
	//LOG(ERROR) << "This is an ERROR message";
	try
	{
		unsigned short port = static_cast<unsigned short>(8080);
		boost::asio::io_context ioc{ 1 };
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&ioc](const boost::system::error_code& ec, int signal_num)
			{
				if (ec)
				{
					return;
				}
				ioc.stop();
			});
		std::make_shared<CServer>(ioc, port)->Start();
		ioc.run();
	}
	catch (std::exception const& e)
	{
		std::cout << "err" << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}

unsigned char ToHex(unsigned char x)
{
	return x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex(unsigned char x)
{
	unsigned char y;
	if (x >= 'A' && x <= 'Z')
	{
		y = x - 'A' + 10;
	}
	else if(x >= 'a' && x <= 'z')
	{
		y = x - 'a' + 10;
	}
	else if(x >= '0' && x <= '9')
	{
		y = x - '0';
	}
	else
	{
		assert(0);
	}
	return y;
}

std::string UrlEncode(const std::string& str)
{
	std::string strTmp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum((unsigned char)str[i]) || 
			(str[i] == '-') || 
			(str[i] == '_') || 
			(str[i] == '.') || 
			(str[i] == '~'))
		{
			strTmp += str[i];
		}
		else if(str[i] == ' ')
		{
			strTmp += "+";
		}
		else
		{
			strTmp += '%';
			strTmp += ToHex((unsigned char)str[i] >> 4);
			strTmp += ToHex((unsigned char)str[i] & 0x0F);
		}
	}
	return strTmp;
}





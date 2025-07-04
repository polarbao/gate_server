#pragma once

#include <iostream>
#include <memory>

#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <jsoncpp/json.h>
#include <jsoncpp/value.h>
#include <jsoncpp/reader.h>


namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

using tcp = boost::asio::ip::tcp;


enum ErrorCodes 
{
	Success = 0, 
	Error_Json = 1001,
	RPCFailed = 1002,
};


class ConfigMgr;
extern ConfigMgr gCfgMgr;
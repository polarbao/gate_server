#pragma once
#include "global.h"
#include <unordered_map>



class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{

	friend class LoginSystem;

public:

	HttpConnection(boost::asio::ip::tcp::socket sock);

	void Start();

private:

	void CheckDeadline();

	void WriteResponse();

	void HandleReq();

	void PreParseGetParam();

private:

	boost::asio::ip::tcp::socket m_socket;
	boost::beast::flat_buffer m_buffer{ 8192 };
	boost::beast::http::request<boost::beast::http::dynamic_body> m_request;
	boost::beast::http::response<boost::beast::http::dynamic_body> m_response;
	boost::asio::steady_timer deadline_{ m_socket.get_executor(), std::chrono::seconds(60) };
	std::string m_get_url;
	std::unordered_map<std::string, std::string> m_get_params;

};


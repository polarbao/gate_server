#include "HttpConnection.h"
#include "gate_ser.cpp"

HttpConnection::HttpConnection(boost::asio::ip::tcp::socket sock)
	: m_socket(std::move(sock))
{


}


void HttpConnection::Start()
{
	auto self = shared_from_this();
	boost::beast::http::async_read(m_socket, m_buffer, m_request, [self](boost::beast::error_code ec, std::size_t bytes_transferred)
		{
			try
			{
				if (ec)
				{
					return;
				}

				boost::ignore_unused(bytes_transferred);
				self->HandleReq();
				self->CheckDeadline();
			}
			catch (std::exception& exp)
			{
				std::cout << "exception is " << exp.what() << std::endl;
			}		
		});
}



void HttpConnection::CheckDeadline()
{

}

void HttpConnection::WriteResponse()
{
	auto self = shared_from_this();
	m_response.content_length(m_response.body().size());
	boost::beast::http::async_write(m_socket, m_response, [self](boost::beast::error_code ec, std::size_t) 
		{
			self->m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
			self->deadline_.cancel();
		});
}

void HttpConnection::HandleReq()
{
	auto self = shared_from_this();
	deadline_.async_wait([self](boost::beast::error_code ec) 
		{
			if (!ec)
			{
				self->m_socket.close(ec);
			}
		});

// 	if (m_request.method() != boost::beast::http::verb::get)
// 	{
// 		PreParseGetParam();
// 		bool success = LoginSystem::GetInstance()->HandleGet(m_get_url, shared_from_this());
// 	}
}

void HttpConnection::PreParseGetParam()
{
	auto uri = m_request.target();
	//查找 查询字符串的开始位置（'?'的位置
	auto query_pos = uri.find('?');
	if (query_pos == std::string::npos)
	{
		m_get_url = uri;
		return;
	}

	m_get_url = uri.substr(0, query_pos);
	std::string query_str = uri.substr(query_pos + 1);
	std::string key, value;
	size_t pos = 0;
	while ((pos = query_str.find('&')) != std::string::npos)
	{
		auto pair = query_str.substr(0, pos);
		size_t eq_pos = pair.find('=');
		if (eq_pos != std::string::npos)
		{
			key = UrlDecode(pair.substr(0, eq_pos));
			value = UrlDecode(pair.substr(eq_pos + 1));
			m_get_params[key] = value;
		}
		query_str.erase(0, pos + 1);
	}

	//处理最后一个参数，如果没&分隔符
	if (!query_str.empty())
	{
		size_t eq_pos = query_str.find('=');
		if (eq_pos != std::string::npos)
		{
			key = UrlDecode(query_str.substr(0, eq_pos));
			value = UrlDecode(query_str.substr(eq_pos + 1));
			m_get_params[key] = value;
		}
	}
}
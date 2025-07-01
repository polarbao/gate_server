#include "HttpConnection.h"
#include "global.h"


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
}
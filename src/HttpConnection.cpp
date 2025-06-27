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

}

void HttpConnection::HandleReq()
{

}
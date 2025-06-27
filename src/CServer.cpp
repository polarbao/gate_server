#include "CServer.h"
#include "HttpConnection.h"
#include <memory>


CServer::CServer(boost::asio::io_context& ioc, unsigned short& port)
	: m_ioc(ioc)
	, m_acceptor(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
	, m_socket(ioc)
{

}


void CServer::Start()
{
	auto self = shared_from_this();
	m_acceptor.async_accept(m_socket, [self](boost::beast::error_code ec) 
		{
			try
			{
				if (ec)
				{
					self->Start();
					return;
				}

				std::make_shared<HttpConnection>(std::move(self->m_socket))->Start();
				self->Start();

			}
			catch (std::exception& exp)
			{
				std::cout << "" << exp.what() << std::endl;
				self->Start();
			}
		
		});


}


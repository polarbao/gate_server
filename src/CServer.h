#pragma once
#include "global.h"


class CServer : public std::enable_shared_from_this<CServer>
{

public:
	CServer(boost::asio::io_context& ioc, unsigned short& port);

	void Start();

private:
	boost::asio::ip::tcp::acceptor m_acceptor;
	boost::asio::io_context& m_ioc;
	boost::asio::ip::tcp::socket m_socket;
};


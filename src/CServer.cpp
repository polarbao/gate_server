#include "CServer.h"
#include "global.h"

class CServer
{
public:
	CServer();

	void Start();

private:
	boost::asio::ip::tcp::acceptor m_acceptor;
	boost::asio::io_context& m_ioc;
	boost::asio::ip::tcp::socket m_socket;
};
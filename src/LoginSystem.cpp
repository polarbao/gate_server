#include "LoginSystem.h"
#include "global.h"


LoginSystem::LoginSystem()
{
	RegGet("/get_test", [](std::shared_ptr<HttpConnection> conn)
		{
			boost::beast::ostream(conn->m_response.body()) << "recv get_test req";
		
		});

	// Initialize any necessary resources or state
}



void LoginSystem::RegGet(std::string url, HttpHandle handle)
{
	m_get_handlers.insert(make_pair(url, handle));
}

bool LoginSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> conn)
{
	if (m_get_handlers.find(path) == m_get_handlers.end())
	{
		return false;
	}

	m_get_handlers[path](conn);

	return true;

}
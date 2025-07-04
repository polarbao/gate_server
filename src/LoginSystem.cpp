#include "LoginSystem.h"
#include "global.h"


LoginSystem::LoginSystem()
{
	//get请求处理
	RegGet("/get_test", [](std::shared_ptr<HttpConnection> conn)
		{
			boost::beast::ostream(conn->m_response.body()) << "recv get_test req" << std::endl;
			int i = 0;
			for (auto& elem : conn->m_get_params)
			{
				i++;
				boost::beast::ostream(conn->m_response.body()) << "param" << i << "key is " << elem.first;
				boost::beast::ostream(conn->m_response.body()) << " param" << i << "value is " << elem.second << std::endl;
			}
		
		});
	
	//post请求处理
	RegPost("/get_varifycode", [](std::shared_ptr<HttpConnection>) 
		{
		
		
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

	//conn数据类型与handler类型不同
	//m_get_handlers[path](conn);
	return true;

}
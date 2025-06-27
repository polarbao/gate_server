#pragma once

#include <functional>
#include <map>

#include "global.h"
#include "CSingleton.h"
#include "HttpConnection.h"


class HttpConnection;
typedef std::function<void(HttpConnection)> HttpHandle;

class LoginSystem : public CSingleton<LoginSystem>
{
	friend class CSingleton<LoginSystem>;

public:

	~LoginSystem();

	bool HandleGet(std::string path, std::shared_ptr<HttpConnection> conn);

	void RegGet(std::string url, HttpHandle handler);

private:

	LoginSystem();


private:
	std::map<std::string, HttpHandle> m_post_handlers;
	std::map<std::string, HttpHandle> m_get_handlers;

};


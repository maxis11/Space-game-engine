#include "log.hpp"

Log::Log()
{
	log.set_priority(true);
	log.set_max_size(20);
}

std::vector<std::string> Log::getLog()
{
	std::vector<std::string> outlog;
	while (log.size() > 0)
	{
		Buffer* buf = log.pop();
        std::string str (buf->data,buf->data+buf->datasize);
		outlog.push_back(str);
        free(buf->data);
        free(buf);
	}
	return outlog;
}

void Log::writeLog(std::string str)
{
    Buffer* buf = (Buffer*)malloc(sizeof(Buffer));
    buf->data = (char*)malloc(str.size());
    memcpy (buf->data,str.c_str(),str.size());
    buf->datasize = str.size();
	log.push(buf);
}

void Log::set_max_log(size_t maxsize)
{
	log.set_max_size(maxsize);
}

Log::~Log()
{
	log.clean();
}

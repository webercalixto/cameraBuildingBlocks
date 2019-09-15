#include "showImgServer.hpp"

#include "global.hpp"
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

using namespace std;
using namespace Pistache;

showImgServer::~showImgServer()
{
	 this->logger->log("showImgServer DESTRUCTOR\n");
}

showImgServer::showImgServer()
{
}

void showImgServer::init(Pistache::Address addr, size_t _numRestServerProcesses, int _maxRestRequestSize,std::shared_ptr<ninjaLogger> _logger)
{
	this->logger = _logger;
    this->httpEndpoint = std::make_shared<Http::Endpoint>(addr);
    auto opts = Http::Endpoint::options()
                    .threads(_numRestServerProcesses)
                    .maxRequestSize(_maxRestRequestSize)
                    .flags(Pistache::Tcp::Options::ReuseAddr | Pistache::Tcp::Options::FastOpen);
    this->httpEndpoint->init(opts);
    this->setRoute();
}

void showImgServer::start()
{
    this->httpEndpoint->setHandler(router.handler());
    this->httpEndpoint->serve();
}

void showImgServer::setRoute()
{
    using namespace Rest;
    Routes::Get(router, "/jpeg/:filename", Routes::bind(&showImgServer::jpegHandler, this));
}

void showImgServer::jpegHandler(const Rest::Request &req, Http::ResponseWriter writer)
{
	auto        filename = req.param(":filename").as<std::string>();
	filename = "/tmp/car.jpg";
	this->logger->log("showImgServer::jpegHandler START filename = "+filename);
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
    std::streamsize fileSize = file.tellg();
    this->logger->log("filesize = " + std::to_string(fileSize));
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(fileSize);
    if (file.read(buffer.data(), fileSize))
    {
        writer.setMime(MIME(Image, Jpeg));
        std::streamsize sz = 0;
		std::streamsize sent = 0;
		auto os = writer.stream(Http::Code::Ok);
		try {
		  while (sz < fileSize)
		  {
			if ((sent = os.write(reinterpret_cast<char*>(&buffer[sz]), (fileSize - sz) < 512L ? fileSize : 512L)) == 0) break;
			sz += sent;
		  }
		}
		catch (...)
		{
			this->logger->log("FAILURE SENDING DATA");
		}
        os.ends();
        return;
    }
    writer.send(Http::Code::Internal_Server_Error);
}


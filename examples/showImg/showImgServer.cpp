#include "showImgServer.hpp"

#include "global.hpp"
#include <sstream>
#include <string>
#include <fstream>

#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>

using namespace std;
using namespace Pistache;

showImgServer::showImgServer(Address addr)
    : httpEndpoint(std::make_shared<Http::Endpoint>(addr))
{
}

void showImgServer::init(size_t _numRestServerProcesses, int _maxRestRequestSize)
{
    auto opts = Http::Endpoint::options()
                    .threads(_numRestServerProcesses)
                    .maxRequestSize(_maxRestRequestSize)
                    .flags(Pistache::Tcp::Options::ReuseAddr | Pistache::Tcp::Options::FastOpen);
    httpEndpoint->init(opts);
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
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    if (file.read(buffer.data(), size))
    {
        writer.setMime(MIME(Image, Jpeg));
        auto os = writer.stream(Http::Code::Ok);
        os.ends();
    }
    else{
    	auto os = writer.stream(Http::Code::Bad_Request);
    	os.ends();
    }


   /* auto data = (drvFrameType == DRV_FRAME_JPEG) ? fotoFrame->cropRegionJPEG[idPista] : fotoFrame->cropRegionRGB[idPista];
    const std::streamsize szData = (drvFrameType == DRV_FRAME_JPEG) ? fotoFrame->info.currentCropRegionJPEGSize[idPista] : fotoFrame->info.cropRegionMaxSize;
    std::streamsize sz = 0;
    std::streamsize sent = 0;
    auto os = writer.stream(Http::Code::Ok);
    try {
      while (sz < szData)
      {
        if ((sent = os.write(reinterpret_cast<char*>(&data[sz]), std::min(512L, szData - sz))) == 0) break;
        sz += sent;
      }
    }
    catch (...)
    {
      NTCLOG("cam_get_picture_lane_by_trigger: catch de exception durante tranmissão");
    }
    os.ends();
    return;
  }
  writer.send(Http::Code::Internal_Server_Error);*/



}


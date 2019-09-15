/*
 * The MIT License
 *
 * Copyright 2019 weber calixto.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   showImg.cpp
 * Author: weber calixto
 *
 * Created on September 8, 2019, 4:38 PM
 */
/*#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>*/
#include "global.hpp"
#include "showImgServer.hpp"
#include <csignal>
#include <syslog.h>
ninjaDaemon ctx("|NINJAEXAMPLEPISTACHE|");

void signalHandler(int signum)
{
    ctx.logger->log("signalHandler: Interrupt signal (" + std::to_string(signum) + ") received");
    ctx.finish = true;
}

void startServer(ninjaTypes::_int restServerPort, ninjaTypes::_int numRestServerProcesses,
                 ninjaTypes::_int maxRestRequestSize)
{
    syslog(LOG_INFO, "startServer INIT restServerPort=%ld maxRestRequestSize=%ld", restServerPort, maxRestRequestSize);
    Pistache::Port    port(restServerPort);
    Pistache::Address addr(Pistache::Ipv4::any(), port);
    showImgServer   showImgServer(addr);
    showImgServer.init(numRestServerProcesses, maxRestRequestSize);
    showImgServer.start();
    syslog(LOG_INFO, "startServer END");
}

void callbackFunc(const int workerNum, const ninjaTypes::workerConfigMap &_workerConfig,
                  const std::shared_ptr<ninjaLogger> &_logger)
{
    static thread_local bool firstRun = true;

    if (firstRun)
    {
        ninjaTypes::workerConfigMap workerConfig   = _workerConfig;
        ninjaTypes::_int            restServerPort = std::get<ninjaTypes::_int>(workerConfig["restServerPort"]);
        ninjaTypes::_int numRestServerProcesses    = std::get<ninjaTypes::_int>(workerConfig["numRestServerProcesses"]);
        ninjaTypes::_int maxRestRequestSize        = std::get<ninjaTypes::_int>(workerConfig["maxRestRequestSize"]);
        _logger->log(std::string("callbackFunc FIRST RUN INIT workerNum = ") + std::to_string(workerNum));
        firstRun       = false;
        std::thread th = std::thread([=] { startServer(restServerPort, numRestServerProcesses, maxRestRequestSize); });
        th.detach();
        /*std::thread th = std::thread([&] {
            _logger->log("callbackFunc STARTING THREAD restServerPort=" + std::to_string(restServerPort));
            Pistache::Port    port(restServerPort);
            Pistache::Address addr(Pistache::Ipv4::any(), port);
            ninjaRestServer         myNinjaRestServer(addr);
            myNinjaRestServer.init(numRestServerProcesses, maxRestRequestSize);
            myNinjaRestServer.start();
            _logger->log("callbackFunc FINISHING THREAD workerNum=" + std::to_string(workerNum));
        });
        th.detach();    */
        _logger->log(std::string("callbackFunc FIRST RUN END workerNum = ") + std::to_string(workerNum));
    }
}


int main(int argc, char *argv[])
{
    /** Until C++ get reflections, this sort of abstraction is necessary to automate variable retrieval **/
    ctx.funcPtr                                 = callbackFunc;
    ctx.workerConfigs["restServerPort"]         = { static_cast<ninjaTypes::_int>(9090) };
    ctx.workerConfigs["numRestServerProcesses"] = { static_cast<ninjaTypes::_int>(0) };
    ctx.workerConfigs["maxRestRequestSize"]     = { static_cast<ninjaTypes::_int>(1024) };
    ctx.workerConfigs["sleepDuration"]          = { static_cast<ninjaTypes::_int>(500) };
    ctx.workerLogLevel                          = ninjaTypes::workerLogLevel::LOGLEVEL_ALL;
    ctx.logger->log("STARTING NINJADAEMONPISTACHE");
    if (argc < 2 || !ninjaUtils::validFile(argv[1]))
    {
        ctx.logger->log("No ini filename provided or ini file doesnt exist. exiting");
        return 0;
    }
    std::cout << "HELLO WORLD" << std::endl;
    if (!ctx.loadConfigFile(std::string(argv[1]))) return 0;
    signal(SIGINT, signalHandler);
    ctx.logger->log("RUNNING");
    while (!ctx.finish)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    ctx.logger->log("FINISHING NINJADAEMONPISTACHE");
    return 0;
}
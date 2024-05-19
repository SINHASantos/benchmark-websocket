//
//  AppComponent.hpp
//  oatpp-web-starter
//
//  Created by Leonid on 3/2/18.
//  Copyright © 2018 lganzzzo. All rights reserved.
//

#ifndef AppComponent_hpp
#define AppComponent_hpp

#include "oatpp/async/Executor.hpp"

#include "oatpp/network/tcp/client/ConnectionProvider.hpp"
#include "oatpp/macro/component.hpp"

#include "oatpp/base/CommandLineArguments.hpp"
#include "oatpp/utils/Conversion.hpp"

#include <list>

/**
 *  Class which creates and holds Application components and registers components in oatpp::Environment
 *  Order of components initialization is from top to bottom
 */
class AppComponent {
private:
  oatpp::base::CommandLineArguments m_cmdArgs;
public:
  AppComponent(const oatpp::base::CommandLineArguments& cmdArgs)
    : m_cmdArgs(cmdArgs)
  {}
public:

  /**
   * Create AsyncExecutor for WebSocket Asynchronous processing.
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor)([this] {

    v_int32 threadsProc = oatpp::utils::Conversion::strToInt32(m_cmdArgs.getNamedArgumentValue("--tp", "8"));
    v_int32 threadsIO = oatpp::utils::Conversion::strToInt32(m_cmdArgs.getNamedArgumentValue("--tio", "2"));
    v_int32 threadsTimer = oatpp::utils::Conversion::strToInt32(m_cmdArgs.getNamedArgumentValue("--tt", "1"));

    return std::make_shared<oatpp::async::Executor>(threadsProc, threadsIO, threadsTimer);

  }());

  /**
   * Create list of TCP Connection Providers. Each provider connects to its specific port.
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<std::list<std::shared_ptr<oatpp::network::ClientConnectionProvider>>>, connectionProviders)([this] {

    auto providers = std::make_shared<std::list<std::shared_ptr<oatpp::network::ClientConnectionProvider>>>();

    const char* host = m_cmdArgs.getNamedArgumentValue("-h", "127.0.0.1");
    v_uint16 basePort = oatpp::utils::Conversion::strToInt32(m_cmdArgs.getNamedArgumentValue("--bp", "8000"));
    v_uint16 portsCount = oatpp::utils::Conversion::strToInt32(m_cmdArgs.getNamedArgumentValue("--pc", "100"));

    for(v_uint16 i = 0; i < portsCount; i++) {
      auto provider = oatpp::network::tcp::client::ConnectionProvider::createShared({host, (v_uint16)(basePort + i)});
      providers->push_back(provider);
    }

    return providers;

  }());


};

#endif /* AppComponent_hpp */

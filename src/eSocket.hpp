//
// Created by EkkoZ on 31/12/2017.
//

#ifndef ENET_ESOCKET_HPP
#define ENET_ESOCKET_HPP

#include <string>
#include <netinet/in.h>

#include "eBuffer.hpp"

class eSocket {
public:
  eSocket();
  ~eSocket();

  bool connect(std::string const &, std::uint16_t);
  void disconnect();

  void sendAll(eBuffer &);
  void send(eBuffer &);

  void recv(eBuffer &);
  void recv(eBuffer &, std::size_t);

private:
  int _fd;
  struct sockaddr_in _addr;
};

#endif //ENET_ESOCKET_HPP

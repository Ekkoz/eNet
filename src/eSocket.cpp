//
// Created by EkkoZ on 31/12/2017.
//

#define _POSIX_C_SOURCE 200112L

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>

#include "eSocket.hpp"
#include "eBuffer.hpp"

eSocket::eSocket()
{
  this->_fd = 0;
}

eSocket::~eSocket()
{
  disconnect();
}

bool eSocket::connect(std::string const &remote, std::uint16_t port)
{
  struct addrinfo *remoteinfos;
  int addrinfo;

  if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    std::cerr << "eSocket::connect: socket call failed: " << strerror(errno) << std::endl;
    return (false);
  }
  if ((addrinfo = getaddrinfo(remote.c_str(), NULL, NULL, &remoteinfos)) != 0)
  {
    std::cerr << "eSocket::connect: getaddrinfo call failed: " << gai_strerror(addrinfo) << std::endl;
    return (false);
  }
  if (remoteinfos)
  {
    this->_addr.sin_addr.s_addr = ((struct sockaddr_in *) remoteinfos->ai_addr)->sin_addr.s_addr;
    this->_addr.sin_family = AF_INET;
    this->_addr.sin_port = htons(port);
    freeaddrinfo(remoteinfos);
  }
  else
  {
    std::cerr << "eSocket::connect: getaddrinfo call failed: cannot get correct remote ip address" << std::endl;
    return (false);
  }
  if (::connect(this->_fd, (struct sockaddr *) &(this->_addr), sizeof(this->_addr)) < 0)
  {
    std::cerr << "eSocket::connect: connect call failed: " << strerror(errno) << std::endl;
    return (false);
  }
  return (true);
}

void eSocket::disconnect()
{
  if (this->_fd)
  {
    close(this->_fd);
    this->_fd = 0;
  }
}

void eSocket::sendAll(eBuffer &buff)
{
  while (this->_fd && !buff.empty())
    send(buff);
}

void eSocket::send(eBuffer &buff)
{
  t_datablock *datablock;
  ssize_t written;

  datablock = buff.get();
  if (this->_fd && datablock)
  {
    written = ::send(this->_fd, &(((char *)datablock->data)[datablock->written]), datablock->length - datablock->written, 0);
    if (written == 0)
      disconnect();
    else if (written < 0)
    {
      std::cerr << "eSocket::send: send call failed: " << strerror(errno) << std::endl;
      disconnect();
    }
    else
      buff.consume((std::size_t) written);
  }
}

void eSocket::recv(eBuffer &buff)
{
  if (this->_fd)
    recv(buff, 4096);
}

void eSocket::recv(eBuffer &buff, std::size_t length)
{
  byte *data;
  ssize_t read;

  if (this->_fd && length > 0)
  {
    data = new byte[length];
    read = ::recv(this->_fd, data, length, 0);
    if (read == 0)
      disconnect();
    else if (read < 0)
    {
      std::cerr << "eSocket::recv: recv call failed: " << strerror(errno) << std::endl;
      disconnect();
    }
    else
    {
      buff.add(data, (std::size_t) read);
    }
  }
}

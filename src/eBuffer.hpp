//
// Created by EkkoZ on 31/12/2017.
//

#ifndef ENET_EBUFFER_HPP
#define ENET_EBUFFER_HPP

#include <queue>

#include "eTypes.hpp"

class eBuffer
{
public:
  eBuffer();
  ~eBuffer();

  void add(byte *, std::size_t);
  void add(t_datablock *);

  t_datablock *get() const;
  void consume(std::size_t);

  bool empty() const;

private:
  std::queue<t_datablock *> _buff;
};

#endif //ENET_EBUFFER_HPP

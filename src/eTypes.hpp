//
// Created by EkkoZ on 03/01/2018.
//

#ifndef ENET_ETYPES_HPP
#define ENET_ETYPES_HPP

#include <cstddef>
#include <cstdint>

typedef std::uint8_t byte;

typedef struct
{
  byte *data;
  std::size_t length;
  std::size_t written;
} t_datablock;

#endif //ENET_ETYPES_HPP

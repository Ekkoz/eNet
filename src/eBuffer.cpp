//
// Created by EkkoZ on 31/12/2017.
//

#include <cstring>

#include "eBuffer.hpp"

eBuffer::eBuffer()
{
}

eBuffer::~eBuffer()
{
  t_datablock *datablock;

  datablock = this->_buff.front();
  while (!this->_buff.empty())
  {
    delete[] ((char *) datablock->data);
    delete datablock;
    this->_buff.pop();
    datablock = this->_buff.front();
  }
}

void eBuffer::add(byte *data, std::size_t length)
{
  byte *content = new byte[length];
  t_datablock *newblock = new t_datablock;

  memcpy(content, data, length);
  newblock->data = content;
  newblock->length = length;
  newblock->written = 0;
  this->_buff.push(newblock);
}

void eBuffer::add(t_datablock *datablock)
{
  this->_buff.push(datablock);
}

t_datablock *eBuffer::get() const
{
  if (!this->_buff.empty())
    return (this->_buff.front());
  return nullptr;
}

void eBuffer::consume(std::size_t value)
{
  t_datablock *datablock;

  datablock = this->_buff.front();
  if (datablock)
  {
    datablock->written = value;
    if (datablock->written >= datablock->length)
    {
      delete[] datablock->data;
      delete datablock;
      this->_buff.pop();
    }
  }
}

bool eBuffer::empty() const
{
  return (this->_buff.empty());
}

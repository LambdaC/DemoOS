#ifndef __PORT_H
#define __PORT_H

#include "types.h"

class Port
{
    uint16_t m_port_number;

public:
    Port(uint16_t port_numer);
    void WriteB(uint8_t data) const;
    uint8_t ReadB() const;

    void WriteW(uint16_t data) const;
    uint16_t ReadW() const;

    void WriteL(uint32_t data) const;
    uint32_t ReadL() const;
};

#endif
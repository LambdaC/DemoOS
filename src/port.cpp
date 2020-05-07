#include "port.h"

Port::Port(uint16_t port_number)
    : m_port_number{port_number}
{}

void Port::WriteB(uint8_t data) const
{
    asm volatile ("outb %0, %1": : "a"(data), "Nd"(m_port_number));
}

uint8_t Port::ReadB() const
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(m_port_number) );
    return ret;
}

void Port::WriteW(uint16_t data) const
{
    asm volatile ("outw %0, %1": : "a"(data), "Nd"(m_port_number));
}

void Port::WriteL(uint32_t data) const
{
    asm volatile ("outl %0, %1": : "a"(data), "Nd"(m_port_number));
}

uint16_t Port::ReadW() const
{
    uint16_t ret;
    asm volatile ( "inw %1, %0"
                   : "=a"(ret)
                   : "Nd"(m_port_number) );
    return ret;
}

uint32_t Port::ReadL() const
{
    uint32_t ret;
    asm volatile ( "inl %1, %0"
                   : "=a"(ret)
                   : "Nd"(m_port_number) );
    return ret;
}
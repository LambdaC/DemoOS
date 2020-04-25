#include "gdt.h"
#include "io.h"

GlobalDescriptorTable::GlobalDescriptorTable()
    : null_segment(0,0,0),
      code_segment(0, 0xffffffff, 0x9a),
      data_segment(0, 0xffffffff, 0x92)
{
    uint8_t gdt_descriptor[6];
    ((uint16_t *)gdt_descriptor)[0] = (uint16_t)sizeof(GlobalDescriptorTable);  // 前两个字节存储GDT的size
    ((uint32_t *)(gdt_descriptor+2))[0] = (uint32_t)this;   // 后四个字节存储GDT开始的地址

    asm volatile("lgdt (%0)": :"p" (gdt_descriptor)); // 使用lgdt指令，把GDT的数据加载进GDT寄存器
}

GlobalDescriptorTable::~GlobalDescriptorTable()
{}

uint16_t GlobalDescriptorTable::CodeSegment() const
{
    return (uint8_t *)(&code_segment)-(uint8_t *)this;
}

uint16_t GlobalDescriptorTable::DataSegment() const
{
    return (uint8_t *)(&data_segment) - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentEntry::SegmentEntry(uint32_t base, uint32_t limit, uint8_t type)
{
    if (limit >= 0x10000 && (limit & 0xfff) != 0xfff)
    {
        print("limit data is wrong");
    }

    if (limit < 0x10000)
    {
        limit_high_flags = 0x40;
    }
    else
    {
        limit = limit >> 12;
        limit_high_flags = 0xc0;
    }

    limit_low = limit & 0xffff;
    limit_high_flags |= (limit >> 16) & 0xf;

    base_low = base & 0xffff;
    base_middle = (base >> 16) & 0xff;
    base_high = (base >> 24) & 0xff;

    access_type = type;
}

uint32_t GlobalDescriptorTable::SegmentEntry::Base() const
{
    return (base_high << 24) + (base_middle << 16) + base_low;
}

uint32_t GlobalDescriptorTable::SegmentEntry::Limit() const
{
    uint32_t result = (limit_high_flags & 0xf) << 16 + limit_low;
    if ((limit_high_flags & 0xf0) == 0xc0)
    {
        result = (result << 12) + 0xfff;
    }

    return result;
}

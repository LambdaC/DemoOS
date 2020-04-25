#ifndef __GDT_H
#define __GDT_H

#include "types.h"

// #pragma pack(1) // 另一种控制数据对齐的方法，告诉编译器进行数据对齐的字节大小

class GlobalDescriptorTable
{
public:
    class SegmentEntry
    {
    private:
        uint16_t limit_low;
        uint16_t base_low;
        uint8_t base_middle;
        uint8_t access_type;
        uint8_t limit_high_flags; // 前4位是limit_high, 后4位是flags
        uint8_t base_high;

    public:
        /**
         * param limit 32位的数据
         *      当limit < 0x10000（65536）时，说明limit只用到低16-bit, 高位全为0，且Gr设为0。
         *      当limit >= 0x10000（65536）时，我们将limit的20位保存在高20位，低12位为0xFFF，且Gr设为1。
         *      其他情况，该limit参数是错误的，即当limit >= 0x10000（65536）且低12位 != 0xFFF时，参数有误。
         */
        SegmentEntry(uint32_t base, uint32_t limit, uint8_t type);
        uint32_t Base() const;
        uint32_t Limit() const;
    } __attribute__((packed)); // 告诉编译器不需要进行数据对齐

private:
    // 创建三个GDT
    SegmentEntry null_segment;
    SegmentEntry code_segment;
    SegmentEntry data_segment;

public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();
    // 返回CodeSegment的入口，即在GDT中的偏移值，单位为Byte，
    // 因为GDT的size只有2个Byte，所以这也是为什么返回类型是uint16_t的原因
    uint16_t CodeSegment() const;
    // 返回DataSegment的入口，即在GDT中的偏移值
    uint16_t DataSegment() const;

};

#endif
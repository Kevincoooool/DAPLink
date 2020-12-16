/* Flash OS Routines (Automagically Generated)
 * Copyright (c) 2009-2015 ARM Limited
 */
#include "my_flash_blob.h"

static const uint32_t flash_code_H7[] = {
	0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
    0x8F4FF3BF, 0xB5104770, 0xF44F4603, 0x4CED7080, 0x48ED6020, 0xF0406800, 0x4CEB0007, 0x48EB6020,
    0xBF006160, 0x690048E8, 0x0004F000, 0xD1F92800, 0x4CE548E7, 0x48E76060, 0x48E46060, 0x60204CE6,
    0x48E5BF00, 0x68001F00, 0x0004F000, 0xD1F82800, 0x4CE148DF, 0x60203C10, 0x4CDB48DE, 0x0104F8C4,
    0xBD102000, 0x48D84601, 0xF04068C0, 0x4AD60001, 0x48D960D0, 0x68003808, 0x0001F040, 0x010CF8C2,
    0x47702000, 0x49D048D1, 0xBF006148, 0x690048CE, 0x0004F000, 0xD1F92800, 0x49CF48CC, 0xBF006008,
    0x1F0048CD, 0xF0006800, 0x28000004, 0xBF00D1F8, 0x690048C5, 0x0004F000, 0xD1F92800, 0x68C048C2,
    0x0030F020, 0x60C849C0, 0x68C04608, 0x0008F040, 0x460860C8, 0xF04068C0, 0x60C80080, 0x48BABF00,
    0xF0006900, 0x28000004, 0x48B7D1F9, 0xF02068C0, 0x49B50008, 0xBF0060C8, 0x1F0048B7, 0xF0006800,
    0x28000004, 0x48B4D1F8, 0x68003808, 0x0030F020, 0xF8C149AD, 0x4608010C, 0x010CF8D0, 0x0008F040,
    0x010CF8C1, 0xF8D04608, 0xF040010C, 0xF8C10080, 0xBF00010C, 0x1F0048A8, 0xF0006800, 0x28000004,
    0x48A5D1F8, 0x68003808, 0x0008F020, 0xF8C1499E, 0x2000010C, 0xB5104770, 0xF3C14601, 0xF1B14243,
    0xD3376F00, 0x6F01F1B1, 0x4897D234, 0x4B976940, 0x4B954318, 0xBF006158, 0x69004893, 0x0004F000,
    0xD1F92800, 0x68C04890, 0x7330F647, 0x4B8E4398, 0x461860D8, 0x230468C0, 0x2302EA43, 0x4B8A4318,
    0x461860D8, 0xF04068C0, 0x60D80080, 0x4886BF00, 0xF0006900, 0x28000004, 0x4883D1F9, 0xF02068C0,
    0x4B810004, 0x461860D8, 0xF0006900, 0xB3E80001, 0xBD102001, 0x68004880, 0x43184B7C, 0xF8C34B7A,
    0xBF000114, 0x1F00487C, 0xF0006800, 0x28000004, 0x4879D1F8, 0x68003808, 0x7330F647, 0x4B724398,
    0x010CF8C3, 0x38084874, 0xF1A26800, 0x24040308, 0x2303EA44, 0x4B6C4318, 0x010CF8C3, 0xF8D04618,
    0xF040010C, 0xF8C30080, 0xBF00010C, 0x1F00486A, 0xF0006800, 0x28000004, 0x4867D1F8, 0x68003808,
    0x0004F020, 0xF8C34B60, 0xE000010C, 0x4862E007, 0x68001F00, 0x0001F000, 0x2001B108, 0x2000E7B9,
    0xB5F0E7B7, 0x460C4603, 0x46194616, 0x22004635, 0x6F00F1B3, 0xF1B3D30D, 0xD20A6F01, 0x4852BF00,
    0xF0006900, 0x28000004, 0x4850D1F9, 0x61784F4E, 0xBF00E00A, 0x1F004850, 0xF0006800, 0x28000004,
    0x484AD1F8, 0x60384F4C, 0xF1B3E087, 0xD30C6F00, 0x6F01F1B3, 0x4844D209, 0xF64768C0, 0x43B87730,
    0x60F84F41, 0x60F82002, 0x4843E00C, 0x68003808, 0x7730F647, 0x4F3C43B8, 0x010CF8C7, 0x4F3E2002,
    0x60383F08, 0xD30C2C20, 0xE0062200, 0x6868682F, 0x6048600F, 0x31083508, 0x2A041C52, 0x3C20DBF6,
    0x2200E013, 0xF815E004, 0xF8010B01, 0x1C520B01, 0xD3F842A2, 0xE0032200, 0xF80120FF, 0x1C520B01,
    0x0020F1C4, 0xD8F74290, 0xF7FF2400, 0xF1B3FE69, 0xD30A6F00, 0x6F01F1B3, 0xBF00D207, 0x69004822,
    0x0004F000, 0xD1F92800, 0xBF00E007, 0x1F004822, 0xF0006800, 0x28000004, 0x481BD1F8, 0x20006900,
    0xF1B3B1B0, 0xD3096F00, 0x6F01F1B3, 0x4816D206, 0xF02068C0, 0x4F140002, 0xE00760F8, 0x38084816,
    0xF0206800, 0x4F100002, 0x010CF8C7, 0xBDF02001, 0x6F00F1B3, 0xF1B3D309, 0xD2066F01, 0x68C0480A,
    0x0002F020, 0x60F84F08, 0x480BE007, 0x68003808, 0x0002F020, 0xF8C74F04, 0x2C00010C, 0xAF75F47F,
    0xE7E42000, 0x58024594, 0x52002000, 0x0FEF0000, 0x45670123, 0xCDEF89AB, 0x52002114, 0x00000000
};

const my_program_target_t flash_algo_H7 = {
    0x20000027,  // Init
    0x20000085,  // UnInit
    0x200000A5,  // EraseChip
    0x20000177,  // EraseSector
    0x20000283,  // ProgramPage

    // BKPT : start of blob + 1
    // RSB  : address to access global/static data
    // RSP  : stack pointer
    {
        0x20000001,
        0x20000C00,
        0x20001000
    },

    0x20000400,  // mem buffer location
    0x20000000,  // location to write prog_blob in target RAM
    sizeof(flash_code_H7),  // prog_blob size
    flash_code_H7,  // address of prog_blob
    0x00000400,  // ram_to_flash_bytes_to_be_written
};
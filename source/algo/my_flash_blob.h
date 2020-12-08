/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2020-08-22 17:55:57
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-12-04 14:52:10
 * @FilePath     : \DAPLink\source\algo\my_flash_blob.h
 */
#ifndef MY_FLASH_BLOB_H
#define MY_FLASH_BLOB_H

#include <stdint.h>


typedef struct {
    uint32_t breakpoint;
    uint32_t static_base;
    uint32_t stack_pointer;
} my_program_syscall_t;

typedef struct {
    const uint32_t  init;
    const uint32_t  uninit;
    const uint32_t  erase_chip;
    const uint32_t  erase_sector;
    const uint32_t  program_page;
    const my_program_syscall_t sys_call_s;
    const uint32_t  program_buffer;
    const uint32_t  algo_start;
    const uint32_t  algo_size;
    const uint32_t *algo_blob;
    const uint32_t  program_buffer_size;
} my_program_target_t;

typedef struct {
    const uint32_t start;
    const uint32_t size;
} my_sector_info_t;

typedef struct {

	char * name;
    my_program_target_t algo;
} my_algo_info_t;

enum 
{
	F0 = 0,
	F1,
	F3,
	F4,
	F7,
	H7
};

extern const my_program_target_t flash_algo_F0;
extern const my_program_target_t flash_algo_F1;
extern const my_program_target_t flash_algo_F3;
extern const my_program_target_t flash_algo_F4;
extern const my_program_target_t flash_algo_F7;
extern const my_program_target_t flash_algo_H7;
extern my_algo_info_t STM32_ALGO[];
void algo_init(void);
#endif

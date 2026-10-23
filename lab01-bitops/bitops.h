#ifndef BITOPS_H
#define BITOPS_H

#include <stdint.h>

/* ==========================================================
 * Part 2：单 bit 操作
 *
 * 要求：全部用宏实现；参数一律加括号；用 1U 而不是 1。
 * ========================================================== */

/* 第 n 位为 1 的掩码 */
#define BIT(n)              (1U<<(n))          /* TODO */

/* 把 reg 的第 n 位置 1 */
#define SET_BIT(reg, n)     ((reg)|=BIT(n))         /* TODO */

/* 把 reg 的第 n 位清 0 */
#define CLEAR_BIT(reg, n)  ((reg)&=~BIT(n))         /* TODO */

/* 把 reg 的第 n 位翻转 */
#define TOGGLE_BIT(reg, n)  ((reg)^=BIT(n))        /* TODO */

/* 读出 reg 的第 n 位，结果是 0 或 1 */
#define READ_BIT(reg, n)    (((reg)>>(n))&1U)         /* TODO */

/* ==========================================================
 * Part 3：位段操作
 *
 * pos 从 0 开始计数。
 * 注意 width == 32 的情况。
 * ========================================================== */

/* 低 width 位全 1 的掩码 */
#define MASK(width)   ((width)==32 ? 0xFFFFFFFFU:((1U<<(width))-1U))   /* TODO */

/* 取出 reg 中 [pos, pos+width) 这一段 */
#define GET_BITS(reg, pos, width)  (((reg)>>(pos)&MASK(width)))  /* TODO */

/* 把 reg 中 [pos, pos+width) 替换为 val（val 超出 width 的部分要截断） */
#define SET_BITS(reg, pos, width, val)  ((reg) = (((reg) & ~(MASK(width) << (pos))) | (((val) & MASK(width)) << (pos))))
/* TODO */
/* ==========================================================
 * Part 4：GPIO 寄存器模拟
 *
 * bit0     EN
 * bit2:1   MODE
 * bit5:3   SPEED
 * bit6     IRQ
 * ========================================================== */

#define GPIO_EN_BIT        0
#define GPIO_MODE_POS      1
#define GPIO_MODE_WIDTH    2
#define GPIO_SPEED_POS     3
#define GPIO_SPEED_WIDTH   3
#define GPIO_IRQ_BIT       6

void gpio_init(uint32_t *reg);
void gpio_set_enable(uint32_t *reg, int on);
void gpio_set_mode(uint32_t *reg, unsigned mode);
unsigned gpio_get_mode(uint32_t reg);
void gpio_set_speed(uint32_t *reg, unsigned speed);
void gpio_set_irq(uint32_t *reg, int on);
void gpio_dump(uint32_t reg);

/* ==========================================================
 * Part 5：面试小题
 * ========================================================== */

/* 是 2 的幂返回 1，否则返回 0。注意 0 不是 2 的幂。 */
int is_power_of_two(uint32_t n);

/* 返回 n 的二进制中 1 的个数 */
int popcount(uint32_t n);

/* 不用临时变量交换两个整数 */
void swap_without_temp(int *a, int *b);

/* 反转一个字节的位序：0x01 -> 0x80 */
uint8_t reverse_bits8(uint8_t b);

/* 数组里只有一个数出现奇数次，其余都出现偶数次，找出它 */
int find_single(int *arr, int n);

#endif /* BITOPS_H */

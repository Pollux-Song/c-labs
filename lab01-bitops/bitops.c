#include <stdio.h>

#include "bitops.h"

/* ==========================================================
 * Part 4：GPIO 寄存器模拟
 * ========================================================== */

void gpio_init(uint32_t *reg)
{
    *reg = 0;
}

void gpio_set_enable(uint32_t *reg, int on)
{
    if (on) {
        SET_BIT(*reg, GPIO_EN_BIT);
    } else {
        CLEAR_BIT(*reg, GPIO_EN_BIT);
    }
}

void gpio_set_mode(uint32_t *reg, unsigned mode)
{
    SET_BITS(*reg, GPIO_MODE_POS, GPIO_MODE_WIDTH, mode);
}

unsigned gpio_get_mode(uint32_t reg)
{
    return GET_BITS(reg, GPIO_MODE_POS, GPIO_MODE_WIDTH);
}

void gpio_set_speed(uint32_t *reg, unsigned speed)
{
    SET_BITS(*reg, GPIO_SPEED_POS, GPIO_SPEED_WIDTH, speed);
}

void gpio_set_irq(uint32_t *reg, int on)
{
    if (on) {
        SET_BIT(*reg, GPIO_IRQ_BIT);
    } else {
        CLEAR_BIT(*reg, GPIO_IRQ_BIT);
    }
}

void gpio_dump(uint32_t reg)
{
    printf("REG=0x%08X  EN=%u  MODE=%u  SPEED=%u  IRQ=%u\n",
           (unsigned)reg,
           (unsigned)GET_BITS(reg, GPIO_EN_BIT, 1),
           (unsigned)gpio_get_mode(reg),
           (unsigned)GET_BITS(reg, GPIO_SPEED_POS, GPIO_SPEED_WIDTH),
           (unsigned)GET_BITS(reg, GPIO_IRQ_BIT, 1));
}

/* ==========================================================
 * Part 5：面试小题
 * ========================================================== */

int is_power_of_two(uint32_t n)
{
    if (n == 0) return 0;
    return (n & (n - 1)) == 0;
}

int popcount(uint32_t n)
{
    int c = 0;
    while (n) {
        n &= n - 1;
        c++;
    }
    return c;
}

void swap_without_temp(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

uint8_t reverse_bits8(uint8_t b)
{
    uint8_t r = 0;
    for (int i = 0; i < 8; i++) {
        r = (r << 1) | (b & 1);
        b >>= 1;
    }
    return r;
}

int find_single(int *arr, int n)
{
    int r = 0;
    for (int i = 0; i < n; i++) {
        r ^= arr[i];
    }
    return r;
}

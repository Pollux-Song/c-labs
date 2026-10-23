#include <stdio.h>
#include <stdint.h>

#include "bitops.h"

static int g_total;
static int g_failed;

#define CHECK_INT(name, got, expect)                                      \
    do {                                                                  \
        g_total++;                                                        \
        if ((uint32_t)(got) != (uint32_t)(expect)) {                      \
            g_failed++;                                                   \
            printf("  FAIL | %-34s got=0x%08X  expected=0x%08X\n",        \
                   (name), (unsigned)(got), (unsigned)(expect));          \
        }                                                                 \
    } while (0)

#define SECTION(s) printf("\n== %s ==\n", (s))

int main(void)
{
    uint32_t r;
    uint32_t v;
    uint32_t g;

    SECTION("Part 2 · 单 bit 操作");

    r = 0U;             SET_BIT(r, 0);   CHECK_INT("SET_BIT n=0",   r, 0x00000001U);
    r = 0U;             SET_BIT(r, 31);  CHECK_INT("SET_BIT n=31",  r, 0x80000000U);
    r = 0xFFFFFFFFU;    CLEAR_BIT(r, 0); CHECK_INT("CLEAR_BIT n=0",  r, 0xFFFFFFFEU);
    r = 0xFFFFFFFFU;    CLEAR_BIT(r, 31);CHECK_INT("CLEAR_BIT n=31", r, 0x7FFFFFFFU);

    r = 0U;             TOGGLE_BIT(r, 3); CHECK_INT("TOGGLE 0->1", r, 0x00000008U);
                        TOGGLE_BIT(r, 3); CHECK_INT("TOGGLE 1->0", r, 0x00000000U);

    r = 0xA5A5A5A5U;
    CHECK_INT("READ_BIT n=0",  READ_BIT(r, 0),  1U);
    CHECK_INT("READ_BIT n=1",  READ_BIT(r, 1),  0U);
    CHECK_INT("READ_BIT n=31", READ_BIT(r, 31), 1U);

    CHECK_INT("BIT(0)",  BIT(0),  0x00000001U);
    CHECK_INT("BIT(31)", BIT(31), 0x80000000U);

    SECTION("Part 3 · 位段操作");

    CHECK_INT("MASK(1)",  MASK(1),  0x00000001U);
    CHECK_INT("MASK(8)",  MASK(8),  0x000000FFU);
    CHECK_INT("MASK(31)", MASK(31), 0x7FFFFFFFU);
    CHECK_INT("MASK(32)", MASK(32), 0xFFFFFFFFU);

    v = 0xABCD1234U;
    CHECK_INT("GET_BITS pos=4  w=8", GET_BITS(v, 4, 8),  0x23U);
    CHECK_INT("GET_BITS pos=0  w=4", GET_BITS(v, 0, 4),  0x04U);
    CHECK_INT("GET_BITS pos=28 w=4", GET_BITS(v, 28, 4), 0x0AU);

    r = 0xFFFFFFFFU;
    SET_BITS(r, 8, 8, 0x00U);
    CHECK_INT("SET_BITS 清 8..15", r, 0xFFFF00FFU);

    r = 0x00000000U;
    SET_BITS(r, 4, 4, 0x0AU);
    CHECK_INT("SET_BITS 写 4..7", r, 0x000000A0U);

    r = 0x00000000U;
    SET_BITS(r, 0, 4, 0xFFU);
    CHECK_INT("SET_BITS 截断到 width", r, 0x0000000FU);

    r = 0x12345678U;
    SET_BITS(r, 0, 32, 0xDEADBEEFU);
    CHECK_INT("SET_BITS width=32", r, 0xDEADBEEFU);

    SECTION("Part 4 · GPIO 寄存器模拟");

    g = 0xFFFFFFFFU;
    gpio_init(&g);
    CHECK_INT("gpio_init 清零", g, 0x00000000U);

    gpio_set_enable(&g, 1);
    CHECK_INT("EN=1", GET_BITS(g, GPIO_EN_BIT, 1), 1U);

    gpio_set_mode(&g, 2U);
    CHECK_INT("MODE=2", gpio_get_mode(g), 2U);
    CHECK_INT("改 MODE 不影响 EN", GET_BITS(g, GPIO_EN_BIT, 1), 1U);

    gpio_set_speed(&g, 5U);
    CHECK_INT("SPEED=5", GET_BITS(g, GPIO_SPEED_POS, GPIO_SPEED_WIDTH), 5U);
    CHECK_INT("改 SPEED 不影响 MODE", gpio_get_mode(g), 2U);

    gpio_set_irq(&g, 1);
    CHECK_INT("IRQ=1", GET_BITS(g, GPIO_IRQ_BIT, 1), 1U);

    CHECK_INT("最终寄存器值", g,
              (1U << GPIO_EN_BIT) |
              (2U << GPIO_MODE_POS) |
              (5U << GPIO_SPEED_POS) |
              (1U << GPIO_IRQ_BIT));

    gpio_set_enable(&g, 0);
    CHECK_INT("EN=0 时其他位不变", g,
              (2U << GPIO_MODE_POS) |
              (5U << GPIO_SPEED_POS) |
              (1U << GPIO_IRQ_BIT));

    gpio_dump(g);

    SECTION("Part 5 · 面试小题");

    CHECK_INT("pow2(1)",          is_power_of_two(1U),          1);
    CHECK_INT("pow2(2)",          is_power_of_two(2U),          1);
    CHECK_INT("pow2(1024)",       is_power_of_two(1024U),       1);
    CHECK_INT("pow2(0x80000000)", is_power_of_two(0x80000000U), 1);
    CHECK_INT("pow2(3)",          is_power_of_two(3U),          0);
    CHECK_INT("pow2(0)",          is_power_of_two(0U),          0);

    CHECK_INT("popcount(0)",          popcount(0U),          0);
    CHECK_INT("popcount(1)",          popcount(1U),          1);
    CHECK_INT("popcount(0xFF)",       popcount(0xFFU),       8);
    CHECK_INT("popcount(0x80000000)", popcount(0x80000000U), 1);
    CHECK_INT("popcount(0xF0F0F0F0)", popcount(0xF0F0F0F0U), 16);

    {
        int a = 5, b = 7;
        swap_without_temp(&a, &b);
        CHECK_INT("swap 后 a", a, 7);
        CHECK_INT("swap 后 b", b, 5);
    }
    {
        int c = 9, d = 9;
        swap_without_temp(&c, &d);
        CHECK_INT("swap 同值 c", c, 9);
        CHECK_INT("swap 同值 d", d, 9);
    }

    CHECK_INT("reverse8(0x01)", reverse_bits8(0x01U), 0x80U);
    CHECK_INT("reverse8(0xAA)", reverse_bits8(0xAAU), 0x55U);
    CHECK_INT("reverse8(0x00)", reverse_bits8(0x00U), 0x00U);
    CHECK_INT("reverse8(0xFF)", reverse_bits8(0xFFU), 0xFFU);

    {
        int arr[] = {1, 2, 3, 2, 1};
        CHECK_INT("find_single", find_single(arr, 5), 3);
    }

    printf("\n----------------------------------------\n");
    printf("TOTAL %d   FAILED %d\n", g_total, g_failed);

    if (g_failed == 0) {
        printf("全部通过。现在合上电脑做 Part 6 的口述。\n");
        return 0;
    }

    printf("还有 %d 项没过，从第一个 FAIL 开始查。\n", g_failed);
    return 1;
}

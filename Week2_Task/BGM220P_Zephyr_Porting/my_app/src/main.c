#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)
#define SW0_NODE DT_ALIAS(sw0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

void main(void)
{
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&button, GPIO_INPUT);

    while (1) {
        if (gpio_pin_get_dt(&button) == 0) {
            gpio_pin_set_dt(&led, 1);
        } else {
            gpio_pin_set_dt(&led, 0);
        }
        k_msleep(100);
    }
}

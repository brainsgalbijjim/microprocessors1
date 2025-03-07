/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/**
 * Bryan Koe, Kimson Lam, Christian Nguyen
 * EECE.3170 Microprocessors 
 * HW4 - Pico LED Blink 
 */
 #include "pico/stdlib.h"
 
// Pico W devices use a GPIO on the WiFi chip for the LED
 #ifdef CYW43_WL_GPIO_LED_PIN
 #include "pico/cyw43_arch.h"
 #endif
 
// Define delay values
#define LED_ON_TIME 100   // 100ms ON
#define LED_OFF_TIME 200  // 200ms OFF
#define PAUSE_TIME  700   // 700ms pause between counts

// Initialize the LED
int pico_led_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
	return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
	return cyw43_arch_init();
#endif
}

// Function to turn the LED on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
	gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

int main() {
	int rc = pico_led_init();
	hard_assert(rc == PICO_OK);
// *****CHANGED PART*****************************
	while (true) {
		for (int count = 1; count <= 5; count++) { // Count from 1 to 5
			for (int i = 0; i < count; i++) { // Blink the number of times equal to count
				pico_set_led(true);
				sleep_ms(LED_ON_TIME);
				pico_set_led(false);
				sleep_ms(LED_OFF_TIME);
			}
			sleep_ms(PAUSE_TIME); // Pause before next count
		}
	}
}
 


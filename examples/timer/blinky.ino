#include "Arduino.h"
#include "xmc_gpio.h"
// the setup function runs once when you press reset or power the board
void setup() {
    setupGPIO();
}

// the loop function runs over and over again forever
void loop() {
  // Toggle the LED using delay
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Delay for 1000 milliseconds (1 second)
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Delay for 1000 milliseconds (1 second)

  // Toggle the LED using delayMicroseconds
  digitalWrite(LED_BUILTIN, LOW);
  delayMicroseconds(500000); // Delay for 500000 microseconds (0.5 seconds)
  digitalWrite(LED_BUILTIN, HIGH);
  delayMicroseconds(500000); // Delay for 500000 microseconds (0.5 seconds)
}


#ifdef __cplusplus
extern "C" {
#endif
void setupGPIO() {
    XMC_GPIO_CONFIG_t gpio_config;

    gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
    gpio_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
    gpio_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
    XMC_GPIO_Init(mapping_port_pin[LED_BUILTIN].port, mapping_port_pin[LED_BUILTIN].pin, &gpio_config);
}

void digitalWrite(pin_size_t pin, PinStatus value) {
    XMC_GPIO_SetOutputLevel(mapping_port_pin[pin].port, mapping_port_pin[pin].pin,
                            (value == LOW) ? XMC_GPIO_OUTPUT_LEVEL_LOW
                                           : XMC_GPIO_OUTPUT_LEVEL_HIGH);
}

#ifdef __cplusplus
}
#endif
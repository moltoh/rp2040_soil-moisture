///
/// Example code to interface with Adafruit soil
/// moisture sensor.
///
/// Created by Michael Hogue.
///

#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "soil_moisture_seesaw.h"

#define I2C_INSTANCE i2c0
#define I2C_SCL_PIN 17
#define I2C_SDA_PIN 16

int main() {
    stdio_init_all();

    i2c_init(I2C_INSTANCE, 100000);
    
    // Setup I2C bus
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL_PIN);
    gpio_pull_up(I2C_SDA_PIN);

    // Perform SW Reset on seesaw
    seesaw_sw_reset(I2C_INSTANCE);

    while(1) {
        // Read moisture level
        uint16_t moisture = seesaw_read_moisture(I2C_INSTANCE);

        printf("Soil moisture: %d\n", moisture);

        sleep_ms(500);
    }

    return 0;
}
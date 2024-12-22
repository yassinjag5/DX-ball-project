#include "dht11.h"
void Delay_mms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}

void readDHT11(uint8_t* humidity, uint8_t* temperature) {
    // Initialize variables to store the data
	int i,j;
    uint8_t data[5] = {0};

    // Request data from the DHT11 sensor
    GPIOE_DIR |= (1 << 3);      // Set PE3 as output
    GPIOE_DATA &= ~(1 << 3);    // Pull the line low
    Delay_mms(18);               // Delay for at least 18ms (DHT11 datasheet requirement)
    GPIOE_DATA |= (1 << 3);     // Release the line
    Delay_mms(1);                // Wait 40us for the DHT11 response

    // Change pin to input for receiving data
    GPIOE_DIR &= ~(1 << 3);     

    // Wait for the sensor to respond
    while (GPIOE_DATA & (1 << 3)); // Wait for low signal
    while (!(GPIOE_DATA & (1 << 3))); // Wait for high signal
    while (GPIOE_DATA & (1 << 3)); // Wait for low signal

    // Read data from the sensor
    for ( i= 0; i < 5; ++i) {
        for ( j = 7; j >= 0; --j) {
            while (!(GPIOE_DATA & (1 << 3))); // Wait for high signal
            Delay_mms(30);                    // Wait ~30us
            if (GPIOE_DATA & (1 << 3)) {
                data[i] |= (1 << j);         // Record as '1'
            }
            while (GPIOE_DATA & (1 << 3));  // Wait for low signal
        }
    }

    // Check the checksum
    if (data[0] + data[1] + data[2] + data[3] == data[4]) {
        *humidity = data[0];
        *temperature = data[2];
    } else {
        *humidity = 0;
        *temperature = 0;
    }
}



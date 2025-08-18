#include "DHT.h"
#include "stm32g4xx.h"
#include "usart.h"

#include "Timer.h"
#include "GpioPin.h"


void OneWire_Begin()
{
	init_pin();
	set_pin_output();
	GPIOB->BSRR = (1 << (6 + 16)); // Set pin to low
	delay_ms(20);
	GPIOB->BSRR = (1 << 6); // Set pin to high
	delay_us(40);
	set_pin_input();


	uint32_t count = 0;

	while ((GPIOB->IDR & (1 << 6)) !=0) // wait for low
	{
		delay_us(1);
		count ++;

		if (count > 150) //timeout
		{
			break;
		}
	}
	count = 0;

	while ((GPIOB->IDR & (1 << 6)) ==0) // wait for high
		{
			delay_us(1);
			count ++;

			if (count > 150) //timeout
			{
				break;
			}

		}
	count = 0;

	while ((GPIOB->IDR & (1 << 6)) !=0) // wait for low
			{
				delay_us(1);
				count ++;

				if (count > 150) //timeout
				{
					break;
				}

			}
	count = 0;
}


void ReadBit(uint8_t data[5])
{
    //clear before read
    for (int i = 0; i < 5; i++) {
        data[i] = 0;
    }

    for (int i = 0; i < 40; i++)
    {
        // 1. wait for beginning of bit (50 us low)
        uint32_t timeout = 0;
        while ((GPIOB->IDR & (1 << 6)) == 0) {
            delay_us(1);
            if (++timeout > 100) break; // timeout
        }

        // 2. count high time
        uint32_t high_time = 0;
        while ((GPIOB->IDR & (1 << 6)) != 0) {
            delay_us(1);
            if (++high_time > 100) break; // timeout
        }

        // 3. specify bit value (26-28us - "0", 70us - "1"
        uint8_t bit = (high_time > 35) ? 1 : 0;
                data[i / 8] <<= 1;
                data[i / 8] |= bit;
    }
}

void ReadData(uint8_t data[5], float *Humidity, float *Temperature)
{
	uint8_t IntRH = data[0]; // Integral byte Humidity
	uint8_t DecRH = data[1]; // Decimal byte Humidity
	uint8_t IntTemp = data[2]; // Integral byte Temperature
	uint8_t DecTemp = data[3]; //Decimal byte Temperature
	uint8_t Checksum = data[4];

	if (IntRH + DecRH + IntTemp + DecTemp == Checksum)
	{
		*Humidity = IntRH + DecRH*0.1f;
		*Temperature = IntTemp + DecTemp*0.1f;
	}
	else
	{
		*Humidity = 0;
		*Temperature = 0;
	}
}













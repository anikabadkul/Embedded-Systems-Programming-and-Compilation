#include <avr/io.h>            // Include header for AVR input/output definitions
#include <util/delay.h>        // Include utility for delays, provides _delay_ms function
#define MYDELAY 200          // Define a constant for the delay duration in milliseconds

int main(void) {

    // Port initialization
    DDRD &= ~(1 << DDD3 | 1 << DDD4 | 1 << DDD5); // Configure pins D3, D4, D5 as inputs
    // By clearing the bits in DDRD, pins D3, D4, D5 are set to input mode

    PORTD |= (1 << PORTD3 | 1 << PORTD4 | 1 << PORTD5); // Enable internal pull-up resistors on pins D3, D4, D5
    // Setting these PORTD bits to 1 activates the pull-up resistors, which are useful when buttons are connected to these pins

    DDRB |= (1 << DDB6 | 1 << DDB7); // Configure pins D6, D7 as outputs
    // Setting the bits in DDRB makes pins D6 and D7 output pins, generally used here to control LEDs

    // Event loop: Continuously check the state of the input pins and control the output pins accordingly
    while (1) {
        if (!(PIND & (1 << PIND3)) && (PIND & (1 << PIND4)) && (PIND & (1 << PIND5))) {
            // Check if only the button connected to D3 is pressed
            PORTD |= (1 << PORTD6); // Turn on the red LED connected to pin D6
            _delay_ms(MYDELAY); // Delay to keep the LED on for a set duration
            PORTD &= ~(1 << PORTD6); // Turn off the red LED
            _delay_ms(MYDELAY); // Delay to keep the LED off for a set duration
        } else if ((PIND & (1 << PIND3)) && !(PIND & (1 << PIND4)) && (PIND & (1 << PIND5))) {
            // Check if only the button connected to D4 is pressed
            PORTD |= (1 << PORTD7); // Turn on the green LED connected to pin D7
            _delay_ms(MYDELAY); // Delay to keep the LED on for a set duration
            PORTD &= ~(1 << PORTD7); // Turn off the green LED
            _delay_ms(MYDELAY); // Delay to keep the LED off for a set duration
        } else if ((PIND & (1 << PIND3)) && (PIND & (1 << PIND4)) && !(PIND & (1 << PIND5))) {
            // Check if only the button connected to D5 is pressed
            PORTD |= (1 << PORTD6 | 1 << PORTD7); // Turn on both LEDs
            _delay_ms(MYDELAY); // Delay to keep the LEDs on for a set duration
            PORTD &= ~(1 << PORTD6 | 1 << PORTD7); // Turn off both LEDs
            _delay_ms(MYDELAY); // Delay to keep the LEDs off for a set duration
        } else {
            // No button or multiple buttons are pressed
            PORTD &= ~(1 << PORTD6 | 1 << PORTD7); // Turn off both LEDs
            // Ensures LEDs are off if conditions for individual LED control are not met
        }
    } // End of event loop

    return 0;                  // This line is theoretically unreachable because the program is designed to run indefinitely in the loop
}


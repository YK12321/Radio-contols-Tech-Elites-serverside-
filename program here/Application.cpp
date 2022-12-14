#include <iostream>
#include <string>
#include <radio.h>

// Define the radio frequency to use for communication
const int FREQUENCY = 915000000;

int main()
{
    std::string message;

    // Initialize the radio module
    radio.on();

    // Set the radio to transmit on the defined frequency
    radio.config(FREQUENCY, 6);

    while (true)
    {
        // Prompt the user to enter a message to transmit
        std::cout << "Enter a message to transmit: ";
        std::cin >> message;

        // Transmit the message over radio as a string
        radio.send_string(message);

        // Receive any incoming messages
        std::string incoming = radio.receive_string();

        // If a message was received, print it to the screen
        if (!incoming.empty())
        {
            std::cout << "Received message: " << incoming << std::endl;
        }
    }

    return 0;
}

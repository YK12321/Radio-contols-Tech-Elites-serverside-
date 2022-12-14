#ifndef RADIO_H
#define RADIO_H

// function declarations for radio module
void on();
void config(int frequency, int power);
void send_string(std::string message);
std::string receive_string();

#endif // RADIO_H

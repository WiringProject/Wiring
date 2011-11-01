/* $Id: Messenger.h 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Thomas Ouellet Fredericks
|| @url            http://wiring.org.co/
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Messenger is a "toolkit" that facilitates the parsing of ASCII messages.
|| | Messenger buffers characters until it receives a carriage return (CR).
|| | It then considers the message complete and available.
|| | The message is split into many elements as defined by a separator.
|| | The default separator is the space character, but can be any character other than NULL, LF or CR.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef MESSENGER_H
#define MESSENGER_H

#define MESSENGER_BUFFER_SIZE 64

#include <inttypes.h>

class Messenger
{
  public:
    typedef void (*messengerCallbackFunction)(void);

    Messenger();
    Messenger(char separator);

    uint8_t process(int serialByte);
    uint8_t available();

    int readInt();
    long readLong();
    char readChar();
    void copyString(char *string, uint8_t size);
    uint8_t checkString(char *string);

    void attach(messengerCallbackFunction newFunction);

  private:
    void init(char separator);
    uint8_t next();
    void reset();

    uint8_t messageState;

    char* current; // Pointer to current data
    char* last;

    char token[2];
    uint8_t dumped;

    char buffer[MESSENGER_BUFFER_SIZE]; // Buffer that holds the data
    uint8_t bufferIndex; // Index where to write the data
    uint8_t bufferLength; // The length of the buffer (defaults to 64)
    uint8_t bufferLastIndex; // The last index of the buffer

    messengerCallbackFunction callback;
};

#endif
// MESSENGER_H

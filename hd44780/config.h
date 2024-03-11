
#include <avr/io.h>



/**
DDRB: PINB0 to PINB7
PORTB: PINB0 to PINB7



                                      +-----+
         +----[PWR]-------------------| USB |--+
         |                            +-----+  |
         |         GND/RST2  [ ][ ]            |
         |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |   PINC5
         |          5V/MISO2 [ ][ ]  A4/SDA[ ] |   PINC4
         |                             AREF[ ] |
         |                              GND[ ] |
         | [ ]N/C                    SCK/13[ ] |   PINB5
         | [ ]IOREF                 MISO/12[ ] |   PINB4
         | [ ]RST                   MOSI/11[ ]~|   PINB3
         | [ ]3V3    +---+               10[ ]~|   PINB2
         | [ ]5v    -| A |-               9[ ]~|   PINB1
         | [ ]GND   -| R |-               8[ ] |   PINB0
         | [ ]GND   -| D |-                    |
         | [ ]Vin   -| U |-               7[ ] |   PIND7
         |          -| I |-               6[ ]~|   PIND6
 PINC0   | [ ]A0    -| N |-               5[ ]~|   PIND5
 PINC1   | [ ]A1    -| O |-               4[ ] |   PIND4
 PINC2   | [ ]A2     +---+           INT1/3[ ]~|   PIND3
 PINC3   | [ ]A3                     INT0/2[ ] |   PIND2
 PINC4   | [ ]A4/SDA  RST SCK MISO     TX>1[ ] |   PIND1
 PINC5   | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |   PIND0
         |            [ ] [ ] [ ]              |
         |  UNO_R3    GND MOSI 5V  ____________/
          \_______________________/


ASCII-art credit to `Warren Creemers <http://busyducks.com/ascii-art-arduinos>`_.
*/

#include "HAP.h"
#include "HAPTLV+Internal.h"
#include "HAPBase.h"

uint8_t streamingSessionTLV[] = {
0x01,0x10, //SessionId
    0xB9,0x41,0x7B,0xE0,0xC3,0x1D,0x4E,0x62,
    0x90,0xA9,0x7F,0xBB,0x90,0xBB,0x5C,0x33,
0x03,0x17, //Controller Address
    0x01,0x01,0x00, // IP Address Version
    0x02,0x0A, // IP Address char[] 10.0.1.210
        0x31,0x30,0x2E,0x30,0x2E,0x31,0x2E,0x32,
        0x31,0x30,
    0x03,0x02,0x80,0xC1, // Video RTP Port uint16
    0x04,0x02,0xAB,0xFF,  // Audio RTP Port uint16
0x04,0x25, // SRTP Video Params
    0x02,0x10, // SRTP Master key
        0x7B,0x24,0x3A,0x3A,0x51,0xF6,0x35,0x13,
        0x0B,0x41,0xD7,0x70,0xFC,0xF2,0xD8,0xE8,
    0x03,0x0E, // SRTP Master Salt
        0x39,0xBF,0x4D,0x91,0x60,0x0D,0xCA,0xE9,
        0xFF,0x0A,0x6B,0xD4,0x6D,0xEC,
    0x01,0x01,0x00, // SRTP Crypto Suite
0x05,0x25, // SRTP Params for Audio
    0x02,0x10, // SRTP Master Key
        0xB1,0xD2,0x6C,0x44,0x55,0xE9,0xC5,0xF1,
        0x9D,0xC7,0xA9,0x49,0x88,0x34,0x8C,0x4D,
    0x03,0x0E, // SRTP Master Salt
        0x4B,0xC7,0x12,0x81,0xDF,0x82,0x76,0xD4,
        0xBE,0xF1,0x28,0xC1,0x58,0xCA,
    0x01,0x01,0x00, // SRTP Crypto Suite
0x02,0x01,0x00, // Streaming Status
0x06,0x04,0x00,0x00,0x00,0x00, // SSRC Video
0x07,0x04,0x40,0xDC,0xB6,0x92 // SSRC Audio
}
/*
power_data:
��̬���ģ�0.36mA

*/


#include "F05_sfr.h" 
#include "F05_common.h" 

#define SCREEN_CLK P0_7
#define SCREEN_DAT P1_0
#define SCREEN_DC P0_6
#define SCREEN_RST P0_5

#define DS1302_CLK P1_4
#define DS1302_DAT P1_5
#define DS1302_RST P2_0

#define BTN_1 P0_3
#define BTN_2 P0_4

#define BG P1_1

#define LONG_PRESS_TIME 0x20 // ����������㳤��

#define MAX_MODE 3


const unsigned char code font[] = { // ���ֿ�ŵ�flash����
  0x00, 0x00, 0x00, 0x00, 0x00, // (Space)
  0x00, 0x00, 0x9E, 0x00, 0x00, // !
  0x00, 0x0E, 0x00, 0x0E, 0x00, // "
  0x28, 0xFE, 0x28, 0xFE, 0x28, // #
  0x48, 0x54, 0xFE, 0x54, 0x24, // $
  0x46, 0x26, 0x10, 0xC8, 0xC4, // %
  0x6C, 0x92, 0xAA, 0x44, 0xA0, // &
  0x00, 0x0A, 0x06, 0x00, 0x00, // '
  0x00, 0x38, 0x44, 0x82, 0x00, // (
  0x00, 0x82, 0x44, 0x38, 0x00, // )
  0x10, 0x54, 0x38, 0x54, 0x10, // *
  0x10, 0x10, 0x7C, 0x10, 0x10, // +
  0x00, 0xA0, 0x60, 0x00, 0x00, // ,
  0x10, 0x10, 0x10, 0x10, 0x10, // -
  0x00, 0x60, 0x60, 0x00, 0x00, // .
  0x40, 0x20, 0x10, 0x08, 0x04, // /

  0x7C, 0xA2, 0x92, 0x8A, 0x7C, // 0
  0x00, 0x84, 0xFE, 0x80, 0x00, // 1
  0x84, 0xC2, 0xA2, 0x92, 0x8C, // 2
  0x42, 0x82, 0x8A, 0x96, 0x62, // 3
  0x30, 0x28, 0x24, 0xFE, 0x20, // 4
  0x4E, 0x8A, 0x8A, 0x8A, 0x72, // 5
  0x78, 0x94, 0x92, 0x92, 0x60, // 6
  0x02, 0xE2, 0x12, 0x0A, 0x06, // 7
  0x6C, 0x92, 0x92, 0x92, 0x6C, // 8
  0x0C, 0x92, 0x92, 0x52, 0x3C, // 9

  0x00, 0x6C, 0x6C, 0x00, 0x00, // :
  0x00, 0xAC, 0x6C, 0x00, 0x00, // ;
  0x00, 0x10, 0x28, 0x44, 0x82, // <
  0x28, 0x28, 0x28, 0x28, 0x28, // =
  0x82, 0x44, 0x28, 0x10, 0x00, // >
  0x04, 0x02, 0xA2, 0x12, 0x0C, // ?
  0x64, 0x92, 0xF2, 0x82, 0x7C, // @

  0xFC, 0x22, 0x22, 0x22, 0xFC, // A
  0xFE, 0x92, 0x92, 0x92, 0x6C, // B
  0x7C, 0x82, 0x82, 0x82, 0x44, // C
  0xFE, 0x82, 0x82, 0x44, 0x38, // D
  0xFE, 0x92, 0x92, 0x92, 0x82, // E
  0xFE, 0x12, 0x12, 0x02, 0x02, // F
  0x7C, 0x82, 0x82, 0xA2, 0x64, // G
  0xFE, 0x10, 0x10, 0x10, 0xFE, // H
  0x00, 0x82, 0xFE, 0x82, 0x00, // I
  0x40, 0x80, 0x82, 0x7E, 0x02, // J
  0xFE, 0x10, 0x28, 0x44, 0x82, // K
  0xFE, 0x80, 0x80, 0x80, 0x80, // L
  0xFE, 0x04, 0x08, 0x04, 0xFE, // M
  0xFE, 0x08, 0x10, 0x20, 0xFE, // N
  0x7C, 0x82, 0x82, 0x82, 0x7C, // O
  0xFE, 0x12, 0x12, 0x12, 0x0C, // P
  0x7C, 0x82, 0xA2, 0x42, 0xBC, // Q
  0xFE, 0x12, 0x32, 0x52, 0x8C, // R
  0x8C, 0x92, 0x92, 0x92, 0x62, // S
  0x02, 0x02, 0xFE, 0x02, 0x02, // T
  0x7E, 0x80, 0x80, 0x80, 0x7E, // U
  0x3E, 0x40, 0x80, 0x40, 0x3E, // V
  0xFE, 0x40, 0x30, 0x40, 0xFE, // W
  0xC6, 0x28, 0x10, 0x28, 0xC6, // X
  0x06, 0x08, 0xF0, 0x08, 0x06, // Y
  0xC2, 0xA2, 0x92, 0x8A, 0x86, // Z

  0x00, 0x00, 0xFE, 0x82, 0x82, // [
  0x04, 0x08, 0x10, 0x20, 0x40, // "\"
  0x82, 0x82, 0xFE, 0x00, 0x00, // ]
  0x08, 0x04, 0x02, 0x04, 0x08, // ^
  0x80, 0x80, 0x80, 0x80, 0x80, // _
  0x00, 0x02, 0x04, 0x08, 0x00, // `

  0x40, 0xA8, 0xA8, 0xA8, 0xF0, // a
  0xFE, 0x90, 0x88, 0x88, 0x70, // b
  0x70, 0x88, 0x88, 0x88, 0x40, // c
  0x70, 0x88, 0x88, 0x90, 0xFE, // d
  0x70, 0xA8, 0xA8, 0xA8, 0x30, // e
  0x10, 0xFC, 0x12, 0x02, 0x04, // f
  0x10, 0x28, 0xA8, 0xA8, 0x78, // g
  0xFE, 0x10, 0x08, 0x08, 0xF0, // h
  0x00, 0x88, 0xFA, 0x80, 0x00, // i
  0x40, 0x80, 0x88, 0x7A, 0x00, // j
  0x00, 0xFE, 0x20, 0x50, 0x88, // k
  0x00, 0x82, 0xFE, 0x80, 0x00, // l
  0xF8, 0x08, 0x30, 0x08, 0xF0, // m
  0xF8, 0x10, 0x08, 0x08, 0xF0, // n
  0x70, 0x88, 0x88, 0x88, 0x70, // o
  0xF8, 0x28, 0x28, 0x28, 0x10, // p
  0x10, 0x28, 0x28, 0x30, 0xF8, // q
  0xF8, 0x10, 0x08, 0x08, 0x10, // r
  0x90, 0xA8, 0xA8, 0xA8, 0x40, // s
  0x08, 0x7E, 0x88, 0x80, 0x40, // t
  0x78, 0x80, 0x80, 0x40, 0xF8, // u
  0x38, 0x40, 0x80, 0x40, 0x38, // v
  0x78, 0x80, 0x60, 0x80, 0x78, // w
  0x88, 0x50, 0x20, 0x50, 0x88, // x
  0x18, 0xA0, 0xA0, 0xA0, 0x78, // y
  0x88, 0xC8, 0xA8, 0x98, 0x88, // z

  0x00, 0x10, 0x6C, 0x82, 0x00, // {
  0x00, 0x00, 0xFE, 0x00, 0x00, // |
  0x00, 0x82, 0x6C, 0x10, 0x00, // }
};



const unsigned char code big_num_font[] = {
  0x80,0xe0,0xf0,0xf8,0xfc,0xfc,0x7c,0x7e,0x7e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x7e,0x7e,0xfc,0xfc,0xf8,0xf8,0xf0,0xc0,0x00,
  0xff,0xff,0xff,0xff,0xff,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,
  0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xff,0xff,0xff,0xff,0xff,
  0x01,0x07,0x0f,0x1f,0x3f,0x3f,0x7e,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7e,0x3f,0x3f,0x1f,0x0f,0x07,0x01,
  
  0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x70,0x78,0x7c,0x7c,0xfc,0xfc,0xfc,0xfc,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x7f,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  
  0x00,0x70,0x78,0x78,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0xfc,0xfc,0xf8,0xf8,0xf0,0xf0,0xc0,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
  0x00,0x80,0xe0,0xf0,0xf0,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xfc,0xff,0x7f,0x7f,0x3f,0x1f,0x03,
  0xfe,0xff,0xff,0xff,0xff,0xff,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x07,0x1f,0x7f,0x7f,0xff,0xff,0xf8,0xf8,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0x70,0x00,

  0x00,0x38,0x3c,0x3c,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x7e,0x7e,0xfe,0xfc,0xfc,0xf8,0xf0,0xc0,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00,
  0x00,0x00,0x70,0x78,0x7c,0x7c,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0xff,0xff,0xff,0xff,0xf7,0xc3,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,
  0x08,0x38,0x78,0x78,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xfc,0xfc,0x7f,0x7f,0x3f,0x1f,0x0f,0x01,
  
  0xe0,0xf0,0xf8,0xf8,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0xf0,0xf8,0xf8,0xf8,0x00,0x00,0x00,0x00,0x00,
  0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
  0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
  0x03,0x0f,0x1f,0x1f,0x3f,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0xff,0xff,0xff,0xff,0xff,0x3e,0x3e,0x3e,0x1e,0x1e,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x7f,0x7f,0x3f,0x0f,0x00,0x00,0x00,0x00,0x00,

  0xe0,0xf0,0xf8,0xfc,0xfc,0x7e,0x7e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3c,0x3c,0x38,0x00,0x00,
  0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x03,0x07,0x0f,0x1f,0x1f,0x3f,0x3f,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x7e,0xfe,0xfc,0xfc,0xf8,0xe0,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00,
  0x08,0x38,0x78,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xfc,0xfc,0xfe,0x7f,0x7f,0x3f,0x1f,0x07,0x00,

  0x00,0xc0,0xe0,0xf0,0xf0,0xf8,0xf8,0xf8,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xf8,0xf8,0xf0,0xe0,0x80,0x00,
  0xff,0xff,0xff,0xff,0xff,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xff,0xff,0xff,0xff,0xff,0x00,0x30,0x38,0x3c,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x7e,0x7e,0xfc,0xfc,0xf8,0xf0,0xe0,0x80,
  0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0xff,
  0x03,0x0f,0x3f,0x3f,0x7f,0x7e,0xfc,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xfc,0x7c,0x7f,0x7f,0x3f,0x1f,0x0f,0x03,

  0x3c,0x3c,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0xfe,0xfe,0xfe,0xfe,0xfe,0x3e,0x02,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xf8,0xff,0xff,0xff,0xff,0x1f,0x01,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xf8,0xff,0xff,0xff,0xff,0x1f,0x01,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xf8,0xff,0xff,0xff,0xff,0x1f,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xf8,0xff,0xff,0x7f,0x3f,0x1f,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  
  0x00,0x80,0xe0,0xf0,0xf0,0xf8,0xf8,0xf8,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xf8,0xf8,0xf8,0xf8,0xf0,0xf0,0xc0,0x80,
  0x00,0xff,0xff,0xff,0xff,0xff,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0xff,
  0x80,0xe7,0xef,0xff,0xff,0xff,0xfe,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0xfe,0xff,0xff,0xff,0xef,0xc3,
  0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xff,0xff,0xff,0xff,
  0x07,0x1f,0x3f,0x7f,0x7f,0xfc,0xfc,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xfc,0x7e,0x7f,0x7f,0x3f,0x1f,
  
  0x80,0xe0,0xf0,0xf8,0xf8,0xfc,0x7c,0x7c,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7c,0x7c,0xfc,0xf8,0xf8,0xf0,0xe0,0x00,
  0xff,0xff,0xff,0xff,0xff,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xff,0xff,0xff,0xff,0xff,
  0x07,0x1f,0x3f,0x7f,0x7f,0xfe,0xfc,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0x78,0x18,0x00,0xff,0xff,0xff,0xff,0xff,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xff,0xff,0xff,0xff,0xff,
  0x00,0x0c,0x3c,0x3c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7e,0x3e,0x3f,0x3f,0x1f,0x0f,0x07,0x01,
};
  
const unsigned char code chinese_font[] = {0x0,0x21,0x23,0xe6,0x0,0x80,0x91,0xd1,0xff,0x91,0x91,0x91,0xf1,0x81,
0x0,0x0,0x40,0x7f,0x30,0x10,0x7c,0x44,0x44,0x44,0x44,0x44,0x7c,0x0,
0x0,0xc8,0x6b,0x38,0x7f,0x28,0x6e,0x48,0x3c,0xff,0x5,0xf4,0x7c,0x4,
0x0,0x82,0xce,0x7f,0x33,0x3a,0x2e,0x42,0x70,0x39,0xf,0x1f,0x70,0x40,
0x0,0x4,0x4,0xc4,0x4f,0x44,0x44,0xf4,0x44,0x4f,0x44,0xc4,0x4,0x0,
0x0,0x84,0xc4,0xc7,0x64,0x34,0x3c,0xf,0x3c,0x34,0x64,0xc7,0xc4,0x84,
0x80,0xf8,0x20,0xfe,0x20,0x40,0x78,0xf,0xf8,0x8,0xf8,0x8,0xf8,0x0,
0x9,0xd,0xc,0xff,0x6,0x36,0x9c,0xcf,0x71,0x3e,0x87,0x80,0xff,0x0,
0x0,0xc0,0x70,0xfc,0x7,0x0,0x0,0x0,0xff,0x80,0xe0,0x70,0x18,0x8,
0x1,0x1,0x0,0xff,0x0,0x4,0x6,0x3,0xff,0xc1,0xc0,0xc0,0xf0,0x70,
0x0,0xc0,0x78,0x1f,0x18,0x18,0x18,0xff,0x18,0x18,0x18,0x18,0x18,0x0,
0x0,0x60,0x63,0x63,0x63,0x63,0x63,0x7f,0x63,0x63,0x63,0x63,0x60,0x0,
0x0,0x0,0xf8,0xf8,0x88,0x88,0x8e,0x8e,0x88,0x88,0x88,0x88,0xf8,0x0,
0x0,0x0,0xff,0xff,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0xff,0x0,
0x0,0xc0,0xf0,0xfe,0x7,0x8,0x88,0xe8,0xff,0xff,0xe8,0x88,0x8,0x0,
0x0,0x1,0x0,0x7f,0x8,0xe,0xb,0x8,0xff,0xff,0x8,0xb,0x6,0xc,
0x0,0x40,0x44,0x44,0x5c,0x74,0x44,0x47,0x44,0x74,0x5c,0x44,0x44,0x40,
0x0,0x0,0x0,0xfe,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xfe,0x0,0x0,
0x0,0x0,0xc0,0x40,0x0,0xf0,0x6,0xe,0x38,0x20,0x0,0xc0,0xc0,0x0,
0x0,0xe,0x7,0x0,0x0,0xff,0x80,0x80,0x80,0x80,0xf0,0x0,0x7,0xc,
0x0,0x42,0x42,0xfe,0x42,0xe2,0xf8,0x0,0xff,0x82,0x82,0xfe,0x82,0x82,
0x0,0x20,0x30,0x1f,0x10,0x1b,0xc1,0x78,0xf,0x40,0x40,0x7f,0x40,0x40,
0x0,0xe4,0xe4,0x64,0x64,0x7f,0x64,0x64,0x64,0x7f,0x64,0x64,0xe4,0x4,
0x0,0x0,0x84,0xc4,0x64,0x74,0x1f,0x4,0x84,0x84,0x84,0xfc,0x0,0x0,
0x0,0x62,0xc6,0x8c,0x0,0x44,0x54,0x54,0x54,0x7f,0x54,0x54,0x54,0x54,
0x0,0xc0,0xfc,0xc,0x0,0xff,0x29,0x29,0x29,0x29,0xa9,0xa9,0xff,0x0,
0x0,0x0,0xfe,0x2,0xfa,0x9e,0x0,0xfe,0x92,0x92,0x92,0x92,0xfe,0x0,
0x0,0x0,0xff,0x0,0x8,0xf,0x40,0x7f,0x60,0x31,0xf,0x1c,0x66,0x42,
0x0,0x10,0x10,0xde,0xf0,0x30,0x0,0x40,0x40,0xff,0xff,0x40,0x40,0x40,
0x4,0xe,0x3,0xff,0x2,0x6,0x84,0x80,0x80,0xff,0xff,0x80,0x80,0x80,
0x0,0x0,0xe0,0x3c,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x40,0x3e,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x10,0xd0,0xff,0x90,0x10,0x0,0xfe,0x6,0x6,0xfe,0xfe,0x0,0x0,
0x8,0xe,0x3,0xff,0x1,0x83,0xfa,0x3f,0x0,0x0,0xff,0xff,0x80,0xf0,
};


const unsigned char code num_start_offset[5] = {0,30,68,100,59};
const unsigned char code qr[] = {0,}; // ��ά�빦�ܶ�Ӧ�������Ѿ�ɾ��
const unsigned char code nts[] = {0 }; // ͼƬ���ܶ�Ӧ�������Ѿ�ɾ��


const unsigned char code week_name[7][10] = {
  "Monday\0","Tuesday\0","Wednesday\0","Thursday\0","Friday\0","Saturday\0","Sunday\0",
};
const unsigned int code time_table[] = {
  435,// morning reading
  460,
  465, // 1
  505,
  515, // 2
  555,
  580, // 3
  620,
  630, // 4
  670,
  680, // 5
  720,
  
  860, // 6
  900,
  910, // 7
  950,
  960, // 8
  1000,
  1010, // 9
  1045,
  
  1140, // night 1
  1220,
  1235, // night 2
  1330,
};
const unsigned char code lesson_table[] = {
  5 ,1 ,4 ,3 ,3  ,0 ,2 ,10,11, // Monday
  2 ,2 ,0 ,7 ,7  ,3 ,1 ,5 ,14, // Tuesday
  1 ,6 ,2 ,0 ,0  ,5 ,6 ,12,12, // Wednesday
  1 ,1 ,2 ,0 ,9  ,15,3 ,13,13, // Thursday
  3 ,5 ,0 ,4 ,1  ,16,8 ,6, 6 , // Friday
  2, 6 ,6 ,4 ,5  ,16,16,16,16, // Saturday
  16,16,16,16,16 ,16,16,16,1 , // Sunday
};
// 0 1 2 3 4 5 6 7 8 9 10111213141516
// ����Ӣ�ﻯ���������İ���������/ ��



unsigned char mode = 0;
unsigned char fast_update = 0;

unsigned char now_time[3] = {11,59,2};
unsigned char display_num_data[4];
unsigned char btn1_press_time, btn2_press_time; // ��¼������ť�������ۼ�ʱ��
unsigned char btn_state, add_state;
unsigned char time_12;
unsigned char edit = 0; // �Ƿ��ڱ༭��
unsigned char lift = 0;

unsigned char max_[2]; // ����λ�������ֵ����̬����
unsigned char hot_num = 0; // �����޸ĵ���ǰ��λ���Ǻ���λ��0/1

unsigned char last_blink = 0;


unsigned char refresh_screen_now = 1;
unsigned int refresh_count = 0x01;

unsigned char INT_EN_flag;


void delay(int q)
{
  int i,j;
  for(i=0;i<q;i++)
    for(j=0;j<10;j++)
      {}
}

void blink()
{
	BG = 1;
	delay(1);
  BG = 0;
}



void high_speed()
{
	// ȫ��
	HRC_16M_EN;
	CLK_PR=0XA5;
	CLK_C0 &= 0Xcf;
	CLK_PR=0X5a;
	SYSCK_DIV1;
}

void low_speed()
{
  // ����
  CLK_PR=0XA5;
  CLK_C0 &= 0Xcf;
  CLK_C0 |= 0X20;
  CLK_PR=0X5a;
  HRC_16M_DIS;
}

// ds1302 start

/* ds1302 datasheet:
    ���е�ַ��ͷ����1
    ��ַ���һλ0д1��

                   | ��ַ             |RAM��������
                   |                  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
    ��             |д0x80 - ��0x81   |  CH |      ��ʮλ     |        ���λ         |
    ��             |д0x82 - ��0x83   |  0  |      ��ʮλ     |        �ָ�λ         |
    ʱ             |д0x84 - ��0x85   |12/24|  0  |   ʱʮλ  |        ʱ��λ         |
    ��             |д0x86 - ��0x87   |     0     |   ��ʮλ  |        �ո�λ         |
    ��             |д0x88 - ��0x89   |        0        |   ��ʮλ  |      �¸�λ     |
    ����           |д0x8A - ��0x8B   |             0               |       ����      |
    ��             |д0x8C - ��0x8D   |         ��ʮλ        |         ���λ        |
    ����           |д0x8E - ��0x8F   |д����|                0                       |
    ���           |д0x90 - ��0x91   | TCS  | TCS | TCS | TCS| DS  | DS  | RS  | RS  |
    ����д��RTC    |д0xCE - ��0xCF   | �����ö��8λ...                              |
    �û�RAM0       |д0xD0 - ��0xD1   | �û��Զ���Ҫд�������                        |
    ...
    �û�RAM31      |д0xFC - ��0xFD   |  �û��Զ���Ҫд�������                       |
    ����д��RAM    |д0xFE - ��0xFF   |  �����ö��8λ...                             |

    CH: 0���� 1ֹͣ
		12/24 0��24,1��12
    
    TCS=1010 ʹ�ܳ�� DS=01һ�������� RS 01

    д���Ȱ�data���úã��ٰ�CLK���ߣ�������д��
    ��ȡ�����ͣ�����֮��1302������ϱ仯��arduino��ȡ���½��ض�ȡ
    ���Ҷ�ȡʱ����д�룬д��CLK����֮�����ϾͿ��Զ�ȡ��

*/

void DS1302_shift_out(unsigned char data_)
{
  unsigned char i;
  P15_IN_DIS; // SCREEN_DAT
  P15_OUT_EN;
  for (i = 0; i < 8; i++)
  {
    // 1302�ȴ�����ǵ�λ��
    DS1302_DAT = data_ >> i & 1;
    //������д����
    DS1302_CLK = 1;
    DS1302_CLK = 0;
  }
}

unsigned char DS1302_shift_in()
{
  unsigned char i, data_=0;
  P15_OUT_DIS; // SCREEN_DAT
  P15_IN_EN;
  for (i = 0; i < 8; i++)
  {
    //�½��ض����� ��DS1302_shift_out��������֮�����϶�
    if (DS1302_DAT==1)
      data_ |= 1 << i;
    
    DS1302_CLK = 1;
    DS1302_CLK = 0;
  }
  return data_;
}

void DS1302_write(unsigned char address, unsigned char data_)
{
  P15_IN_DIS; // SCREEN_DAT
  P15_OUT_EN;
  DS1302_DAT = 0;
  
  DS1302_RST = 0;
  DS1302_RST = 1;
  DS1302_shift_out(address);
  DS1302_shift_out(data_);
  DS1302_RST = 0;
  
}

unsigned char DS1302_read(unsigned char address)
{
  unsigned char data_;

  DS1302_DAT = 0;
  DS1302_RST = 0;
  DS1302_RST = 1;
  DS1302_shift_out(address);
  data_ = DS1302_shift_in();
  DS1302_RST = 0;
  return data_;
}

void DS1302_init()
{
  if ((DS1302_read(0x81) >> 7) & 1 == 1)
  {
    DS1302_write(0x8E, 0x00); // д����off
    DS1302_write(0x80, DS1302_read(0x81) & 0x7F); // �������� // bug:ÿ��������֮�󣬺�������㡣������1s�ڲ���reset�Ļ���ʱ��Ῠס����
  }
  DS1302_write(0x8E, 0x80); // д����on
}


void read_now_time()
{
  unsigned char time_data;

  // ��һ�Ѷ���һ��Ҫ����������Ȼ��ӵ�15������
  time_data = DS1302_read(0x85); // hour
  now_time[0] = (time_data >> 4 & 7) * 10 + (time_data & 15);

  time_data = DS1302_read(0x83); // min
  now_time[1] = (time_data >> 4 & 7) * 10 + (time_data & 15);
  
  now_time[2] = DS1302_read(0x8B); // ����
}

void set_now_time()
{
  DS1302_write(0x84, (now_time[0] / 10 << 4) + now_time[0] % 10); // hour
  DS1302_write(0x82, (now_time[1] / 10 << 4) + now_time[1] % 10); // min
  DS1302_write(0x8A, now_time[2]); // week
}


// screen
void SCREEN_shift(unsigned char data_)
{
  char i;
  SCREEN_CLK = 0;
  for (i = 7; i >= 0; i--)
  {
    SCREEN_DAT = (data_ >> i) & 1;
    SCREEN_CLK = 1;
    SCREEN_CLK = 0;
  }
}

void SCREEN_write_cmd(unsigned char cmd)
{
  SCREEN_DC = 0;
  SCREEN_shift(cmd);
}

void SCREEN_write_data(unsigned char data_)
{
  SCREEN_DC = 1;
  SCREEN_shift(data_);
}

void SCREEN_write_data_0x00()
{
  SCREEN_DC = 1;
  SCREEN_CLK = 0;
  SCREEN_DAT = 0;

  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
}

void SCREEN_write_data_0xFF()
{
  SCREEN_DC = 1;
  SCREEN_CLK = 0;
  SCREEN_DAT = 1;

  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
  SCREEN_CLK = 1;
  SCREEN_CLK = 0;
}



void SCREEN_clear()
{
  unsigned char x,y;
	high_speed();
	INT_EN_flag = TMR1_C0>>7;
	TMR1_DIS;
  for (y = 0; y < 8; y++)
  {
    SCREEN_write_cmd(0xB0 + y);//��
    SCREEN_write_cmd(0x00);//��ʼx
    SCREEN_write_cmd(0x10);//��ʼx
    for (x = 0; x < 128; x++)
    {
      SCREEN_write_data_0x00();
    }
  }
  if(INT_EN_flag)
  {
    TMR1_EN;
  }
	low_speed();
}

void SCREEN_init()
{
  // ������λ ����ʾ �ڲ���ѹ����*3 �Աȶ� ����page1 ���µߵ�
  const unsigned char code init_cmds[8] = {0xE2, 0xAF, 0x2C, 0x2E, 0x2F, 0x24, 0x40, 0xC8};
  unsigned char i;
  SCREEN_DC = 0; // cmd
  for (i = 0; i < 8; i++)
  {
    SCREEN_write_cmd(init_cmds[i]);
    delay(1);
  }
  SCREEN_clear();
}

void print_line(unsigned char start_x, unsigned char start_y, char words[])
{
  unsigned char x, character;
  SCREEN_write_cmd(0xB0 + start_y); //��
  SCREEN_write_cmd(0x00 + (start_x & 0xF)); //��ʼx ��4λ
  SCREEN_write_cmd(0x10 + (start_x >> 4)); //��ʼx ��4λ

  character = 0; // �����words��β��\0 (������character��ʱ��Ҫ-1)
  while (words[character++])
  {
    for (x = 0; x < 5; x++)
      SCREEN_write_data(font[(words[character - 1] - ' ') * 5 + x]);
    SCREEN_write_data_0x00();
  }
}

void print_var(unsigned char start_x, unsigned char start_y, unsigned char num, unsigned char len)
{
  unsigned char x;
  SCREEN_write_cmd(0xB0 + start_y); //��
  SCREEN_write_cmd(0x00 + (start_x & 0xF)); //��ʼx ��4λ
  SCREEN_write_cmd(0x10 + (start_x >> 4)); //��ʼx ��4λ
  
  if(len==3)
  {
    for (x = 0; x < 5; x++)
      SCREEN_write_data(font[('0' + num/100 - ' ') * 5 + x]);
    SCREEN_write_data_0x00();
  }
  if(len>=2)
  {
    for (x = 0; x < 5; x++)
      SCREEN_write_data(font[('0' + num/10%10 - ' ') * 5 + x]);
    SCREEN_write_data_0x00();
  }
  if(len>=1)
  {
    for (x = 0; x < 5; x++)
      SCREEN_write_data(font[('0' + num%10 - ' ') * 5 + x]);
    SCREEN_write_data_0x00();
  }
}


void print_big_num(unsigned char start_x, unsigned char start_y,unsigned char num)
{
  unsigned char x, y;
  for (y = 0; y < 5; y++)
  {
    SCREEN_write_cmd(0xB0 + start_y + y); //��
    SCREEN_write_cmd(0x00 + (start_x & 0xF)); //��ʼx ��4λ
    SCREEN_write_cmd(0x10 + (start_x >> 4)); //��ʼx ��4λ
    
    if(num==10)
      for (x = 0; x < 24; x++)
        SCREEN_write_data_0x00();
    else
      for (x = 0; x < 24; x++)
        SCREEN_write_data(big_num_font[num*120 + y*24+x]);
   }
}

void print_time(unsigned char start_x, unsigned char start_y,unsigned char nums[])
{
  unsigned char x,digit;
	
  last_blink = 1 - last_blink;
  if (edit == 1 && last_blink==0 && btn_state!=4)
  {
    if (hot_num == 0)
    {
      display_num_data[0] = 10;
      display_num_data[1] = 10;
    }
    else
    {
      display_num_data[2] = 10;
      display_num_data[3] = 10;
    }
  }
  
  if(display_num_data[0] == 0)
    display_num_data[0] = 10;
  
  for(digit=0;digit<4;digit++)
  {
    print_big_num(start_x+num_start_offset[digit], start_y,nums[digit]);
  }
  
  start_x += num_start_offset[4];
  SCREEN_write_cmd(0xB1 + start_y); //��
  SCREEN_write_cmd(0x00 + (start_x & 0xF)); //��ʼx ��4λ
  SCREEN_write_cmd(0x10 + (start_x >> 4)); //��ʼx ��4λ
  for (x = 0; x < 4; x++)
    SCREEN_write_data(0x7E);
  
  SCREEN_write_cmd(0xB3 + start_y); //��
  SCREEN_write_cmd(0x00 + (start_x & 0xF)); //��ʼx ��4λ
  SCREEN_write_cmd(0x10 + (start_x >> 4)); //��ʼx ��4λ
  for (x = 0; x < 4; x++)
    SCREEN_write_data(0x7E);
}

void update_display_num_data()
{
  // ������ʾ��ʱ��

  if(time_12 && now_time[0]>12)
  {
    display_num_data[0] = (now_time[0] - 12) / 10;
    display_num_data[1] = (now_time[0] - 12) % 10;
  }
  else
  {
    display_num_data[0] = now_time[0] / 10;
    display_num_data[1] = now_time[0] % 10;
  }

  display_num_data[2] = now_time[1] / 10;
  display_num_data[3] = now_time[1] % 10;
}

void draw_qr()
{
  unsigned char line, x;

  for (line = 0; line < 8; line++)
  {
    SCREEN_write_cmd(0xB0 +line); //��
    SCREEN_write_cmd(0x00); //��ʼx ��4λ
    SCREEN_write_cmd(0x12); //��ʼx ��4λ
    
    for (x = 0; x < 58; x++)
    {
      SCREEN_write_data(qr[line*58+x]);
    }
  }
}

void draw_nts(unsigned char start_x, unsigned char start_y)
{
  unsigned char line, x;

  for (line = 0; line < 4; line++)
  {
    SCREEN_write_cmd(0xB0 + start_y +line); //��
    SCREEN_write_cmd(0x00 + (start_x & 0xF)); //��ʼx ��4λ
    SCREEN_write_cmd(0x10 + (start_x >> 4)); //��ʼx ��4λ
    
    for (x = 0; x < 45; x++)
    {
      SCREEN_write_data(nts[line*45+x]);
    }
  }
}

void draw_class(unsigned char day)
{
  // day ���㿪ʼ
  unsigned char line, x, lesson;
  unsigned int temp;

  for (line = 0; line < 2; line++)
  {
    SCREEN_write_cmd(0xB2 +line); //��
    SCREEN_write_cmd(0x00); //��ʼx ��4λ
    SCREEN_write_cmd(0x10); //��ʼx ��4λ
    
    for(lesson = 0; lesson<9; lesson++)
    {
      temp = lesson_table[lesson+day*9]*28+line*14; 
      if(lesson==5)
      {
        SCREEN_write_data_0x00();
        SCREEN_write_data_0x00();
        SCREEN_write_data_0x00();
      }
      for (x = 0; x <14; x++)
      {
        SCREEN_write_data(chinese_font[temp+x]);
      }
    }
  }
}

void print_next_time(unsigned char start_x, unsigned char start_y)
{
  unsigned char i;
  unsigned int now_time_min;
  now_time_min = now_time[0]*60+now_time[1];
  for(i=0;i<23;i++)
  {
    if(now_time_min<time_table[i])
      break;
  }
  if(time_table[i]/60>=10)
    print_var(start_x, start_y, time_table[i]/60,2);
  else
  {
    print_line(start_x, start_y, " ");
    print_var(start_x+5, start_y, time_table[i]/60,1);
  }
  
  print_line(start_x+12, start_y, ":");
  print_var(start_x+17, start_y, time_table[i]%60,2);

}

void refresh_screen()
{
	INT_EN_flag = TMR1_C0>>7;
	TMR1_DIS;
	high_speed();
	
	if(mode==0)
	{
		read_now_time();
		update_display_num_data();
    
    if(now_time[0]>12)
      print_line(2,0, "PM");
    else
      print_line(2,0, "AM");
    
    print_next_time(98, 0);

		print_time(2,2,display_num_data);
    BG = 0;
	}
  else if (mode==1)
	{
    read_now_time();
    
    last_blink = 1-last_blink;
    if (edit == 1 && last_blink==0)
    {
      print_line(2,0, "          ");
    }
    else
    {
      print_line(2,0, week_name[now_time[2]-1]);
    }
    
    // 6����֮����ʾ�ڶ���Ŀα�
    if(now_time[0] > 17)
    {
      print_line(70,0, "Tomorrow:");
      draw_class(now_time[2] % 7);
    }
    else
    {
      print_line(70,0, "Today:");
      draw_class(now_time[2] - 1);
    }
    
    
    draw_nts(0x50, 4);
    BG = 0;
  }  
  else
  {
		draw_qr();
    BG = 1;
  }
	
	if(INT_EN_flag)
    TMR1_EN;
	low_speed();
}

void btn()
{
  // ��ȡ������btn_state״̬
  // btn_state 0-�� 1-btn1�� 2-btn1�� 3-btn2�� 4-btn2�� 5-ͬʱ�� 6-ͬʱ����

  if (BTN_1 == 0 && BTN_2 == 0)
  {
    if (btn1_press_time) //btn1 �̰�
      btn_state = 1;
    else if (btn2_press_time) //btn2 �̰�
      btn_state = 3;
    lift = 1;
    btn1_press_time = 0;
    btn2_press_time = 0;
  }
  else
  {
    TMR1_CLR;
    if (lift == 1) // ��û������
    {
      if (BTN_1 == 1 && BTN_2 == 0)
        btn1_press_time += 1;
      else
        btn1_press_time = 0;
      
      if (BTN_2 == 1 && BTN_1 == 0)
        btn2_press_time += 1;
      else
        btn2_press_time = 0;
      
      //if (BTN_1 == 1 && BTN_2 == 1)
      //  btn_both_press_time += 1;
    }
    
    if (btn1_press_time > LONG_PRESS_TIME)
    {
      // btn1 ����
      btn_state = 2;
      btn1_press_time = 0;
      lift = 0;
    }
    if (btn2_press_time > LONG_PRESS_TIME)
    {
      // btn2 ����
      btn_state = 4;
      btn2_press_time = 0;
      lift = 0;
    }
  }
}


void btn_process()
{
  if (btn_state == 1 && ! edit) //btn1 ��
  {
    delay(1);
    mode = (mode + 1) % MAX_MODE;
    SCREEN_clear();
		refresh_screen_now = 1;
    btn_state = 0;
   
    return;
  }
  
  if (btn_state == 2) //btn1 ��
  {
    if (mode < 2)
    {
			refresh_screen_now = 1;
      if (edit==1)
      {
        edit = 0;
				TMR0_DIS;
        DS1302_write(0x8E, 0x80);
      }
      else
      {
        edit = 1;
				refresh_count = 0x2F;
				TMR0_EN;
        DS1302_write(0x8E, 0x00);
      }
      btn_state = 0;
      return;
    }
  }
  
  if(mode==0)
  {
    max_[0] = 24;
    max_[1] = 60; 
    if(edit==1)
    {
      if (btn_state == 1) //btn1 ��
      {
        hot_num = 1 - hot_num;
				refresh_screen_now = 1;
        btn_state = 0;
        return;
      }
      if (btn_state == 3) //btn2 ��
      {
        now_time[hot_num] = (now_time[hot_num] + 1) % max_[hot_num];
        set_now_time();
				refresh_screen_now = 1;
        btn_state = 0;
        return;
      }
      // btn2 ��д���ж�������
    }
    else
    {
      if (btn_state == 3) //btn2 ��
      {
        time_12 = 1 - time_12;
        DS1302_write(0xD0, time_12);
        refresh_screen_now = 1;
        btn_state = 0;
        return;
      }
    }
  }
  
  if(mode==1)
  {
    if(edit==1)
    {
      if (btn_state == 3) //btn2 ��
      {
        now_time[2] = now_time[2] % 7 + 1;
        set_now_time();
				refresh_screen_now = 1;
        btn_state = 0;
        return;
      }
    }
  }

  
  if (btn_state==2 && BTN_1 == 0)
  {
    btn_state = 0;
    return;
  }
  if (btn_state==4 && BTN_2 == 0)
  {
    btn_state = 0;
    return;
  }
  if (btn_state==3)
  {
    btn_state = 0;
    return;
  }
}

void INT_init()
{
	/*
	16 λ TMR0 ʹ�ܺ�����ۼӼ������������� TMR0 ֵ�����ڼĴ��� TMRn_CY ֵ���ʱ������ 1 ��
  ��������� TMRn ���Զ����������ۼӼ���
	*/
	GIE_EN; // ���ж�ʹ��
  
  // ��ʱ��0 ������һ
	TMR0_LRC; // TMR0ʱ��Դѡ��
	TMR0_CYH = 0x14;
  TMR0_CYL = 0x00;
	
	TMR0_DIV8_DIS; 	  //�˷�Ƶ��ֹ
	TMR0_PST_1;	      //���ƵΪ1

	TMR0_INT_EN; // ��������һ���жϣ��ж�2��
	//TMR0_EN; // ����ʹ��TMR0��ʼ�ۼ�
  
  // ��ʱ��1 �Զ�power saving
	TMR1_LRC; // TMR1ʱ��Դѡ��LRC
	TMR1_CYH = 0x30; // ��������0x40
  TMR1_CYL = 0x00;
	
	TMR1_DIV8_EN; 	  //�˷�Ƶ��
	TMR1_PST_1;	      //���ƵΪ1

	TMR1_INT_EN; // ��������һ���жϣ��ж�2��
	TMR1_EN; // ����ʹ��TMR1��ʼ�ۼ�
  
  INT2_EN; // timer
}

void timer_INT() interrupt 7 // TMR01��Ӧ��������Ŷ���2���жϱ����7 datasheetP44
{
  if(TMR0_IF)
	{
    TMR0_IF = 0;

    if(edit==1 && btn_state==4) // btn2 ��
    {
      refresh_screen_now = 1;
      if(mode==0)
        now_time[hot_num] = (now_time[hot_num] + 1) % max_[hot_num];
      else if (mode==1)
        now_time[2] = now_time[2] % 7 + 1;
      set_now_time();
    }
	}
  if(TMR1_IF)
	{
    // auto_power saving
    TMR1_IF = 0;
    TMR1_DIS;
    SCREEN_clear();

    
    mode = 0;
    edit = 0;
    refresh_screen_now = 1;
  }
}

void main()
{
  SYSCK_DIV4;
  P07_OUT_EN; // SCREEN_CLK
  P10_OUT_EN; // SCREEN_DAT
  P05_OUT_EN; // SCREEN_RST
  P06_OUT_EN; // SCREEN_DC
  P11_OUT_EN; // BG LED

  P14_OUT_EN; // DS1302_CLK
  P15_OUT_EN; // DS1302_DAT
  P20_OUT_EN; // DS1302_RST
  
  P03_IN_EN; // BTN_1
  P04_IN_EN; // BTN_2
  P03_PD_EN;
  P04_PD_EN;
  
  SCREEN_RST = 0;
  delay(1);
  SCREEN_RST = 1;
  BG = 0;

  SCREEN_init();
  DS1302_init();

  DS1302_write(0x8E, 0x00); // д����off
  DS1302_write(0x90, 0xA5); // ���
  DS1302_write(0x8E, 0x80); // д����on
  time_12 = DS1302_read(0xD1)%2;
  
  INT_init();

  SYSCK_DIV1;
  low_speed();
  while(1)
  {
		if(refresh_screen_now)
		{
			refresh_screen_now = 0;
			refresh_screen();
		}		
		btn();
		

		if(btn_state)
		{
			btn_process();
			TMR1_EN;      
		}


		if(refresh_count--==0) 
		{
			refresh_screen_now = 1;
			
			if(mode<=2&&edit)
				refresh_count = 0x20;
			else
				refresh_count = 0xFFF;
		}

  }
}
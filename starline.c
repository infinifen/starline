#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "starline.h"

#define ARR(...) __VA_ARGS__
#define RAWCMD(FN_NAME, CMD_ARRAY) int FN_NAME (char* buf, int max_bytes)\
  {\
    char cmd[] = CMD_ARRAY;\
    int len = sizeof(cmd) / sizeof(char);       \
    if(max_bytes < len) return -len;\
    memcpy(buf, cmd, len);          \
    return len;\
  }

#define ARGSUFFIXCMD(FN_NAME, CMD_ARRAY, PARAM_TYPE, PARAM_NAME) int FN_NAME (char* buf, int max_bytes, PARAM_TYPE PARAM_NAME) \
  {                                                                     \
    char cmd[] = CMD_ARRAY;                                             \
    int len_fixed = sizeof(cmd) / sizeof(char);                               \
    if(max_bytes < len_fixed + 1) return -len_fixed;                                    \
    memcpy(buf, cmd, len_fixed); \
    buf[len_fixed] = PARAM_NAME;                                                           \
    return len_fixed + 1;                                                         \
  }



RAWCMD(starline_select_thermal, ARR({0x1b, 0x2b, 0x41, 0x00}));
RAWCMD(starline_select_slip, ARR({0x1b, 0x2b, 0x41, 0x00}));
ARGSUFFIXCMD(starline_set_charset, ARR({0x1b, 0x52}), uint8_t, charset);
ARGSUFFIXCMD(starline_set_zero_style, ARR({0x1b, 0x2f}), bool, slashed);
ARGSUFFIXCMD(starline_set_character_spacing, ARR({0x1b, 0x20}), uint8_t, spacing);

// This function *does not* do character code translation for CODE128/CODE93. If I decide to do it, it will be a separate function. This one accepts raw barcode data that goes to the printer.
int starline_print_barcode(char* buf, int max_bytes, enum starline_barcode_type bc_type, enum starline_barcode_print_option bc_print_opt, uint8_t bc_mode, uint8_t bc_height, char* data, int data_len) {
  // Calculate needed space (ESC + b + n1-n4 + data + RS) -> 7 bytes + amount of data
  int msg_len = 7 + data_len;
  if (max_bytes < msg_len) return -msg_len;

  buf[0] = 0x1b;
  buf[1] = 0x62;
  buf[2] = bc_type;
  buf[3] = bc_print_opt + 1;
  buf[4] = bc_mode;
  buf[5] = bc_height;
  memcpy(&buf[6], data, data_len);
  buf[msg_len - 1] = 0x1e;
  return msg_len;
}

RAWCMD(starline_set_pitch_12, ARR({0x1b, 0x4d}));
RAWCMD(starline_set_halfdot, ARR({0x1b, 0x4d}));

RAWCMD(starline_set_pitch_14, ARR({0x1b, 0x70}));

RAWCMD(starline_set_pitch_15, ARR({0x1b, 0x50}));
RAWCMD(starline_set_doublepulse, ARR({0x1b, 0x50}));

RAWCMD(starline_set_pitch_16, ARR({0x1b, 0x3a}));
RAWCMD(starline_set_triplepulse, ARR({0x1b, 0x3a}));

RAWCMD(starline_set_doublewidth, ARR({0x0e}));
RAWCMD(starline_reset_doublewidth, ARR({0x14}));
ARGSUFFIXCMD(starline_set_width, ARR({0x1b, 0x57}), uint8_t, width);

RAWCMD(starline_set_doubleheight, ARR({0x1b, 0x0e}));
RAWCMD(starline_reset_doubleheight, ARR({0x1b, 0x14}));
ARGSUFFIXCMD(starline_set_height, ARR({0x1b, 0x68}), uint8_t, height);


int starline_set_width_height(char* buf, int max_bytes, uint8_t height, uint8_t width) {
  if (max_bytes < 4) return -4;
  buf[0] = 0x1b;
  buf[1] = 0x69;
  buf[2] = height;
  buf[3] = width;
  return 4;
}

ARGSUFFIXCMD(starline_set_underline, ARR({0x1b, 0x2d}), bool, underline);
ARGSUFFIXCMD(starline_set_overline, ARR({0x1b, 0x2d}), bool, overline);

RAWCMD(starline_set_highlight, ARR({0x1b, 0x34}));
RAWCMD(starline_reset_highlight, ARR({0x1b, 0x35}));

RAWCMD(starline_set_invert, ARR({0x0f}));
RAWCMD(starline_reset_invert, ARR({0x12}));

RAWCMD(starline_set_emphasis, ARR({0x1b, 0x45}));
RAWCMD(starline_reset_emphasis, ARR({0x1b, 0x46}));

ARGSUFFIXCMD(starline_set_bidirectional, ARR({0x1b, 0x55}), bool, bidi);

ARGSUFFIXCMD(starline_set_page_length_lines, ARR({0x1b, 0x43}), uint8_t, lines);
ARGSUFFIXCMD(starline_set_page_length_inches, ARR({0x1b, 0x43, 0x00}), uint8_t, inches);

ARGSUFFIXCMD(starline_set_bottom_margin, ARR({0x1b, 0x4e}), uint8_t, lines);
RAWCMD(starline_cancel_bottom_margin, ARR({0x1b, 0x4f}));

ARGSUFFIXCMD(starline_set_left_margin, ARR({0x1b, 0x6c}), uint8_t, column);
ARGSUFFIXCMD(starline_set_right_margin, ARR({0x1b, 0x51}), uint8_t, column);

ARGSUFFIXCMD(starline_feed_lines, ARR({0x1b, 0x61}), uint8_t, lines);

ARGSUFFIXCMD(starline_define_n_72in_line_spacing, ARR({0x1b, 0x41}), uint8_t, line_spacing);
RAWCMD(starline_set_n_72in_line_spacing, ARR({0x1b, 0x32}));

RAWCMD(starline_set_3mm_line_spacing, ARR({0x1b, 0x7a, 0x30}));
RAWCMD(starline_set_4mm_line_spacing, ARR({0x1b, 0x7a, 0x31}));

RAWCMD(starline_set_12in_line_spacing, ARR({0x1b, 0x7a, 0x30}));
RAWCMD(starline_set_6in_line_spacing, ARR({0x1b, 0x7a, 0x31}));
RAWCMD(starline_set_8in_line_spacing, ARR({0x1b, 0x30}));
RAWCMD(starline_set_7_72in_line_spacing, ARR({0x1b, 0x31}));

ARGSUFFIXCMD(starline_n_4mm_feed, ARR({0x1b, 0x4a}), uint8_t, n);
ARGSUFFIXCMD(starline_n_72in_feed, ARR({0x1b, 0x4a}), uint8_t, n);

ARGSUFFIXCMD(starline_n_4mm_backfeed, ARR({0x1b, 0x6a}), uint8_t, n);
ARGSUFFIXCMD(starline_n_72in_backfeed, ARR({0x1b, 0x6a}), uint8_t, n);

ARGSUFFIXCMD(starline_set_n_216in_line_spacing, ARR({0x1b, 0x33}), uint8_t, n);
ARGSUFFIXCMD(starline_set_n_144in_line_spacing, ARR({0x1b, 0x79}), uint8_t, n);

ARGSUFFIXCMD(starline_n_8mm_feed, ARR({0x1b, 0x49}), uint8_t, n);

int compare_u8 (const void *a, const void *b) {
  const uint8_t *da = (const uint8_t *) a;
  const uint8_t *db = (const uint8_t *) b;

  return (*da > *db) - (*da < *db);
}

int starline_set_vertical_tabstops(char* buf, int max_bytes, uint8_t* stops, uint8_t n_stops) {
  int msg_len = 3 + n_stops;
  if (max_bytes < msg_len) return -msg_len;

  qsort(stops, n_stops, sizeof(uint8_t), compare_u8);
  buf[0] = 0x1b;
  buf[1] = 0x42;
  memcpy(&buf[2], stops, n_stops);
  buf[msg_len - 1] = 0x00;
  return msg_len;
}

int starline_set_horizontal_tabstops(char* buf, int max_bytes, uint8_t* stops, uint8_t n_stops) {
  int msg_len = 3 + n_stops;
  if (max_bytes < msg_len) return -msg_len;

  qsort(stops, n_stops, sizeof(uint8_t), compare_u8);
  buf[0] = 0x1b;
  buf[1] = 0x44;
  memcpy(&buf[2], stops, n_stops);
  buf[msg_len - 1] = 0x00;
  return msg_len;
}

int starline_normal_density_graphics(char* buf, int max_bytes, uint8_t* img_data, uint8_t img_data_len) {
  int msg_len = 4 + img_data_len;
  if (max_bytes < msg_len) return -msg_len;

  buf[0] = 0x1b;
  buf[1] = 0x4b;
  buf[2] = img_data_len;
  buf[3] = 0x00;
  memcpy(&buf[4], img_data, img_data_len);
  return msg_len;
}

int starline_high_density_graphics(char* buf, int max_bytes, uint8_t* img_data, int img_data_len) {
  int msg_len = 4 + img_data_len;
  if (max_bytes < msg_len) return -msg_len;

  buf[0] = 0x1b;
  buf[1] = 0x4c;
  buf[2] = img_data_len % 256;
  buf[3] = img_data_len / 256;
  memcpy(&buf[4], img_data, img_data_len);
  return msg_len;
}

int starline_fine_density_graphics_k(char* buf, int max_bytes, uint8_t* img_data, uint8_t img_data_width) {
  int msg_len = 4 + (24 * img_data_width);
  if (max_bytes < msg_len) return -msg_len;

  buf[0] = 0x1b;
  buf[1] = 0x6b;
  buf[2] = img_data_width;
  buf[3] = 0x00;
  memcpy(&buf[4], img_data, 24 * img_data_width);
  return msg_len;
}

// documentation is very unclear on what the actual data length is; the 3 * is guesswork
int starline_fine_density_graphics_X(char* buf, int max_bytes, uint8_t* img_data, uint8_t img_data_len) {
  int msg_len = 4 + 3 * img_data_len;
  if (max_bytes < msg_len) return -msg_len;

  buf[0] = 0x1b;
  buf[1] = 0x58;
  buf[2] = img_data_len % 256;
  buf[3] = img_data_len / 256;
  memcpy(&buf[4], img_data, 3 * img_data_len);
  return msg_len;
}


//todo: function that accepts the actual 12x24 graphics and shifts them accordingly
int starline_define_thermal_download_character_rawgfx(char* buf, int max_bytes, uint8_t charcode, uint8_t* gfx) {
  // message length = ESC + & + 1 + 1 + n (5 bytes) + 48 data bytes = 53 bytes
  if (max_bytes < 53) return -53;

  buf[0] = 0x1b;
  buf[1] = 0x26;
  buf[2] = 0x01;
  buf[3] = 0x01;
  buf[4] = charcode;
  memcpy(&buf[5], gfx, 48);

  return 53;
}

// does not support defining multiple chars at once!
// gfx needs to be 7 bytes
int starline_define_slip_download_character_7x9(char* buf, int max_bytes, uint8_t charcode, enum starline_slip_character_alignment align, uint8_t* gfx) {
  // message length = ESC + & + 0 + n1 + n2 + 8 data bytes (m0-m7) = 13 bytes
  if (max_bytes < 13) return -13;

  buf[0] = 0x1b;
  buf[1] = 0x26;
  buf[2] = 0x00;
  buf[3] = charcode;
  buf[4] = charcode;

  memcpy(&buf[5], gfx, 7);
  return 13;
}

// does not support defining multiple chars at once!
// gfx needs to be 5 bytes
int starline_define_slip_download_character_5x9(char* buf, int max_bytes, uint8_t charcode, enum starline_slip_character_alignment align, uint8_t* gfx) {
  // message length = ESC + & + 0 + n1 + n2 + 5 data bytes (m0-m7) = 10 bytes
  if (max_bytes < 10) return -10;

  buf[0] = 0x1b;
  buf[1] = 0x26;
  buf[2] = 0x00;
  buf[3] = charcode;
  buf[4] = charcode;

  memcpy(&buf[5], gfx, 5);
  return 10;
}

ARGSUFFIXCMD(starline_delete_thermal_download_character, ARR({0x1b, 0x26, 0x01, 0x00}), uint8_t, charcode);
ARGSUFFIXCMD(starline_set_download_characters_enabled, ARR({0x1b, 0x25}), bool, enabled);

ARGSUFFIXCMD(starline_cut, ARR({0x1b, 0x64}), bool, partial);

int starline_slip_sensor_set(char* buf, int max_bytes, bool tof, bool bof) {
  if (max_bytes < 3) return -3;

  buf[0] = 0x1b;
  buf[1] = 0x0f;
  buf[2] = (tof ? 0 : 2) + (bof ? 0 : 1);
  return 3;
}

ARGSUFFIXCMD(starline_slip_function, ARR({0x1b, 0x0c}), enum starline_slip_function_option, option);

int starline_set_slip_eject(char* buf, int max_bytes, enum starline_slip_eject_mode mode, uint8_t length) {
  if (max_bytes < 4) return -4;
  buf[0] = 0x1b;
  buf[1] = 0x0b;
  buf[2] = mode;
  buf[3] = length;
  return 4;
}

int starline_set_clamp_wait_time(char* buf, int max_bytes, uint8_t time) {
  if (max_bytes < 6) return -6;
  buf[0] = 0x1b;
  buf[1] = 0x19;
  buf[2] = time;
  buf[3] = 0x00;
  buf[4] = 0x0a;
  buf[5] = 0x00;
  return 6;
}

RAWCMD(starline_enter_page_mode, ARR({0x1b, 0x6e}));
RAWCMD(starline_select_line_mode, ARR({0x1b, 0x21}));

int starline_set_print_area(char* buf, int max_bytes, int x, int y, int dx, int dy) {
  if (max_bytes < 10) return -10;
  buf[0] = 0x1b;
  buf[1] = 0x2a;
  buf[2] = x % 256;
  buf[3] = x / 256;
  buf[4] = y % 256;
  buf[5] = y / 256;
  buf[6] = dx % 256;
  buf[7] = dx / 256;
  buf[8] = dy % 256;
  buf[9] = dy / 256;
  return 10;
}

ARGSUFFIXCMD(starline_set_rotation, ARR({0x1b, 0x54}), enum starline_print_rotation, rotation);


RAWCMD(starline_print_page, ARR({0x0c}));
RAWCMD(starline_cancel_and_init, ARR({0x18}));
RAWCMD(starline_deselect, ARR({0x13}));
RAWCMD(starline_select, ARR({0x11}));
RAWCMD(starline_beep, ARR({0x1e}));
RAWCMD(starline_reset_and_test, ARR({0x1b, 0x3f, 0x0a, 0x00}));

#include <stdbool.h>
#include <stdint.h>

// All functions accept a char* buf that will be written into and a max_bytes argument.
// If the message to be written exceeds max_bytes in length, then the function will
// return without writing.

// Return values:
// >0 - success, return value is number of bytes written
// <=0 - failure, return value is number of bytes the message needs

int starline_select_thermal(char* buf, int max_bytes);
int starline_select_slip(char* buf, int max_bytes);

int starline_set_charset(char* buf, int max_bytes, uint8_t charset);
int starline_set_zero_style(char* buf, int max_bytes, bool slashed);
int starline_set_character_spacing(char* buf, int max_bytes, uint8_t spacing);

enum starline_barcode_type {
  BARCODE_UPC_E = 0,
  BARCODE_UPC_A = 1,
  BARCODE_EAN_8 = 2,
  BARCODE_EAN_13 = 3,
  BARCODE_CODE39 = 4,
  BARCODE_ITF = 5,
  BARCODE_CODE128 = 6,
  BARCODE_CODE93 = 7,
  BARCODE_NW_7 = 8
};

// shifted to 0-3 from the original 1-4 control codes!!!!
enum starline_barcode_print_option {
  BARCODE_OPT_DEFAULT = 0x0,
  BARCODE_OPT_PRINT_BELOW = 0x1,
  BARCODE_OPT_NOLF = 0x2,
};

// refer to programmer's manual for mode values cba to model them here
int starline_print_barcode(char* buf, int max_bytes, enum starline_barcode_type bc_type, enum starline_barcode_print_option bc_print_opt, uint8_t bc_mode, uint8_t bc_height, char* data, int data_len);

// these two are the same
int starline_set_pitch_12(char* buf, int max_bytes);
int starline_set_halfdot(char* buf, int max_bytes);

int starline_set_pitch_14(char* buf, int max_bytes);

// these two are the same
int starline_set_pitch_15(char* buf, int max_bytes);
int starline_set_doublepulse(char* buf, int max_bytes);

int starline_set_pitch_16(char* buf, int max_bytes);
int starline_set_triplepulse(char* buf, int max_bytes);

int starline_set_doublewidth(char* buf, int max_bytes);
int starline_reset_width(char* buf, int max_bytes);
int starline_set_width(char* buf, int max_bytes, uint8_t width);

int starline_set_doubleheight(char* buf, int max_bytes);
int starline_reset_height(char* buf, int max_bytes);
int starline_set_height(char* buf, uint8_t height, int max_bytes);

int starline_set_width_height(char* buf, int max_bytes, uint8_t height, uint8_t width);

int starline_set_underline(char* buf, int max_bytes, bool underline);
int starline_set_overline(char* buf, int max_bytes, bool overline);

int starline_set_highlight(char* buf, int max_bytes);
int starline_reset_highlight(char* buf, int max_bytes);

int starline_set_invert(char* buf, int max_bytes);
int starline_reset_invert(char* buf, int max_bytes);


int starline_set_emphasis(char* buf, int max_bytes);
int starline_reset_emphasis(char* buf, int max_bytes);

int starline_set_bidirectional(char* buf, int max_bytes, char bidi);

int starline_set_page_length_lines(char* buf, int max_bytes, uint8_t lines);
int starline_set_page_length_inches(char* buf, int max_bytes, uint8_t inches);

int starline_set_bottom_margin(char* buf, int max_bytes, uint8_t lines);
int starline_cancel_bottom_margin(char* buf, int max_bytes);

int starline_set_left_margin(char* buf, int max_bytes, uint8_t column);
int starline_set_right_margin(char* buf, int max_bytes, uint8_t column);

int starline_feed_lines(char* buf, int max_bytes, uint8_t lines);

int starline_define_n_72in_line_spacing(char* buf, int max_bytes, uint8_t line_spacing);
int starline_set_n_72in_line_spacing(char* buf, int max_bytes);

int starline_set_3mm_line_spacing(char* buf, int max_bytes);
int starline_set_4mm_line_spacing(char* buf, int max_bytes);

// first two are the same as 3mm/4mm line spacing
int starline_set_12in_line_spacing(char* buf, int max_bytes);
int starline_set_6in_line_spacing(char* buf, int max_bytes);
int starline_set_8in_line_spacing(char* buf, int max_bytes);
int starline_set_7_72in_line_spacing(char* buf, int max_bytes);

// these are the same
int starline_n_4mm_feed(char* buf, int max_bytes, uint8_t n);
int starline_n_72in_feed(char* buf, int max_bytes, uint8_t n);

// these are the same
int starline_n_4mm_backfeed(char* buf, int max_bytes, uint8_t n);
int starline_n_72in_backfeed(char* buf, int max_bytes, uint8_t n);

int starline_set_n_216in_line_spacing(char* buf, int max_bytes, uint8_t n);
int starline_set_n_144in_line_spacing(char* buf, int max_bytes, uint8_t n);

int starline_n_8mm_feed(char* buf, int max_bytes, uint8_t n);

int starline_set_vertical_tabstops(char* buf, int max_bytes, uint8_t* stops, uint8_t n_stops);
int starline_set_horizontal_tabstops(char* buf, int max_bytes, uint8_t* stops, uint8_t n_stops);

int starline_normal_density_graphics(char* buf, int max_bytes, uint8_t* img_data, uint8_t img_data_len);
int starline_high_density_graphics(char* buf, int max_bytes, uint8_t* img_data, int img_data_len);

int starline_fine_density_graphics_k(char* buf, int max_bytes, uint8_t* img_data, uint8_t img_data_width);
int starline_fine_density_graphics_X(char* buf, int max_bytes, uint8_t* img_data, uint8_t img_data_len);

//todo: download character messages

//todo: peripheral device control

int starline_cut(char* buf, int max_bytes, bool partial);

int starline_slip_sensor_set(char* buf, int max_bytes, bool tof, bool bof);

enum starline_slip_function_option {
  STARLINE_SLIP_CLAMP = 0,
  STARLINE_SLIP_RELEASE = 1,
  STARLINE_SLIP_RELEASEWAIT = 2,
  STARLINE_SLIP_BACKFEED = 3,
  STARLINE_SLIP_FORWARDFEED = 4,
  STARLINE_SLIP_FEED = 5,
};

int starline_slip_function(char* buf, int max_bytes, enum starline_slip_function_option option);

enum starline_slip_eject_mode {
  STARLINE_MODE_FWDFEED_LINES = '+',
  STARLINE_MODE_BACKFEED_LINES = '-',
  STARLINE_MODE_BACKFEED_INCHES = '0'
};

int starline_set_slip_eject(char* buf, int max_bytes, enum starline_slip_eject_mode mode, uint8_t length);

// slip enquiry is a single byte and i can't read so i ain't including it rn

int starline_set_clamp_wait_time(char* buf, int max_bytes, uint8_t time);

int starline_enter_page_mode(char* buf, int max_bytes);
int starline_select_line_mode(char* buf, int max_bytes);

int starline_set_print_area(char* buf, int max_bytes, int x, int y, int dx, int dy);

enum starline_print_rotation {
  STARLINE_ROT_0 = 0,
  STARLINE_ROT_270 = 1,
  STARLINE_ROT_180 = 2,
  STARLINE_ROT_90 = 3,
  STARLINE_ROT_270_BIDI = 4
};

int starline_set_print_direction(char* buf, int max_bytes, enum starline_print_rotation rotation);

// these are one byte commands but non-standard ascii meaning and important enough to include nevertheless imo
int starline_print_page(char* buf, int max_bytes);
int starline_cancel_and_init(char* buf, int max_bytes);
int starline_deselect(char* buf, int max_bytes);
int starline_select(char* buf, int max_bytes);
int starline_beep(char* buf, int max_bytes);

// todo: memory switch set

int starline_initialize(char* buf, int max_bytes);
int starline_reset_and_test(char* buf, int max_bytes);



#ifndef _lib_v2x_wmcp_h_
#define _lib_v2x_wmcp_h_

#include <stdbool.h>

#include "v2x_includes.h"

extern void set_relative_pos_flag(bool flag);
extern bool get_relative_pos_flag(void);
extern void set_spat_utc_timing_flag(bool flag);

extern int encode_wireless_message(int in_type, char *in_buf, char *out_buf, int out_size, char *err_buf, int err_size);
extern int decode_wireless_message(char *in_buf, int in_len, char *out_buf, int *out_type, char *err_buf, int err_size);

#endif
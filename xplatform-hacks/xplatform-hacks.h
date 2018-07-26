#include <stdio.h>

// These constants have been defined only recently (in osx 10.7 and later)
// But, just to make compilation succeed with deployment target of 10.6, defining them here.
#define DICE_KIND_DATA              0x0001  /* L$start$data$...  label */
#define DICE_KIND_JUMP_TABLE8       0x0002  /* L$start$jt8$...   label */
#define DICE_KIND_JUMP_TABLE16      0x0003  /* L$start$jt16$...  label */
#define DICE_KIND_JUMP_TABLE32      0x0004  /* L$start$jt32$...  label */
#define DICE_KIND_ABS_JUMP_TABLE32  0x0005  /* L$start$jta32$... label */


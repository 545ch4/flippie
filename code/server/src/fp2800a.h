#ifndef FP2800A_H
#define FP2800A_H

#define FP2800A_COLUMN_CODE_LINES 5
#define FP2800A_ACTIVE_TIME_IN_USEC 250
#define FP2800A_MAX_COLUMNS 28

// column index to FP2800A column code (B1, B0, A2, A1, A0)
extern "C" const unsigned int FP2800A_COLUMN_CODES[FP2800A_MAX_COLUMNS][FP2800A_COLUMN_CODE_LINES] = {
   {0, 0, 0, 0, 1},
   {0, 0, 0, 1, 0},
   {0, 0, 0, 1, 1},
   {0, 0, 1, 0, 0},
   {0, 0, 1, 0, 1},
   {0, 0, 1, 1, 0},
   {0, 0, 1, 1, 1},
   {0, 1, 0, 0, 1},
   {0, 1, 0, 1, 0},
   {0, 1, 0, 1, 1},
   {0, 1, 1, 0, 0},
   {0, 1, 1, 0, 1},
   {0, 1, 1, 1, 0},
   {0, 1, 1, 1, 1},
   {1, 0, 0, 0, 1},
   {1, 0, 0, 1, 0},
   {1, 0, 0, 1, 1},
   {1, 0, 1, 0, 0},
   {1, 0, 1, 0, 1},
   {1, 0, 1, 1, 0},
   {1, 0, 1, 1, 1},
   {1, 1, 0, 0, 1},
   {1, 1, 0, 1, 0},
   {1, 1, 0, 1, 1},
   {1, 1, 1, 0, 0},
   {1, 1, 1, 0, 1},
   {1, 1, 1, 1, 0},
   {1, 1, 1, 1, 1}
};

#endif

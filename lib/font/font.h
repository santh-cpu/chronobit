
#define FONT_WIDTH 3
#define FONT_HEIGHT 6
#define CHAR_SPACING 1 // 1 pixel gap between characters

const byte font_0[FONT_HEIGHT][FONT_WIDTH] = {
  {1,1,1},
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {1,1,1}
};

const byte font_1[FONT_HEIGHT][FONT_WIDTH] = {
  {1,1,0},
  {0,1,0},
  {0,1,0},
  {0,1,0},
  {0,1,0},
  {1,1,1}
};

const byte font_2[FONT_HEIGHT][FONT_WIDTH] = {
  {1,1,1},
  {0,0,1},
  {0,1,0},
  {1,0,0},
  {1,0,0},
  {1,1,1}
};

const byte font_3[FONT_HEIGHT][FONT_WIDTH] = {
  {1,1,1},
  {0,0,1},
  {0,0,1},
  {1,1,1},
  {0,0,1},
  {1,1,1}
};

const byte font_4[FONT_HEIGHT][FONT_WIDTH] = {
  {1,0,0},
  {1,0,0},
  {1,0,1},
  {1,1,1},
  {0,0,1},
  {0,0,1},
};

const byte font_5[FONT_HEIGHT][FONT_WIDTH] = {
  {1,1,1},
  {1,0,0},
  {0,1,0},
  {0,0,1},
  {0,0,1},
  {1,1,1}
};

const byte font_6[FONT_HEIGHT][FONT_WIDTH] = {
  {1,0,0},
  {1,0,0},
  {1,1,0},
  {1,0,1},
  {1,0,1},
  {1,1,1},
};

const byte font_7[FONT_HEIGHT][FONT_WIDTH] = {
  {1,1,1},
  {0,0,1},
  {0,1,0},
  {0,1,0},
  {0,1,0},
  {0,1,0}
};

const byte font_8[FONT_HEIGHT][FONT_WIDTH] = {
  {1,1,1},
  {1,0,1},
  {0,1,0},
  {1,0,1},
  {1,0,1},
  {1,1,1},
};

const byte font_9[FONT_HEIGHT][FONT_WIDTH] = {
  {1,1,1},
  {1,0,1},
  {0,1,1},
  {0,0,1},
  {0,0,1},
  {0,0,1}
};

// A pointer array to easily access the font data
const byte* const font_bitmaps[] = {
  (const byte*)font_0, (const byte*)font_1, (const byte*)font_2, (const byte*)font_3, (const byte*)font_4,
  (const byte*)font_5, (const byte*)font_6, (const byte*)font_7, (const byte*)font_8, (const byte*)font_9
};




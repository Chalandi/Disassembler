#ifndef __OUTPUT_CFG_H__
#define __OUTPUT_CFG_H__

#define _SCREEN_    0
#define _S_FILE_    1
#define _NOTHING_   2

#define OUTPUT_MODE _SCREEN_

#if (OUTPUT_MODE == _SCREEN_)
  #define OUTPUT(x,...)  printf(x,__VA_ARGS__)
#elif (OUTPUT_MODE == _S_FILE_)
  #define OUTPUT(x,...)  fprintf(file,x,__VA_ARGS__)
#else
  #define OUTPUT(x,...)
#endif

#endif // __OUTPUT_CFG_H__

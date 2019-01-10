#ifndef __GUI_FONT_PORT_H
#define	__GUI_FONT_PORT_H

#ifdef __cplusplus
extern "C" {
#endif 
  
#include	"emXGUI.h"
#include "stm32f4xx.h"
#include	"gui_drv_cfg.h"

/* 默认字体 */
extern HFONT defaultFont;
/* logo字体 */
extern HFONT logoFont;
/* 图标字体 */
extern HFONT iconFont_100;
/* 控制图标字体 */
extern HFONT controlFont_48;
extern HFONT controlFont_64;
extern HFONT controlFont_72;
/* 其它 */
extern HFONT GB2312_32_Font;
extern HFONT iconFont_300;

HFONT GUI_Default_FontInit(void);
HFONT GUI_Init_Extern_Font(const char* res_name);

#ifdef	__cplusplus
}
#endif

#endif /* __GUI_FONT_PORT_H */

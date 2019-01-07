#include <emXGUI.h>
#include "./camera/bsp_ov5640.h"
#include "x_libc.h"
#include "./camera/ov5640_AF.h"

#define ID_BUTTON_Exit  0x1000
#define FONT_H          72
#define FONT_W          72

rt_thread_t h1;
BOOL update_flag = 0;//帧率更新标志
static RECT win_rc;
static int b_close=FALSE;
uint8_t fps=0;//帧率
OV5640_IDTypeDef OV5640_Camera_ID;
RECT rc_fps = {0,400,800,72};//帧率显示子窗口
HWND Cam_hwnd;//主窗口句柄
HWND SetWIN;//参数设置窗口
int state = 0;
U16 *bits;
GUI_SEM *cam_sem = NULL;//同步信号量（二值型）
int focus_status = 1;//默认没有被按下
//定义控件ID
enum eID
{
	eID_OK =0x1000,
	eID_SET,             //设置键（摄像头窗口）
	eID_SET1,            //自动对焦
	eID_SET2,            //白平衡
	eID_SET3,            //饱和度
	eID_SET4,            //对比度
   eID_SET5,            //分辨率
   eID_SET6,            //光线模式
   eID_SET7,            //特殊效果
   eID_SCROLLBAR,       //白平衡滑动条
   eID_SCROLLBAR1,      //饱和度滑动条
   eID_SCROLLBAR2,      //对比度滑动条
   //单选框---分辨率
   eID_RB1,             //320*240
   eID_RB2,             //480*272
   eID_RB3,             //800*480（默认）
   //单选框---光线模式
   eID_RB4,             //自动
   eID_RB5,             //光照
   eID_RB6,             //阴天
   eID_RB7,             //办公室
   eID_RB8,             //家里
   //单选框---特殊效果
   eID_RB9,              //复古
   eID_RB10,             //偏蓝
   eID_RB11,             //偏绿
   eID_RB12,             //偏红
   eID_RB13,             //黑白   
   eID_RB14,             //反相
   eID_RB15,             //黑白反相
   eID_RB16,             //正常  

   eID_TB1,             //当前分辨率显示
   eID_TB2,             //当前光线模式显示   
   eID_TB3,             //当前特殊效果显示
   
   eID_switch,          //自动对焦开关
   eID_Setting1,        //设置分辨率按钮
   eID_Setting2,        //设置光线模式按钮
   eID_Setting3,        //设置特殊效果按钮
   
   eID_BT1,             //分辨率界面返回按键
   eID_BT2,             //光线模式界面返回按键
   eID_BT3,             //特殊效果界面返回按键
};
int flag = 0;

static BOOL cbErase(HDC hdc, const RECT* lprc,HWND hwnd)
{
   SetBrushColor(hdc, MapRGB(hdc,0,0,0));
   FillRect(hdc, lprc);
   return TRUE;
}

/*
 * @brief  绘制滚动条
 * @param  hwnd:   滚动条的句柄值
 * @param  hdc:    绘图上下文
 * @param  back_c：背景颜色
 * @param  Page_c: 滚动条Page处的颜色
 * @param  fore_c：滚动条滑块的颜色
 * @retval NONE
*/
static void draw_scrollbar(HWND hwnd, HDC hdc, COLOR_RGB32 back_c, COLOR_RGB32 Page_c, COLOR_RGB32 fore_c)
{
	RECT rc;
   RECT rc_scrollbar;
	GetClientRect(hwnd, &rc);
	/* 背景 */
	SetBrushColor(hdc, back_c);
	FillRect(hdc, &rc);

   rc_scrollbar.x = rc.x;
   rc_scrollbar.y = rc.h/2;
   rc_scrollbar.w = rc.w;
   rc_scrollbar.h = 2;
   
	SetBrushColor(hdc, MapRGB888(hdc, Page_c));
	FillRect(hdc, &rc_scrollbar);

	/* 滑块 */
	SendMessage(hwnd, SBM_GETTRACKRECT, 0, (LPARAM)&rc);

	SetBrushColor(hdc, MapRGB(hdc, 169, 169, 169));
	//rc.y += (rc.h >> 2) >> 1;
	//rc.h -= (rc.h >> 2);
	/* 边框 */
	//FillRoundRect(hdc, &rc, MIN(rc.w, rc.h) >> 2);
	FillCircle(hdc, rc.x + rc.w / 2, rc.y + rc.h / 2, rc.h / 2);
   InflateRect(&rc, -2, -2);

	SetBrushColor(hdc, MapRGB888(hdc, fore_c));
	FillCircle(hdc, rc.x + rc.w / 2, rc.y + rc.h / 2, rc.h / 2);
   //FillRoundRect(hdc, &rc, MIN(rc.w, rc.h) >> 2);
}
/*
 * @brief  自定义滑动条绘制函数
 * @param  ds:	自定义绘制结构体
 * @retval NONE
*/
static void scrollbar_owner_draw(DRAWITEM_HDR *ds)
{
	HWND hwnd;
	HDC hdc;
	HDC hdc_mem;
	HDC hdc_mem1;
	RECT rc;
	RECT rc_cli;
	//	int i;

	hwnd = ds->hwnd;
	hdc = ds->hDC;
	GetClientRect(hwnd, &rc_cli);

	hdc_mem = CreateMemoryDC(SURF_SCREEN, rc_cli.w, rc_cli.h);
	hdc_mem1 = CreateMemoryDC(SURF_SCREEN, rc_cli.w, rc_cli.h);   	
	//绘制白色类型的滚动条
	draw_scrollbar(hwnd, hdc_mem1, RGB888( 0, 0, 0), RGB888( 250, 250, 250), RGB888( 255, 255, 255));
	//绘制绿色类型的滚动条
	draw_scrollbar(hwnd, hdc_mem, RGB888( 0, 0, 0), RGB888( 250, 0, 0), RGB888( 250, 0, 0));
   SendMessage(hwnd, SBM_GETTRACKRECT, 0, (LPARAM)&rc);   

	//左
	BitBlt(hdc, rc_cli.x, rc_cli.y, rc.x, rc_cli.h, hdc_mem, 0, 0, SRCCOPY);
	//右
	BitBlt(hdc, rc.x + rc.w, 0, rc_cli.w - (rc.x + rc.w) , rc_cli.h, hdc_mem1, rc.x + rc.w, 0, SRCCOPY);

	//绘制滑块
	if (ds->State & SST_THUMBTRACK)//按下
	{
      BitBlt(hdc, rc.x, 0, rc.w, rc_cli.h, hdc_mem1, rc.x, 0, SRCCOPY);
		
	}
	else//未选中
	{
		BitBlt(hdc, rc.x, 0, rc.w+1, rc_cli.h, hdc_mem, rc.x, 0, SRCCOPY);
	}
	//释放内存MemoryDC
	DeleteDC(hdc_mem1);
	DeleteDC(hdc_mem);
}

static void Checkbox_owner_draw(DRAWITEM_HDR *ds) //绘制一个按钮外观
{
	//	HWND hwnd;
	HDC hdc;
	RECT rc;
	WCHAR wbuf[128];

	//	hwnd =ds->hwnd; //button的窗口句柄.
	hdc = ds->hDC;   //button的绘图上下文句柄.
	rc = ds->rc;     //button的绘制矩形区.
	SetBrushColor(hdc, MapRGB(hdc, 0, 0, 0)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
	FillRect(hdc, &rc);

	if (focus_status==1)
	{ //按钮是按下状态
		SetBrushColor(hdc, MapRGB(hdc, 119, 136, 153)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
		FillRoundRect(hdc, &rc, rc.h / 2); //用矩形填充背景
		InflateRect(&rc, -3, -3);

		SetBrushColor(hdc, MapRGB(hdc, 60, 179, 113)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
		FillRoundRect(hdc, &rc, rc.h / 2); //用矩形填充背景

		GetClientRect(ds->hwnd, &rc);
		SetBrushColor(hdc, MapRGB(hdc, 119, 136, 153)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
		FillCircle(hdc, rc.w - 15, 15, 15);


		SetBrushColor(hdc, MapRGB(hdc, 250, 250, 250)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
		FillCircle(hdc, rc.w - 15, 15, 12);
	}
	else
	{ //按钮是弹起状态
		SetBrushColor(hdc, MapRGB(hdc, 119, 136, 153)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
		FillRoundRect(hdc, &rc, rc.h/2); //用矩形填充背景
		InflateRect(&rc, -3,  -3);

		SetBrushColor(hdc, MapRGB(hdc, 250, 250, 250)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
		FillRoundRect(hdc, &rc, rc.h / 2); //用矩形填充背景

		GetClientRect(ds->hwnd, &rc);
		SetBrushColor(hdc, MapRGB(hdc, 119, 136, 153)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
		FillCircle(hdc, rc.x + 15, 15, 15);

		
		SetBrushColor(hdc, MapRGB(hdc, 250, 250, 250)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
		FillCircle(hdc, rc.x + 15, 15, 12);

	}


}
static void Button_owner_draw(DRAWITEM_HDR *ds) //绘制一个按钮外观
{
	//	HWND hwnd;
	HDC hdc;
	RECT rc;
	WCHAR wbuf[128];

	//	hwnd =ds->hwnd; //button的窗口句柄.
	hdc = ds->hDC;   //button的绘图上下文句柄.
	rc = ds->rc;     //button的绘制矩形区.
	SetBrushColor(hdc, MapRGB(hdc, 0, 0, 0)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
	FillRect(hdc, &rc);
   
	if(ds->State & BST_PUSHED)
	{ //按钮是按下状态
//    GUI_DEBUG("ds->ID=%d,BST_PUSHED",ds->ID);
//		SetBrushColor(hdc,MapRGB(hdc,150,200,250)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
//		SetPenColor(hdc,MapRGB(hdc,250,0,0));        //设置绘制色(PenColor用于所有Draw类型的绘图函数)
		SetTextColor(hdc, MapRGB(hdc, 105, 105, 105));      //设置文字色
	}
	else
	{ //按钮是弹起状态
//		SetBrushColor(hdc,MapRGB(hdc,255,255,255));
//		SetPenColor(hdc,MapRGB(hdc,0,250,0));
		SetTextColor(hdc, MapRGB(hdc, 250, 250, 250));
	}
   GetWindowText(ds->hwnd, wbuf, 128); //获得按钮控件的文字
   DrawText(hdc, wbuf, -1, &rc, DT_VCENTER | DT_LEFT);//绘制文字(居中对齐方式)

}

static void button_owner_draw(DRAWITEM_HDR *ds) //绘制一个按钮外观
{
	//	HWND hwnd;
	HDC hdc;
	RECT rc;
	WCHAR wbuf[128];

	//	hwnd =ds->hwnd; //button的窗口句柄.
	hdc = ds->hDC;   //button的绘图上下文句柄.
	rc = ds->rc;     //button的绘制矩形区.
	SetBrushColor(hdc, MapRGB(hdc, 0, 0, 0)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
	FillRect(hdc, &rc);
   
	if(ds->State & BST_PUSHED)
	{ //按钮是按下状态
//    GUI_DEBUG("ds->ID=%d,BST_PUSHED",ds->ID);
//		SetBrushColor(hdc,MapRGB(hdc,150,200,250)); //设置填充色(BrushColor用于所有Fill类型的绘图函数)
//		SetPenColor(hdc,MapRGB(hdc,250,0,0));        //设置绘制色(PenColor用于所有Draw类型的绘图函数)
		SetTextColor(hdc, MapRGB(hdc, 105, 105, 105));      //设置文字色
	}
	else
	{ //按钮是弹起状态
//		SetBrushColor(hdc,MapRGB(hdc,255,255,255));
//		SetPenColor(hdc,MapRGB(hdc,0,250,0));
		SetTextColor(hdc, MapRGB(hdc, 250, 250, 250));
	}
   GetWindowText(ds->hwnd, wbuf, 128); //获得按钮控件的文字
   DrawText(hdc, wbuf, -1, &rc, DT_VCENTER | DT_LEFT);//绘制文字(居中对齐方式)

}
static void Update_Dialog()
{
	int app=0;

	while(1) //线程已创建了
	{
		if(app==0)
		{
         app=1;
			GUI_SemWait(cam_sem, 0xFFFFFFFF);
         InvalidateRect(Cam_hwnd,NULL,FALSE);
			app=0;
		}
	}
}
/*============================================================================*/
//设置分辨率
int cur_Resolution = eID_RB3;
static LRESULT	dlg_set_Resolution_WinProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口.
		{
         RECT rc;
         GetClientRect(hwnd, &rc);
			rc.x =35;
			rc.y =55;
			rc.w =200;
			rc.h =24;
         CreateWindow(BUTTON,L"320*240",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB1,NULL,NULL);
         OffsetRect(&rc,0,rc.h+10);
         CreateWindow(BUTTON,L"480*272",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB2,NULL,NULL);         
         OffsetRect(&rc,0,rc.h+10);
         CreateWindow(BUTTON,L"800*480(默认)",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB3,NULL,NULL);   
         
         switch(cur_Resolution)
         {
            case eID_RB1:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB1),BM_SETSTATE,BST_CHECKED,0);
               break;
            }
            case eID_RB2:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB2),BM_SETSTATE,BST_CHECKED,0);
               break;
            }    
            case eID_RB3:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB3),BM_SETSTATE,BST_CHECKED,0);
               break;
            }              
         }   
         CreateWindow(BUTTON,L"FYZ",WS_OWNERDRAW|WS_VISIBLE,
                      5,0,100,40,hwnd,eID_BT1,NULL,NULL); 
         SetWindowFont(GetDlgItem(hwnd, eID_BT1), hFont_SDCARD);         
		
         SetWindowEraseEx(hwnd, cbErase, TRUE);
      
      }
		return TRUE;
		////
		case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
		{
			PAINTSTRUCT ps;
			HDC hdc;
			RECT rc;
			hdc =BeginPaint(hwnd,&ps); //开始绘图

			////用户的绘制内容...
         GetClientRect(hwnd, &rc);
			SetTextColor(hdc,MapRGB(hdc,250,250,250));
			SetBrushColor(hdc,MapRGB(hdc,0,0,0));
         FillRect(hdc, &rc);


			//TextOut(hdc,10,10,L"Hello",-1);

			EndPaint(hwnd,&ps); //结束绘图
		}
		break;
      case WM_DRAWITEM:
      {
         
         
         DRAWITEM_HDR *ds;
         ds = (DRAWITEM_HDR*)lParam;
         if (ds->ID == eID_SCROLLBAR)
         {
            scrollbar_owner_draw(ds);
            return TRUE;
         }
         if (ds->ID == eID_BT1)
         {
            button_owner_draw(ds);
            return TRUE;
         }
      } 
      case WM_NOTIFY:
      {
			u16 code,id;
			code =HIWORD(wParam); //获得通知码类型.
			id   =LOWORD(wParam); //获得产生该消息的控件ID.
         if(id==eID_BT1 && code==BN_CLICKED)
         {
            PostCloseMessage(hwnd);
         }
         if(id >= eID_RB1 && id<= eID_RB3)
			{
				if(code == BN_CLICKED)
				{ 
					cur_Resolution = id;
				}
			}
         break;
      }
 		case	WM_CTLCOLOR:
		{
			/* 控件在绘制前，会发送 WM_CTLCOLOR到父窗口.
			 * wParam参数指明了发送该消息的控件ID;lParam参数指向一个CTLCOLOR的结构体指针.
			 * 用户可以通过这个结构体改变控件的颜色值.用户修改颜色参数后，需返回TRUE，否则，系统
			 * 将忽略本次操作，继续使用默认的颜色进行绘制.
			 *
			 */
			u16 id;
			id =LOWORD(wParam);
         CTLCOLOR *cr;
         cr =(CTLCOLOR*)lParam;
         if(id >=eID_RB1 && id <= eID_RB3)
         {
				cr->TextColor =RGB888(250,250,250);
				cr->BackColor =RGB888(200,220,200);
				cr->BorderColor =RGB888(50,50,50);
				cr->ForeColor =RGB888(105,105,105);
				return TRUE;            
         }
         
			return FALSE;
			
		}     
      case WM_CLOSE:
      {
//         WCHAR wbuf[128];
//         GetWindowText(GetDlgItem(hwnd, cur_Resolution), wbuf, 128); //获得按钮控件的文字
         switch(cur_Resolution)
         {
            case eID_RB1:
               SetWindowText(GetDlgItem(SetWIN, eID_TB1), L"320*240");break;                 
            case eID_RB2:
               SetWindowText(GetDlgItem(SetWIN, eID_TB1), L"480*272");break;
            case eID_RB3:
               SetWindowText(GetDlgItem(SetWIN, eID_TB1), L"800*480(默认)");break;
         }         
         
         DestroyWindow(hwnd);
         return TRUE; 
      }
      
      default: //用户不关心的消息,由系统处理.
		{
			return DefWindowProc(hwnd,msg,wParam,lParam);
		}

	}
	return WM_NULL;

}
int cur_LightMode = eID_RB4;
//设置光线模式
static LRESULT	dlg_set_LightMode_WinProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口.
		{
         RECT rc;
         GetClientRect(hwnd, &rc);
			rc.x =35;
			rc.y =55;
			rc.w =200;
			rc.h =24;
         CreateWindow(BUTTON,L"自动(默认)",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB4,NULL,NULL);
         OffsetRect(&rc,0,rc.h+10);
         CreateWindow(BUTTON,L"光照",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB5,NULL,NULL);         
         OffsetRect(&rc,0,rc.h+10);
         CreateWindow(BUTTON,L"阴天",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB6,NULL,NULL);          
          OffsetRect(&rc,0,rc.h+10);
         CreateWindow(BUTTON,L"办公室",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB7,NULL,NULL);         
         OffsetRect(&rc,0,rc.h+10);
         CreateWindow(BUTTON,L"家里",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB8,NULL,NULL);     

         CreateWindow(BUTTON,L"FYZ",WS_OWNERDRAW|WS_VISIBLE,
                      5,0,100,40,hwnd,eID_BT2,NULL,NULL); 
         SetWindowFont(GetDlgItem(hwnd, eID_BT2), hFont_SDCARD);         
		
         SetWindowEraseEx(hwnd, cbErase, TRUE);
         
         switch(cur_LightMode)
         {
            case eID_RB4:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB4),BM_SETSTATE,BST_CHECKED,0);
               break;
            }
            case eID_RB5:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB5),BM_SETSTATE,BST_CHECKED,0);
               break;
            }    
            case eID_RB6:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB6),BM_SETSTATE,BST_CHECKED,0);
               break;
            }    
            case eID_RB7:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB7),BM_SETSTATE,BST_CHECKED,0);
               break;
            }    
            case eID_RB8:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB8),BM_SETSTATE,BST_CHECKED,0);
               break;
            }             
         }          
         
		}
		return TRUE;
		////
		case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
		{
			PAINTSTRUCT ps;
			HDC hdc;
			RECT rc;
			hdc =BeginPaint(hwnd,&ps); //开始绘图

			////用户的绘制内容...

			SetTextColor(hdc,MapRGB(hdc,250,250,250));
			SetBrushColor(hdc,MapRGB(hdc,240,10,10));



			//TextOut(hdc,10,10,L"Hello",-1);

			EndPaint(hwnd,&ps); //结束绘图
		}
		break;
 		case	WM_CTLCOLOR:
		{
			/* 控件在绘制前，会发送 WM_CTLCOLOR到父窗口.
			 * wParam参数指明了发送该消息的控件ID;lParam参数指向一个CTLCOLOR的结构体指针.
			 * 用户可以通过这个结构体改变控件的颜色值.用户修改颜色参数后，需返回TRUE，否则，系统
			 * 将忽略本次操作，继续使用默认的颜色进行绘制.
			 *
			 */
			u16 id;
			id =LOWORD(wParam);
         CTLCOLOR *cr;
         cr =(CTLCOLOR*)lParam;
         if(id >=eID_RB4 && id <= eID_RB8)
         {
				cr->TextColor =RGB888(250,250,250);
				cr->BackColor =RGB888(200,220,200);
				cr->BorderColor =RGB888(50,50,50);
				cr->ForeColor =RGB888(105,105,105);
				return TRUE;            
         }
         
			return FALSE;
			
		}  
      case WM_NOTIFY:
      {
			u16 code,id;
			code =HIWORD(wParam); //获得通知码类型.
			id   =LOWORD(wParam); //获得产生该消息的控件ID.
         if(id==eID_BT2 && code==BN_CLICKED)
         {
            PostCloseMessage(hwnd);
         }
         if(id >= eID_RB4 && id<= eID_RB8)
			{
				if(code == BN_CLICKED)
				{ 
					cur_LightMode = id;

				}
			}
         break;
      }     
      case WM_DRAWITEM:
      { 
         DRAWITEM_HDR *ds;
         ds = (DRAWITEM_HDR*)lParam;
         if (ds->ID == eID_BT2)
         {
            button_owner_draw(ds);
            return TRUE;
         }
      }  
      case WM_CLOSE:
      {
//         WCHAR wbuf[128];
//         GetWindowText(GetDlgItem(hwnd, cur_Resolution), wbuf, 128); //获得按钮控件的文字
         switch(cur_LightMode)
         {
            case eID_RB4:
               SetWindowText(GetDlgItem(SetWIN, eID_TB2), L"自动(默认)");break;                 
            case eID_RB5:
               SetWindowText(GetDlgItem(SetWIN, eID_TB2), L"光照");break;
            case eID_RB6:
               SetWindowText(GetDlgItem(SetWIN, eID_TB2), L"阴天");break;
            case eID_RB7:
               SetWindowText(GetDlgItem(SetWIN, eID_TB2), L"办公室");break;
            case eID_RB8:
               SetWindowText(GetDlgItem(SetWIN, eID_TB2), L"家里");break;
         }         
         
         DestroyWindow(hwnd);
         return TRUE; 
      }      
		default: //用户不关心的消息,由系统处理.
		{
			return DefWindowProc(hwnd,msg,wParam,lParam);
		}

	}
	return WM_NULL;

}


int cur_SpecialEffects = eID_RB16;
//设置特殊效果
static LRESULT	dlg_set_SpecialEffects_WinProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口.
		{
         RECT rc;
         GetClientRect(hwnd, &rc);
			rc.x =35;
			rc.y =55;
			rc.w =200;
			rc.h =24;
         CreateWindow(BUTTON,L"复古",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB9,NULL,NULL);
         OffsetRect(&rc,0,rc.h+10);
         CreateWindow(BUTTON,L"偏蓝",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB10,NULL,NULL);         
         OffsetRect(&rc,0,rc.h+10);
         CreateWindow(BUTTON,L"偏绿",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB11,NULL,NULL);          
          OffsetRect(&rc,0,rc.h+10);
         CreateWindow(BUTTON,L"偏红",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB12,NULL,NULL);         
         OffsetRect(&rc,0,rc.h+10);
         CreateWindow(BUTTON,L"黑白",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB13,NULL,NULL);     
         CreateWindow(BUTTON,L"反相",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB14,NULL,NULL);         
         OffsetRect(&rc,0,rc.h+10);
         CreateWindow(BUTTON,L"黑白反相",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB15,NULL,NULL);   
          CreateWindow(BUTTON,L"正常(默认)",BS_RADIOBOX|WS_VISIBLE,
                      rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|eID_RB16,NULL,NULL); 
         CreateWindow(BUTTON,L"FYZ",WS_OWNERDRAW|WS_VISIBLE,
                      5,0,100,40,hwnd,eID_BT3,NULL,NULL); 
         SetWindowFont(GetDlgItem(hwnd, eID_BT3), hFont_SDCARD);         
		
         SetWindowEraseEx(hwnd, cbErase, TRUE);
         
         switch(cur_SpecialEffects)
         {
            case eID_RB9:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB9),BM_SETSTATE,BST_CHECKED,0);
               break;
            }
            case eID_RB10:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB10),BM_SETSTATE,BST_CHECKED,0);
               break;
            }    
            case eID_RB11:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB11),BM_SETSTATE,BST_CHECKED,0);
               break;
            }    
            case eID_RB12:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB12),BM_SETSTATE,BST_CHECKED,0);
               break;
            }    
            case eID_RB13:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB13),BM_SETSTATE,BST_CHECKED,0);
               break;
            }     
            case eID_RB14:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB14),BM_SETSTATE,BST_CHECKED,0);
               break;
            }    
            case eID_RB15:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB15),BM_SETSTATE,BST_CHECKED,0);
               break;
            }    
            case eID_RB16:
            {
               SendMessage(GetDlgItem(hwnd, eID_RB16),BM_SETSTATE,BST_CHECKED,0);
               break;
            }              
         }          
         
		}
		return TRUE;
		////
		case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
		{
			PAINTSTRUCT ps;
			HDC hdc;
			RECT rc;
			hdc =BeginPaint(hwnd,&ps); //开始绘图

			////用户的绘制内容...

			SetTextColor(hdc,MapRGB(hdc,250,250,250));
			SetBrushColor(hdc,MapRGB(hdc,240,10,10));



			//TextOut(hdc,10,10,L"Hello",-1);

			EndPaint(hwnd,&ps); //结束绘图
		}
		break;
 		case	WM_CTLCOLOR:
		{
			/* 控件在绘制前，会发送 WM_CTLCOLOR到父窗口.
			 * wParam参数指明了发送该消息的控件ID;lParam参数指向一个CTLCOLOR的结构体指针.
			 * 用户可以通过这个结构体改变控件的颜色值.用户修改颜色参数后，需返回TRUE，否则，系统
			 * 将忽略本次操作，继续使用默认的颜色进行绘制.
			 *
			 */
			u16 id;
			id =LOWORD(wParam);
         CTLCOLOR *cr;
         cr =(CTLCOLOR*)lParam;
         if(id >=eID_RB9 && id <= eID_RB16)
         {
				cr->TextColor =RGB888(250,250,250);
				cr->BackColor =RGB888(200,220,200);
				cr->BorderColor =RGB888(50,50,50);
				cr->ForeColor =RGB888(105,105,105);
				return TRUE;            
         }
         
			return FALSE;
			
		}  
      case WM_NOTIFY:
      {
			u16 code,id;
			code =HIWORD(wParam); //获得通知码类型.
			id   =LOWORD(wParam); //获得产生该消息的控件ID.
         if(id==eID_BT3 && code==BN_CLICKED)
         {
            PostCloseMessage(hwnd);
         }
         if(id >= eID_RB9 && id<= eID_RB16)
			{
				if(code == BN_CLICKED)
				{ 
					cur_SpecialEffects = id;

				}
			}
         break;
      }     
      case WM_DRAWITEM:
      { 
         DRAWITEM_HDR *ds;
         ds = (DRAWITEM_HDR*)lParam;
         if (ds->ID == eID_BT3)
         {
            button_owner_draw(ds);
            return TRUE;
         }
      }  
      case WM_CLOSE:
      {
//         WCHAR wbuf[128];
//         GetWindowText(GetDlgItem(hwnd, cur_Resolution), wbuf, 128); //获得按钮控件的文字
         switch(cur_SpecialEffects)
         {
            case eID_RB9:
               SetWindowText(GetDlgItem(SetWIN, eID_TB3), L"复古");break;                 
            case eID_RB10:
               SetWindowText(GetDlgItem(SetWIN, eID_TB3), L"偏蓝");break;
            case eID_RB11:
               SetWindowText(GetDlgItem(SetWIN, eID_TB3), L"偏绿");break;
            case eID_RB12:
               SetWindowText(GetDlgItem(SetWIN, eID_TB3), L"偏红");break;
            case eID_RB13:
               SetWindowText(GetDlgItem(SetWIN, eID_TB3), L"黑白");break;
            case eID_RB14:
               SetWindowText(GetDlgItem(SetWIN, eID_TB3), L"反相");break;
            case eID_RB15:
               SetWindowText(GetDlgItem(SetWIN, eID_TB3), L"黑白反相");break;
            case eID_RB16:
               SetWindowText(GetDlgItem(SetWIN, eID_TB3), L"正常(默认)");break;            
         }         
         
         DestroyWindow(hwnd);
         return TRUE; 
      }      
		default: //用户不关心的消息,由系统处理.
		{
			return DefWindowProc(hwnd,msg,wParam,lParam);
		}

	}
	return WM_NULL;

}
//参数设置窗口回调函数
static LRESULT	dlg_set_WinProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	RECT rc,rc0;
   static SCROLLINFO sif, sif1, sif2;
   static HWND wnd;
	switch(msg)
	{
		case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口.
		{
			b_close =FALSE;

//			GetClientRect(hwnd,&rc0); //获得窗口的客户区矩形.
//			CreateWindow(BUTTON,L"OK",WS_VISIBLE,rc0.w-80,8,68,32,hwnd,eID_OK,NULL,NULL);
			rc.x =40;
			rc.y =50;
			rc.w =100;
			rc.h =40;
         CreateWindow(TEXTBOX,L"自动对焦",WS_VISIBLE,rc.x,rc.y,rc.w,rc.h,hwnd,eID_SET1,NULL,NULL);
         SendMessage(GetDlgItem(hwnd, eID_SET1),TBM_SET_TEXTFLAG,0,
                     DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND|DT_BORDER); 
         
			OffsetRect(&rc,0,rc.h+10);
         CreateWindow(TEXTBOX,L"白平衡",WS_VISIBLE,rc.x,rc.y,rc.w,rc.h,hwnd,eID_SET2,NULL,NULL);
         SendMessage(GetDlgItem(hwnd, eID_SET2),TBM_SET_TEXTFLAG,0,
                     DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND|DT_BORDER);         
         
			OffsetRect(&rc,0,rc.h+10);
         CreateWindow(TEXTBOX,L"饱和度",WS_VISIBLE,rc.x,rc.y,rc.w,rc.h,hwnd,eID_SET3,NULL,NULL);
         SendMessage(GetDlgItem(hwnd, eID_SET3),TBM_SET_TEXTFLAG,0,
                     DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND|DT_BORDER); 

			OffsetRect(&rc,0,rc.h+10);
         CreateWindow(TEXTBOX,L"对比度",WS_VISIBLE,rc.x,rc.y,rc.w,rc.h,hwnd,eID_SET4,NULL,NULL);
         SendMessage(GetDlgItem(hwnd, eID_SET4),TBM_SET_TEXTFLAG,0,
                     DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND|DT_BORDER); 
			OffsetRect(&rc,0,rc.h+10);
         CreateWindow(TEXTBOX,L"分辨率",WS_VISIBLE,rc.x,rc.y,rc.w,rc.h,hwnd,eID_SET5,NULL,NULL);
         SendMessage(GetDlgItem(hwnd, eID_SET5),TBM_SET_TEXTFLAG,0,
                     DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND|DT_BORDER);         
         
			OffsetRect(&rc,0,rc.h+10);
         CreateWindow(TEXTBOX,L"光线模式",WS_VISIBLE,rc.x,rc.y,rc.w,rc.h,hwnd,eID_SET6,NULL,NULL);
         SendMessage(GetDlgItem(hwnd, eID_SET6),TBM_SET_TEXTFLAG,0,
                     DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND|DT_BORDER); 

			OffsetRect(&rc,0,rc.h+10);
         CreateWindow(TEXTBOX,L"特殊效果",WS_VISIBLE,rc.x,rc.y,rc.w,rc.h,hwnd,eID_SET7,NULL,NULL);
         SendMessage(GetDlgItem(hwnd, eID_SET7),TBM_SET_TEXTFLAG,0,
                     DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND|DT_BORDER); 

			SetTimer(hwnd,2,20,TMR_START,NULL);
         
         sif.cbSize = sizeof(sif);
         sif.fMask = SIF_ALL;
         sif.nMin = -3;
         sif.nMax = 3;//音量最大值为63
         sif.nValue = 0;//初始音量值
         sif.TrackSize = 31;//滑块值
         sif.ArrowSize = 0;//两端宽度为0（水平滑动条）
         CreateWindow(SCROLLBAR, L"SCROLLBAR_R", WS_OWNERDRAW|WS_VISIBLE, 
                       180, 105, 180, 31, hwnd, eID_SCROLLBAR, NULL, NULL);
         SendMessage(GetDlgItem(hwnd, eID_SCROLLBAR), SBM_SETSCROLLINFO, TRUE, (LPARAM)&sif);


         sif1.cbSize = sizeof(sif1);
         sif1.fMask = SIF_ALL;
         sif1.nMin = -3;
         sif1.nMax = 3;//音量最大值为63
         sif1.nValue = 0;//初始音量值
         sif1.TrackSize = 31;//滑块值
         sif1.ArrowSize = 0;//两端宽度为0（水平滑动条）
         CreateWindow(SCROLLBAR, L"SCROLLBAR_R", WS_OWNERDRAW|WS_VISIBLE, 
                       180, 155, 180, 31, hwnd, eID_SCROLLBAR1, NULL, NULL);
         SendMessage(GetDlgItem(hwnd, eID_SCROLLBAR1), SBM_SETSCROLLINFO, TRUE, (LPARAM)&sif1);
         
         
         sif2.cbSize = sizeof(sif2);
         sif2.fMask = SIF_ALL;
         sif2.nMin = -3;
         sif2.nMax = 3;//音量最大值为63
         sif2.nValue = 0;//初始音量值
         sif2.TrackSize = 31;//滑块值
         sif2.ArrowSize = 0;//两端宽度为0（水平滑动条）
         CreateWindow(SCROLLBAR, L"SCROLLBAR_R", WS_OWNERDRAW|WS_VISIBLE, 
                       180, 205, 180, 31, hwnd, eID_SCROLLBAR2, NULL, NULL);
         SendMessage(GetDlgItem(hwnd, eID_SCROLLBAR2), SBM_SETSCROLLINFO, TRUE, (LPARAM)&sif2);
         
         CreateWindow(BUTTON,L" ",WS_OWNERDRAW|WS_VISIBLE,
                      280,55,60,30,hwnd,eID_switch,NULL,NULL);
                      
         CreateWindow(TEXTBOX,L"800*480(默认)",WS_VISIBLE,
                      200,255,160,30,hwnd,eID_TB1,NULL,NULL);                      
         SendMessage(GetDlgItem(hwnd, eID_TB1),TBM_SET_TEXTFLAG,0,
                     DT_SINGLELINE|DT_RIGHT|DT_VCENTER|DT_BKGND|DT_BORDER);
         switch(cur_Resolution)
         {
            case eID_RB1:
               SetWindowText(GetDlgItem(hwnd, eID_TB1), L"320*240");break;                 
            case eID_RB2:
               SetWindowText(GetDlgItem(hwnd, eID_TB1), L"480*272");break;
            case eID_RB3:
               SetWindowText(GetDlgItem(hwnd, eID_TB1), L"800*480(默认)");break;
         }                       
         CreateWindow(BUTTON,L"C",WS_OWNERDRAW|WS_VISIBLE,
                      358,253,40,30,hwnd,eID_Setting1,NULL,NULL); 
         SetWindowFont(GetDlgItem(hwnd, eID_Setting1), hFont_SDCARD);
         
         CreateWindow(TEXTBOX,L"自动(默认)",WS_VISIBLE,
                      200,305,160,30,hwnd,eID_TB2,NULL,NULL);                      
         SendMessage(GetDlgItem(hwnd, eID_TB2),TBM_SET_TEXTFLAG,0,
                     DT_SINGLELINE|DT_RIGHT|DT_VCENTER|DT_BKGND|DT_BORDER);        
         switch(cur_LightMode)
         {
            case eID_RB4:
               SetWindowText(GetDlgItem(hwnd, eID_TB2), L"自动(默认)");break;                 
            case eID_RB5:
               SetWindowText(GetDlgItem(hwnd, eID_TB2), L"光照");break;
            case eID_RB6:
               SetWindowText(GetDlgItem(hwnd, eID_TB2), L"阴天");break;
            case eID_RB7:
               SetWindowText(GetDlgItem(hwnd, eID_TB2), L"办公室");break;
            case eID_RB8:
               SetWindowText(GetDlgItem(hwnd, eID_TB2), L"家里");break;
         }  
         CreateWindow(BUTTON,L"C",WS_OWNERDRAW|WS_VISIBLE,
                      358,303,40,30,hwnd,eID_Setting2,NULL,NULL); 
         SetWindowFont(GetDlgItem(hwnd, eID_Setting2), hFont_SDCARD);         
         
         CreateWindow(TEXTBOX,L"正常(默认)",WS_VISIBLE,
                      200,355,160,30,hwnd,eID_TB3,NULL,NULL);                      
         SendMessage(GetDlgItem(hwnd, eID_TB3),TBM_SET_TEXTFLAG,0,
                     DT_SINGLELINE|DT_RIGHT|DT_VCENTER|DT_BKGND|DT_BORDER);
         switch(cur_SpecialEffects)
         {
            case eID_RB9:
               SetWindowText(GetDlgItem(hwnd, eID_TB3), L"复古");break;                 
            case eID_RB10:
               SetWindowText(GetDlgItem(hwnd, eID_TB3), L"偏蓝");break;
            case eID_RB11:
               SetWindowText(GetDlgItem(hwnd, eID_TB3), L"偏绿");break;
            case eID_RB12:
               SetWindowText(GetDlgItem(hwnd, eID_TB3), L"偏红");break;
            case eID_RB13:
               SetWindowText(GetDlgItem(hwnd, eID_TB3), L"黑白");break;
            case eID_RB14:
               SetWindowText(GetDlgItem(hwnd, eID_TB3), L"反相");break;
            case eID_RB15:
               SetWindowText(GetDlgItem(hwnd, eID_TB3), L"黑白反相");break;
            case eID_RB16:
               SetWindowText(GetDlgItem(hwnd, eID_TB3), L"正常(默认)");break;            
         }           
         CreateWindow(BUTTON,L"C",WS_OWNERDRAW|WS_VISIBLE,
                      358,353,40,30,hwnd,eID_Setting3,NULL,NULL); 
         SetWindowFont(GetDlgItem(hwnd, eID_Setting3), hFont_SDCARD); 
 

      }
		return TRUE;

		case WM_TIMER:
		{
			switch(wParam)
			{

				case 1:
				{
					//tmr_500ms++;
					//InvalidateRect(hwnd,NULL,FALSE);

				}
				break;
				////

				case 2:
				{
					if(GetKeyState(VK_LBUTTON)!=0)
					{
						break;
					}

					////
					GetWindowRect(hwnd,&rc);

					if(b_close==FALSE)
					{
						if(rc.y < win_rc.y )
						{
							if((win_rc.y-rc.y)>50)
							{
								rc.y +=30;
							}
							if((win_rc.y-rc.y)>30)
							{
								rc.y +=20;
							}
							else
							{
								rc.y +=4;
							}
							ScreenToClient(GetParent(hwnd),(POINT*)&rc.x,1);
							MoveWindow(hwnd,rc.x,rc.y,rc.w,rc.h,TRUE);
						}
					}
					else
					{
						if(rc.y > -(rc.h))
						{
							rc.y -= 40;

							ScreenToClient(GetParent(hwnd),(POINT*)&rc.x,1);
							MoveWindow(hwnd,rc.x,rc.y,rc.w,rc.h,TRUE);
						}
						else
						{
							PostCloseMessage(hwnd);
						}
					}


				}
				break;
			}
		}
		break;
		////

		case WM_NOTIFY: //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;lParam指向了一个NMHDR结构体.
		{
			u16 code,id;
         int i;
         NMHDR *nr;  
         u16 ctr_id = LOWORD(wParam); //wParam低16位是发送该消息的控件ID. 
         nr = (NMHDR*)lParam; //lParam参数，是以NMHDR结构体开头.
			code =HIWORD(wParam); //获得通知码类型.
			id   =LOWORD(wParam); //获得产生该消息的控件ID.
         if (ctr_id == eID_SCROLLBAR || ctr_id == eID_SCROLLBAR1 || ctr_id == eID_SCROLLBAR2)
         {
            NM_SCROLLBAR *sb_nr;
            sb_nr = (NM_SCROLLBAR*)nr; //Scrollbar的通知消息实际为 NM_SCROLLBAR扩展结构,里面附带了更多的信息.
            switch (nr->code)
            {
               case SBN_THUMBTRACK: //R滑块移动
               {
                  i= sb_nr->nTrackValue; //得到当前的音量值
                  SendMessage(nr->hwndFrom, SBM_SETVALUE, TRUE, i); //发送SBM_SETVALUE，设置音量值
               }
               break;
            }
         } 
			if((id==eID_Setting1|| id == eID_TB1)&& code==BN_CLICKED)
			{
 
               WNDCLASS wcex;

//               GetWindowRect(GetDlgItem(hwnd,eID_SET1),&rc);
//               ScreenToClient(hwnd,(POINT*)&rc.x,1);
               GetClientRect(hwnd,&rc);
               rc.x = rc.x+(rc.w-win_rc.w)/2;
               //rc.y = 50;
               rc.w =400;
               rc.h =400;
            
               wcex.Tag	 		= WNDCLASS_TAG;
               wcex.Style			= CS_HREDRAW | CS_VREDRAW;
               wcex.lpfnWndProc	= (WNDPROC)dlg_set_Resolution_WinProc;
               wcex.cbClsExtra		= 0;
               wcex.cbWndExtra		= 0;
               wcex.hInstance		= NULL;
               wcex.hIcon			= NULL;
               wcex.hCursor		= NULL;


               wnd = CreateWindowEx(
                           WS_EX_FRAMEBUFFER,
                           &wcex,L"Set_1_xxx",
                           WS_OVERLAPPED|WS_CLIPCHILDREN|WS_VISIBLE,
                           rc.x,rc.y,rc.w,rc.h,
                           hwnd,0,NULL,NULL);

			}

			if((id==eID_Setting2|| id == eID_TB2) && code==BN_CLICKED)
			{
				WNDCLASS wcex;
            GetClientRect(hwnd,&rc);
//				GetWindowRect(GetDlgItem(hwnd,eID_SET2),&rc);
//				ScreenToClient(hwnd,(POINT*)&rc.x,1);
	         rc.x = rc.x+(rc.w-win_rc.w)/2;
               //rc.y = 50;
            rc.w =400;
            rc.h =400;
				wcex.Tag	 		= WNDCLASS_TAG;
				wcex.Style			= CS_HREDRAW | CS_VREDRAW;
				wcex.lpfnWndProc	= (WNDPROC)dlg_set_LightMode_WinProc;
				wcex.cbClsExtra		= 0;
				wcex.cbWndExtra		= 0;
				wcex.hInstance		= NULL;
				wcex.hIcon			= NULL;
				wcex.hCursor		= NULL;


				CreateWindowEx(
								WS_EX_FRAMEBUFFER,
								&wcex,L"Set_2_xxx",
								WS_OVERLAPPED|WS_CLIPCHILDREN|WS_VISIBLE,
								rc.x,rc.y,rc.w,rc.h,
								hwnd,0,NULL,NULL);

			}
			if((id==eID_Setting3|| id == eID_TB3) && code==BN_CLICKED)
			{
				WNDCLASS wcex;
            GetClientRect(hwnd,&rc);
//				GetWindowRect(GetDlgItem(hwnd,eID_SET2),&rc);
//				ScreenToClient(hwnd,(POINT*)&rc.x,1);
	         rc.x = rc.x+(rc.w-win_rc.w)/2;
               //rc.y = 50;
            rc.w =400;
            rc.h =400;
				wcex.Tag	 		= WNDCLASS_TAG;
				wcex.Style			= CS_HREDRAW | CS_VREDRAW;
				wcex.lpfnWndProc	= (WNDPROC)dlg_set_SpecialEffects_WinProc;
				wcex.cbClsExtra		= 0;
				wcex.cbWndExtra		= 0;
				wcex.hInstance		= NULL;
				wcex.hIcon			= NULL;
				wcex.hCursor		= NULL;


				CreateWindowEx(
								WS_EX_FRAMEBUFFER,
								&wcex,L"Set_3_xxx",
								WS_OVERLAPPED|WS_CLIPCHILDREN|WS_VISIBLE,
								rc.x,rc.y,rc.w,rc.h,
								hwnd,0,NULL,NULL);

			}
			if(id==eID_OK && code==BN_CLICKED) // 按钮“单击”了.
			{
				PostCloseMessage(hwnd); //使产生WM_CLOSE消息关闭窗口.
			}
         
			if (id == eID_switch && code == BN_CLICKED)
			{
				focus_status = ~focus_status;
            if(focus_status != 1)
            {
               //暂停对焦
               OV5640_FOCUS_AD5820_Pause_Focus();
               
            }
            else
            {
               //自动对焦
               OV5640_FOCUS_AD5820_Constant_Focus();
              
            }
            
			}         
//			if(id==eID_Setting1 && code==BN_CLICKED)
//			{
//				WNDCLASS wcex;


//				wcex.Tag	 		= WNDCLASS_TAG;
//				wcex.Style			= CS_HREDRAW | CS_VREDRAW;
//				wcex.lpfnWndProc	= (WNDPROC)dlg_set11_WinProc;
//				wcex.cbClsExtra		= 0;
//				wcex.cbWndExtra		= 0;
//				wcex.hInstance		= NULL;
//				wcex.hIcon			= NULL;
//				wcex.hCursor		= NULL;

//				if(1)
//				{
//					RECT rc;

//					GetClientRect(hwnd,&rc);
//					//ClientToScreen(hwnd,(POINT*)&rc.x,1);

//					win_rc.w =400;
//					win_rc.h =400;

//					win_rc.x = rc.x+(rc.w-win_rc.w)/2;
//					win_rc.y = rc.y;//rc.y+(rc.h>>2);

//					CreateWindowEx(
//									NULL,
//									&wcex,L"Set",
//									WS_OVERLAPPED|WS_CLIPCHILDREN|WS_VISIBLE,

//									win_rc.x,-win_rc.h-4,win_rc.w,win_rc.h,
//									hwnd,0,NULL,NULL);
//				}

//			}         
		}
		break;
		////
      
      case WM_ERASEBKGND:
      {
         HDC hdc =(HDC)wParam;

         return TRUE;
      }

		case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
		{
			PAINTSTRUCT ps;
			HDC hdc;
         HDC hdc_mem;
			RECT rc;
			hdc =BeginPaint(hwnd,&ps); //开始绘图
         
			////用户的绘制内容...
         GetClientRect(hwnd, &rc);
		//	hdc_mem = CreateMemoryDC(SURF_ARGB4444, rc.w, rc.h);
	
         SetBrushColor(hdc,MapRGB(hdc,0,0,0));
         FillRect(hdc, &rc);
//			//TextOut(hdc,10,10,L"Hello",-1);
//         SetBrushColor(hdc_mem,MapARGB(hdc_mem,0,0,0,0));
//         FillRect(hdc_mem, &rc);

//         
//         BitBlt(hdc, rc.x, rc.y, rc.w, rc.h, hdc_mem, 0, 0, SRCCOPY);
//         DeleteDC(hdc_mem);
         HFONT hfont_old = NULL;
         rc.x =5;
         rc.y =5;
         rc.w =40;
         rc.h =40;
         SetTextColor(hdc,MapRGB(hdc,240,250,250));
         hfont_old = SetFont(hdc, hFont_SDCARD);
         DrawText(hdc,L"a",-1,&rc,DT_CENTER|DT_VCENTER|DT_BKGND);
         SetFont(hdc, hfont_old);
         rc.x = 45;
         rc.y = 10;
         DrawText(hdc,L"设置",-1,&rc,DT_CENTER|DT_VCENTER|DT_BKGND);         
         
         EndPaint(hwnd,&ps); //结束绘图
         break;
		}
		case	WM_CTLCOLOR:
		{
			/* 控件在绘制前，会发送 WM_CTLCOLOR到父窗口.
			 * wParam参数指明了发送该消息的控件ID;lParam参数指向一个CTLCOLOR的结构体指针.
			 * 用户可以通过这个结构体改变控件的颜色值.用户修改颜色参数后，需返回TRUE，否则，系统
			 * 将忽略本次操作，继续使用默认的颜色进行绘制.
			 *
			 */
			u16 id;
			id =LOWORD(wParam);
         CTLCOLOR *cr;
         cr =(CTLCOLOR*)lParam;
//			if(id== eID_SET1 || id == eID_SET2)
//			{		
//				cr->TextColor =RGB888(255,255,255);//文字颜色（RGB888颜色格式)
//				cr->BackColor =RGB888(0,0,0);//背景颜色（RGB888颜色格式)
//				cr->BorderColor =RGB888(255,0,0);//边框颜色（RGB888颜色格式)
//				return TRUE;
//			}
         if((id >=eID_SET1 && id <= eID_SET7 )|| (id >= eID_TB1 && id <= eID_TB3) )
         {
				cr->TextColor =RGB888(255,255,255);//文字颜色（RGB888颜色格式)
				cr->BackColor =RGB888(0,0,0);//背景颜色（RGB888颜色格式)
				cr->BorderColor =RGB888(0,0,0);//边框颜色（RGB888颜色格式)
				return TRUE;            
         }
         
			return FALSE;
			
		}	

		case	WM_DRAWITEM:
		{
			/*　当控件指定了WS_OWNERDRAW风格，则每次在绘制前都会给父窗口发送WM_DRAWITEM消息。
			 *  wParam参数指明了发送该消息的控件ID;lParam参数指向一个DRAWITEM_HDR的结构体指针，
			 *  该指针成员包含了一些控件绘制相关的参数.
			 */
			DRAWITEM_HDR *ds;
			ds = (DRAWITEM_HDR*)lParam;
			if (ds->ID == eID_switch)
			{
				Checkbox_owner_draw(ds); //执行自绘制按钮
			}
         if (ds->ID == eID_SCROLLBAR || ds->ID == eID_SCROLLBAR1 || ds->ID == eID_SCROLLBAR2)
         {
            scrollbar_owner_draw(ds);
            return TRUE;
         }         
			if (ds->ID >= eID_Setting1&& ds->ID <= eID_Setting3)
			{
				Button_owner_draw(ds); //执行自绘制按钮
			}         
         
			return TRUE;
		}
		////
		case WM_CLOSE:
		{
			b_close=TRUE;

			GetWindowRect(hwnd,&rc);

			if(rc.y <= -(rc.h))
			{
				DestroyWindow(hwnd);
				return TRUE;
			}
			return FALSE;
		}
		break;
		////
 
		default: //用户不关心的消息,由系统处理.
		{
			return DefWindowProc(hwnd,msg,wParam,lParam);
		}

	}

	return WM_NULL;

}
//摄像头窗口回调函数
static LRESULT WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   switch(msg)
   {
      case WM_CREATE:
      {

        /* 初始化摄像头GPIO及IIC */
        OV5640_HW_Init();  
        /* 读取摄像头芯片ID，确定摄像头正常连接 */
        OV5640_ReadID(&OV5640_Camera_ID);

        if(OV5640_Camera_ID.PIDH  == 0x56)
        {
          GUI_DEBUG("OV5640 ID:%x %x",OV5640_Camera_ID.PIDH ,OV5640_Camera_ID.PIDL);
        }
        else
        {
          MSGBOX_OPTIONS ops;
          //const WCHAR *btn[]={L"确定"};
          int x,y,w,h;

          ops.Flag =MB_ICONERROR;
          //ops.pButtonText =btn;
          ops.ButtonCount =0;
          w =500;
          h =200;
          x =(GUI_XSIZE-w)>>1;
          y =(GUI_YSIZE-h)>>1;
          MessageBox(hwnd,x,y,w,h,L"没有检测到OV5640摄像头，\n请重新检查连接。",L"消息",&ops); 
          break;  
        }     
        cam_sem = GUI_SemCreate(1,1);
        h1=rt_thread_create("Update_Dialog",(void(*)(void*))Update_Dialog,NULL,4096,5,5);
        rt_thread_startup(h1);	
        bits = (U16 *)GUI_VMEM_Alloc(2*800*480); 
		  SetTimer(hwnd,1,1000,TMR_START,NULL);  
        RECT rc;
        GetClientRect(hwnd, &rc);
        CreateWindow(BUTTON,L"Set",NULL,rc.w-80,rc.h-32-2,68,32,hwnd,eID_SET,NULL,NULL);        
        
        
        break;
      }

 		case WM_TIMER:
      {
         switch(state)
         {
            case 0:
            {
              OV5640_Init();  
              OV5640_RGB565Config();
              OV5640_USER_Config();
              OV5640_FOCUS_AD5820_Init();
               
               if(cam_mode.auto_focus ==1)
               {
                  OV5640_FOCUS_AD5820_Constant_Focus();
                  focus_status = 1;
               }
               //使能DCMI采集数据
              DCMI_Cmd(ENABLE); 
              DCMI_CaptureCmd(ENABLE); 
                             
               state = 1;
               break;
            }
            case 1:
            {
               ShowWindow(GetDlgItem(hwnd, eID_SET), SW_SHOW);
               state=2;
               break;
            }
            case 2:
            {
               update_flag = 1;
               break;
            }
         }
         break;
      }     
      case WM_PAINT:
      {
         PAINTSTRUCT ps;
         SURFACE *pSurf;
         HDC hdc_mem;
         HDC hdc;
         RECT rc;
         static int old_fps = 0;
         WCHAR wbuf[128];
         hdc = BeginPaint(hwnd,&ps);
         GetClientRect(hwnd,&rc);
			if(state==0)
			{
				SetTextColor(hdc,MapRGB(hdc,250,0,0));
				SetBrushColor(hdc,MapRGB(hdc,50,0,0));
				SetPenColor(hdc,MapRGB(hdc,250,0,0));

				DrawText(hdc,L"正在初始化摄像头\r\n请等待...",-1,&rc,DT_VCENTER|DT_CENTER|DT_BKGND);

			}              
         if(state == 2)
         {         
            pSurf =CreateSurface(SURF_RGB565,GUI_XSIZE, GUI_YSIZE, 0, bits);
            hdc_mem =CreateDC(pSurf,NULL);
            if(update_flag)
            {
               update_flag = 0;
               old_fps = fps;
               fps = 0;
            } 
            SetTextColor(hdc_mem, MapRGB(hdc_mem, 255,255,255));                 
            x_wsprintf(wbuf,L"帧率FPS:%d/s",old_fps);
            DrawText(hdc_mem, wbuf, -1, &rc_fps, DT_SINGLELINE| DT_VCENTER|DT_CENTER);
            
//            /****************绘制退出按钮******************/
//            SetBrushColor(hdc_mem, MapRGB(hdc_mem, 0,0,0));
//            FillCircle(hdc_mem, rc.w, 0, 54);
//            //边框
//            SetBrushColor(hdc_mem, MapRGB(hdc_mem, 250,0,0));
//            FillCircle(hdc_mem, rc.w, 0, 50);
//            
//            SetFont(hdc_mem, hFont_SDCARD);
//            TextOut(hdc_mem, rc.w - 20, 0, L"O", -1);
//            
//            if(show_menu)
//            {
//               RECT rc = {0, 0, 72, 480};
//               
//               SetBrushColor(hdc_mem, MapARGB(hdc_mem,50, 0,0,0));
//               FillRect(hdc_mem, &rc);
//            }            
            BitBlt(hdc, 0, 0, 800, 480, 
                   hdc_mem, 0, 0, SRCCOPY);          
            DeleteSurface(pSurf);
            DeleteDC(hdc_mem);
         }

         EndPaint(hwnd,&ps);
         break;
      }
      case WM_DESTROY:
      {
         state = 0;
         OV5640_Capture_Control(DISABLE);
         DMA_ITConfig(DMA2_Stream1,DMA_IT_TC,DISABLE); 
         DCMI_Cmd(DISABLE); 
         DCMI_CaptureCmd(DISABLE); 
         rt_thread_delete(h1);
         GUI_VMEM_Free(bits);
      
         return PostQuitMessage(hwnd);	
      }    
 		case WM_NOTIFY: //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;lParam指向了一个NMHDR结构体.
		{
			u16 code,id;
         static int flag = 0;
			code =HIWORD(wParam); //获得通知码类型.
			id   =LOWORD(wParam); //获得产生该消息的控件ID.
         if(flag == 0)
         {
            if(id==eID_SET && code==BN_CLICKED)
            {
               flag = 1;
               WNDCLASS wcex;


               wcex.Tag	 		= WNDCLASS_TAG;
               wcex.Style			= CS_HREDRAW | CS_VREDRAW;
               wcex.lpfnWndProc	= (WNDPROC)dlg_set_WinProc;
               wcex.cbClsExtra		= 0;
               wcex.cbWndExtra		= 0;
               wcex.hInstance		= NULL;
               wcex.hIcon			= NULL;
               wcex.hCursor		= NULL;

               if(1)
               {
                  RECT rc;

                  GetClientRect(hwnd,&rc);
                  //ClientToScreen(hwnd,(POINT*)&rc.x,1);

                  win_rc.w =400;
                  win_rc.h =400;

                  win_rc.x = rc.x+(rc.w-win_rc.w)/2;
                  win_rc.y = rc.y;//rc.y+(rc.h>>2);

                  SetWIN = CreateWindowEx(
                              NULL,
                              &wcex,L"Set",
                              WS_OVERLAPPED|WS_CLIPCHILDREN|WS_VISIBLE,

                              win_rc.x,-win_rc.h-4,win_rc.w,win_rc.h,
                              hwnd,0,NULL,NULL);
               }

            }
         }
         else
         {
            flag = 0;
            PostCloseMessage(SetWIN);
         
         }
         break;  
		}
		   
      default:
         return DefWindowProc(hwnd, msg, wParam, lParam);
   }
   return WM_NULL;
}


//摄像头窗口
void	GUI_Camera_DIALOG(void)
{	
	WNDCLASS	wcex;
	MSG msg;


	wcex.Tag = WNDCLASS_TAG;

	wcex.Style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = NULL;//hInst;
	wcex.hIcon = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);
	wcex.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);

	//创建主窗口
	Cam_hwnd = CreateWindowEx(WS_EX_NOFOCUS,
                                    &wcex,
                                    L"GUI_Camera_Dialog",
                                    WS_VISIBLE|WS_CLIPCHILDREN,
                                    0, 0, GUI_XSIZE, GUI_YSIZE,
                                    NULL, NULL, NULL, NULL);

	//显示主窗口
	ShowWindow(Cam_hwnd, SW_SHOW);

	//开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。
	while (GetMessage(&msg, Cam_hwnd))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


#include "u8g2.h"
#include <stdio.h>
#include <string.h>
#include "mui.h"
#include "mui_u8g2.h"



uint8_t mui_style_helv_r_08(mui_t *ui, uint8_t msg)
{
  
  u8g2_t *u8g2 = mui_get_U8g2(ui);
  switch(msg)
  {
    case MUIF_MSG_DRAW:
      u8g2_SetFont(u8g2, u8g2_font_helvR08_tr);
    
      break;
  }
  return 0;
}

uint8_t mui_style_helv_b_08(mui_t *ui, uint8_t msg)
{
  u8g2_t *u8g2 = mui_get_U8g2(ui);
  switch(msg)
  {
    case MUIF_MSG_DRAW:
      u8g2_SetFont(u8g2, u8g2_font_helvB08_tr);
      break;
  }
  return 0;
}

uint8_t mui_hrule(mui_t *ui, uint8_t msg)
{
  u8g2_t *u8g2 = mui_get_U8g2(ui);
  switch(msg)
  {
    case MUIF_MSG_DRAW:
      u8g2_DrawHLine(u8g2, 0, mui_get_y(ui), u8g2_GetDisplayWidth(u8g2));
      break;
  }
  return 0;
}

u8g2_t u8g2;
mui_t ui;

/* A variable where the user can input a number between 0 and 9 */
uint8_t number_input = 2;
uint8_t fruit_input = 2;
uint8_t my_value3 = 0;
uint8_t color_input = 0;




muif_t muif_list[] = {
  /* normal text style */
  MUIF("S0",0,0,mui_style_helv_r_08),
  
  /* bold text style */
  MUIF("S1",0,0,mui_style_helv_b_08),

  /* horizontal line (hrule) */
  MUIF("HR",0,0,mui_hrule),

  /* Button where the width is equal to the size of the text, spaces can be used to extend the size */
  MUIF("G1",MUIF_CFLAG_IS_CURSOR_SELECTABLE,0,mui_goto_frame_button_invers_select_u8g2),
  
  /* input for a number between 0 to 9 */
  MUIF("IN",MUIF_CFLAG_IS_CURSOR_SELECTABLE,&number_input,mui_input_uint8_invers_select_u8g2),
  
  /* input for a fruit (0..3), implements a selection, where the user can cycle through the options  */
  MUIF("IF",MUIF_CFLAG_IS_CURSOR_SELECTABLE,&fruit_input,mui_single_line_option_invers_select_u8g2),
  
  
  MUIF("I3",MUIF_CFLAG_IS_CURSOR_SELECTABLE,&my_value3,mui_checkbox_invers_select_u8g2),
  
  /* the following two fields belong together and implement a single selection combo box to select a color */
  MUIF("IC",MUIF_CFLAG_IS_CURSOR_SELECTABLE,&color_input,mui_show_option_goto_form_invers_select_u8g2),
  MUIF("OC",MUIF_CFLAG_IS_CURSOR_SELECTABLE,&color_input,mui_assign_arg_go_back_invers_select_u8g2),
    
  MUIF(".G",MUIF_CFLAG_IS_CURSOR_SELECTABLE,0,mui_goto_half_width_frame_button_invers_select_u8g2),    /* MUI_GOTO has the id FG */
  MUIF(".g",MUIF_CFLAG_IS_CURSOR_SELECTABLE,0,mui_goto_line_button_invers_select_u8g2),    /* MUI_goto has the id Fg */
  MUIF(".L",0,0,mui_label_u8g2)
};

fds_t fds = 

MUI_FORM(1)
MUI_STYLE(1)
MUI_LABEL(0,10, "Main Menu")
MUI_XY("HR", 0,13)
MUI_STYLE(0)
MUI_goto(12,30,2, "Test 1")
MUI_goto(12,43,10, "Enter a number")
MUI_goto(12,55,11, "Selection/Combo Box")
//MUI_goto(12,22,10, "Button Test")
//MUI_goto(12,34,101, "Story")

MUI_FORM(2)
MUI_LABEL(0,10, "Number:")
MUI_XY("IN",50, 10)
MUI_LABEL(0,22, "Fruit:")
MUI_XYAT("IF",50, 22, 60, "Banana|Apple|Peach")

MUI_LABEL(0,34, "Check:")
MUI_XY("I3",50, 34)

MUI_LABEL(0,46, "Color:")
MUI_XYAT("IC",50, 46, 4, "red|green|blue")


//MUI_BUTTON("B1",32,50, "Ok")
MUI_GOTO(32,60,3, "Goto 2")
MUI_GOTO(96,60,1, "Home")

MUI_FORM(3)
MUI_goto(32,50,2, "Goto 1")

MUI_FORM(4)
MUI_XYA("OC", 2, 10, 0)
MUI_XYA("OC", 2, 22, 1)
MUI_XYAT("OC", 2, 34, 2, "blue color")  /* provide a different text for this option */

/* number entry demo */
MUI_FORM(10)
MUI_STYLE(1)
MUI_LABEL(0,10, "Number 0..9 Menu")
MUI_XY("HR", 0,13)
MUI_STYLE(0)

MUI_LABEL(5,30, "Number:")
MUI_XY("IN",50, 30)

MUI_XYAT("G1",64, 59, 1, " OK ")

/* selection / combo box */
MUI_FORM(11)
MUI_STYLE(1)
MUI_LABEL(0,10, "Selection/Combo Box")
MUI_XY("HR", 0,13)
MUI_STYLE(0)

MUI_LABEL(5,29, "Fruit:")
MUI_XYAT("IF",50, 29, 60, "Banana|Apple|Melon|Cranberry")

MUI_LABEL(5,43, "Color:")
MUI_XYAT("IC",50, 43, 12, "red|green|blue")     /* jump to sub form 12 */

MUI_XYAT("G1",64, 59, 1, " OK ")

/* combo box color selection */
MUI_FORM(12)
MUI_STYLE(1)
MUI_LABEL(0,10, "Color Selection")
MUI_XY("HR", 0,13)
MUI_STYLE(0)
MUI_XYA("OC", 5, 30, 0) /* takeover the selection text from calling field ("red") */
MUI_XYA("OC", 5, 42, 1) /* takeover the selection text from calling field ("green") */
MUI_XYAT("OC", 5, 54, 2, "blue")  /* just as a demo: provide a different text for this option */

;


int main(void)
{
  int x, y;
  int k;

  
  u8g2_SetupBuffer_SDL_128x64_4(&u8g2, &u8g2_cb_r0);
  u8x8_InitDisplay(u8g2_GetU8x8(&u8g2));
  u8x8_SetPowerSave(u8g2_GetU8x8(&u8g2), 0);  
  
  
  mui_Init(&ui, &u8g2, fds, muif_list, sizeof(muif_list)/sizeof(muif_t));
  mui_EnterForm(&ui, 0);

  //puts(fds);
  
  
  x = 4;  // use as height for the box
  y = 0;
  
  for(;;)
  {
    u8g2_SetFontRefHeightExtendedText(&u8g2);
    u8g2_FirstPage(&u8g2);
    do
    {
      mui_Draw(&ui);
    } while( u8g2_NextPage(&u8g2) );
    
    // printf("mui_GetCurrentCursorFocusPosition=%d\n", mui_GetCurrentCursorFocusPosition(&ui));
    
    do
    {
      k = u8g_sdl_get_key();
    } while( k < 0 );
    
    if ( k == 273 ) y -= 1;
    if ( k == 274 ) y += 1;
    if ( k == 276 ) x -= 1;
    if ( k == 275 ) x += 1;
    
    /*
    if ( k == 'e' ) y -= 1;
    if ( k == 'x' ) y += 1;
    if ( k == 's' ) x -= 1;
    if ( k == 'd' ) x += 1;
    */
    
    if ( k == 'q' ) break;

    if ( k == 'n' ) mui_NextField(&ui);
    if ( k == 'p' ) mui_PrevField(&ui);
    if ( k == 's' ) mui_SendSelect(&ui);

    
    if ( x < 0 )
      x = 0;
    
  }
  return 0;
}


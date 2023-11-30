#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"

#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

#include "lib/usb_descriptors.h"

//SD card
#include "sd_card.h"
#include "ff.h"
#include "hw_config.h"

#include "lib/blackwhitelist/blackwhitelist.h"

sd_card_t *sdcard;


void hid_task(void);



/*------------- MAIN -------------*/
int main(void)
{

  stdio_init_all();
  board_init();
  tusb_init();

  sd_init_driver();

  sdcard = sd_get_by_num(0);

  while (1)
  {
    tud_task(); // tinyusb device task
    tud_mount_cb();
    hid_task();
    
  }

  
}


//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  f_mount(&sdcard->fatfs,sdcard->pcName, 1);
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  f_unmount(sdcard->pcName);
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{

}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

static void send_hid_report(uint8_t report_id, uint32_t btn)
{
  // skip if hid is not ready yet
  if ( !tud_hid_ready() ) return;

  if (report_id == REPORT_ID_KEYBOARD)
  {
    // use to avoid send multiple consecutive zero report for keyboard
    static bool has_keyboard_key = false;

    if ( btn )
    {

      // Press 'Win + X and I' to open PowerShell
      uint8_t win_x_keys[6] = {0};
      win_x_keys[0] = HID_KEY_GUI_LEFT;
      win_x_keys[1] = HID_KEY_X;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, win_x_keys);
      // Tiny delay to mimic human typing
      board_delay(100);
      // Release all keys
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
      
      // Tiny delay to mimic human typing
      board_delay(100);

      // Press 'I' to open PowerShell
      uint8_t i_key[6] = {0};
      i_key[0] = HID_KEY_I;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, i_key);

      // Tiny delay to mimic human typing
      board_delay(100);

      // Release all keys
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);

      // Tiny delay to mimic human typing
      board_delay(10000);
      
      // Type in the string ' get-itemproperty hklm:\software\microsoft\windows\currentversion\uninstall\* | 
      // select-object displayname, displayversion > D:\output.txt'
      // Writes the output of the command to a text file on the mounted SD card
      // Only 6 keycodes at a time

      uint8_t keypress[6] = {0};
      keypress[0] = HID_KEY_G;
      keypress[1] = HID_KEY_E;
      keypress[2] = HID_KEY_T;
      keypress[3] = HID_KEY_MINUS;
      keypress[4] = HID_KEY_I;
      keypress[5] = HID_KEY_T;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress);

      // Tiny delay to mimic human typing
      board_delay(100);

      // Release all keys
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
      board_delay(100);

      
      uint8_t keypress_2[6] = {0};
      keypress_2[0] = HID_KEY_E;
      keypress_2[1] = HID_KEY_M;
      keypress_2[2] = HID_KEY_P;
      keypress_2[3] = HID_KEY_R;
      keypress_2[4] = HID_KEY_O;
      keypress_2[5] = HID_KEY_P;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_2);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

     
      uint8_t keypress_3[6] = {0};
      keypress_3[0] = HID_KEY_E;
      keypress_3[1] = HID_KEY_R;
      keypress_3[2] = HID_KEY_T;
      keypress_3[3] = HID_KEY_Y;
      keypress_3[4] = HID_KEY_SPACE;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_3);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

   
      uint8_t keypress_4[6] = {0};
      keypress_4[0] = HID_KEY_H;
      keypress_4[1] = HID_KEY_K;
      keypress_4[2] = HID_KEY_L;
      keypress_4[3] = HID_KEY_M;
      keypress_4[4] = HID_KEY_SHIFT_LEFT;
      keypress_4[5] = HID_KEY_SEMICOLON;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_4);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

    
      uint8_t keypress_5[6] = {0};
      keypress_5[0] = HID_KEY_BACKSLASH;
      keypress_5[1] = HID_KEY_S;
      keypress_5[2] = HID_KEY_O;
      keypress_5[3] = HID_KEY_F;
      keypress_5[4] = HID_KEY_T;
      keypress_5[5] = HID_KEY_W;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_5);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

    
      uint8_t keypress_6[6] = {0};
      keypress_6[0] = HID_KEY_A;
      keypress_6[1] = HID_KEY_R;
      keypress_6[2] = HID_KEY_E;
      keypress_6[3] = HID_KEY_BACKSLASH;
      keypress_6[4] = HID_KEY_M;
      keypress_6[5] = HID_KEY_I;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_6);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      
      uint8_t keypress_7[6] = {0};
      keypress_7[0] = HID_KEY_C;
      keypress_7[1] = HID_KEY_R;
      keypress_7[2] = HID_KEY_O;
      keypress_7[3] = HID_KEY_S;
      keypress_7[4] = HID_KEY_O;
      keypress_7[5] = HID_KEY_F;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_7);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      
      uint8_t keypress_8[6] = {0};
      keypress_8[0] = HID_KEY_T;
      keypress_8[1] = HID_KEY_BACKSLASH;
      keypress_8[2] = HID_KEY_W;
      keypress_8[3] = HID_KEY_I;
      keypress_8[4] = HID_KEY_N;
      keypress_8[5] = HID_KEY_D;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_8);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      
      uint8_t keypress_9[6] = {0};
      keypress_9[0] = HID_KEY_O;
      keypress_9[1] = HID_KEY_W;
      keypress_9[2] = HID_KEY_S;
      keypress_9[3] = HID_KEY_BACKSLASH;
      keypress_9[4] = HID_KEY_C;
      keypress_9[5] = HID_KEY_U;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_9);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

     
      uint8_t keypress_10[6] = {0};
      keypress_10[0] = HID_KEY_R;
      keypress_10[1] = HID_KEY_R;
      keypress_10[2] = HID_KEY_E;
      keypress_10[3] = HID_KEY_N;
      keypress_10[4] = HID_KEY_T;
      keypress_10[5] = HID_KEY_V;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_10);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

     
      uint8_t keypress_11[6] = {0};
      keypress_11[0] = HID_KEY_E;
      keypress_11[1] = HID_KEY_R;
      keypress_11[2] = HID_KEY_S;
      keypress_11[3] = HID_KEY_I;
      keypress_11[4] = HID_KEY_O;
      keypress_11[5] = HID_KEY_N;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_11);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      uint8_t keypress_12[6] = {0};
      keypress_12[0] = HID_KEY_BACKSLASH;
      keypress_12[1] = HID_KEY_U;
      keypress_12[2] = HID_KEY_N;
      keypress_12[3] = HID_KEY_I;
      keypress_12[4] = HID_KEY_N;
      keypress_12[5] = HID_KEY_S;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_12);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      uint8_t keypress_13[6] = {0};
      keypress_13[0] = HID_KEY_T;
      keypress_13[1] = HID_KEY_A;
      keypress_13[2] = HID_KEY_L;

      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_13);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      uint8_t keypress_14[6] = {0};
      keypress_14[2] = HID_KEY_L;
      keypress_14[3] = HID_KEY_BACKSLASH;

      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_14);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      uint8_t keypress_15[6] = {0};
      keypress_15[0] = HID_KEY_SHIFT_LEFT;
      keypress_15[1] = HID_KEY_8;
      keypress_15[2] = HID_KEY_SPACE;
      keypress_15[3] = HID_KEY_SHIFT_LEFT;
      keypress_15[4] = HID_KEY_BACKSLASH;
      keypress_15[5] = HID_KEY_SPACE;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_15);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      uint8_t keypress_16[6] = {0};
      keypress_16[0] = HID_KEY_S;
      keypress_16[1] = HID_KEY_E;
      keypress_16[2] = HID_KEY_L;
      keypress_16[3] = HID_KEY_E;
      keypress_16[4] = HID_KEY_C;
      keypress_16[5] = HID_KEY_T;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_16);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      uint8_t keypress_17[6] = {0};
      keypress_17[0] = HID_KEY_MINUS;
      keypress_17[1] = HID_KEY_O;
      keypress_17[2] = HID_KEY_B;
      keypress_17[3] = HID_KEY_J;
      keypress_17[4] = HID_KEY_E;
      keypress_17[5] = HID_KEY_C;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_17);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      uint8_t keypress_18[6] = {0};
      keypress_18[0] = HID_KEY_T;
      keypress_18[1] = HID_KEY_SPACE;
      keypress_18[2] = HID_KEY_D;
      keypress_18[3] = HID_KEY_I;
      keypress_18[4] = HID_KEY_S;
      keypress_18[5] = HID_KEY_P;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_18);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      uint8_t keypress_19[6] = {0};
      keypress_19[0] = HID_KEY_L;
      keypress_19[1] = HID_KEY_A;
      keypress_19[2] = HID_KEY_Y;
      keypress_19[3] = HID_KEY_N;
      keypress_19[4] = HID_KEY_A;
      keypress_19[5] = HID_KEY_M;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_19);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      uint8_t keypress_20[6] = {0};
      keypress_20[0] = HID_KEY_E;
      keypress_20[1] = HID_KEY_COMMA;
      keypress_20[2] = HID_KEY_SPACE;
      keypress_20[3] = HID_KEY_D;
      keypress_20[4] = HID_KEY_I;
      keypress_20[5] = HID_KEY_S;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_20);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      uint8_t keypress_21[6] = {0};
      keypress_21[0] = HID_KEY_P;
      keypress_21[1] = HID_KEY_L;
      keypress_21[2] = HID_KEY_A;
      keypress_21[3] = HID_KEY_Y;
      keypress_21[4] = HID_KEY_V;
      keypress_21[5] = HID_KEY_E;

      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_21);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(100);

      uint8_t keypress_22[6] = {0};
      keypress_22[0] = HID_KEY_R;
      keypress_22[1] = HID_KEY_S;
      keypress_22[2] = HID_KEY_I;
      keypress_22[3] = HID_KEY_O;
      keypress_22[4] = HID_KEY_N;
      keypress_22[5] = HID_KEY_SPACE;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_22);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(1000);

      uint8_t keypress_23[6] = {0};
      keypress_23[0] = HID_KEY_SHIFT_LEFT;
      keypress_23[1] = HID_KEY_PERIOD;
      keypress_23[2] = HID_KEY_SPACE;
      keypress_23[3] = HID_KEY_D;
      keypress_23[4] = HID_KEY_SHIFT_LEFT;
      keypress_23[5] = HID_KEY_SEMICOLON;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_23);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(1000);

      uint8_t keypress_24[6] = {0};
      keypress_24[0] = HID_KEY_BACKSLASH;
      keypress_24[1] = HID_KEY_O;
      keypress_24[2] = HID_KEY_U;
      keypress_24[3] = HID_KEY_T;
      keypress_24[4] = HID_KEY_P;
      keypress_24[5] = HID_KEY_U;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_24);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(1000);

      uint8_t keypress_25[6] = {0};
      keypress_25[0] = HID_KEY_T;
      keypress_25[1] = HID_KEY_PERIOD;
      keypress_25[2] = HID_KEY_T;
      keypress_25[3] = HID_KEY_X;
      keypress_25[4] = HID_KEY_T;
      keypress_25[5] = HID_KEY_ENTER;
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keypress_25);
      board_delay(100);
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // Release all keys
      board_delay(1000);


      has_keyboard_key = true;

    }
    else
    {
      // send empty key report if previously has key pressed
      if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);

      has_keyboard_key = false;
    }
  }
}


// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(void)
{
  // Poll every 10ms
  const uint32_t interval_ms = 10;
  static uint32_t start_ms = 0;

  if ( board_millis() - start_ms < interval_ms) return; // not enough time
  start_ms += interval_ms;

  uint32_t const btn = board_button_read();

  // Remote wakeup
  if ( tud_suspended() && btn )
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  }else
  {
    // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
    send_hid_report(REPORT_ID_KEYBOARD, btn);
  }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
  (void) instance;
  (void) len;

  uint8_t next_report_id = report[0] + 1;

  if (next_report_id < REPORT_ID_COUNT)
  {
    send_hid_report(next_report_id, board_button_read());
  }
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) instance;

  if (report_type == HID_REPORT_TYPE_OUTPUT)
  {
    // Set keyboard LED e.g Capslock, Numlock etc...
    if (report_id == REPORT_ID_KEYBOARD)
    {
      // bufsize should be (at least) 1
      if ( bufsize < 1 ) return;

      uint8_t const kbd_leds = buffer[0];

      if (kbd_leds & KEYBOARD_LED_CAPSLOCK)
      {
        board_led_write(true);
      }
      else
      {
        board_led_write(false);
       
      }
    }
  }
}

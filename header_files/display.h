/* ========================= display.h ========================= */
/* Display ECU interface - provides text/graphics primitives to higher layers */


/* Display initialization result codes */
typedef enum {
DISPLAY_OK = 0,
DISPLAY_ERR_HW = 1,
DISPLAY_ERR_TIMEOUT = 2,
DISPLAY_ERR_INVALID_PARAM = 3
} Display_ReturnType;


/* Display brightness level 0..100 */
typedef uint8_t Display_BrightnessType;


/* Basic display handle */
typedef struct {
bool initialized;
Display_BrightnessType brightness;
uint16_t width;
uint16_t height;
} Display_HandleType;


/* Initialize display hardware and driver */
Display_ReturnType Display_Init(Display_HandleType *handle);


/* Shutdown display */
Display_ReturnType Display_Deinit(Display_HandleType *handle);


/* Clear screen */
Display_ReturnType Display_Clear(Display_HandleType *handle);


/* Draw a pixel at x,y */
Display_ReturnType Display_DrawPixel(Display_HandleType *handle, uint16_t x, uint16_t y, uint32_t color);


/* Draw text at position */
Display_ReturnType Display_DrawText(Display_HandleType *handle, uint16_t x, uint16_t y, const char *text);


/* Draw progress bar */
Display_ReturnType Display_DrawProgress(Display_HandleType *handle, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t percent);


/* Set brightness */
Display_ReturnType Display_SetBrightness(Display_HandleType *handle, Display_BrightnessType level);


/* Low-level flush (commit buffer to hardware) */
Display_ReturnType Display_Flush(Display_HandleType *handle);


/* Diagnostics */
uint32_t Display_GetErrorCode(void);


#endif /* DISPLAY_H */
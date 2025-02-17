#pragma once


#define PH_KEY_SPACE              32
#define PH_KEY_APOSTROPHE         39  /* ' */
#define PH_KEY_COMMA              44  /* , */
#define PH_KEY_MINUS              45  /* - */
#define PH_KEY_PERIOD             46  /* . */
#define PH_KEY_SLASH              47  /* / */
#define PH_KEY_0                  48
#define PH_KEY_1                  49
#define PH_KEY_2                  50
#define PH_KEY_3                  51
#define PH_KEY_4                  52
#define PH_KEY_5                  53
#define PH_KEY_6                  54
#define PH_KEY_7                  55
#define PH_KEY_8                  56
#define PH_KEY_9                  57
#define PH_KEY_SEMICOLON          59  /* ; */
#define PH_KEY_EQUAL              61  /* = */
#define PH_KEY_A                  65
#define PH_KEY_B                  66
#define PH_KEY_C                  67
#define PH_KEY_D                  68
#define PH_KEY_E                  69
#define PH_KEY_F                  70
#define PH_KEY_G                  71
#define PH_KEY_H                  72
#define PH_KEY_I                  73
#define PH_KEY_J                  74
#define PH_KEY_K                  75
#define PH_KEY_L                  76
#define PH_KEY_M                  77
#define PH_KEY_N                  78
#define PH_KEY_O                  79
#define PH_KEY_P                  80
#define PH_KEY_Q                  81
#define PH_KEY_R                  82
#define PH_KEY_S                  83
#define PH_KEY_T                  84
#define PH_KEY_U                  85
#define PH_KEY_V                  86
#define PH_KEY_W                  87
#define PH_KEY_X                  88
#define PH_KEY_Y                  89
#define PH_KEY_Z                  90
#define PH_KEY_LEFT_BRACKET       91  /* [ */
#define PH_KEY_BACKSLASH          92  /* \ */
#define PH_KEY_RIGHT_BRACKET      93  /* ] */
#define PH_KEY_GRAVE_ACCENT       96  /* ` */
#define PH_KEY_WORLD_1            161 /* non-US #1 */
#define PH_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define PH_KEY_ESCAPE             256
#define PH_KEY_ENTER              257
#define PH_KEY_TAB                258
#define PH_KEY_BACKSPACE          259
#define PH_KEY_INSERT             260
#define PH_KEY_DELETE             261
#define PH_KEY_RIGHT              262
#define PH_KEY_LEFT               263
#define PH_KEY_DOWN               264
#define PH_KEY_UP                 265
#define PH_KEY_PAGE_UP            266
#define PH_KEY_PAGE_DOWN          267
#define PH_KEY_HOME               268
#define PH_KEY_END                269
#define PH_KEY_CAPS_LOCK          280
#define PH_KEY_SCROLL_LOCK        281
#define PH_KEY_NUM_LOCK           282
#define PH_KEY_PRINT_SCREEN       283
#define PH_KEY_PAUSE              284
#define PH_KEY_F1                 290
#define PH_KEY_F2                 291
#define PH_KEY_F3                 292
#define PH_KEY_F4                 293
#define PH_KEY_F5                 294
#define PH_KEY_F6                 295
#define PH_KEY_F7                 296
#define PH_KEY_F8                 297
#define PH_KEY_F9                 298
#define PH_KEY_F10                299
#define PH_KEY_F11                300
#define PH_KEY_F12                301
#define PH_KEY_F13                302
#define PH_KEY_F14                303
#define PH_KEY_F15                304
#define PH_KEY_F16                305
#define PH_KEY_F17                306
#define PH_KEY_F18                307
#define PH_KEY_F19                308
#define PH_KEY_F20                309
#define PH_KEY_F21                310
#define PH_KEY_F22                311
#define PH_KEY_F23                312
#define PH_KEY_F24                313
#define PH_KEY_F25                314
#define PH_KEY_KP_0               320
#define PH_KEY_KP_1               321
#define PH_KEY_KP_2               322
#define PH_KEY_KP_3               323
#define PH_KEY_KP_4               324
#define PH_KEY_KP_5               325
#define PH_KEY_KP_6               326
#define PH_KEY_KP_7               327
#define PH_KEY_KP_8               328
#define PH_KEY_KP_9               329
#define PH_KEY_KP_DECIMAL         330
#define PH_KEY_KP_DIVIDE          331
#define PH_KEY_KP_MULTIPLY        332
#define PH_KEY_KP_SUBTRACT        333
#define PH_KEY_KP_ADD             334
#define PH_KEY_KP_ENTER           335
#define PH_KEY_KP_EQUAL           336
#define PH_KEY_LEFT_SHIFT         340
#define PH_KEY_LEFT_CONTROL       341
#define PH_KEY_LEFT_ALT           342
#define PH_KEY_LEFT_SUPER         343
#define PH_KEY_RIGHT_SHIFT        344
#define PH_KEY_RIGHT_CONTROL      345
#define PH_KEY_RIGHT_ALT          346
#define PH_KEY_RIGHT_SUPER        347
#define PH_KEY_MENU               348

#define PH_KEY_LAST               PH_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

 /*! @brief If this bit is set one or more Shift keys were held down.
  *
  *  If this bit is set one or more Shift keys were held down.
  */
#define PH_MOD_SHIFT           0x0001
  /*! @brief If this bit is set one or more Control keys were held down.
   *
   *  If this bit is set one or more Control keys were held down.
   */
#define PH_MOD_CONTROL         0x0002
   /*! @brief If this bit is set one or more Alt keys were held down.
	*
	*  If this bit is set one or more Alt keys were held down.
	*/
#define PH_MOD_ALT             0x0004
	/*! @brief If this bit is set one or more Super keys were held down.
	 *
	 *  If this bit is set one or more Super keys were held down.
	 */
#define PH_MOD_SUPER           0x0008
	 /*! @brief If this bit is set the Caps Lock key is enabled.
	  *
	  *  If this bit is set the Caps Lock key is enabled and the @ref
	  *  PH_LOCK_KEY_MODS input mode is set.
	  */
#define PH_MOD_CAPS_LOCK       0x0010
	  /*! @brief If this bit is set the Num Lock key is enabled.
	   *
	   *  If this bit is set the Num Lock key is enabled and the @ref
	   *  PH_LOCK_KEY_MODS input mode is set.
	   */
#define PH_MOD_NUM_LOCK        0x0020

	   /*! @} */

	   /*! @defgroup buttons Mouse buttons
		*  @brief Mouse button IDs.
		*
		*  See [mouse button input](@ref input_mouse_button) for how these are used.
		*
		*  @ingroup input
		*  @{ */
#define PH_MOUSE_BUTTON_1         0
#define PH_MOUSE_BUTTON_2         1
#define PH_MOUSE_BUTTON_3         2
#define PH_MOUSE_BUTTON_4         3
#define PH_MOUSE_BUTTON_5         4
#define PH_MOUSE_BUTTON_6         5
#define PH_MOUSE_BUTTON_7         6
#define PH_MOUSE_BUTTON_8         7
#define PH_MOUSE_BUTTON_LAST      PH_MOUSE_BUTTON_8
#define PH_MOUSE_BUTTON_LEFT      PH_MOUSE_BUTTON_1
#define PH_MOUSE_BUTTON_RIGHT     PH_MOUSE_BUTTON_2
#define PH_MOUSE_BUTTON_MIDDLE    PH_MOUSE_BUTTON_3
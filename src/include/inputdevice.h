 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Joystick, mouse and keyboard emulation prototypes and definitions
  *
  * Copyright 1995 Bernd Schmidt
  * Copyright 2001-2002 Toni Wilen
  */


#define IDTYPE_JOYSTICK 0
#define IDTYPE_MOUSE 1
#define IDTYPE_KEYBOARD 2

struct inputdevice_functions {
    int		(*init)				(void);
    void	(*close)			(void);
    int		(*acquire)			(int,int);
    void	(*unacquire)		(int);
    void	(*read)				(void);
    int		(*get_num)			(void);
    TCHAR*	(*get_friendlyname)	(int);
    TCHAR*	(*get_uniquename)	(int);
    int		(*get_widget_num)	(int);
    int		(*get_widget_type)	(int,int,TCHAR*,uae_u32*);
    int		(*get_widget_first)	(int,int);
    int		(*get_flags)		(int);
};
extern struct inputdevice_functions idev[3];
extern struct inputdevice_functions inputdevicefunc_joystick;
extern struct inputdevice_functions inputdevicefunc_mouse;
extern struct inputdevice_functions inputdevicefunc_keyboard;
extern int pause_emulation;

struct uae_input_device_kbr_default {
    int scancode;
    int evt;
	int flags;
};

struct inputevent {
	const TCHAR *confname;
	const TCHAR *name;
	int allow_mask;
	int type;
	int unit;
	int data;
};

/* event flags */
#define ID_FLAG_AUTOFIRE 1
#define ID_FLAG_TOGGLE 2
#define ID_FLAG_GAMEPORTSCUSTOM 4
#define ID_FLAG_SAVE_MASK 0xff
#define ID_FLAG_TOGGLED 0x100

#define IDEV_WIDGET_NONE 0
#define IDEV_WIDGET_BUTTON 1
#define IDEV_WIDGET_AXIS 2
#define IDEV_WIDGET_BUTTONAXIS 3
#define IDEV_WIDGET_KEY 4

#define IDEV_MAPPED_AUTOFIRE_POSSIBLE 1
#define IDEV_MAPPED_AUTOFIRE_SET 2
#define IDEV_MAPPED_TOGGLE 4
#define IDEV_MAPPED_GAMEPORTSCUSTOM 8

#define ID_BUTTON_OFFSET 0
#define ID_BUTTON_TOTAL 32
#define ID_AXIS_OFFSET 32
#define ID_AXIS_TOTAL 32

extern int inputdevice_iterate (int devnum, int num, TCHAR *name, int *af);
extern int inputdevice_set_mapping (int devnum, int num, TCHAR *name, TCHAR *custom, int flags, int port, int sub);
extern int inputdevice_get_mapped_name (int devnum, int num, int *pflags, int *port, TCHAR *name, TCHAR *custom, int sub);
extern void inputdevice_copyconfig (const struct uae_prefs *src, struct uae_prefs *dst);
extern void inputdevice_copy_single_config (struct uae_prefs *p, int src, int dst, int devnum);
extern void inputdevice_swap_ports (struct uae_prefs *p, int devnum);
extern void inputdevice_swap_compa_ports (struct uae_prefs *p, int portswap);
extern void inputdevice_config_change (void);
extern int inputdevice_config_change_test (void);
extern int inputdevice_get_device_index (int devnum);
extern TCHAR *inputdevice_get_device_name (int type, int devnum);
extern TCHAR *inputdevice_get_device_name2 (int devnum);
extern TCHAR *inputdevice_get_device_unique_name (int type, int devnum);
extern int inputdevice_get_device_status (int devnum);
extern void inputdevice_set_device_status (int devnum, int enabled);
extern int inputdevice_get_device_total (int type);
extern int inputdevice_get_widget_num (int devnum);
extern int inputdevice_get_widget_type (int devnum, int num, TCHAR *name);

extern int input_get_default_mouse (struct uae_input_device *uid, int num, int port, int af);
extern int input_get_default_lightpen (struct uae_input_device *uid, int num, int port, int af);
extern int input_get_default_joystick (struct uae_input_device *uid, int num, int port, int af, int mode);
extern int input_get_default_joystick_analog (struct uae_input_device *uid, int num, int port, int af);
extern int input_get_default_keyboard (int num);

#define DEFEVENT(A, B, C, D, E, F) INPUTEVENT_ ## A,
enum inputevents {
INPUTEVENT_ZERO,
#include "inputevents.def"
INPUTEVENT_END
};
#undef DEFEVENT

extern void handle_cd32_joystick_cia (uae_u8, uae_u8);
extern uae_u8 handle_parport_joystick (int port, uae_u8 pra, uae_u8 dra);
extern uae_u8 handle_joystick_buttons (uae_u8);
extern int getbuttonstate (int joy, int button);
extern int getjoystate (int joy);

#define MAGICMOUSE_BOTH 0
#define MAGICMOUSE_NATIVE_ONLY 1
#define MAGICMOUSE_HOST_ONLY 2

extern int magicmouse_alive (void);
extern int is_tablet (void);
extern int inputdevice_is_tablet (void);
extern void input_mousehack_status (int mode, uaecptr diminfo, uaecptr dispinfo, uaecptr vp, uae_u32 moffset);
extern void input_mousehack_mouseoffset (uaecptr pointerprefs);
extern int mousehack_alive (void);
extern void setmouseactive (int);

extern void setmousebuttonstateall (int mouse, uae_u32 buttonbits, uae_u32 buttonmask);
extern void setjoybuttonstateall (int joy, uae_u32 buttonbits, uae_u32 buttonmask);
extern void setjoybuttonstate (int joy, int button, int state);
extern void setmousebuttonstate (int mouse, int button, int state);
extern void setjoystickstate (int joy, int axle, int state, int max);
extern int getjoystickstate (int mouse);
void setmousestate (int mouse, int axis, int data, int isabs);
extern int getmousestate (int mouse);
extern void inputdevice_updateconfig (struct uae_prefs *prefs);
extern void inputdevice_devicechange (struct uae_prefs *prefs);

extern int inputdevice_translatekeycode (int keyboard, int scancode, int state);
extern void inputdevice_setkeytranslation (struct uae_input_device_kbr_default *trans, int **kbmaps);
extern int handle_input_event (int nr, int state, int max, int autofire);
extern void inputdevice_do_keyboard (int code, int state);
extern int inputdevice_iskeymapped (int keyboard, int scancode);
extern int inputdevice_synccapslock (int, int*);
extern void inputdevice_testrecord (int type, int num, int wtype, int wnum, int state);
extern int inputdevice_get_compatibility_input (struct uae_prefs*, int, int*, int**, int**);
extern struct inputevent *inputdevice_get_eventinfo (int evt);
extern void inputdevice_get_eventname (const struct inputevent *ie, TCHAR *out);
extern void inputdevice_compa_prepare_custom (struct uae_prefs *prefs, int index);
extern void inputdevice_compa_clear (struct uae_prefs *prefs, int index);
extern int intputdevice_compa_get_eventtype (int evt, int **axistable);


extern uae_u16 potgo_value;
extern uae_u16 POTGOR (void);
extern void POTGO (uae_u16 v);
extern uae_u16 POT0DAT (void);
extern uae_u16 POT1DAT (void);
extern void JOYTEST (uae_u16 v);
extern uae_u16 JOY0DAT (void);
extern uae_u16 JOY1DAT (void);

extern void inputdevice_vsync (void);
extern void inputdevice_hsync (void);
extern void inputdevice_reset (void);

extern void write_inputdevice_config (struct uae_prefs *p, FILE *f);
extern void read_inputdevice_config (struct uae_prefs *p, TCHAR *option, TCHAR *value);
extern void reset_inputdevice_config (struct uae_prefs *pr);
extern int inputdevice_joyport_config (struct uae_prefs *p, TCHAR *value, int portnum, int mode, int type);
extern int inputdevice_getjoyportdevice (int port, int val);

extern void inputdevice_init (void);
extern void inputdevice_close (void);
extern void inputdevice_default_prefs (struct uae_prefs *p);

extern void inputdevice_acquire (int allmode);
extern void inputdevice_unacquire (void);

extern void indicator_leds (int num, int state);

extern void warpmode (int mode);
extern void pausemode (int mode);

extern void inputdevice_add_inputcode (int code, int state);
extern void inputdevice_handle_inputcode (void);

extern void inputdevice_tablet (int x, int y, int z,
	      int pressure, uae_u32 buttonbits, int inproximity,
	      int ax, int ay, int az);
extern void inputdevice_tablet_info (int maxx, int maxy, int maxz, int maxax, int maxay, int maxaz, int xres, int yres);
extern void inputdevice_tablet_strobe (void);


#define JSEM_MODE_DEFAULT 0
#define JSEM_MODE_MOUSE 1
#define JSEM_MODE_JOYSTICK 2
#define JSEM_MODE_JOYSTICK_ANALOG 3
#define JSEM_MODE_MOUSE_CDTV 4
#define JSEM_MODE_JOYSTICK_CD32 5
#define JSEM_MODE_LIGHTPEN 6

#define JSEM_KBDLAYOUT 0
#define JSEM_JOYS      100
#define JSEM_MICE      200
#define JSEM_END       300
#define JSEM_XARCADE1LAYOUT (JSEM_KBDLAYOUT + 3)
#define JSEM_XARCADE2LAYOUT (JSEM_KBDLAYOUT + 4)
#define JSEM_DECODEVAL(port,p) ((p)->jports[port].id)
#define JSEM_ISNUMPAD(port,p)        (jsem_iskbdjoy (port,p) == JSEM_KBDLAYOUT)
#define JSEM_ISCURSOR(port,p)        (jsem_iskbdjoy (port,p) == JSEM_KBDLAYOUT + 1)
#define JSEM_ISSOMEWHEREELSE(port,p) (jsem_iskbdjoy (port,p) == JSEM_KBDLAYOUT + 2)
#define JSEM_ISXARCADE1(port,p) (jsem_iskbdjoy(port,p) == JSEM_XARCADE1LAYOUT)
#define JSEM_ISXARCADE2(port,p) (jsem_iskbdjoy(port,p) == JSEM_XARCADE2LAYOUT)
#define JSEM_LASTKBD 5
#define JSEM_ISANYKBD(port,p)        (jsem_iskbdjoy (port,p) >= JSEM_KBDLAYOUT && jsem_iskbdjoy(port,p) < JSEM_KBDLAYOUT + JSEM_LASTKBD)

extern int jsem_isjoy    (int port, const struct uae_prefs *p);
extern int jsem_ismouse  (int port, const struct uae_prefs *p);
extern int jsem_iskbdjoy (int port, const struct uae_prefs *p);

extern int inputdevice_uaelib (TCHAR *, TCHAR *);

#define INPREC_JOYPORT 1
#define INPREC_JOYBUTTON 2
#define INPREC_KEY 3
#define INPREC_DISKINSERT 4
#define INPREC_DISKREMOVE 5
#define INPREC_VSYNC 6
#define INPREC_CIAVSYNC 7
#define INPREC_END 0xff
#define INPREC_QUIT 0xfe

extern int input_recording;
extern void inprec_close (void);
extern int inprec_open (TCHAR*, int);
extern void inprec_rend (void);
extern void inprec_rstart (uae_u8);
extern void inprec_ru8 (uae_u8);
extern void inprec_ru16 (uae_u16);
extern void inprec_ru32 (uae_u32);
extern void inprec_rstr (const TCHAR*);
extern int inprec_pstart (uae_u8);
extern void inprec_pend (void);
extern uae_u8 inprec_pu8 (void);
extern uae_u16 inprec_pu16 (void);
extern uae_u32 inprec_pu32 (void);
extern int inprec_pstr (TCHAR*);

extern int inputdevice_testread (int*, int*, int*);
extern int inputdevice_istest (void);
extern void inputdevice_settest (int);
extern int inputdevice_testread_count (void);

static int kb_np[] = { INPUTEVENT_KEY_NP_4, -1, INPUTEVENT_KEY_NP_6, -1, INPUTEVENT_KEY_NP_8, -1, INPUTEVENT_KEY_NP_2, -1, INPUTEVENT_KEY_NP_0, INPUTEVENT_KEY_NP_5, -1, INPUTEVENT_KEY_NP_PERIOD, INPUTEVENT_KEY_NP_DIV, INPUTEVENT_KEY_ENTER, -1, -1 };
static int kb_ck[] = { INPUTEVENT_KEY_CURSOR_LEFT, -1, INPUTEVENT_KEY_CURSOR_RIGHT, -1, INPUTEVENT_KEY_CURSOR_UP, -1, INPUTEVENT_KEY_CURSOR_DOWN, -1, INPUTEVENT_KEY_CTRL, INPUTEVENT_KEY_ALT_RIGHT, -1, INPUTEVENT_KEY_SHIFT_LEFT, -1, -1 };
static int kb_se[] = { INPUTEVENT_KEY_A, -1, INPUTEVENT_KEY_D, -1, INPUTEVENT_KEY_W, -1, INPUTEVENT_KEY_S, -1, INPUTEVENT_KEY_ALT_LEFT, -1, INPUTEVENT_KEY_SHIFT_RIGHT, -1, -1 };
static int kb_cd32_np[] = { INPUTEVENT_KEY_NP_4, -1, INPUTEVENT_KEY_NP_6, -1, INPUTEVENT_KEY_NP_8, -1, INPUTEVENT_KEY_NP_2, -1, INPUTEVENT_KEY_NP_1, -1, INPUTEVENT_KEY_NP_3, -1, INPUTEVENT_KEY_NP_7, -1, INPUTEVENT_KEY_NP_9, -1, INPUTEVENT_KEY_PERIOD, -1, INPUTEVENT_KEY_NP_SUB, -1, INPUTEVENT_KEY_NP_MUL, -1, -1 };
static int kb_cd32_ck[] = { INPUTEVENT_KEY_CURSOR_LEFT, -1, INPUTEVENT_KEY_CURSOR_RIGHT, -1, INPUTEVENT_KEY_CURSOR_UP, -1, INPUTEVENT_KEY_CURSOR_DOWN, -1, INPUTEVENT_KEY_NP_1, -1, INPUTEVENT_KEY_NP_3, -1, INPUTEVENT_KEY_NP_7, -1, INPUTEVENT_KEY_NP_9, -1, INPUTEVENT_KEY_NP_DIV, -1, INPUTEVENT_KEY_NP_SUB, -1, INPUTEVENT_KEY_NP_MUL, -1, -1 };
static int kb_cd32_se[] = { INPUTEVENT_KEY_A, -1, INPUTEVENT_KEY_D, -1, INPUTEVENT_KEY_W, -1, INPUTEVENT_KEY_S, -1, INPUTEVENT_KEY_NP_1, -1, INPUTEVENT_KEY_NP_3, -1, INPUTEVENT_KEY_NP_7, -1, INPUTEVENT_KEY_NP_9, -1, INPUTEVENT_KEY_NP_DIV, -1, INPUTEVENT_KEY_NP_SUB, -1, INPUTEVENT_KEY_NP_MUL, -1, -1 };
static int kb_xa1[] = { INPUTEVENT_KEY_NP_4, -1, INPUTEVENT_KEY_NP_6, -1, INPUTEVENT_KEY_NP_8, -1, INPUTEVENT_KEY_NP_2, INPUTEVENT_KEY_NP_5, -1, INPUTEVENT_KEY_CTRL, -1, INPUTEVENT_KEY_ALT_LEFT, -1, INPUTEVENT_KEY_SPACE, -1, -1 };
static int kb_xa2[] = { INPUTEVENT_KEY_D, -1, INPUTEVENT_KEY_G, -1, INPUTEVENT_KEY_R, -1, INPUTEVENT_KEY_F, -1, INPUTEVENT_KEY_A, -1, INPUTEVENT_KEY_S, -1, INPUTEVENT_KEY_Q, -1 };
static int kb_arcadia[] = { INPUTEVENT_KEY_F2, -1, INPUTEVENT_KEY_1, -1, INPUTEVENT_KEY_2, -1, INPUTEVENT_KEY_5, -1, INPUTEVENT_KEY_6, -1, -1 };
static int kb_arcadiaxa[] = { INPUTEVENT_KEY_1, -1, INPUTEVENT_KEY_2, -1, INPUTEVENT_KEY_3, -1, INPUTEVENT_KEY_4, -1, INPUTEVENT_KEY_6, -1, INPUTEVENT_KEY_LEFTBRACKET, INPUTEVENT_KEY_SHIFT_LEFT, -1, INPUTEVENT_KEY_RIGHTBRACKET, -1, INPUTEVENT_KEY_C, -1, INPUTEVENT_KEY_5, -1, INPUTEVENT_KEY_Z, -1, INPUTEVENT_KEY_X, -1, -1 };
static int *kbmaps[] = { kb_np, kb_ck, kb_se, kb_cd32_np, kb_cd32_ck, kb_cd32_se, kb_xa1, kb_xa2, kb_arcadia, kb_arcadiaxa };
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

/* scroller layout settings */
static int centermode                = CenterOnFlow; /* CenterOnFlow, CenterAlways, CenterNever */
static const float winsizes[]        = { 0.33333f, 0.50f, 0.66667f, 1.0f }; /* window width presets [0.1..1.0] */
static const float defwinw           = 0.50f; /* default width factor for multi-window ribbons [0.1..1.0] */
static const float swinw             = 0.50f; /* default width factor for single window or stack [0.1..1.0] */
static const int centerswin          = 0;     /* 1 means always center single window */
static const int scrollstep          = 45;    /* trackpad and mouse wheel scroll step in pixels */
static const int strutleft           = 55;    /* pixels reserved on left edge for focus jump (0 to disable) */
static const int strutright          = 55;    /* pixels reserved on right edge for focus jump (0 to disable) */
static int loopnav                   = 1;     /* 1 means loop navigation */

/* overview layout settings */
static const int ovgappov            = 16;    /* vert outer padding between overview area and screen edge */
static const int ovgappoh            = 24;    /* horiz outer padding between overview ribbons and screen edge */
static const int ovlayergap          = 14;    /* vert gap between workspace layers */
static const int ovinpady            = 6;     /* vert inner padding inside workspace layer */
static const int ovgappih            = 8;     /* horiz gap between miniature windows */
static const int ovgappiv            = 4;     /* vert gap between stacked window panes */
static const float ovsingleh         = 0.45f; /* single layer window height factor */
static const int ovuniformlayer      = 1;     /* 0 means scale to fit ovmaxfit */
static const int ovmaxfit            = 4;     /* max visible workspace layers before vertical scrolling */
static const int ovedgezone          = 80;    /* edge distance in pixels triggering auto-scroll during drag */
static const int ovedgestep          = 25;    /* auto-scroll step in pixels per motion event during drag */
static int ovloopnav                 = 1;     /* 1 means loop navigation */

#include "scrollview.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[|||]",    scroller },
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[⊞]",      overview },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ Normal,   MODKEY,                       KEY,      view,             {.ui = 1 << TAG} }, \
	{ Normal,   MODKEY|ControlMask,           KEY,      toggleview,       {.ui = 1 << TAG} }, \
	{ Normal,   MODKEY|ShiftMask,             KEY,      tag,              {.ui = 1 << TAG} }, \
	{ Normal,   MODKEY|ControlMask|ShiftMask, KEY,      toggletag,        {.ui = 1 << TAG} }, \
	{ Overview, 0,                            KEY,      ovjumptag,  {.ui = TAG} }, \
	{ Overview, MODKEY,                       KEY,      ovjumptag,  {.ui = TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[8]; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "overview.c"

static const Key keys[] = {
	/* mode     modifier                      key        function        argument */
	{ Normal,	MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ Normal,	MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ Normal,	MODKEY,                       XK_b,      togglebar,      {0} },
	{ Normal,	MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ Normal,	MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ Normal,	MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ Normal,	MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ Normal,	MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ Normal,	MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ Normal,	MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ Normal,	MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ Normal,	MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ Normal,	MODKEY,                       XK_Return, zoom,           {0} },
	{ Normal,	MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ Normal,	MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ Normal,	MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ Normal,	MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ Normal,	MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ Normal,	MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ Normal,	MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ Normal,	MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ Normal,	MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ Normal,	MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ Normal,	MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ Normal,	MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ Normal,	MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ Normal,	MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ Normal,	MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ Normal,	MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ Normal,	MODKEY,                       XK_Tab,    view,           {0} },
	{ Normal,	MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ Normal,	MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ Normal,   MODKEY,                       XK_s,      setlayout,      {.v = &layouts[1]} },
	{ Normal,	MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ Normal,	MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ Normal,	MODKEY,                       XK_space,  setlayout,      {0} },
	{ Normal,	MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ Normal,	MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ Normal,	MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ Normal,	MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ Normal,	MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ Normal,	MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ Normal,	MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	/* scroll */
	{ Scroll,   MODKEY,                       XK_Left,    scrollwin,           {.i = -1} },
	{ Scroll,   MODKEY,                       XK_Right,   scrollwin,           {.i = +1} },
	{ Scroll,   MODKEY,                       XK_Up,      focuswinstack,       {.i = -1} },
	{ Scroll,   MODKEY,                       XK_Down,    focuswinstack,       {.i = +1} },
	{ Scroll,   MODKEY,                       XK_Tab,     toggleov, 		   {0} },
	{ Scroll,   MODKEY,                       XK_o,       toggleov, 		   {0} },
	{ Scroll,   MODKEY,                       XK_w,       togglestack,         {0} },
	{ Scroll,   MODKEY,                       XK_r,       cyclewinwidth,       {0} },
	{ Scroll,   MODKEY,                       XK_c,       centerfocused,       {0} },
	{ Scroll,   MODKEY|ShiftMask,             XK_c,       togglecentering,     {0} },
	{ Scroll,   MODKEY|ShiftMask,             XK_Left,    movewin,             {.i = -1} },
	{ Scroll,   MODKEY|ShiftMask,             XK_Right,   movewin,             {.i = +1} },
	{ Scroll,   MODKEY|ShiftMask,             XK_Up,      movewinstack,        {.i = -1} },
	{ Scroll,   MODKEY|ShiftMask,             XK_Down,    movewinstack,        {.i = +1} },
	{ Scroll,   MODKEY|ControlMask,           XK_n,       toggleloopnav,       {0} },
	
	/* overview */
	{ Overview,	0,                      	  XK_Escape, toggleov,       {0} },
	{ Overview,	0,					  		  XK_Return, zoomov,         {0} },
	{ Overview,	MODKEY,                 	  XK_Return, zoomov,         {0} },
	{ Overview,	0,                      	  XK_Up,     focusovlayer,   {.i = -1} },
	{ Overview,	0,                      	  XK_Down,   focusovlayer,   {.i = +1} },
	{ Overview, 0,                      	  XK_k,      focusovlayer,   {.i = -1} },
	{ Overview,	0,                      	  XK_j,      focusovlayer,   {.i = +1} },
	{ Overview,	0,					  		  XK_Left,   focusovwin,     {.i = -1} },
	{ Overview,	0,                            XK_Right,  focusovwin,     {.i = +1} },
	{ Overview,	0,                      	  XK_h,      focusovwin,     {.i = -1} },
	{ Overview,	0,                            XK_l,      focusovwin,     {.i = +1} },
	{ Overview,	MODKEY|ShiftMask,             XK_Left,   ovmovewin,      {.i = -1} },
	{ Overview,	MODKEY|ShiftMask,             XK_Right,  ovmovewin,      {.i = +1} },
	{ Overview,	MODKEY|ShiftMask,             XK_h,      ovmovewin,      {.i = -1} },
	{ Overview,	MODKEY|ShiftMask,             XK_l,      ovmovewin,      {.i = +1} },
	{ Overview,	MODKEY|ShiftMask,             XK_Up,     ovmovewinlayer, {.i = -1} },
	{ Overview,	MODKEY|ShiftMask,		      XK_Down,   ovmovewinlayer, {.i = +1} },
	{ Overview,	MODKEY|ShiftMask,             XK_k,      ovmovewinlayer, {.i = -1} },
	{ Overview,	MODKEY|ShiftMask,             XK_j,      ovmovewinlayer, {.i = +1} },
	{ Overview,	MODKEY,                       XK_n,      toggleovloopnav,{0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ Normal,	MODKEY|ShiftMask,             XK_q,      quit,           {0} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* mode     click                 event mask      button          function        argument */
	{ Normal,	ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ Normal,	ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ Normal,	ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ Normal,	ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ All,      ClkClientWin,   	  MODKEY,         Button1,        dragdrop,       {0} },
	{ Normal,	ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ All,		ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ Normal,	ClkTagBar,            0,              Button1,        view,           {0} },
	{ Normal,	ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ Normal,	ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ Normal,	ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ Scroll,     ClkClientWin,   MODKEY,         Button4,        scrollwin,      {.i = -1} },
	{ Scroll,     ClkClientWin,   MODKEY,         Button5,        scrollwin,      {.i = +1} },
	{ Scroll,     ClkRootWin,     MODKEY,         Button4,        scrollwin,      {.i = -1} },
	{ Scroll,     ClkRootWin,     MODKEY,         Button5,        scrollwin,      {.i = +1} },
	{ Scroll,     ClkClientWin,   MODKEY,         6,              trackscroll,    {.i = -1} },
	{ Scroll,     ClkClientWin,   MODKEY,         7,              trackscroll,    {.i = +1} },
	{ Scroll,     ClkRootWin,     MODKEY,         6,              trackscroll,    {.i = -1} },
	{ Scroll,     ClkRootWin,     MODKEY,         7,              trackscroll,    {.i = +1} },
	{ Overview,   ClkClientWin,   0,              Button4,        ovscrollvert,   {.i = -1} },
	{ Overview,   ClkClientWin,   0,              Button5,        ovscrollvert,   {.i = +1} },
	{ Overview,   ClkRootWin,     0,              Button4,        ovscrollvert,   {.i = -1} },
	{ Overview,   ClkRootWin,     0,              Button5,        ovscrollvert,   {.i = +1} },
	{ Overview,   ClkClientWin,   ShiftMask,      Button4,        ovscrollribbon, {.i = -1} },
	{ Overview,   ClkClientWin,   ShiftMask,      Button5,        ovscrollribbon, {.i = +1} },
	{ Overview,   ClkRootWin,     ShiftMask,      Button4,        ovscrollribbon, {.i = -1} },
	{ Overview,   ClkRootWin,     ShiftMask,      Button5,        ovscrollribbon, {.i = +1} },
	{ Overview,   ClkClientWin,   0,              6,              ovscrollribbon, {.i = -1} },
	{ Overview,   ClkClientWin,   0,              7,              ovscrollribbon, {.i = +1} },
	{ Overview,   ClkRootWin,     0,              6,              ovscrollribbon, {.i = -1} },
	{ Overview,   ClkRootWin,     0,              7,              ovscrollribbon, {.i = +1} },
};


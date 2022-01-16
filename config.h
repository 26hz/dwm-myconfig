/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "SauceCodePro Nerd Font Mono:size=18",
					"WenQuanYi Micro Hei:size=16" };
static const char dmenufont[]       = "Source Code Pro:size=18";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#aaaaaa";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#54487a";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask     isfloating   monitor */
	//{ "Google-chrome",  NULL,       NULL,       2,            0,           -1 },
	{ "Cadence",        NULL,       NULL,       1 << 7,       0,           -1 },
	{ "Ardour",         NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "tiling",        tile },    /* first entry is default */
	{ "floating",      NULL },    /* no layout function means floating behavior */
	{ "monocle",       monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *menu[]  = { "rofi", "-show","drun", NULL };
static const char *term[]  = { "kitty", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scra[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *brow[]  = { "google-chrome-stable", NULL };
static const char *shot[] = { "flameshot", "gui", NULL };
static const char *netm[] = { "netease-cloud-music", "--ignore-certificate-errors", NULL };
static const char *jack[]  = { "cadence", NULL };
static const char *ardo[]  = { "ardour6", NULL };
static const char *edit[]  = { "leafpad", NULL };
static const char *file[]  = { "spacefm", NULL };
//static const char *tray[]  = { "~/.scripts/trayer.sh", NULL };

static Key keys[] = {
        /* modifier            key                      function        argument */
        { MODKEY,              XK_space,                spawn,          {.v = menu } },
        { MODKEY,              XK_Return,               spawn,          {.v = term } },
	{ MODKEY,              XK_grave,                togglescratch,  {.v = scra } },
        { MODKEY,              XK_c,                    spawn,          {.v = brow } },
        { MODKEY,              XK_s,                    spawn,          {.v = shot } },
        { MODKEY,              XK_n,                    spawn,          {.v = netm } },
        { MODKEY,              XK_p,                    spawn,          {.v = jack } },
        { MODKEY,              XK_a,                    spawn,          {.v = ardo } },
        { MODKEY,              XK_e,                    spawn,          {.v = edit } },
        { MODKEY,              XK_f,                    spawn,          {.v = file } },
        //{ MODKEY,              XK_t,                    spawn,          {.v = tray } },
	{ MODKEY,              XK_j,                    focusstackvis,  {.i = -1 } },
	{ MODKEY,              XK_k,                    focusstackvis,  {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_e,                    focusstackhid,  {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_r,                    focusstackhid,  {.i = -1 } },
	{ MODKEY,              XK_g,                    show,           {0} },
	{ MODKEY,              XK_v,                    hide,           {0} },
	{ MODKEY|ShiftMask,    XK_j,                    rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_k,                    rotatestack,    {.i = -1 } },
	{ MODKEY,              XK_i,                    viewtoleft,     {0} },
        { MODKEY,              XK_o,                    viewtoright,    {0} },
	{ MODKEY|ShiftMask,    XK_i,                    tagtoleft,      {0} },
        { MODKEY|ShiftMask,    XK_o,                    tagtoright,     {0} },
        { MODKEY|ShiftMask,    XK_h,                    incnmaster,     {.i = +1 } },
        { MODKEY|ShiftMask,    XK_l,                    incnmaster,     {.i = -1 } },
        { MODKEY,              XK_h,                    setmfact,       {.f = +0.05} },
        { MODKEY,              XK_l,                    setmfact,       {.f = -0.05} },
        { MODKEY,              XK_Tab,                  view,           {0} },
        { MODKEY,              XK_q,                    killclient,     {0} },
	{ MODKEY,              XK_b,                    togglebar,      {0} },
        { MODKEY,              XK_0,                    view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,    XK_0,                    tag,            {.ui = ~0 } },
        { MODKEY,              XK_comma,                focusmon,       {.i = -1 } },
        { MODKEY,              XK_period,               focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,    XK_comma,                tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,    XK_period,               tagmon,         {.i = +1 } },
	{ MODKEY,              XK_minus,                setgaps,        {.i = -1 } },
	{ MODKEY,              XK_equal,                setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_equal,                setgaps,        {.i = 0  } },
        TAGKEYS(               XK_1,                      0)
        TAGKEYS(               XK_2,                      1)
        TAGKEYS(               XK_3,                      2)
        TAGKEYS(               XK_4,                      3)
        TAGKEYS(               XK_5,                      4)
        TAGKEYS(               XK_6,                      5)
        TAGKEYS(               XK_7,                      6)
        TAGKEYS(               XK_8,                      7)
        TAGKEYS(               XK_9,                      8)
        { MODKEY|ControlMask,  XK_q,                    quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = term } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

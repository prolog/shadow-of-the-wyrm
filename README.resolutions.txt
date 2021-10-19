Shadow of the Wyrm was built curses-first, and its logical size is 80x25 in text
mode.  The tiles are 16x24. This means that the game is naturally 
80*16 x 24*25 = 1280x600.

When playing using SDL graphics, the game supports both windowed and fullscreen
modes.  These are controlled in swyrm.ini by the setting 
display_sdl_window_mode.  Fake (desktop) fullscreen is currently the default.
Real fullscreen (with a video mode switch) is also available, and documented
in swyrm.ini.

The sprites use integer scaling in SDL to ensure they look good.  SDL will
attempt to scale using integer values, so the game will appear letterboxed 
in some way to fit to your resolution.  

If you are trying to make things look larger, you have a few options:

 1. Reduce your resolution to something close to 1280x600, e.g. 1366x768
 2. Turn on integer scaling (display_sdl_integer_scaling in swyrm.ini)
 3. If you're using Windows, in your display properties, you can increase
    the size of text, apps, and other items
    `
You can also set display_sdl_window_mode=0 (to use windowed display) and turn
integer scaling off, and then expand the window to get the size that you want,
though this may provide undesirable artifacts.

require ${OEBASE}/arago-oe-dev/recipes/libsdl/libsdl-1.2.14.inc

COMPATIBLE_MACHINE = "(dm814x-z3|dm814x-evm)"

PR = "${INC_PR}.8"

EXTRA_OECONF = " \
  --disable-static --disable-debug --disable-cdrom --enable-threads --enable-timers --enable-endian \
  --enable-file --disable-oss --enable-alsa --disable-esd --disable-arts \
  --disable-diskaudio --disable-nas --disable-esd-shared --disable-esdtest \
  --disable-mintaudio --disable-nasm --disable-video-x11 --disable-video-dga \
  --enable-video-fbcon --disable-video-directfb --disable-video-ps2gs \
  --disable-video-xbios --disable-video-gem --disable-video-dummy \
  --disable-video-opengl --enable-input-events --enable-pthreads \
  --disable-video-picogui --disable-video-qtopia --disable-dlopen \
  --disable-input-tslib --disable-video-ps3 --disable-rpath \
"

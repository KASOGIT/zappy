#configuration
CONFIG +=  shared qpa no_mocdepend release qt_no_framework
host_build {
    QT_ARCH = x86_64
    QT_TARGET_ARCH = x86_64
} else {
    QT_ARCH = x86_64
    QMAKE_DEFAULT_LIBDIRS  = 
    QMAKE_DEFAULT_INCDIRS  = 
}
QT_CONFIG +=  minimal-config small-config medium-config large-config full-config gtk2 gtkstyle fontconfig evdev xlib xrender xcb-plugin xcb-qt xcb-xlib xcb-sm xkbcommon-qt accessibility-atspi-bridge linuxfb kms c++11 c++14 accessibility egl egl_x11 eglfs opengl shared qpa reduce_exports reduce_relocations clock-gettime clock-monotonic posix_fallocate mremap getaddrinfo ipv6ifname getifaddrs inotify eventfd threadsafe-cloexec png system-freetype harfbuzz system-zlib nis cups iconv glib dbus dbus-linked openssl xcb xinput2 rpath alsa pulseaudio gstreamer-0.10 icu concurrent audio-backend release

#versioning
QT_VERSION = 5.6.1
QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 6
QT_PATCH_VERSION = 1

#namespaces
QT_LIBINFIX = 
QT_NAMESPACE = 

QT_EDITION = OpenSource
QT_LICHECK = licheck64
QT_RELEASE_DATE = 2016-06-02

QT_COMPILER_STDCXX = 199711
QT_GCC_MAJOR_VERSION = 4
QT_GCC_MINOR_VERSION = 9
QT_GCC_PATCH_VERSION = 1
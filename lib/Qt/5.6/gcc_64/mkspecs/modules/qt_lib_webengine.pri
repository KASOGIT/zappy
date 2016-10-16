QT.webengine.VERSION = 5.6.1
QT.webengine.MAJOR_VERSION = 5
QT.webengine.MINOR_VERSION = 6
QT.webengine.PATCH_VERSION = 1
QT.webengine.name = QtWebEngine
QT.webengine.module = Qt5WebEngine
QT.webengine.libs = $$QT_MODULE_LIB_BASE
QT.webengine.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtWebEngine
QT.webengine.frameworks =
QT.webengine.bins = $$QT_MODULE_BIN_BASE
QT.webengine.libexecs = $$QT_MODULE_LIBEXEC_BASE
QT.webengine.plugins = $$QT_MODULE_PLUGIN_BASE
QT.webengine.imports = $$QT_MODULE_IMPORT_BASE
QT.webengine.qml = $$QT_MODULE_QML_BASE
QT.webengine.depends = core gui qml quick webenginecore
QT.webengine.run_depends = quick_private gui_private core_private
QT.webengine.module_config = v2
QT.webengine.DEFINES = QT_WEBENGINE_LIB
QT_MODULES += webengine

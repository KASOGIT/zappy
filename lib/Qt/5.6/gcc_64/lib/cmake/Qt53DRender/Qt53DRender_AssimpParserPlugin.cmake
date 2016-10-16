
add_library(Qt5::AssimpParserPlugin MODULE IMPORTED)

_populate_3DRender_plugin_properties(AssimpParserPlugin RELEASE "sceneparsers/libassimpsceneparser.so")

list(APPEND Qt53DRender_PLUGINS Qt5::AssimpParserPlugin)

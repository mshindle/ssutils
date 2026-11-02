add_library(cgic STATIC cgic/cgic.c cgic/cgic.h)
target_include_directories(cgic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cgic)

add_library(md5 STATIC md5/md5.c md5/md5.h)
target_include_directories(md5 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/md5)

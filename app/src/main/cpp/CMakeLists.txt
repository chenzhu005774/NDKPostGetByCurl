
cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             CommonTools.cpp
             JniUtils.cpp
             native-lib.cpp )

include_directories(
                    #include/jsoncpp
                    include/curl
                      )

#add_library(curl STATIC IMPORTED)
#set_target_properties(curl
 #      PROPERTIES IMPORTED_LOCATION
  #      ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libcurl.a)

#add_library(jsoncpp STATIC IMPORTED)
#set_target_properties(jsoncpp
 #       PROPERTIES IMPORTED_LOCATION
 #       ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libjsoncpp.a)


 add_library( curl
         SHARED
         IMPORTED )

 set_target_properties( curl
         PROPERTIES IMPORTED_LOCATION
         ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libcurl.so )

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )



target_link_libraries( # Specifies the target library.
                       native-lib
                       #jsoncpp
                       curl

                       ${log-lib} )
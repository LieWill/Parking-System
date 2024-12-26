# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\park2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\park2_autogen.dir\\ParseCache.txt"
  "park2_autogen"
  )
endif()

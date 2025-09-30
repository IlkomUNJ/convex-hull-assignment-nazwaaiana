# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Tugass_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Tugass_autogen.dir/ParseCache.txt"
  "Tugass_autogen"
  )
endif()

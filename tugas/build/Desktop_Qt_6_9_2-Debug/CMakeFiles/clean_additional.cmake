# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/tugas_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/tugas_autogen.dir/ParseCache.txt"
  "tugas_autogen"
  )
endif()

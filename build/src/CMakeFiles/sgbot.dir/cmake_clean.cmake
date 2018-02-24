file(REMOVE_RECURSE
  "libsgbot.pdb"
  "libsgbot.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/sgbot.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

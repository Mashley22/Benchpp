function(add_sample TARGET_NAME)

  target_link_libraries(${TARGET_NAME}
    PUBLIC
      benchpp_with_main
  )

  target_compile_options(${TARGET_NAME}
    PRIVATE
      -Wall
      -Wextra
      -Wpedantic
      -Werror
      -Wshadow
      -Wconversion
      -Wsign-conversion
  )
  
  set_target_properties(${TARGET_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )

  set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${TARGET_NAME}
  )

  target_include_directories(${TARGET_NAME}
    PRIVATE
      ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/utils/include
  )

endfunction()

add_subdirectory(post_vs_pre_increment)

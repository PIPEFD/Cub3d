if(EXISTS "/home/pipe/Cub42/build/tests/unit_tests[1]_tests.cmake")
  include("/home/pipe/Cub42/build/tests/unit_tests[1]_tests.cmake")
else()
  add_test(unit_tests_NOT_BUILT unit_tests_NOT_BUILT)
endif()
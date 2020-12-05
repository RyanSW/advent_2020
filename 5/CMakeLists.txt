set(NUMBER 5)

project(Puzzle${NUMBER})

add_executable(puzzle${NUMBER} main.cpp)

add_custom_target(run_puzzle${NUMBER}
  COMMAND puzzle${NUMBER} input.txt
  DEPENDS puzzle${NUMBER}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

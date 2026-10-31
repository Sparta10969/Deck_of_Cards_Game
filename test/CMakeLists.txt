find_package(Catch2 3 REQUIRED)

add_executable(tests card_tests.cpp deck_of_cards_tests.cpp)


target_link_libraries(tests lib Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(tests)
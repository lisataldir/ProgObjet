if(EXISTS "/home/lisa/Documents/M1 CHPS/Semestre 1/Programmation Object/chps2023-main/TDs/TD2/build/Test.exe[1]_tests.cmake")
  include("/home/lisa/Documents/M1 CHPS/Semestre 1/Programmation Object/chps2023-main/TDs/TD2/build/Test.exe[1]_tests.cmake")
else()
  add_test(Test.exe_NOT_BUILT Test.exe_NOT_BUILT)
endif()

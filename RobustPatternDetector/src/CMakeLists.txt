add_executable(my_demo
main.cpp
CameraCalibration.cpp
CameraCalibration.hpp
Pattern.cpp
Pattern.hpp
PatternDetector.cpp
PatternDetector.hpp
)

target_link_libraries( my_demo ${OpenCV_LIBRARIES} )
     
install (TARGETS my_demo DESTINATION bin)

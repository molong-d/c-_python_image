cmake_minimum_required(VERSION 2.8)
project(python_test)

set(CMAKE_CXX_STANDARD 14) 

include_directories(
    /home/l/anaconda3/envs/yolo/include/python3.8
)

# 寻找pybind11
list(APPEND CMAKE_PREFIX_PATH "/usr/local/include/dlib/external/pybind11")
find_package(pybind11 CONFIG REQUIRED)


find_package(OpenCV REQUIRED)



# 如果你已经安装了Pybind11，你可以使用find_package方式
# find_package(pybind11 REQUIRED)

# find_package(pybind11 REQUIRED) #找到依赖

# add_subdirectory(/usr/local/include/dlib/external/pybind11)

# pybind11_add_module(python_test main.cpp)

add_executable(python_test
    main.cpp)

# target_link_libraries(python_test  pybind11::embed)   

target_link_libraries(python_test ${OpenCV_LIBS})
    
target_link_libraries(python_test
    /home/l/anaconda3/envs/yolo/lib/libpython3.8.so
    # python3.8 numpy
)


# cmake_minimum_required(VERSION 2.8)
# project(python_test)
# include_directories(
#     /home/jinye/anaconda3/envs/tensorflow-gpu/include/python3.7m
# )
# add_executable(main
#     main.cpp)
# target_link_libraries(main
#     /home/jinye/anaconda3/envs/tensorflow-gpu/lib/libpython3.7m.so
# )

# // file name: CMakeLists.txt
# cmake_minimum_required(VERSION 3.5)
# project(test_pybind)


# add_executable(cpp_call_py cpp_call_py.cc test_add.py)

# target_include_directories(cpp_call_py
#   PUBLIC
#   /usr/include/python3.8
# )

# target_link_libraries(cpp_call_py
#   PUBLIC
#   /home/ubuntu/miniconda3/lib/libpython3.8.so
# )
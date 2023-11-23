#include <Python.h>
#include <iostream>
#include <opencv2/opencv.hpp>

// #include <numpy/arrayobject.h>
// #include </usr/local/include/dlib/external/pybind11/include/pybind11/embed.h>



int main(int argc, char *argv[]) {
    


// version 2

    // 初始化 Python 解释器
    Py_Initialize();

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/l/slam/cv/YOLO/YOLO8/ultralytics-1113/')"); //显示绝对路径文件夹


    // 导入 Python 模块和函数
    PyObject* pModule = PyImport_ImportModule("c++_python_API-1");  // 替换为你的 Python 模块名
    if (!pModule) {
        std::cout << "Failed to import Python module!" << std::endl;
        return -1;
    }

    PyObject* pFunc = PyObject_GetAttrString(pModule, "process_image");  // 替换为你的 Python 函数名

    // 读取图像
    cv::Mat image = cv::imread("/home/l/slam/cv/YOLO/YOLO8/ultralytics-1113/data/bus.jpg");  // 替换为你的图像路径和名称
    if (image.empty()) {
        std::cout << "Failed to read the image!" << std::endl;
        return -1;
    }

    // 输出图片的宽度、高度和通道数
    std::cout << "图像宽度: " << image.cols << std::endl;
    std::cout << "图像高度: " << image.rows << std::endl;
    std::cout << "通道数: " << image.channels() << std::endl;

    // 转换为灰度图像
    //核心 转成为 灰度图片传输
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_RGB2GRAY);

    // 输出图片的宽度、高度和通道数
    std::cout << "图像宽度: " << grayImage.cols << std::endl;
    std::cout << "图像高度: " << grayImage.rows << std::endl;
    std::cout << "通道数: " << grayImage.channels() << std::endl;

    image = grayImage;

    // 转换图像数据为 Python 字节对象
    PyObject* pImage = PyBytes_FromStringAndSize((const char*)image.data, image.total());
    if (!pImage) {
        std::cout << "Failed to convert image data to Python bytes object!" << std::endl;
        Py_DECREF(pModule);
        return -1;
    }

    // 调用 Python 函数并传递图像数据
    PyObject* pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, pImage);
    PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
    if (!pResult) {
        std::cout << "Failed to call Python function!" << std::endl;
        Py_DECREF(pModule);
        Py_DECREF(pImage);
        Py_DECREF(pArgs);
        return -1;
    }
    
    // 将 Python 返回的对象转换为二维数组
    Py_ssize_t rows, cols;
    PyObject* pResultIter = PyObject_GetIter(pResult);
    PyObject* pRow = PyIter_Next(pResultIter);
    rows = PyList_Size(pRow);
    cols = PyList_Size(pResult);
    std::cout << "返回的矩阵数据：" << std::endl;
    for (Py_ssize_t i = 0; i < rows; ++i) {
        for (Py_ssize_t j = 0; j < cols; ++j) {
            PyObject* pItem = PyList_GetItem(PyList_GetItem(pResult, j), i);
            int value = PyLong_AsLong(pItem);
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }


    // // numpy  
    // // 解析 Python 返回的矩阵数据
    // PyObject* pResultArray = reinterpret_cast<PyArrayObject*>(pResult);
    // unsigned char* resultData = static_cast<unsigned char*>(PyArray_DATA(pResultArray));
    // npy_intp* resultDims = PyArray_DIMS(pResultArray);

    // // 打印矩阵数据
    // std::cout << "返回的矩阵数据：" << std::endl;
    // for (int i = 0; i < resultDims[0]; ++i) {
    //     for (int j = 0; j < resultDims[1]; ++j) {
    //         unsigned char value = resultData[i * resultDims[1] + j];
    //         std::cout << static_cast<int>(value) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    
    std::cout << "！！！！！！: " << std::endl;   

    // // 清理内存
    // Py_DECREF(pImage);
    // Py_DECREF(pArgs);
    // Py_DECREF(pResult);

    // 清理内存
    Py_DECREF(pResultIter);
    Py_DECREF(pResult);
    Py_DECREF(pImage);
    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);


    // 关闭 Python 解释器
    Py_DECREF(pModule);
    Py_Finalize();

  


// version 1
/*
    Py_Initialize();

    // 判断初始化是否成功
    if(!Py_IsInitialized())
    {
        std::cout << "Python init failed!" << std::endl;
        return -1;
    }

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/l/slam/cv/YOLO/YOLO8/ultralytics-1113/')"); //显示绝对路径文件夹

    // 导入 Python 文件
    PyObject* pModule = PyImport_ImportModule("c++_python_API-1");
    if (!pModule) {
        std::cout << "Can not open python file!!!!!" << std::endl;
        return -1;
    }

    // 读取图片
    cv::Mat image = cv::imread("/home/l/slam/cv/YOLO/YOLO8/ultralytics-1113/data/zidane.jpg");
    if (image.empty()) {
        std::cout << "Failed to read the image!" << std::endl;
        return -1;
    }

    // 输出图片的宽度、高度和通道数
    std::cout << "图像宽度: " << image.cols << std::endl;
    std::cout << "图像高度: " << image.rows << std::endl;
    std::cout << "通道数: " << image.channels() << std::endl;

    //可视化
    cv::namedWindow("Image", cv::WINDOW_NORMAL);
    cv::imshow("Image", image);
    cv::waitKey(0);

    // 转换图像数据为 Python 字节对象
    PyObject* pImage = PyBytes_FromStringAndSize((const char*)image.data, image.total());


    // 获取转换后的矩阵大小
    Py_ssize_t size = PyBytes_Size(pImage);
    std::cout << "转换后的矩阵大小: " << size << std::endl;
    // 释放 Python 字节对象
    Py_XDECREF(pImage);


    // 获取 Python 函数对象
    PyObject* pFunc = PyObject_GetAttrString(pModule, "process_image");


    // 调用 Python 函数并传递图像数据
    PyObject* pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, pImage);
    PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
*/


/*

    if (pFunc && PyCallable_Check(pFunc)) {
        // 调用 Python 函数并传递图像数据
        PyObject* pResult = PyObject_CallFunctionObjArgs(pFunc, pImage, NULL);
        // 处理 Python 返回的结果
        if (pResult != NULL) {
            // 将 Python 返回的结果转换为 C++ 数据
            if (PyUnicode_Check(pResult)) {
                // 如果返回结果是字符串
                const char* result_str = PyUnicode_AsUTF8(pResult);
                std::cout << "Received result from Python: " << result_str << std::endl;
            } else {
                // 如果返回结果不是字符串，根据实际情况进行处理
                std::cout << "Received result from Python is not a string" << std::endl;
            }
            Py_DECREF(pResult);
        }else {
            PyErr_Print(); 
            std::cout << "Failed to call the function!!!!!" << std::endl;
        }
    } else {
        std::cout << "Function is not callable!" << std::endl;
    }


    Py_DECREF(pFunc);
    Py_DECREF(pModule);
    Py_DECREF(pImage);
    Py_Finalize();
*/



  return 0;


}

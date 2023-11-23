import time
from PIL import Image
import numpy as np
from ultralytics import YOLO
import cv2
import matplotlib.pyplot as plt
import torch


def process_image(image_data):

    print(torch.cuda.is_available())  # 查看CUDA是否可用
    print(torch.cuda.device_count())  # 查看可用的CUDA数量
    print(torch.version.cuda)         # 查看CUDA的版本号
    print(torch.__version__)          # 查看torch的版本号
    print(torch.cuda.is_available())  # 查看torch的CUDA是否可用





    # 将接收到的图像数据转换为 numpy 数组
    # image_array = np.frombuffer(image_data, dtype=np.uint8)
    image_array = np.frombuffer(image_data, dtype=np.uint8, count=len(image_data))

    # 根据图像尺寸还原图像
    width = 810
    height = 1080
    channels = 1

    # 查看image_array数组的大小
    # print("image_array的形状：", image_array.shape)
    image = image_array.reshape((height, width, channels))

    # 转换颜色空间为BGR
    image_bgr = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
    # 显示图像

    # plt.imshow(image_bgr)
    # plt.axis('off')
    # plt.show()

    # Load the model  
    model = YOLO("/home/l/slam/cv/YOLO/YOLO8/ultralytics-1113/weights/yolov8n.pt") 
   
    start = time.perf_counter()
    ######## 实际程序开始 ##########

    results = model(image_bgr)

    detection_result = []



    for r in results:
        detection_result= r.boxes.data.cpu().numpy()
        # print('aaaaaaaaa',detection_result) 
        # print('bbbbbbbbb',detection_result.shape) 

    # print('转化前数组类型',type(detection_result)) 
    # print('数组数据为',detection_result) 

    # ##注意需要返回list数组
    detection_result_list = detection_result.tolist() 
    # print('转化后数组类型',type(detection_result_list)) 
    # print('数组数据为',detection_result_list) 

    ######## 实际程序结束 ##########
    end = time.perf_counter()
    print("运行时间为", round(end - start), 'seconds')
    

    #返回数据
    return  detection_result_list



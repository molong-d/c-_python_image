import torch
import sys

def printHello():
    print(sys.version)
    
    print(torch.cuda.is_available())  # 查看CUDA是否可用
    print(torch.cuda.device_count())  # 查看可用的CUDA数量
    print(torch.version.cuda)         # 查看CUDA的版本号
    print(torch.__version__)          # 查看torch的版本号
    print(torch.cuda.is_available())  # 查看torch的CUDA是否可用

    print("hello world!+++")

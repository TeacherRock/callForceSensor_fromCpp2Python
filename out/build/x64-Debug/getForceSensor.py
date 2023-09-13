import ctypes
from ctypes import cdll, c_char_p, c_float, CDLL
import time

dll = CDLL('ForceSensor_dll.dll', winmode=0)
dll.getForceData.restype = ctypes.POINTER(ctypes.c_ushort)
dll.addThread_ForceSensor(4)

data_main = dll.getForceData()
inidata = [data_main[i] for i in range(6)]


while True:
    data_main = dll.getForceData()
    array = [data_main[i] for i in range(6)]
    # print("Before normaliztion : ", array)
    array[0] = (array[0] - inidata[0]) / 8192 * 200
    array[1] = (array[1] - inidata[1]) / 8192 * 200
    array[2] = (array[2] - inidata[2]) / 8192 * 200
    array[3] = (array[3] - inidata[3]) / 8192 * 20
    array[4] = (array[4] - inidata[4]) / 8192 * 20
    array[5] = (array[5] - inidata[5]) / 8192 * 20
    print(" After normaliztion : ", array)
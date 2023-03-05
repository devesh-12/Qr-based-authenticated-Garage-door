import cv2
import numpy as np
from pyzbar.pyzbar import decode
import time
import serial


#img = cv2.imread()
cap=cv2.VideoCapture(0)
cap.set(3,640)
cap.set(4,480)

if __name__ == '__main__': 
    ser = serial.Serial('/dev/ttyUSB0',9600,timeout=1)
    ser.flush()

    while True:
        success, img = cap.read()
        for barcode in decode(img):
            print(barcode.data)
            myData = barcode.data.decode('utf-8')
            ser.write(b"led\n")
            time.sleep(1)
            print(myData)
            pts = np.array([barcode.polygon],np.int32)
            pts = pts.reshape((-1,1,2))
            cv2.polylines(img,[pts],True,(255,0,255),5)
            pts2 = barcode.rect
            cv2.putText(img,myData,(pts2[0],pts2[1]),cv2.FONT_HERSHEY_PLAIN,0.9,(255,0,255),2)
        
        cv2.imshow('Result',img)
        cv2.waitKey(1) 

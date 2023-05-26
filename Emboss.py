import cv2
import numpy as np

def moveKernel(img, EmbossKernel, dst):
    for i in range(img.shape[0] - 2):
        for j in range(img.shape[1] - 2):
            SumOfIndex = 0.0
            for m in range(3):
                for n in range(3):
                    ValueOne = i + m
                    ValueTwo = j + n
                    SumOfIndex += EmbossKernel[m, n] * img[ValueOne, ValueTwo]
            dst[i, j] = SumOfIndex

img = cv2.imread("test.jpg", 0)
EmbossKernel = np.array([[-2, -1, 0], [-1, 1, 1], [0, 1, 2]])

dstRow = img.shape[0] - 3 + 1
dstCol = img.shape[1] - 3 + 1
dst = np.zeros((dstRow, dstCol), dtype=np.uint8)

if img is None:
    print("Error reading robot image")
else:
    print("rows:", img.shape[0])
    print("cols:", img.shape[1])

    cv2.imshow("inputWindow", img)
    moveKernel(img, EmbossKernel, dst)
    cv2.imshow("blur", dst)

    print("rows:", dst.shape[0])
    print("cols:", dst.shape[1])

    cv2.waitKey(0)
    cv2.destroyAllWindows() 

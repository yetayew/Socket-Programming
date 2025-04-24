import os
import numpy as np
import cv2
import pickle


dir = 'C:\\Users\\user\\3D Objects\\Drowsy\\eyes'

catagories = ['Closed_Eyes','Open_Eyes']

data = []

for catagory in catagories:
    path = os.path.join(dir,catagory)
    label = catagories.index(catagory)

    for img in os.listdir(path):
        imgpath = os.path.join(path,img)
        closed_eye =cv2.imread(imgpath,0)
        try:
            closed_eye =cv2.resize(closed_eye,(50,50))
            image = np.array(closed_eye).flatten()
            data.append([image,label])
        except Exception as e:
            pass

pick_in =open('data1.pickle','wb')
pickle.dump(data,pick_in)
pick_in.close()
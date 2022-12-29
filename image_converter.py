from PIL import Image
from numpy import asarray

numpydata = asarray(Image.open('hello-kitty.jpg'))

with open('hk.txt','w') as file:
    for i in range(len(numpydata)):
        for j in range(len(numpydata[0])):
            adc1 = numpydata[i][j][0] << 16
            adc2 = numpydata[i][j][1] << 8
            adc3 = numpydata[i][j][2]
            
            color = adc1 | adc2 | adc3
            
            file.write(f'{hex(color)[2:]}\n')
            
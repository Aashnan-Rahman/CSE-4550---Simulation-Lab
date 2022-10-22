
# -*- coding: utf-8 -*-
"""
Created on Sat Oct  22 10:08:27 2022

@author: Aashnan
"""

import pandas as pd
import matplotlib.pyplot as plt
 
# take data
data = pd.read_csv("aash_1.csv")

# plot the dataframe
#data.plot(x="Traffic Intensity", y=["Average Queue Delay"], kind="line", figsize=(20, 10))
#data.plot(x="Traffic Intensity", y=["Average Queue Length"], kind="line", figsize=(20, 10))
data.plot(x="Traffic Intensity", y=["Average System Delay"], kind="line", figsize=(20, 10))
plt.xlabel('Traffic Intensity')


#plt.ylabel('Avg Queue Delay')
#plt.ylabel('Avg Queue Length')
plt.ylabel('Avg System Delay')
# print bar graph
plt.show()

#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 22 14:58:23 2022

@author: Aashnan
"""

import pandas as pd
import matplotlib.pyplot as plt
 
# take data
data = pd.read_csv("aash_3.csv")

# plot the dataframe

#data.plot(x="Traffic Intensity", y=["Average Queue Delay(Queue 1)","Average Queue Delay(Queue 2)"], kind="line", figsize=(20, 10))
#data.plot(x="Traffic Intensity", y=["Average Queue Length(Queue 1)","Average Queue Length(Queue 2)"], kind="line", figsize=(20, 10))
data.plot(x="Traffic Intensity", y=["Average System Delay(Queue 1)","Average System Delay(Queue 2)"], kind="line", figsize=(20, 10))
plt.xlabel('Traffic Intensity')

#plt.ylabel('Average Queue Delay')
#plt.ylabel('Average Queue Length')
plt.ylabel('Average System Delay')

# print bar graph
plt.show() 
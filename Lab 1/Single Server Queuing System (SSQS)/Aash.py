#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Sep  6 03:08:27 2022

@author: sanz
"""


import pandas as pd
import matplotlib.pyplot as plt
 
# take data
data = pd.read_csv("out.csv")

data=data.dropna()  # Removing the missing Values 
df = pd.DataFrame(data, columns=["Ratio", "Avg Delay", "Avg Queue Length"])
 
# plot the dataframe
df.plot(x="Ratio", y=["Avg Delay", "Avg Queue Length"], kind="line", figsize=(20, 10))
plt.xlabel('Ratio')
plt.ylabel('Avg Delay & Avg Queue Length')
# print bar graph
plt.show()
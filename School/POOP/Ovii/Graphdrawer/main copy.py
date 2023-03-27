import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from pyparsing import java_style_comment

df = pd.read_csv("Minres.csv")

x = df.x

y_1 = df.y_1
y_2 = df.y_2

d = np.array([1600,
1625,
1650,
1675,
1700,
1725,
1750,
1775,
1800,
1825,
1850,
1875,
1900,
1925,
1950,
1975,
2000,
2025,
2050,
2075,
2100,
2125,
2150,
2175,
2200,
2225,
2250,
2275,
2300,
2325,
2350,
2375,
2400,
2425,
2450,
2475,
2500,
2525,
2550,
2575,
2600,
2625,
2650,
2675,
2700
])

fraser = []

i=1
j=0

while j <= len(d):
    j = i+1
    res = (d[i]+d[j])/2
    i += 1
    print(res)


import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("Book2.csv")

x = df.x

y_1 = df.y_1
y_2 = df.y_2

fig, ax = plt.subplots()
plt.plot(x , y_1, label = 'Dip angle')
plt.plot(x , y_2, label = 'Fraser filtered graph')
plt.legend(loc = 'upper left')
plt.grid()
plt.title('Fraser filtered graph of dip angle')
plt.axhline(0, color = 'black')
plt.xlabel("Position [m]")
plt.ylabel("Imag degrees")
plt.show()

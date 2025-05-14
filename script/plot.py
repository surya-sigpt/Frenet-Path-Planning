import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("output/frenetpath.csv")
df1 = pd.read_csv("output/cubicspline.csv")

x = np.array([0.0, 10.0, 20.5, 35.0, 70.5])
y = np.array([0.0, -6.0, 5.0, 6.5, 0.0])

Obstacle = np.array([
    [20.0, 10.0],
    [30.0, 6.0],
    [30.0, 8.0],
    [35.0, 8.0],
    [50.0, 3.0]
])

fx = np.array(df.x)
fy = np.array(df.y)

cx = np.array(df1.rx)
cy = np.array(df1.ry)

plt.plot(Obstacle[:, 0], Obstacle[:, 1], 'x')
plt.plot(fx, fy, color="red")
plt.plot(x, y, color="green")
plt.plot(cx, cy, color="blue")

plt.show()

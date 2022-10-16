import matplotlib.pyplot as plt
import numpy as np

double_data = np.loadtxt("double.dat")
n = double_data[:, 0]
double_recursion = double_data[:, 1]
double_direct = double_data[:, 2]

float_data = np.loadtxt("float.dat")
float_recursion = float_data[:, 1]
float_direct = float_data[:, 2]

fig, ax = plt.subplots(1, 1, figsize=(5, 5), dpi=200)

ax.plot(n, np.abs(float_direct-float_recursion), label="| float_direct - float_recursion |" )
# ax.plot(n, float_direct, label="float direct",lw=1)
# ax.plot(n, float_recursion, label="float recursion",lw=1 )

ax.plot(n, np.abs(double_direct-double_recursion), label="| double_direct - double_recursion |" )
# ax.plot(n, double_direct, label="double direct",lw=1)
# ax.plot(n, double_recursion, label="double recursion",lw=1 )

ax.set(xlabel="n", ylabel="value")
ax.legend()
plt.savefig("./p1_results.png", dpi=300)

# plots for the second question
data = np.loadtxt("./ps2.dat")

x_pos = data[:, 0]  # - np.mean(data[:, 0])
y_pos = data[:, 1]  # - np.mean(data[:, 1])
z_pos = data[:, 2]  # - np.mean(data[:, 2])

x_vel = data[:, 3]  # - np.mean(data[:, 3])
y_vel = data[:, 4]  # - np.mean(data[:, 4])
z_vel = data[:, 5]  # - np.mean(data[:, 5])

fig = plt.figure(figsize=(5, 5), dpi=200)
ax = plt.axes(projection="3d")
p = ax.scatter(
    x_pos,
    y_pos,
    z_pos,
    c=np.sqrt(x_vel**2 + y_vel**2 + z_vel**2),
    s=0.5,
    cmap=plt.cm.magma,
)
fig.colorbar(p, ax=ax)
ax.set(xlabel="x (m)", ylabel="y (m)", zlabel="z (m)")
plt.savefig("./p2_results.png", dpi=300)

# positions = np.vstack([x_pos, y_pos, z_pos]).T # 1908 x 3 array of the positions
# velocities = np.vstack([x_vel, y_vel, z_vel]).T # 1908 x 3 array of the velcoties
# cros_products = np.cross(positions, velocities) # 1908 x 3 array of the velcoties
# ang_momentum = np.sum(cros_products , axis=0) # 3 - component vector, made by summing each column
# print(ang_momentum)
# tensor = np.array(
#     [[np.sum(y_pos**2 + z_pos**2), np.sum(-x_pos*y_pos), np.sum(-x_pos*z_pos)],
#     [np.sum(-y_pos*x_pos), np.sum(x_pos**2 + z_pos**2), np.sum(-y_pos*z_pos)],
#     [np.sum(-x_pos*z_pos), np.sum(-y_pos*z_pos), np.sum(x_pos**2 + y_pos**2)]]
# )

# test = np.linalg.solve(tensor, ang_momentum)
# print(2*np.pi / np.sqrt(np.sum(np.square(test))))
# print(ang_momentum )
# print(test)
# print(tensor)

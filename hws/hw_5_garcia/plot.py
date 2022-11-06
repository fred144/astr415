import matplotlib.pyplot as plt
import numpy as np
import os

print("plotting script")
p1_parent_dir = "problem_1_data/"
p1_data_set = sorted(os.listdir(p1_parent_dir), reverse=True)

fig, ax = plt.subplots(
    nrows=5, ncols=3, dpi=400, figsize=(10, 8), sharex=True, sharey=True
)
plt.subplots_adjust(hspace=0, wspace=0)

step_sizes = []
euler_minus_exact = []
frog_minus_exact = []
rk4_minus_exact = []

for i, ds in enumerate(p1_data_set):

    step_size = float(ds.split("_")[-1].split(".d")[0])
    data = np.loadtxt(p1_parent_dir + ds)
    euler = data[:, 1]
    frog = data[:, 2]
    rk4 = data[:, 3]

    anal_t = np.linspace(data[:, 0][0], data[:, 0][-1], 100)
    anal = np.sin(anal_t)

    step_sizes.append(step_size)
    euler_minus_exact.append(np.abs(anal[-1] - euler[-1]))
    frog_minus_exact.append(np.abs(anal[-1] - frog[-1]))
    rk4_minus_exact.append(np.abs(anal[-1] - rk4[-1]))

    for col in range(3):
        ax[i, col].plot(anal_t, anal, color="red", zorder=0)

        if i == 0 and col == 1:
            ax[i, col].plot(
                anal_t, np.sin(anal_t), color="red", zorder=0, label="analytic"
            )
            ax[i, col].legend(loc="upper center")

    ax[i, 0].scatter(
        data[:, 0], euler, s=4, alpha=0.5, label="h = {}".format(step_size)
    )
    ax[i, 1].scatter(
        data[:, 0],
        frog,
        s=4,
        alpha=0.5,
    )
    ax[i, 2].scatter(
        data[:, 0],
        rk4,
        s=2,
        alpha=0.5,
    )

    ax[i, 0].legend(loc="upper left")
    ax[i, 1].tick_params(axis="both", direction="in", which="both")
    ax[i, 0].tick_params(axis="both", direction="in", which="both")

ax[0, 0].set_title("Euler's")
ax[0, 1].set_title("Leap Frog")
ax[0, 2].set_title("Runge Kutta")

ax[4, 1].set_xlabel("time t")
ax[2, 0].set_ylabel("position x(t)")

plt.savefig("./p1_b.png", bbox_inches='tight')

fig, ax = plt.subplots(nrows=1, ncols=1, dpi=400, figsize=(4, 4))
ax.plot(step_sizes, euler_minus_exact, label="euler")
ax.plot(step_sizes, frog_minus_exact, ls="--", label="frog")
ax.plot(step_sizes, rk4_minus_exact, label="rk4")
ax.set(
    xscale="log",
    yscale="log",
    xlabel="step size h ",
    ylabel="|exact(15) - numerical(15)|",
)
# ax.plot(step_sizes, np.sqrt(step_sizes), label="sqrt(h)")
ax.invert_xaxis()
ax.legend()

plt.savefig("./p1_c.png", bbox_inches='tight')


def pot(x, y):
    return -1 / np.sqrt(1 + 2 * x**2 + 2 * y**2)


frog_data_dir = "./problem_2_data/frog/"
frog_data_set = sorted(os.listdir(frog_data_dir), reverse=True)

rk4_data_dir = "./problem_2_data/rk4/"
rk4_data_set = sorted(os.listdir(rk4_data_dir), reverse=True)

fig, ax = plt.subplots(
    nrows=4, ncols=2, dpi=400, figsize=(6, 12), sharex=True, sharey=True
)
plt.subplots_adjust(hspace=0, wspace=0)


for i, (ds_frog, ds_rk4) in enumerate(zip(frog_data_set, rk4_data_set)):
    step_size = float(ds_frog.split("_")[-1].split(".d")[0])
    frog_data = np.loadtxt(frog_data_dir + ds_frog)
    rk4_data = np.loadtxt(rk4_data_dir + ds_rk4)

    time = frog_data[:, 0]
    frog_x = frog_data[:, 1]
    frog_y = frog_data[:, 2]
    frog_x_vel = frog_data[:, 3]
    frog_y_vel = frog_data[:, 4]

    frog_kinetic_e = (frog_x_vel**2 + frog_y_vel**2) / 2
    frog_potential_e = pot(frog_x, frog_y)

    rk4_x = rk4_data[:, 1]
    rk4_y = rk4_data[:, 2]
    rk4_x_vel = rk4_data[:, 3]
    rk4_y_vel = rk4_data[:, 4]

    rk4_kinetic_e = (rk4_x_vel**2 + rk4_y_vel**2) / 2
    rk4_potential_e = pot(rk4_x, rk4_y)

    ax[i, 0].plot(frog_x, frog_y, lw=1, color="black")
    ax[i, 1].plot(rk4_x, rk4_y, lw=1, color="black", label="h = {}".format(step_size))

    ax[i, 1].tick_params(axis="both", direction="in", which="both")
    ax[i, 0].tick_params(axis="both", direction="in", which="both")

    ax[i, 1].legend(loc="upper right")

    # ax[i, 0].inset_axes([1, 1, 1, 1])
    energy_ax = ax[i, 1].inset_axes([1.2, 0, 1, 1])

    energy_ax.plot(time, frog_kinetic_e + frog_potential_e, label="leapfrog")
    energy_ax.plot(time, rk4_kinetic_e + rk4_potential_e, label="rk4 ")

    energy_ax.set(ylim=(-1, 0.3), xlabel="time")

    if i == 0:
        energy_ax.legend()
        energy_ax.tick_params(axis="both", direction="in", which="both")
        energy_ax.set(title="Total Energy = KE + $\Phi$")


fig.text(0.5, 0.08, r"x", ha="center")
fig.text(0.01, 0.5, r"y", va="center", rotation="vertical")
ax[0, 0].set_title("Leap Frog")
ax[0, 1].set_title("Runge Kutta")

plt.savefig("./p2_ab.png", dpi=400, bbox_inches='tight')



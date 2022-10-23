from tkinter.messagebox import RETRY
from black import read_pyproject_toml
import numpy as np
import matplotlib.pyplot as plt


def reyleigh(x):
    y = x * np.exp(-(x ** 2) / 2)
    return y


problem_1_data = np.loadtxt("./p1_data.txt")
uniform_deviate = problem_1_data[:, 0]
rayleig_deviate = problem_1_data[:, 1]
num_bins = 100

rey_count, bin_edges = np.histogram(rayleig_deviate, num_bins, density=True)
right_edges = bin_edges[1:]
left_edges = bin_edges[:-1]
bin_ctrs = 0.5 * (left_edges + right_edges)
uni_count, uni_bin_edges = np.histogram(uniform_deviate, num_bins, density=True)
unibin_ctrs = 0.5 * (uni_bin_edges[:-1] + uni_bin_edges[1:])

fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(5, 4), dpi=200)

ax.plot(
    unibin_ctrs,
    uni_count,
    drawstyle="steps-mid",
    linewidth=1,
    alpha=0.4,
    color="grey",
    label="Uniform",
)
ax.fill_between(unibin_ctrs, uni_count, step="mid", alpha=0.4, color="grey")

ax.plot(
    bin_ctrs,
    rey_count,
    drawstyle="steps-mid",
    linewidth=1,
    alpha=0.8,
    color="red",
    label="Transformed Rayleigh",
)
ax.fill_between(bin_ctrs, rey_count, step="mid", alpha=0.8, color="red")

ax.tick_params(axis="y", direction="in", which="both")
ax.tick_params(axis="x", direction="in", which="both")
ax.plot(bin_ctrs, reyleigh(bin_ctrs), ls="--", color="black", label="p(y)")


ax.set(
    xlabel="random n",
    ylabel="normalized Prob.",
    xlim=(0, np.max(bin_ctrs)),
    ylim=(0, 1.2),
)
ax.legend(title=r"$N = 1 \times 10^6$")
plt.savefig("./p1_results.png", dpi=200)
plt.show()

problem_2_data = np.loadtxt("./p2_data.txt")
fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(5, 4), dpi=200)

ax.errorbar(
    problem_2_data[:, 0],
    problem_2_data[:, 1],
    yerr=problem_2_data[:, 2],
    fmt="o",
    ms=2,
    lw=1,
    capsize=3,
)
ax.tick_params(axis="y", direction="in", which="both")
ax.tick_params(axis="x", direction="in", which="both")
ax.set(xscale="log", ylabel="Object Mass (kg or arbitrary units)", xlabel="N")
plt.savefig("./p2_results.png", dpi=200)
plt.show()

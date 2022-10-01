import matplotlib.pyplot as plt
import numpy as np


dy_rmajor = np.loadtxt("./dynamic_row_major.dat")
dy_cmajor = np.loadtxt("./dynamic_col_major.dat")
opt_dy_rmajor = np.loadtxt("./dynamic_row_major_optimized.dat")
opt_dy_cmajor = np.loadtxt("./dynamic_col_major_optimized.dat")

st_rmajor = np.loadtxt("./static_row_major.dat")
st_cmajor = np.loadtxt("./static_col_major.dat")

fig, ax = plt.subplots(nrows = 3, ncols = 1, sharex=True,  dpi=200)
plt.subplots_adjust(hspace=0, wspace=0)

ax[0].plot(st_rmajor[:,0], st_rmajor[:,1], label="static row major")
ax[0].plot(st_cmajor[:,0], st_cmajor[:,1], label="static col major")
ax[0].plot(dy_rmajor[:,0], dy_rmajor[:,1], label="dynamic row major")
ax[0].plot(dy_cmajor[:,0], dy_cmajor[:,1], label="dynamic col major")
ax[0].axvline(
    st_cmajor[:,0].max(), 
    ls = "--", 
    color="k", 
    label="static segfault ({:.0f})".format(st_cmajor[:,0].max())
)
print(dy_cmajor[:,1].max() - dy_rmajor[:,1].max())
ax[1].plot(opt_dy_rmajor[:,0], opt_dy_rmajor[:,1], label="optimized dynamic row major")
ax[1].plot(opt_dy_cmajor[:,0], opt_dy_cmajor[:,1], label="optimized dynamic col major")

ax[2].scatter(dy_cmajor[:,0], dy_cmajor[:,1] - dy_rmajor[:,1], s=1, label="dynamic column maj - row maj ")

ax[2].set(yscale="log", xscale="log", xlabel="size n x n matrix", ylabel="time (s)")
ax[0].set(ylabel="execution times (s)",yscale="log",)
ax[1].set(ylabel="execution times (s)", yscale="log",)
ax[0].legend(fontsize=8)
ax[1].legend()
ax[2].legend()

plt.savefig("./results.png",  dpi=300)
plt.show()

import matplotlib.pyplot as plt
import numpy as np


dy_rmajor = np.loadtxt("./dynamic_row_major.dat")
dy_cmajor = np.loadtxt("./dynamic_col_major.dat")
opt_dy_rmajor = np.loadtxt("./dynamic_row_major_optimized.dat")
opt_dy_cmajor = np.loadtxt("./dynamic_col_major_optimized.dat")

st_rmajor = np.loadtxt("./static_row_major.dat")
st_cmajor = np.loadtxt("./static_col_major.dat")

fig, ax = plt.subplots(nrows = 2, ncols = 1, sharex=True,   dpi=200)
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
print(dy_rmajor[:,0].max())

ax[0].plot(opt_dy_rmajor[:,0],  opt_dy_rmajor[:,1], ls = "--", label="optimized dynamic row major")
ax[0].plot(opt_dy_cmajor[:,0],  opt_dy_cmajor[:,1], ls = "--", label="optimized dynamic col major")

ax[1].scatter(dy_rmajor[:,0],  dy_cmajor[:,1] - dy_rmajor[:,1] )

ax[0].set(yscale="log", xscale="log", ylabel="execution times (s)" )
ax[1].set(xlabel="size n x n matrix", ylabel=" col major - row_major (s)")
ax[0].legend(ncol=2, fontsize=10)


plt.savefig("./results.png",  dpi=300)
plt.show()

import numpy as np
import matplotlib.pyplot as plt

add = np.loadtxt("./gcc_double_add_results.dat")
multiply = np.loadtxt("./gcc_double_multiply_results.dat")
power = np.loadtxt("./gcc_pow_results.dat")
sqrt = np.loadtxt("./gcc_sqrt_results.dat")

add_optimized = np.loadtxt("./gcc_optimized_add_results.dat")
sqrt_optimized = np.loadtxt("./gcc_optimized_sqrt_results.dat")

cc_sqrt_optimized = np.loadtxt("cc_optimized_sqrt_results.dat")

fig, ax = plt.subplots(nrows = 2, ncols = 1, sharex=True, sharey=True,  dpi=200)
plt.subplots_adjust(hspace=0, wspace=0)

ax[0].plot(add[:,0], add[:,1], "-o", label= "addition")
ax[0].plot(multiply[:,0], multiply[:,1], "-o", label= "multiplication")
ax[0].plot(sqrt[:,0], sqrt[:,1], "-o", label= "sqrt")
ax[0].plot(power[:,0], power[:,1], "-o", label= "power")
ax[0].legend(ncol=2, fontsize=10) 
ax[0].set_ylabel("execution times (s)")

ax[1].plot(add_optimized[:,0], add_optimized[:,1], "-o", label= "optimized addition")
ax[1].plot(sqrt_optimized [:,0], sqrt_optimized [:,1], "-o", label= "optimized sqrt")
ax[1].plot(cc_sqrt_optimized [:,0], cc_sqrt_optimized[:,1], "--o", label= "cc optimized sqrt")

ax[1].set(yscale="log", xscale="log", xlabel="n loops", ylabel="execution times (s)")
ax[1].legend(fontsize=10) 

plt.savefig("./results.png",  dpi=300)
plt.show()

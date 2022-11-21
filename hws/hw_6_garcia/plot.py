import matplotlib.pyplot as plt
import numpy as np
import os
import sys
import glob
from PIL import Image

if len(sys.argv) != 5:
    print(sys.argv[0], "usage:")
    print("{} data_directory output_directory method eccentricity".format(sys.argv[0]))

    exit()

print("plotting script")
parent_dir = sys.argv[1]
frames_dir = sys.argv[2]
method = sys.argv[3]
eccentricty = sys.argv[4]
data_set = sorted(os.listdir(parent_dir))  # [0:10]

t = []
total_e = []
traj_x_par_1 = []
traj_y_par_1 = []
# traj_z_par_1 = []
traj_x_par_2 = []
traj_y_par_2 = []
# traj_z_par_2 = []
v_r = []
r = []
with plt.style.context("dark_background"):
    with plt.rc_context({"xtick.labelsize": 8, "ytick.labelsize": 8, "font.size": 8}):
        for i, ds in enumerate(data_set):
            print("plotting sequence", ds)
            out = ds.split("_")[-1].split(".")[0]
            data = np.loadtxt(parent_dir + ds)
            time = data[0, 0]
            par_x = data[:, 1]  # all the x coords of all the particles
            par_y = data[:, 2]
            par_z = data[:, 3]

            t.append(time)

            traj_x_par_1.append(par_x[0])
            traj_y_par_1.append(par_y[0])

            traj_x_par_2.append(par_x[1])
            traj_y_par_2.append(par_y[1])

            # x_vel = data[:, 4]
            # y_vel = data[:, 5]
            # z_vel = data[:, 6]
            relative_pos = par2_xyz - par1_xyz
            separation = np.linalg.norm(relative_pos)
            v_rel_rad = np.dot(relative_vel, relative_pos) / separation

            par1_xyz = data[0, 1:3]
            par2_xyz = data[1, 1:3]
            
            par1_vxvyvz = data[0, 4:6]
            par2_vxvyvz = data[1, 4:6]
            
            # par1_vmag = np.sqrt(np.sum(np.square(par1_vxvyvz)))
            # par2_vmag = np.sqrt(np.sum(np.square(par2_vxvyvz)))
            separation = np.linalg.norm(relative_pos)
            
            par1_vmag = np.sqrt(np.sum(par1_vxvyvz**2))
            par2_vmag = np.sqrt(np.sum(par2_vxvyvz**2))
            energy = 0.5 * (par1_vmag**2) + 0.5 * (par2_vmag**2) - (1 / separation)
            total_e.append(energy)

            relative_vel = par2_vxvyvz - par1_vxvyvz
            

            separation = np.linalg.norm(relative_pos)
            v_rel_rad = np.dot(relative_vel, relative_pos) / separation

            r.append(separation)
            v_r.append(v_rel_rad)

            fig, ax = plt.subplots(
                nrows=1,
                ncols=1,
                dpi=200,
                figsize=(4, 4),  # sharex=True, sharey=True
            )
            ax.scatter(par_x[0], par_y[0], zorder=3)
            ax.scatter(par_x[1], par_y[1], zorder=3)
            ax.scatter(0, 0, marker="+", color="k", zorder=3)
            ax.set(
                xlim=(-1.5, 1.5),
                ylim=(-1.5, 1.5),
                # xticklabels=[],
                # yticklabels=[],
            )
            ax.tick_params(direction="in")
            ax.plot(traj_x_par_1, traj_y_par_1, lw=0.8, ls="--", alpha=0.50)
            ax.plot(traj_x_par_2, traj_y_par_2, lw=0.8, ls="--", alpha=0.50)
            ax.text(
                0.05,
                0.85,
                method + "\ne={}".format(eccentricty),
                transform=ax.transAxes,
            )

            phase_plot = ax.inset_axes([1.2, 0.6, 1, 0.4])
            energy_plot = ax.inset_axes([1.2, 0.05, 1, 0.4])

            phase_plot.tick_params(direction="in")
            energy_plot.tick_params(direction="in")

            phase_plot.plot(r, v_r, lw=1, color="magenta", alpha=0.50)
            phase_plot.set(
                xlabel=r"Relative Radial Velocity ($v_r$)",
                ylabel="Separation (r)",
                xlim=(0, 2),
                ylim=(-8, 8),
            )

            energy_plot.plot(t, total_e, lw=1, color="cyan", alpha=0.50)
            # energy_plot.set(xlabel=r"Time", ylabel="Total Energy", ylim=(-1.5, 8))

            # phase_plot.plot()
            # ax.axis("off")
            plt.savefig("./{}/{}.png".format(frames_dir, out), bbox_inches="tight")
            plt.close()


# filepaths

fp_in = "./frog_sequence/*.png"
fp_out = "./{}_{}.gif".format(method, eccentricty)
print(fp_in)
# https://pillow.readthedocs.io/en/stable/handbook/image-file-formats.html#gif
img, *imgs = [Image.open(f) for f in sorted(glob.glob(fp_in))]
print("Processing Frames to a gif...")
img.save(
    fp=fp_out, format="GIF", append_images=imgs, save_all=True, duration=20, loop=0
)
print("Image saved to", fp_out)

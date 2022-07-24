import pandas as pd

data_r = pd.read_csv('log/esti_pi_sttf_regular.txt', sep=' ', header=None)
data_s = pd.read_csv('log/esti_pi_sttf_stratified.txt', sep=' ', header=None)


import matplotlib.pyplot as plt
ax = data_r.T.plot()
data_s.T.plot(ax=ax)
plt.legend(['regular', 'stratified'], loc='center left')
plt.savefig('esti_pi_sttf.png')

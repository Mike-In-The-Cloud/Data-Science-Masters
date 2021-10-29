import matplotlib.pyplot as plt
import pandas as pd

profiles = pd.read_csv('https://tinyurl.com/ChrisCoDV/CustomerProfiles.csv')
print(profiles.head())
print(profiles.describe())

x_min = 0
x_max = 100
bin_width = 10
n_bins = int((bin_width + x_max - x_min) / bin_width)
print(str(n_bins) + ' bins')
bins = [(x_min + x * (bin_width + x_max - x_min) / n_bins) for x in range(int(n_bins))]
# print(bins)

plt.figure(figsize=(8, 8))
plt.hist(profiles['Spending'], bins=bins, edgecolor='w')
plt.title('Spending distribution (£)', fontsize=20)
plt.show()

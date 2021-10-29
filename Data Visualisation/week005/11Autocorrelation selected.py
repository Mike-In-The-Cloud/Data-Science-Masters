# see  https://pandas.pydata.org/pandas-docs/version/0.13.1/visualization.html#autocorrelation-plot
import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv('https://tinyurl.com/ChrisCoDV/Products/DailySales.csv', index_col=0)
pd.plotting.register_matplotlib_converters()
data.index = pd.to_datetime(data.index)
print(data.head())

selected = ['A', 'J', 'S', 'H', 'M', 'O']

for name in selected:
    pd.plotting.autocorrelation_plot(data[name])
    # plt.xlim([0, 50]) # uncomment this line to zoom in
    plt.title('Product ' + name)
    plt.show()

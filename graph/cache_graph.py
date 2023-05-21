from matplotlib import pyplot 
import numpy 
from textwrap import wrap 
import matplotlib.ticker as ticker 
import matplotlib.lines as mlines


data_array = numpy.loadtxt('data.txt', dtype = int)
data_x_cache_size = []
data_y_cache_hits = []
data_y_pss_hits = []
data_y_lru_hits = []
for i in range(int(data_array.size / 4)):
    data_x_cache_size.append(data_array[i][0])
    data_y_cache_hits.append(data_array[i][1])
    data_y_pss_hits.append(data_array[i][2])
    data_y_lru_hits.append(data_array[i][3])


fig, ax = pyplot.subplots(figsize = (16, 10), dpi = 400, linewidth = 2) 

ax.plot(data_x_cache_size, data_y_cache_hits, '--', label = 'cache_hits')
ax.plot(data_x_cache_size, data_y_lru_hits, '-.', label = 'LRU')
ax.plot(data_x_cache_size, data_y_pss_hits, '-', label = 'PSS')
pyplot.legend(("cache_hits", "lru_hits", "pss_hits"))

ax.set_xlabel("Cache size", size = 20) 
ax.set_ylabel("Cache hits", size = 20) 

ax.axis([data_x_cache_size[0], data_x_cache_size[len(data_x_cache_size) - 1] + 10, data_y_cache_hits[0], data_y_cache_hits[len(data_y_cache_hits) - 1] + 10])
ax.set_title('A comparison of PSS and LRU.', size = 20, loc = 'center') 

ax.grid(which='major', color = 'k')
ax.minorticks_on()
ax.grid(which='minor', color = '0.8', linestyle = ':') 

fig.savefig("cache_graph.png")
pyplot.show()
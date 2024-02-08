# Resources Methodology

# sma.csv
* Use Mersenne Twister as the pseudo-random number generator;  
* Set seed to 42;  
* Generate a column with 100 numbers in the interval [0, 1);  
* Calculates the simple moving average (SMA) with window 5;  
* Saves all 100 numbers (first column) and 100 iterations of the SMA (second column) with 6 decimal places.  

## Code Sample  
```python
# !/usr/bin/python3
# -*- coding: utf-8 -*-
import numpy as np

SEED = 42

if __name__ == "__main__":
  np.random.seed(SEED)
  random_nums = np.random.rand(100) 
  window_size = 5
  sma = np.convolve(random_nums, np.ones(window_size)/window_size, mode='valid')
  nan_values = np.full(window_size - 1, np.nan) 
  sma_with_nan = np.concatenate((nan_values, sma))
  data = np.column_stack((random_nums, sma_with_nan))
  np.savetxt('sma.csv', data, delimiter=',', header='Data, SMA', comments='', fmt='%f')
```

# sma-nan.csv  
* Same as "sma.csv" but replaces 10 numbers for not-a-number randomly.  
## Code Sample
```python
# !/usr/bin/python3
# -*- coding: utf-8 -*-
import numpy as np

SEED = 42

if __name__ == "__main__":
  np.random.seed(SEED)
  random_nums = np.random.rand(100) 
  nan_indices = np.random.choice(100, 10, replace=False)
  random_nums[nan_indices] = np.nan
  window_size = 5
  sma = np.array([np.nanmean(random_nums[i:i+window_size]) \
                  for i in range(len(random_nums) - window_size + 1)])
  nan_values = np.full(window_size - 1, np.nan) 
  sma_with_nan = np.concatenate((nan_values, sma))
  data = np.column_stack((random_nums, sma_with_nan))
  np.savetxt('sma-nan.csv', data, delimiter=',', header='Data, SMA', comments='', fmt='%f')
```

# SHA1SUMS
> 2a5a9c4b2c7dbfe9d336c241518d2ab681bd8b79  sma-nan.csv
> c48b8b0b1cd28b6cf32d35daa7c77a93a2f3d3a5  sma.csv

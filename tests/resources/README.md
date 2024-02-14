# Resources Methodology

# sma.csv
* Use Mersenne Twister as the pseudo-random number generator;  
* Set seed to 42;  
* Generate a column with 100 numbers in the interval [0, 1);  
* Calculates the simple moving average (SMA) with window 5;  
* Saves all 100 numbers (first column) and 100 iterations of the SMA (second column) with 12 decimal places.  

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
  np.savetxt('sma.csv', data, delimiter=',', header='Data, SMA', comments='', fmt='%.12f')
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
  np.savetxt('sma-nan.csv', data, delimiter=',', header='Data, SMA', comments='', fmt='%.12f')
```

# mcorr.csv  
* Use Mersenne Twister as the pseudo-random number generator;  
* Set seed to 42;  
* Generate two columns with 100 numbers in the interval [0, 1);  
* Calculates the moving correlation with window 5;  
* Saves all 100 numbers for both columns and 96 iterations of the moving correlation with 12 decimal places. 
* The moving correlation start with the current index. The last "window size-1" values are NAN. 

## Code Sample
```python
# !/usr/bin/python3
# -*- coding: utf-8 -*-
import numpy as np

SEED = 42

if __name__ == "__main__":
  np.random.seed(SEED)
  random_nums_a = np.random.rand(100) 
  random_nums_b = np.random.rand(100) 
  window_size = 5
  mcoor = np.array([np.corrcoef(random_nums_a[i:i+window_size], random_nums_b[i:i+window_size])[0, 1] \
                  for i in range(len(random_nums_a) - window_size + 1)])
  nan_values = np.full(window_size - 1, np.nan) 
  mcoor = np.concatenate((mcoor, nan_values))
  data = np.column_stack((random_nums_a, random_nums_b, mcoor))
  np.savetxt('mcorr.csv', data, delimiter=',', header='A, B, Moving Correlation A and B', comments='', fmt='%.12f')
```


# SHA1SUMS
fbeb357843c725cfb5efdfe8548c1d41e7068441  sma-nan.csv
5bb0905b8e5e21322af3907d7848bd876fb899dd  sma.csv
87188a0ff07313b659f69a6d1605f8b2ca4ce07e  mcorr.csv

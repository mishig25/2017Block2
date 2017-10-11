## Final Project: Parallel Neural Networks
Simple multi-layer perceptron (with one hidden layer) that can predict gender based on voice acoustic properties.
#### Dataset:
* [Gender Recognition by Voice [Kaggle Dataset]](https://www.kaggle.com/primaryobjects/voicegender) - contains 3,168 recorded voice samples with 18 acoustic properties (meanfreq, sfm, peakf, etc.).

#### Contents:
* [Data Cleaner [iPython]](https://github.com/mishig25/2017Block2/blob/master/project/data_cleaner.ipynb) - jupyter notebook that normalizes the data and divides it into train (80%) and test (20%) samples. The samples are stored in [dataset](https://github.com/mishig25/2017Block2/tree/master/project/dataset) folder.
* [Serial Neural Networks [C++]](https://github.com/mishig25/2017Block2/blob/master/project/serial.cpp) - C++ file that contains custom Matrix and Neural Networks classes.
<!-- * [Parallel Neural Networks [C++, CilkPlus]](https://github.com/mishig25/2017Block2/blob/master/project/serial.cpp) - C++ file that contains custom Matrix and Neural Networks classes and uses CilkPlus for parallelization to achieve speedup in execution.  -->

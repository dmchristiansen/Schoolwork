# Program to take normalize spambase dataset,
# and split it into a train and test sets.
# Daniel Christiansen
# CS445

import pandas as pd
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.datasets import dump_svmlight_file

# Read in data from file
data = pd.read_csv('spambase.data', header=None, index_col=57)

# Split data into train & test sets
train_data, test_data = train_test_split(data, test_size=0.5, random_state=69)

# Store in separate files
train_data.to_csv('spambase_train.txt', header=False)
test_data.to_csv('spambase_test.txt', header=False)

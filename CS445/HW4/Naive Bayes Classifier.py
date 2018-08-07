# Daniel Christiansen
# CS 445
# HW 4 - Naive Bayes Classifier

import numpy as np
import pandas as pd
from mpmath import * # For arbitrary precision floats

# Set decimal precision
mp.dps = 1000

# Computes pdf using mpmath arbitrary precision floats to avoid underflow
def pdf(x, mu, sigma):
    x = mpf(x)
    mu = mpf(mu)
    sigma = mpf(sigma)
    return mp.fdiv(mp.exp(mp.fneg(mp.power(mp.fsub(x, mu), 2) / mp.fmul(2, mp.power(sigma, 2)))),
            mp.fmul(mp.sqrt(2*pi), sigma))

if __name__ == "__main__":

    # Get train and test sets
    training_set = pd.read_csv('spambase_train.txt', header=None, index_col=0)
    testing_set = pd.read_csv('spambase_test.txt', header=None, index_col=0)
    test_class = testing_set.index.values
    test_attribute = testing_set.values

    # Calculate prior probability
    class_count = training_set.index.value_counts()
    class_proportion = ([class_count[0]/(class_count[0]+class_count[1]),
                         class_count[1]/(class_count[0]+class_count[1])])

    # Compute mean and std for the training set
    set_mean = training_set.groupby(training_set.index).mean().values
    set_std = training_set.groupby(training_set.index).std(ddof=0).values

    # Rows = actual, Columns = predicted
    confusion_matrix = np.zeros((2, 2), dtype=np.int)

    # Iterate over test set
    for i in range(len(test_class)):
        probability = ([mp.log(class_proportion[0]), mp.log(class_proportion[1])])
        # Calculate probability
        for c in range(2):
            for x in range(57):
                if(set_std[c, x] != 0):
                    pdf_val = pdf(test_attribute[i, x], set_mean[c, x], set_std[c, x])
                    probability[c] = mp.fadd(probability[c], mp.log(pdf_val))
        guess = probability.index(max(probability))
        confusion_matrix[test_class[i], guess] += 1

    # Save confusion matrix
    np.savetxt('confusion_matrix.txt', confusion_matrix, delimiter=',')








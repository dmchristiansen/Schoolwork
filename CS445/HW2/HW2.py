# Daniel Christiansen
# CS 445
# HW 2 - Neural Networks

import csv
import timeit
import numpy as np


class Network:
    def __init__(self, n):
        # initialize random weights in range [-0.05, 0.05]
        self.w_ji = np.random.random((n, 785)) / 10 - 0.05     # input -> hidden
        self.w_kj = np.random.random((10, n + 1)) / 10 - 0.05  # hidden -> output
        # initialize change of weights to use calculate momentum
        self.delta_w_ji = np.zeros((n, 785))
        self.delta_w_kj = np.zeros((10, n + 1))
        self.hidden_size = n

    def sigmoid(self, z):
        return (1 / (1+ (np.exp(-1 * z))))

    def forward_propagate(self, x):
        # propagate inputs to the hidden layer, apply sigmoid function
        hidden = self.sigmoid(np.dot(self.w_ji, x))
        # prepend a '1' to hidden layer values for bias calculation
        hidden_activation = np.insert(hidden, 0, 1)
        # propagate hidden layer activations to output layer, apply sigmoid
        output = self.sigmoid(np.dot(self.w_kj, hidden_activation))
        return hidden, output

    def output_error(self, target, output):
        return output * ( 1 - output) * (target - output)

    def hidden_error(self, delta_k, hidden):
        return hidden * (1 - hidden) * np.delete(np.dot(np.reshape(delta_k, (1, 10)), self.w_kj), 0)

    def update_w_kj(self, delta_k, hidden, delta_w_kj):
        delta_w_kj = eta * np.dot(np.reshape(delta_k, (10, 1)), np.reshape(np.insert(hidden, 0, 1), (1, self.hidden_size + 1))) + alpha * delta_w_kj
        self.w_kj += delta_w_kj
        return delta_w_kj

    def update_w_ji(self, delta_j, inputs, delta_w_ji):
        delta_w_ji = eta * np.dot(np.reshape(delta_j, (self.hidden_size, 1)), np.reshape(inputs, (1, 785))) + alpha * delta_w_ji
        self.w_ji += delta_w_ji
        return delta_w_ji

    def train_network(self, file_name):
        correct = 0
        total = 0
        # open csv file for testing
        with open(file_name, 'r') as train:
            for line in train:
                # create array from input
                x = np.fromstring(line, dtype=float, sep=',')
                # first item in each line will be the class of that example
                answer = int(x[0])
                # the first element of the input array should be a 1, for the bias calculation
                x[0] = 1
                h, o = self.forward_propagate(x)
                guess = np.argmax(o)
                # create array of targets for output layer
                target = np.array([0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1])
                target[answer] = 0.9
                if (guess == answer): correct += 1
                total += 1
                # calculate error in network
                delta_k = self.output_error(target, o)
                delta_j = self.hidden_error(delta_k, h)
                # update the two layers of weights, saving the delta w for the next update's momentum
                self.delta_w_kj = self.update_w_kj(delta_k, h, self.delta_w_kj)
                self.delta_w_ji = self.update_w_ji(delta_j, x, self.delta_w_ji)
        return correct / total

    def test_network(self, file_name):
        correct = 0
        total = 0
        # open csv file for testing
        with open(file_name, 'r') as test:
            for line in test:
                # read in a line from csv file
                x = np.fromstring(line, dtype=float, sep=',')
                # first item in each line will be the class of that example
                answer = int(x[0])
                # the first element of the input array should be a 1, for the bias calculation
                x[0] = 1
                h, o = NN.forward_propagate(x)
                guess = np.argmax(o)
                if (guess == answer): correct += 1
                total += 1
        return correct / total


eta = 0.1     # training rate
alpha = 0.5    # momentum
NN = Network(100)
accuracy = np.zeros((2, 50))

start_time = timeit.default_timer()
for epoch in range(50):
    epoch_start_time = timeit.default_timer()
    training = NN.train_network('mnist_train_scaled.csv')
    accuracy[0][epoch] = NN.test_network('mnist_train_scaled.csv')
    accuracy[1][epoch] = NN.test_network('mnist_test_scaled.csv')
    epoch_stop_time = timeit.default_timer()
    print('training epoch accuracy: ', training)
    print('training set accuracy: ', accuracy[0][epoch])
    print('test set accuracy: ', accuracy[1][epoch])
    print('epoch ', epoch, ' run time: ', epoch_stop_time - epoch_start_time)

stop_time = timeit.default_timer()
print('run time: ', stop_time - start_time)
np.savetxt('alpha_' + str(alpha), accuracy, fmt='%4.4f', delimiter=',', newline='\n')





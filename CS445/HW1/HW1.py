import csv
import random
import timeit

eta = 0.001

starttime = timeit.default_timer()


class Perceptron:
    def __init__(self):
        self.weights = [[((random.random() - 0.5)/10) for i in range(785)] for j in range(10)]

# Preprocessing mnist_train.csv
# Only executes if mnist_train_scaled.csv doesn't already exist
try:
    with open('mnist_train_scaled.csv', 'x') as train_scaled:
        with open('mnist_train.csv', 'r') as train:
            print('opening files')
            linereader = csv.reader(train, quoting=csv.QUOTE_NONNUMERIC)
            linewriter = csv.writer(train_scaled, lineterminator = '\n')
            for i in range(60000):
                data = next(linereader)
                # the first value in each line is the correct answer...
                answer = [data[0]]
                # scale the rest of the inputs as they're read in
                inputs = [data[x]/255 for x in range(1, len(data))]
                linewriter.writerow(answer + inputs)
except FileExistsError:
    print('mnist_train_scaled.csv already exists.')

# Preprocessing mnist_train.csv
# Only executes if mnist_train_scaled.csv doesn't already exist
try:
    with open('mnist_test_scaled.csv', 'x') as test_scaled:
        with open('mnist_test.csv', 'r') as test:
            print('opening files')
            linereader = csv.reader(test, quoting=csv.QUOTE_NONNUMERIC)
            linewriter = csv.writer(test_scaled, lineterminator = '\n')
            for i in range(10000):
                data = next(linereader)
                answer = [data[0]]
                inputs = [data[x]/255 for x in range(1, len(data))]
                linewriter.writerow(answer + inputs)
except FileExistsError:
    print('mnist_test_scaled.csv already exists.')

def test_network(fileName, network, confusionmatrix, fillMatrix):
    # test on the test set for epoch accuracy
    correct, incorrect = 0, 0
    # Open csv files for testing
    with open(fileName, 'r') as test:
        linereader = csv.reader(test, quoting=csv.QUOTE_NONNUMERIC)
        for data in linereader:
            # first value in line will be the correct digit...
            answer = data[0]
            # ...the next 784 values will be the pixel values used as input,
            # with a 1 appended to the front for calculating the bias
            network.inputs = [1] + [data[x] for x in range(1, len(data))]
            # compute w^k*x^k for all ten outputs
            network.outputs = [sum([(network.weights[i][j] * network.inputs[j]) for j in range(785)]) for i in
                               range(10)]
            # select the largest output as the network's 'choice'
            guess = network.outputs.index(max(network.outputs))
            # if that choice was incorrect...
            if (answer != guess):
                incorrect = incorrect + 1
            else:
                correct = correct + 1
            if (fillMatrix == True):
                confusionmatrix[int(answer)][int(guess)] += 1
    return correct

def train_network(fileName, network):
    correct, incorrect = 0, 0
    # Open csv files for training
    with open(fileName, 'r') as train:
        linereader = csv.reader(train, quoting=csv.QUOTE_NONNUMERIC)
        for data in linereader:
            # first value in line will be the correct digit...
            answer = data[0]
            # ...the next 784 values will be the pixel values used as input,
            # with a 1 appended to the front for calculating the bias
            network.inputs = [1] + [data[x] for x in range(1, len(data))]
            # compute w^k*x^k for all ten outputs
            network.outputs = [sum([(network.weights[i][j] * network.inputs[j]) for j in range(785)]) for i in
                               range(10)]
            # select the largest output as the network's 'choice'
            guess = network.outputs.index(max(network.outputs))
            # if that choice was incorrect, adjust weights...
            if (answer != guess):
                incorrect = incorrect + 1
                # expected nextwork output
                t = [0 for i in range(10)]
                t[int(answer)] = 1
                # actual network output
                y = [(1 if network.outputs[i] > 0 else 0) for i in range(len(network.outputs))]
                # adjust weights with formula w_i = w_i + eta(t - y)x_i
                tmy = [eta * (t[i] - y[i]) for i in range(10)]
                for i in range(10):
                    # only recalculate weights for an output unit if it will actually change...
                    if (tmy[i] != 0):
                        network.weights[i] = [(network.weights[i][j] + tmy[i] * network.inputs[j]) for j in range(785)]
            else:
                correct = correct + 1
    return correct

# Steps for training:
# Generate random weights
# Open input files
# For each example k (all 60k training examples) -
#   for all 10 outputs -
#       compute w*x + b
#   select the largest value as the digit predicted
#   if the prediction is correct -
#       do nothing
#   else -
#       for each of the 785 weights for all 10 outputs, calculate w_i = w_i + eta(t - y)x_i, where
#       w_i is a weight
#       eta is the learning rate
#       t = 1 if the output is correct one for this training example, 0 otherwise
#       y = 1 if w*x + b > 0, 0 otherwise
# Once all 60k examples have been computed, one epoch is complete
# Track success rate for training set and run test set through network

network = Perceptron()
epoch = 0
prevaccuracy, accuracy = -1, 0.00
trainaccuracy = []
testaccuracy = []
lastepoch = False
epochcount = 70
confusionmatrix = [[0 for j in range(10)] for i in range(10)]

while (epoch < epochcount and lastepoch == False):
    print('epoch: ', epoch)

    # test network on test data set
    correct = test_network('mnist_test_scaled.csv', network, confusionmatrix, False)
    accuracy = round(correct / 10000, 4)
    print('test set accuracy: ', accuracy)
    testaccuracy.append(accuracy)

    # test network on training data set (without training)
    correct = test_network('mnist_train_scaled.csv', network, confusionmatrix, False)
    accuracy = round(correct / 60000, 4)
    trainaccuracy.append(accuracy)
    print('train set accuracy: ', accuracy)
    if(abs(prevaccuracy - accuracy) < 0.01):
        lastepoch = True
    prevaccuracy = accuracy

    # train network
    correct = train_network('mnist_train_scaled.csv', network)
    accuracy = round(correct / 60000, 4)
    print('testing accuracy: ', accuracy)

    epoch = epoch + 1

# test network on test data set, filling the confusion matrix
correct = test_network('mnist_test_scaled.csv', network, confusionmatrix, True)
accuracy = round(correct / 10000, 4)
print('test accuracy: ', accuracy)
testaccuracy.append(accuracy)

# test network on training data set (without training)
correct = test_network('mnist_train_scaled.csv', network, confusionmatrix, False)
accuracy = round(correct / 60000, 4)
trainaccuracy.append(accuracy)
print('train accuracy: ', accuracy)


with open('training_results.csv', 'w') as results:
    linewriter = csv.writer(results, lineterminator='\n')
    linewriter.writerow('confusionmatrix')
    for i in range(10):
        linewriter.writerow(confusionmatrix[i])
    linewriter.writerow('train accuracy')
    linewriter.writerow(trainaccuracy)
    linewriter.writerow('test accuracy')
    linewriter.writerow(testaccuracy)

stoptime = timeit.default_timer()

print('run time: ', stoptime - starttime)


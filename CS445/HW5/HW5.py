# Daniel Christiansen
# CS 445
# HW 5 - K-Means Clustering

# import training data
# generate random centroid locations
# repeat until centroids stop moving:
#   assign owner to each data point
#   find mean of each data cluster
#   move centroid
#   check centroids for movement and oscillation

import numpy as np
import pandas as pd
import matplotlib.pyplot as mpl

np.set_printoptions(linewidth=500)

# number of centroids
k = 30

# function assigns data points to centroids
def cluster_data(centroids, values):
    clusters = np.zeros((values.shape[0]), dtype=np.int)

    for x in range(0, values.shape[0]):
        distance = [np.linalg.norm(values[x] - centroids[c]) for c in range(0, centroids.shape[0])]
        clusters[x] = distance.index(min(distance))

    return clusters

# function takes data points and cluster they're assigned to and re-calculates centroids
def move_centroids(centroids, clusters, values):
    sum = np.zeros((k, 64), dtype=np.int)
    n = np.zeros((k, 1), dtype=np.int)

    # sum data point components per cluster, number of data points in each cluster
    for i in range(0, values.shape[0]):
        sum[clusters[i]] += values[i]
        n[clusters[i]] += 1

    # average data point components and assign as new centroid
    # if there were no data points assigned to a centroid, do nothing
    for c in range(0, k):
        if(n[c] > 0):
            centroids[c] = sum[c] / n[c]

    return centroids

# function takes current and previous centroids
# evaluates if the centroid has stopped / is oscillating
# updates previous centroid array
def final_clusters(previous, centroids):
    # if centroid is the same as last iteration...
    if np.array_equal(previous[0], centroids):
        final = True
    # or bouncing between two values...
    elif np.array_equal(previous[1], centroids):
        final = True
        print('osc')
    else:
        final = False

    previous[1] = previous[0]
    previous[0] = centroids

    return final

# function computes the average mean square error of a set of centroids
def ave_mse(centroids, clusters, values):

    n = np.zeros((k, 1), dtype=np.int)
    mse = np.zeros((k), dtype=np.int)
    nonempty_clusters = 0
    amse = 0

    for i in range(values.shape[0]):
        mse[clusters[i]] += (np.linalg.norm(values[i] - centroids[clusters[i]]) ** 2)
        n[clusters[i]] += 1

    for c in range(k):
        if n[c] > 0:
            amse += (mse[c] / n[c])
            nonempty_clusters += 1

    return amse / nonempty_clusters

# function to convert centroid values to images
def draw_centroids(centroids, classes):
    # loop through, creating new image for each centroid
    for c in range(centroids.shape[0]):
        cntr = np.uint8(centroids[c].reshape((8, 8)))
        mpl.figure()
        mpl.imshow(cntr, interpolation="nearest", cmap=mpl.cm.Greys)
        mpl.title("Centroid Visualization - Class '" + str(classes[c]) + "'")
        mpl.tight_layout()
        mpl.savefig("centroid visualization " + str(c) + " of " + str(centroids.shape[0]) + ".png")

# function to plot confusion matrix
def plot_cm(confusion):
    mpl.figure()
    mpl.imshow(confusion, interpolation="nearest", cmap=mpl.cm.Greys)
    mpl.title("Confusion Matrix - " + str(k) + " clusters")
    ticks = np.arange(10)
    mpl.xticks(ticks)
    mpl.yticks(ticks)
    mpl.xlabel('Predicted Class')
    mpl.ylabel('True Class')
    for i in range(10):
        for j in range(10):
            mpl.text(j, i, confusion[i][j], horizontalalignment="center",
                     color="black" if confusion[i][j] < (confusion.max() / 2) else "white")
    mpl.tight_layout()
    mpl.savefig("confusion matrix " + str(k) + " clusters.png")


if __name__ == "__main__":

    # import train & test sets
    train_data = pd.read_csv('optdigits.train', header=None, index_col=64)
    test_data = pd.read_csv('optdigits.test', header=None, index_col=64)

    final_centroids = np.zeros((5, k, 64), dtype=np.int)
    final_amse = np.zeros((5), dtype=np.int)

    # finds five sets of k centroids
    for i in range(5):
        # randomly generate centroid locations
        centroids = np.random.random_integers(0, high=16, size=(k, 64))
        previous_centroids = np.zeros((2, k, 64), dtype=np.int)

        # cluster data points and adjust centroids until they stop moving
        while final_clusters(previous_centroids, centroids) == False:
            clusters = cluster_data(centroids, train_data.values)
            centroids = move_centroids(centroids, clusters, train_data.values)

        # save results of current run
        final_centroids[i] = centroids
        final_amse[i] = ave_mse(centroids, clusters, train_data.values)

    # choose the centroid with the lowest average mse
    centroids = final_centroids[final_amse.argmin()]
    clusters = cluster_data(centroids, train_data.values)
    amse = final_amse[final_amse.argmin()]

    # associate centroids with classes
    centroid_classes = np.zeros((k), dtype=np.int)
    class_count = np.zeros((k, 10), dtype=np.int)
    for i in range(len(clusters)):
        class_count[clusters[i]][train_data.index[i]] += 1
    centroid_classes = class_count.argmax(axis=1)

    # delete any centroids with no associated data points
    empty_index = []
    for c in range(k):
        if class_count[c].sum() == 0:
            empty_index.append(c)
    class_count = np.delete(class_count, empty_index, axis=0)
    centroid_classes = np.delete(centroid_classes, empty_index, axis=0)
    centroids = np.delete(centroids, empty_index, axis=0)

    # find mean square separation
    mss = 0
    for i in range(1, centroids.shape[0]):
        for j in range(i, centroids.shape[0]):
            mss += np.linalg.norm(centroids[i-1] - centroids[j]) ** 2
    mss /= (centroids.shape[0] * (centroids.shape[0] - 1) / 2)

    # evaluate test set
    confusion = np.zeros((10, 10), dtype=np.int) # row = actual, column = predicted
    clusters = cluster_data(centroids, test_data.values)
    for i in range(len(clusters)):
        confusion[test_data.index.values[i]][centroid_classes[clusters[i]]] += 1
    correct = 0
    for i in range(10):
        correct += confusion[i][i]
    accuracy = correct / confusion.sum()

    # create and save images
    draw_centroids(centroids, centroid_classes)
    plot_cm(confusion)

    print('mss: ', str(mss))
    print('amse: ', str(amse))
    print('accuracy: ', str(accuracy))



import pickle
import numpy as np
import matplotlib.pyplot as plt
from random import random
import random
import time


def unpickle(file):
    with open(file, 'rb') as f:
        dict = pickle.load(f, encoding="latin1")
    return dict


def class_acc(pred, gt):

    number_of_values = len(pred)
    matching_values = 0
    for i in range(number_of_values):

        if pred[i] == gt[i]:
            matching_values += 1

    accuracy = 100 * (matching_values/number_of_values)
    return accuracy


def cifar10_classifier_random(x):

    number_of_data_points = len(x)
    random_labels = []

    for value in range(number_of_data_points):

        random_labels.append(random.randint(0, 9))

    return random_labels


def cifar10_classifier_1nn(x, trdata, trlabels):

    X = x.astype(np.int32)
    trdata = trdata.astype(np.int32)

    smallest_error = 0
    smallest_error_index = 0

    i = 0
    for row in trdata:
        error_vec = pow(np.subtract(X, row), 2)
        error = np.sum(error_vec)

        if i == 0 or (smallest_error > error):
            smallest_error = error
            smallest_error_index = i

        i += 1

    return trlabels[smallest_error_index]


def test_data(X, training_data, training_labels):

    # container for all predicted labels of the input data
    prediction_data = np.array([])

    start_time = time.time()
    i = 1
    for sample in X:

        print("Test #", i, "/", len(X))

        # add the predicted label into the array
        prediction_data = np.append(prediction_data, cifar10_classifier_1nn(
                sample, training_data, training_labels))

        # Print elapsed time after every 100 tests
        if i % 100 == 0:
            print("Elapsed time:", time.time()-start_time, "seconds")

        i += 1

    return prediction_data


def main():
    start_time = time.time()

    # datadict = unpickle('/home/kamarain/Data/cifar-10-batches-py/data_batch_1')
    # datadict = unpickle('/home/kamarain/Data/cifar-10-batches-py/test_batch')
    testdict = unpickle(
        'C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/test_batch')
    datadict1 = unpickle(
        'C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/data_batch_1')
    datadict2 = unpickle(
        'C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/data_batch_2')
    datadict3 = unpickle(
        'C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/data_batch_3')
    datadict4 = unpickle(
        'C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/data_batch_4')
    datadict5 = unpickle(
        'C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/data_batch_5')

    X1 = datadict1["data"]
    X2 = datadict2["data"]
    X3 = datadict3["data"]
    X4 = datadict4["data"]
    X5 = datadict5["data"]

    Y1 = datadict1["labels"]
    Y2 = datadict2["labels"]
    Y3 = datadict3["labels"]
    Y4 = datadict4["labels"]
    Y5 = datadict5["labels"]

    test_X = testdict["data"]
    test_Y = testdict["labels"]

    training_data = np.concatenate((X1, X2, X3, X4, X5), axis=0)
    training_labels = np.concatenate((Y1, Y2, Y3, Y4, Y5), axis=0)

    print("Size of training data:", len(training_data))

    #sub_sets for faster testing
    #test_X = test_X[1:1000:1]
    #gt = test_Y[1:1000:1]
    #training_data = training_data[1:1000:1]
    #training_labels = training_labels[1:1000:1]

    #pred = cifar10_classifier_random(test_X) #For classifier testing
    #pred = test_data(test_X, test_X, gt)     #For classifier testing

    pred = test_data(test_X, training_data, training_labels)

    gt = test_Y

    #print("(class_acc) test accuracy (should be 100%) is",
    #      class_acc(test_Y, test_Y), "%")

    #rand_labels = cifar10_classifier_random(test_X)
    #print("Accuracy of randomization (should be around 10%) is",
         #class_acc(rand_labels, test_Y), "%")

    accuracy = class_acc(pred, gt)

    elapsed_time = time.time() - start_time
    min = elapsed_time//60
    sec = elapsed_time%60
    print("Classification accuracy is ", str(accuracy), "%")
    print("Time used for the simulation: ", int(min), "min", int(sec), "seconds")


main()

'''
#datadict = unpickle('/home/kamarain/Data/cifar-10-batches-py/data_batch_1')
datadict = unpickle('C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/test_batch')

X = datadict["data"]
Y = datadict["labels"]

labeldict = unpickle('C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/batches.meta')
label_names = labeldict["label_names"]

X = X.reshape(10000, 3, 32, 32).transpose(0,2,3,1).astype("uint8")
Y = np.array(Y)

for i in range(X.shape[0]):
    # Show some images randomly
    if random() > 0.999:
        plt.figure(1);
        plt.clf()
        plt.imshow(X[i])
        plt.title(f"Image {i} label={label_names[Y[i]]} (num {Y[i]})")
        plt.pause(1)
'''
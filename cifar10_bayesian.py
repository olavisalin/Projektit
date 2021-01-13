import pickle
import numpy as np
import matplotlib.pyplot as plt
from random import random
from skimage.transform import rescale, resize, downscale_local_mean
import scipy.stats
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


def cifar10_color(X):

    X_mean = np.zeros((len(X), 3))

    for i in range(X.shape[0]):
        # Convert images to mean values of each color channel
        img = X[i]
        img_1x1 = resize(img, (1, 1))
        r_vals = img_1x1[:, :, 0].reshape(1 * 1)
        g_vals = img_1x1[:, :, 1].reshape(1 * 1)
        b_vals = img_1x1[:, :, 2].reshape(1 * 1)
        mu_r = r_vals.mean()
        mu_g = g_vals.mean()
        mu_b = b_vals.mean()
        X_mean[i, :] = (mu_r, mu_g, mu_b)

        print("Downscaling images", i+1, "/", X.shape[0])

    return X_mean


def cifar10_2x2_color(X):

    X_mean = np.zeros((len(X), 12))

    for i in range(X.shape[0]):
        # Convert images to mean values of each color channel
        img = X[i]
        img_2x2 = resize(img, (2, 2))
        pixels = []
        for j in range(2):
            for k in range(2):
                r_vals = img_2x2[j, k, 0].reshape(1 * 1)
                g_vals = img_2x2[j, k, 1].reshape(1 * 1)
                b_vals = img_2x2[j, k, 2].reshape(1 * 1)
                mu_r = r_vals.mean()
                mu_g = g_vals.mean()
                mu_b = b_vals.mean()
                pixels = np.append(pixels, [mu_r, mu_g, mu_b])

        X_mean[i, :] = pixels
        print("Downscaling images", i+1, "/", X.shape[0])

    return X_mean


def cifar10_NxN_color(X, dimension):

    vec_len = dimension * dimension * 3
    X_mean = np.zeros((len(X), vec_len))

    for i in range(X.shape[0]):
        # Convert images to mean values of each color channel
        img = X[i]
        img_kxk = resize(img, (dimension, dimension))
        pixels = []
        for j in range(dimension):
            for k in range(dimension):
                r_vals = img_kxk[j, k, 0].reshape(1 * 1)
                g_vals = img_kxk[j, k, 1].reshape(1 * 1)
                b_vals = img_kxk[j, k, 2].reshape(1 * 1)
                mu_r = r_vals.mean()
                mu_g = g_vals.mean()
                mu_b = b_vals.mean()
                pixels = np.append(pixels, [mu_r, mu_g, mu_b])

        X_mean[i, :] = pixels
        print("Downscaling images", i+1, "/", X.shape[0])

    return X_mean


def cifar10_naivebayes_learn(Xf, Y):

    mu = {}
    sigma = {}

    # i represents one class (0-9)
    for i in range(10):
        mu[i] = []
        sigma[i] = []
        data_r = []
        data_g = []
        data_b = []

        k = 0
        for sample in Xf:
            classnum = Y[k]
            if classnum == i:
                data_r.append(sample[0])
                data_g.append(sample[1])
                data_b.append(sample[2])
            k += 1

        mu_r = np.mean(data_r)
        mu_g = np.mean(data_g)
        mu_b = np.mean(data_b)

        std_r = np.std(data_r)
        std_g = np.std(data_g)
        std_b = np.std(data_b)

        mu[i] = [mu_r, mu_g, mu_b]
        sigma[i] = [std_r, std_g, std_b]
        print("Learned the data in class", i)

    return mu, sigma


def cifar10_bayes_learn(Xf, Y):

    mu = {}
    sigma = {}

    # i represents one class (0-9)
    for i in range(10):
        mu[i] = []
        sigma[i] = []
        data_rgb = []

        k = 0
        for sample in Xf:
            classnum = Y[k]
            if classnum == i:
                data_rgb.append(sample)
            k += 1

        mu_rgb = np.mean(data_rgb, axis=0)
        cov_rgb = np.cov(data_rgb, rowvar=False)

        mu[i] = mu_rgb
        sigma[i] = cov_rgb
        print("Learned the data in class", i)

    return mu, sigma


def cifar10_classifier_naivebayes(x, mu, sigma):

    highest_probability = 0

    for i in range(10):
        nd_r = scipy.stats.norm.pdf(x[0], loc=mu[i][0], scale=sigma[i][0])
        nd_g = scipy.stats.norm.pdf(x[1], loc=mu[i][1], scale=sigma[i][1])
        nd_b = scipy.stats.norm.pdf(x[2], loc=mu[i][2], scale=sigma[i][2])

        p = nd_r * nd_g * nd_b

        if i == 0 or (highest_probability < p):
            highest_probability = p
            predicted_class = i

    return predicted_class


def cifar10_classifier_bayes(x, mu, sigma):

    highest_probability = 0

    for i in range(10):
        mean = np.asarray(mu[i])
        cov = np.asarray(sigma[i])
        p = scipy.stats.multivariate_normal(mean, cov).pdf(x)

        if i == 0 or (highest_probability < p):
            highest_probability = p
            predicted_class = i

    return predicted_class


def test_data_naivebayes(X, mu, sigma):

    prediction_data = np.array([])
    i = 1
    for sample in X:
        print("Test #", i, "/", len(X))
        prediction_data = np.append(
            prediction_data, cifar10_classifier_naivebayes(sample, mu, sigma))
        i += 1
    return prediction_data


def test_data_bayes(X, mu, sigma):

    prediction_data = np.array([])
    i = 1
    for sample in X:
        print("Test #", i, "/", len(X))
        prediction_data = np.append(
            prediction_data, cifar10_classifier_bayes(sample, mu, sigma))
        i += 1
    return prediction_data


def main():

    start_time = time.time()

    testdict = unpickle('C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/test_batch')
    datadict1 = unpickle('C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/data_batch_1')
    datadict2 = unpickle('C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/data_batch_2')
    datadict3 = unpickle('C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/data_batch_3')
    datadict4 = unpickle('C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/data_batch_4')
    datadict5 = unpickle('C:/Users/oasal/PycharmProjects/Intro_prml/Excercise 2/cifar-10-batches-py/data_batch_5')

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

    X = np.concatenate((X1, X2, X3, X4, X5), axis=0)
    Y = np.concatenate((Y1, Y2, Y3, Y4, Y5), axis=0)

    X = X.reshape(len(X), 3, 32, 32).transpose(0,2,3,1).astype("uint8")
    test_X = test_X.reshape(len(test_X), 3, 32, 32).transpose(0, 2, 3, 1).astype("uint8")

    # Use these two with 1x1 scale
    Xf = cifar10_color(X)
    test_Xf = cifar10_color(test_X)

    # Use these two with 2x2 scale
    #Xf = cifar10_2x2_color(X)
    #test_Xf = cifar10_2x2_color(test_X)

    # Use these two with NxN scale
    #Xf = cifar10_NxN_color(X, 8)
    #test_Xf = cifar10_NxN_color(test_X, 8)

    # Use these two with naive version
    #mu, sigma = cifar10_naivebayes_learn(Xf, Y)
    #pred = test_data_naivebayes(test_Xf, mu, sigma)

    # Use these two with better version
    mu, sigma = cifar10_bayes_learn(Xf, Y)
    pred = test_data_bayes(test_Xf, mu, sigma)

    accuracy = class_acc(pred, test_Y)

    elapsed_time = time.time() - start_time
    min = elapsed_time // 60
    sec = elapsed_time % 60
    print("Classification accuracy is ", str(accuracy), "%")
    print("Time used for the simulation: ", int(min), "min", int(sec),
          "seconds")


"""""
X_mean = np.zeros((10000,3))


for i in range(X.shape[0]):
    # Convert images to mean values of each color channel
    img = X[i]
    img_8x8 = resize(img, (8, 8))        
    img_1x1 = resize(img, (1, 1))
    r_vals = img_1x1[:,:,0].reshape(1*1)
    g_vals = img_1x1[:,:,1].reshape(1*1)
    b_vals = img_1x1[:,:,2].reshape(1*1)
    mu_r = r_vals.mean()
    mu_g = g_vals.mean()
    mu_b = b_vals.mean()
    X_mean[i,:] = (mu_r, mu_g, mu_b)
    
    # Show some images randomly
    if random() > 0.999:
        plt.figure(1);
        plt.clf()
        plt.imshow(img_8x8)
        plt.title(f"Image {i} label={label_names[Y[i]]} (num {Y[i]})")
        plt.pause(1)
        
"""
main()
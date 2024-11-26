#!/usr/bin/env python3

import sys
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

def plot_normal_distribution(mean, std_dev):
    """
    Generate and plot the PDF of a Normal distribution with given mean and standard deviation.
    
    Parameters:
    mean (float): Mean of the distribution (μ)
    std_dev (float): Standard deviation of the distribution (σ)
    """
    # Define the x-axis (values over a range centered around the mean)
    x = np.linspace(mean - 4*std_dev, mean + 4*std_dev, 100)
    
    # Compute the PDF
    pdf = norm.pdf(x, mean, std_dev)
    
    # Plot the PDF
    plt.plot(x, pdf, label=f"Normal(μ={mean}, σ={std_dev})")
    plt.title(f"Normal Distribution PDF (μ={mean}, σ={std_dev})")
    plt.xlabel("x")
    plt.ylabel("Density")
    plt.legend()
    plt.grid()
    plt.show()

def main():
    # Ensure correct number of arguments
    if len(sys.argv) != 3:
        print("Usage: plot_normal.py <mean> <std_dev>")
        sys.exit(1)

    # Parse command-line arguments
    try:
        mean = float(sys.argv[1])
        std_dev = float(sys.argv[2])
    except ValueError:
        print("Error: Both mean and standard deviation must be valid numbers.")
        sys.exit(1)
    
    # Plot the Normal distribution
    plot_normal_distribution(mean, std_dev)

if __name__ == "__main__":
    main()


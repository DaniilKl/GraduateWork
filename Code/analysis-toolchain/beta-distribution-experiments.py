#!/usr/bin/env python3

import sys
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import beta

def plot_beta_distribution(alpha, beta_param):
    """
    Generate and plot the PDF of a Beta distribution with given alpha and beta parameters.

    Parameters:
    alpha (float): Shape parameter α
    beta_param (float): Shape parameter β
    """
    # Define the x-axis (values between 0 and 1)
    x = np.linspace(0, 1, 100)
    
    # Compute the PDF
    pdf = beta.pdf(x, alpha, beta_param)
    
    # Plot the PDF
    plt.plot(x, pdf, label=f"Beta({alpha}, {beta_param})")
    plt.title(f"Beta Distribution PDF (α={alpha}, β={beta_param})")
    plt.xlabel("x")
    plt.ylabel("Density")
    plt.legend()
    plt.grid()
    plt.show()

def main():
    # Ensure correct number of arguments
    if len(sys.argv) != 3:
        print("Usage: plot_beta.py <alpha> <beta>")
        sys.exit(1)

    # Parse command-line arguments
    try:
        alpha = float(sys.argv[1])
        beta_param = float(sys.argv[2])
    except ValueError:
        print("Error: Both alpha and beta must be valid numbers.")
        sys.exit(1)
    
    # Plot the Beta distribution
    plot_beta_distribution(alpha, beta_param)

if __name__ == "__main__":
    main()


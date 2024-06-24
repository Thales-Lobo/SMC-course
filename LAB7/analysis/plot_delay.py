import os
import matplotlib.pyplot as plt
import numpy as np
import argparse

# Define the paths to the result files
RESULTS_DIR = './results'
LOCAL_RESULTS_FILE = os.path.join(RESULTS_DIR, 'local_results.dat')
TCP_RESULTS_FILE = os.path.join(RESULTS_DIR, 'TCP_results.dat')
UDP_RESULTS_FILE = os.path.join(RESULTS_DIR, 'UDP_results.dat')
IMAGES_DIR = './analysis/images'

def parse_results(file_path, delimiter=','):
    """
    Parses the results file and extracts the total time and delta values.
    
    Parameters:
        file_path (str): The path to the results file.
        delimiter (str): The delimiter used in the file to separate values.
        
    Returns:
        list of tuples: A list of (total_time, delta) tuples in milliseconds.
    """
    results = []
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split(delimiter)
            total_time = int(parts[0].split(': ')[1].strip().split()[0]) / 1000  # Convert from microseconds to milliseconds
            delta = int(parts[1].split(': ')[1].strip().split()[0]) / 1000  # Convert from microseconds to milliseconds
            results.append((total_time, delta))
    return results

def compute_statistics(data):
    """
    Computes statistics (mean, variance, standard deviation, min, max) for the delta values.
    
    Parameters:
        data (list of tuples): The parsed results.
        
    Returns:
        dict: A dictionary containing the statistics.
    """
    deltas = [delta for _, delta in data]
    stats = {
        'mean': np.mean(deltas),
        'variance': np.var(deltas),
        'std_dev': np.std(deltas),
        'min': np.min(deltas),
        'max': np.max(deltas)
    }
    return stats

def plot_results(local_results, tcp_results, udp_results, show_local, dpi):
    """
    Plots the delay as a function of time for local, TCP, and UDP results, and saves the plot as an image.
    
    Parameters:
        local_results (list of tuples): The parsed local results.
        tcp_results (list of tuples): The parsed TCP results.
        udp_results (list of tuples): The parsed UDP results.
        show_local (bool): Whether to show the local results in the plot.
        dpi (int): The resolution of the saved plot image.
    """
    # Create images directory if it doesn't exist
    os.makedirs(IMAGES_DIR, exist_ok=True)
    
    plt.figure(figsize=(12, 6), dpi=dpi)
    
    # Extract data for plotting
    tcp_times, tcp_deltas = zip(*tcp_results)
    udp_times, udp_deltas = zip(*udp_results)
    
    # Plot TCP and UDP results
    plt.plot(tcp_times, tcp_deltas, label='TCP', color='green')
    plt.plot(udp_times, udp_deltas, label='UDP', color='red')
    
    # Plot local results if requested
    if show_local:
        local_times, local_deltas = zip(*local_results)
        plt.plot(local_times, local_deltas, label='Local', color='blue', linestyle='--')

    # Compute statistics
    tcp_stats = compute_statistics(tcp_results)
    udp_stats = compute_statistics(udp_results)

    # Add labels and title
    plt.xlabel('Total Time (milliseconds)')
    plt.ylabel('Delta (milliseconds)')
    plt.title('Delay vs. Time')
    plt.legend()

    # Display statistics on the plot
    stats_text = (
        f"TCP:\n"
        f"Mean: {tcp_stats['mean']:.2f} ms\n"
        f"Variance: {tcp_stats['variance']:.2f} ms²\n"
        f"Std Dev: {tcp_stats['std_dev']:.2f} ms\n"
        f"Min: {tcp_stats['min']} ms\n"
        f"Max: {tcp_stats['max']} ms\n\n"
        f"UDP:\n"
        f"Mean: {udp_stats['mean']:.2f} ms\n"
        f"Variance: {udp_stats['variance']:.2f} ms²\n"
        f"Std Dev: {udp_stats['std_dev']:.2f} ms\n"
        f"Min: {udp_stats['min']} ms\n"
        f"Max: {udp_stats['max']} ms"
    )
    
    plt.gcf().text(0.98, 0.5, stats_text, fontsize=10, va='center', ha='right', bbox=dict(facecolor='white', alpha=0.5))
    
    # Save plot as an image with different filenames for local results
    plot_filename = os.path.join(IMAGES_DIR, 'delay_vs_time_local.png' if show_local else 'delay_vs_time.png')
    plt.savefig(plot_filename, dpi=dpi)
    
    # Show plot
    plt.grid(True)
    plt.show()

def main(dpi=100, show_local=False):
    # Parse the result files
    local_results = parse_results(LOCAL_RESULTS_FILE)
    tcp_results = parse_results(TCP_RESULTS_FILE, delimiter='|')
    udp_results = parse_results(UDP_RESULTS_FILE, delimiter='|')
    
    # Plot the results
    plot_results(local_results, tcp_results, udp_results, show_local, dpi)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Plot delay vs. time from result files.')
    parser.add_argument('--dpi', type=int, default=100, help='The resolution of the saved plot image (default: 100).')
    parser.add_argument('--show-local', action='store_true', help='Show local results in the plot.')
    args = parser.parse_args()

    main(dpi=args.dpi, show_local=args.show_local)

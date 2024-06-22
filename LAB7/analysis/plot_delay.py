import os
import matplotlib.pyplot as plt

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
        list of tuples: A list of (total_time, delta) tuples.
    """
    results = []
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split(delimiter)
            total_time = int(parts[0].split(': ')[1].strip().split()[0])
            delta = int(parts[1].split(': ')[1].strip().split()[0])
            results.append((total_time, delta))
    return results

def adjust_local_results(local_results):
    """
    Adjusts the local results by normalizing them to match the scale of external results.
    
    Parameters:
        local_results (list of tuples): The parsed local results.
        
    Returns:
        list of tuples: The adjusted local results.
    """
    scale_factor = 100  # Adjust this factor based on the magnitude difference
    adjusted_results = [(total, delta * scale_factor) for total, delta in local_results]
    return adjusted_results

def plot_results(local_results, tcp_results, udp_results, dpi=500):
    """
    Plots the delay as a function of time for local, TCP, and UDP results, and saves the plot as an image.
    
    Parameters:
        local_results (list of tuples): The parsed and adjusted local results.
        tcp_results (list of tuples): The parsed TCP results.
        udp_results (list of tuples): The parsed UDP results.
        dpi (int): The resolution of the saved plot image.
    """
    # Create images directory if it doesn't exist
    os.makedirs(IMAGES_DIR, exist_ok=True)
    
    plt.figure(figsize=(12, 6), dpi=dpi)
    
    # Extract data for plotting
    local_times, local_deltas = zip(*local_results)
    tcp_times, tcp_deltas = zip(*tcp_results)
    udp_times, udp_deltas = zip(*udp_results)
    
    # Plot the data
    plt.plot(local_times, local_deltas, label='Local (Adjusted)', color='blue', linestyle='--')
    plt.plot(tcp_times, tcp_deltas, label='TCP', color='green')
    plt.plot(udp_times, udp_deltas, label='UDP', color='red')
    
    # Add labels and title
    plt.xlabel('Total Time (microseconds)')
    plt.ylabel('Delta (microseconds)')
    plt.title('Delay vs. Time')
    plt.legend()
    
    # Save plot as an image
    plot_filename = os.path.join(IMAGES_DIR, 'delay_vs_time.png')
    plt.savefig(plot_filename, dpi=dpi)
    
    # Show plot
    plt.grid(True)
    plt.show()

def main(dpi=100):
    # Parse the result files
    local_results = parse_results(LOCAL_RESULTS_FILE)
    tcp_results = parse_results(TCP_RESULTS_FILE, delimiter='|')
    udp_results = parse_results(UDP_RESULTS_FILE, delimiter='|')
    
    # Adjust the local results for better visualization
    adjusted_local_results = adjust_local_results(local_results)
    
    # Plot the results
    plot_results(adjusted_local_results, tcp_results, udp_results, dpi)

if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description='Plot delay vs. time from result files.')
    parser.add_argument('--dpi', type=int, default=100, help='The resolution of the saved plot image (default: 100).')
    args = parser.parse_args()

    main(dpi=args.dpi)

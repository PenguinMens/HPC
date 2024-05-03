import os
import re
import matplotlib.pyplot as plt

def extract_parameters(filename):
    # Regex pattern to match the format and capture nomp, grid, and nsteps
    pattern = r"GOL-loop-\.nomp-(?P<nomp>\d+)\.ngrid-(?P<grid>\d+)x\2\.(?P<nsteps>\d+)"
    
    # Search for the pattern in the filename
    match = re.search(pattern, filename)
    
    # If a match is found, extract the groups
    if match:
        return {
            'nomp': int(match.group('nomp')),
            'grid': int(match.group('grid')),
            'nsteps': int(match.group('nsteps'))
        }
    else:
        return None

def get_last_line_of_file(filepath):
    last_line = None
    times = []
    with open(filepath, 'r') as file:
        for last_line in file:
            row = last_line.split(" ")
            if row[0] == "Elapsed":
                times.append(float(row[2]))
            pass
    if len(times) == 0:
        return None
    times.pop()
    times.pop(0)
    return sum(times) / len(times)

# def get_last_line_of_file(filepath):
#     last_line = None
#     with open(filepath, 'r') as file:
#         for last_line in file:
#             pass
#     if last_line is None:
#         return None
#     time_pattern = r"Elapsed time ([\d.]+) s"
#     match = re.search(time_pattern, last_line)
#     if match:
#         return float(match.group(1))
#     return None

def process_directory(directory):
    results = []
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)
        params = extract_parameters(filename)
        if params:
            elapsed_time = get_last_line_of_file(file_path)
            if elapsed_time is None:
                print(f"Could not extract elapsed time from {file_path}")
                continue
            if params["grid"] == 40000 or params["grid"] == 20000:
                continue
            if elapsed_time:
                results.append({**params, 'elapsed_time': elapsed_time})
    return results

def plot_data(results):
    fig, ax = plt.subplots()
    colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']

    # Group by 'nomp' and sort the groups by 'nomp' values before iterating
    sorted_groups = sorted(group_by(results, 'nomp'), key=lambda x: int(x[0]))

    for idx, (key, group) in enumerate(sorted_groups):
        # Sort the group by grid size
        sorted_group = sorted(group, key=lambda item: item['grid'])
        x = [item['grid'] for item in sorted_group]
        y = [item['elapsed_time'] for item in sorted_group]
        # Plot the sorted data
        ax.plot(x, y, marker='o', linestyle='-', color=colors[idx % len(colors)], label=f'nomp = {key}', markersize=4)
    
    ax.set_xlabel('Grid Size')
    ax.set_ylabel('Elapsed Time (s)')
    ax.set_title('Average iteration vs Grid Size')
    # Sort legend entries
    handles, labels = ax.get_legend_handles_labels()
    handles_labels = sorted(zip(handles, labels), key=lambda t: int(t[1].split(' = ')[1]))
    ax.legend(*zip(*handles_labels))
    plt.show()
def group_by(data, key):
    grouped_data = {}
    for item in data:
        grouped_data.setdefault(item[key], []).append(item)
    return grouped_data.items()

# Example usage
directory_path = 'sentonix_scaling/loop'
results = process_directory(directory_path)
print(results)
plot_data(results)

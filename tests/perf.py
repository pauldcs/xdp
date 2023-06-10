__author__  = 'pducos'
__version__ = '0.0.1'
__date__    = '08/04/2023'
__description__ = 'execute a shell command and generate a performance report'

import subprocess
import time
import statistics

def format_time(time_in_seconds):
    if time_in_seconds >= 1:
        return f'{time_in_seconds:.2f} seconds'
    elif time_in_seconds >= 0.001:
        return f'{time_in_seconds * 1000:.2f} milliseconds'
    else:
        return f'{time_in_seconds * 1000000:.2f} microseconds'

def run_command(cmd, num_runs=20, timeout=None):
    """
    Args:
        cmd (str): The shell command to execute.
        num_runs (int): The number of times to run the command (default: 1).
        timeout (int): The maximum amount of time to wait for the command to complete (in seconds).

    Returns:
        dict: A performance report containing the command, return code, and execution time.
    """
    times = []
    for _ in range(num_runs):
        start_time = time.time()

        try:
            process = subprocess.run(
                cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                shell=True,
                timeout=timeout,
                check=True,
                universal_newlines=True
            )
            return_code = process.returncode
        except subprocess.CalledProcessError as e:
            return {
                'command': cmd,
                'error_message': e.stderr.strip(),
            }

        end_time = time.time()
        times.append(end_time - start_time)

    report = {
        'min_time': format_time(min(times)),
        'max_time': format_time(max(times)),
        'avg_time': format_time(statistics.mean(times)),
    }
    return report

def start_performance_test():
	
	normal = run_command("xdp -n 1000000 /dev/urandom")
	color = run_command("xdp -n 1000000 /dev/urandom -c")
    
	print("\n - Normal:")
	for key in normal:
		print(f'\t{key:<15} {normal[key]}')
	print("\n - Color:")
	for key in normal:
		print(f'\t{key:<15} {color[key]}')
	print()

def main():
	start_performance_test()

if __name__ == "__main__":
    main()

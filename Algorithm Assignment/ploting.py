import time
import random
import matplotlib.pyplot as plt

# Sorting Algorithms

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def quick_sort(arr):
    def _quick_sort(items, low, high):
        if low < high:
            pi = partition(items, low, high)
            _quick_sort(items, low, pi - 1)
            _quick_sort(items, pi + 1, high)

    def partition(items, low, high):
        pivot = items[high]
        i = low - 1
        for j in range(low, high):
            if items[j] <= pivot:
                i += 1
                items[i], items[j] = items[j], items[i]
        items[i + 1], items[high] = items[high], items[i + 1]
        return i + 1

    _quick_sort(arr, 0, len(arr) - 1)

# Timing Function
def time_sorting_algorithm(sort_func, arr):
    start_time = time.time()
    sort_func(arr)
    end_time = time.time()
    return end_time - start_time

# Generate Random Array
def generate_random_array(size):
    return [random.randint(0, 1000) for _ in range(size)]

# Sizes of input arrays
sizes = list(range(100, 1001, 100))  # Input sizes from 100 to 1000 with step size 100

# Collect timing data for insertion sort and quick sort
insertion_sort_times = []
quick_sort_times = []

for size in sizes:
    random_array = generate_random_array(size)

    # Measure execution time for insertion sort
    arr_copy = random_array.copy()
    insertion_sort_time = time_sorting_algorithm(insertion_sort, arr_copy)
    insertion_sort_times.append(insertion_sort_time)

    # Measure execution time for quick sort
    arr_copy = random_array.copy()
    quick_sort_time = time_sorting_algorithm(quick_sort, arr_copy)
    quick_sort_times.append(quick_sort_time)
#Input output pair
print(f"Input size: {size}")
print(f"Insertion Sort Time: {insertion_sort_time:.6f} seconds")
print(f"Quick Sort Time: {quick_sort_time:.6f} seconds")
print("---")


# Plot timing data for insertion sort and quick sort
plt.figure(figsize=(10, 6))

plt.plot(sizes, insertion_sort_times, marker='o', label='Insertion Sort')
plt.plot(sizes, quick_sort_times, marker='o', label='Quick Sort')

plt.xlabel('Input Size (n)')
plt.ylabel('Execution Time (s)')
plt.title('Comparison of Insertion Sort and Quick Sort')
plt.legend()
plt.grid(True)
plt.show()

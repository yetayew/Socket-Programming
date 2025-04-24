import time
import random
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

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

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]

        merge_sort(L)
        merge_sort(R)

        i = j = k = 0

        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

def selection_sort(arr):
    for i in range(len(arr)):
        min_idx = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]

def heap_sort(arr):
    def heapify(arr, n, i):
        largest = i
        l = 2 * i + 1
        r = 2 * i + 2

        if l < n and arr[l] > arr[largest]:
            largest = l

        if r < n and arr[r] > arr[largest]:
            largest = r

        if largest != i:
            arr[i], arr[largest] = arr[largest], arr[i]
            heapify(arr, n, largest)

    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)

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
sizes = list(range(0, 20001, 500))

# Collect timing data for all sorting algorithms
algorithms = {
    "Insertion Sort": insertion_sort,
    "Quick Sort": quick_sort,
    "Merge Sort": merge_sort,
    "Selection Sort": selection_sort,
    "Heap Sort": heap_sort
}

timing_data = {name: [] for name in algorithms}

for size in sizes:
    random_array = generate_random_array(size)
    for name, sort_func in algorithms.items():
        arr_copy = random_array.copy()
        time_taken = time_sorting_algorithm(sort_func, arr_copy)
        timing_data[name].append(time_taken)

# Define polynomial function (e.g., quadratic)
def polynomial(n, a, b, c):
    return a * n**2 + b * n + c

# Fit polynomials to timing data and plot
plt.figure(figsize=(10, 6))

for name, times in timing_data.items():
    # Convert timing data to numpy arrays
    sizes_np = np.array(sizes)
    times_np = np.array(times)

    # Perform curve fitting
    params, _ = curve_fit(polynomial, sizes_np, times_np)

    # Extract coefficients
    a, b, c = params
    fitted_label = f"{a:.6e} * n^2 + {b:.6e} * n + {c:.6e}"

    # Plot the data and the fitted polynomial
    plt.plot(sizes_np, times_np, label=f"{name}")

plt.xlabel('Input Size (n)')
plt.ylabel('f(n)')
plt.title('Comparison of Sorting Algorithms')
plt.legend()
plt.grid(True)
plt.show()
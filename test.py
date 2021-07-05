import merge
import timeit

a = list(range(-1, 1700))
b = list(range(1400, 1800))
def merge1():
   m1 = merge.merge(a, b)
def merge2():
   m2 = list(a + b).sort()

sort_time = timeit.timeit("merge1()", setup="from __main__ import merge1", number=100000)
merge_time = timeit.timeit("merge2()", setup="from __main__ import merge2",number=100000)

print(f'sort took {sort_time} seconds')
print(f'merge took {merge_time} seconds')

import merge
import timeit

a = list(range(-1, 1700))
b = list(range(1400, 1800)) + [19001.1]

a = ["aa","bb","cc","za"]
b = ["ab","bc","ca","zz"]


def merge_test():
   m1 = merge.merge(a, b)

def sort_test():
   m2 = list(a + b).sort()

sort_time = timeit.timeit("sort_test()", setup="from __main__ import sort_test", number=100000)
merge_time = timeit.timeit("merge_test()", setup="from __main__ import merge_test",number=100000)


m2 = list(a + b)
m2.sort()
print(f'sort took {sort_time} seconds')
print(m2)
print(f'merge took {merge_time} seconds')
print(merge.merge(a, b))
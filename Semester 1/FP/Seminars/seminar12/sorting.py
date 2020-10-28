import random
data = list(range(10))
random.shuffle(data)
print(data)
'''
insert sort
    -insert each element into its correct place in a sorted list
'''

def insertSort(data):
    for i in range(1, len(data)):   #data [0:i] is already sorted
        elem = data[i]  #current elem to move
        #figure out where to move elem
        j = i - 1
        while j >= 0 and data[j] > elem :
            data[j+1] = data[j]
            j -= 1
        #insert the element in the correct place
        data[j+1] = elem

'''
WC:
    n = len(data)
    T(n)= sum(i=1, n) i = 1 + 2 + ... + n = n(n+1)/2 belongs to O(n ^ 2)
'''

'''
merge sort
    - devide the list into halves
    - sort the halves
    - merge the 2 halves (merge = interclasare) 
    
T(n) = { 1, n=1
       { 2 T(n/2) + n/2 + n/2 , n>1
'''

def merge(data1, data2):
    pass

def mergeSort(data):
    m = len(data) // 2
    left = mergeSort(data[:m])
    right = mergeSort(data[m:])
    return merge(left, right)


data = list(range(10))
random.shuffle(data)
insertSort(data)
print(data)

'''
binary search
T(n) = { 1, n=1
        { T(n/2) + 1, n > 1
T(n) = T(n/2) + 1
= T(n/ 2^k) +1 + 1 + ... + 1 k times
= 1 + k = 1 + log 2 (n) ~ log 2 (n)
'''
data = [6,-2,-3,1,5,-2,-1,2]

# 10th grade CD yay :)

def maxSum(arr):
    # global = best i've seen so far
    # local = best right now
    global_sum = arr[0]
    for i in range(len(arr)):
        local_sum = arr[i]
        if local_sum > global_sum:
            global_sum = local_sum
        for j in range(i+1, len(arr)):
            local_sum += arr[j]
            if local_sum > global_sum:
                global_sum = local_sum
    return global_sum

#print(maxSum(data))
def dcMiddle(arr,low, high):
    m = (low + high) // 2
    # for loop w partial sums between low and m
    # for loop w partial sums between m and high
    # add mas partial sum in left half to right half and with arr[m] and return it
    pass
def dcMax(arr, low, high):
    if low == high:
        return arr[0]
    m= (low + high)//2
    return max(dcMax(arr, low,m), dcMax(arr, m+1, high), dcMiddle(arr, low, high))

def dpMax(arr):
    # memorization is in max_local
    max_local = arr[0]
    max_global = arr[0]
    for i in range(1, len(arr)):
        max_local = max(arr[i], arr[i] + max_local)
        max_global = max(max_global, max_local)
    return max_global

print(maxSum(data))
print(dpMax(data))

s1 = 'abcd'
s2 = 'axd'

def xform(s1,s2):
    '''
    transform s1-> s2
    character by character, start from the end
    '''

    if len(s1) == 0:
        return len(s2)
    elif len(s2) == 0:
        return len(s1)
    elif s1[-1] == s2[-1]:
        return xform(s1[:-1], s2[:-1])

    #gr8, what know?
    return 1+ min(
    xform(s1[:-1], s2) ,# delete last char of s1
    xform(s1[:-1], s2[:-1]), #replace last char in s1
    xform(s1, s2[:-1])) #insert character at theend

print(xform(s1,s2))
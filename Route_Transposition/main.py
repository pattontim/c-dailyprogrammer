class board:
    def __init__():
        pass

# TODO replace with list comprehension
def buildBoard(unenc, width, height):
    board = []
    for i in range(0, height):
        row = []
        for j in range(0, width):
            flat_loc = (width*i)+j
            if(flat_loc < len(unenc)):
                row.append(unenc[flat_loc].upper())
            else:
                row.append('X')
        board.append(row)
    return board

    # split_arr = [unenc[i::height] for i in range(height)]
    # print(split_arr)
    # [line.upper() for line in []

def finished(actions):
    parsed = [len(action) for action in actions]
    return 1 in parsed

def finishIndex(actions):
    parsed = [len(action) for action in actions]
    for i in range(4):
        if(parsed[i] == 1):
            return i
    return -1

def iterSpiral(enc_board, direction, a, b, c, d):

    # difficult because of arbitrary step values + etc
    # def myApplicator(action, one, two):
        # return lambda action : [action for i in range(d, b+1)]

    return_list = []
    actionList = []
    if(direction):
        while(True):
            actionList = []
            actionList.append([(-1,0) for i in range(a, c-1, -1)])
            d += 1
            actionList.append([(0,1) for i in range(d, b+1)])
            c += 1
            actionList.append([(1,0) for i in range(c, a+1)])
            b -= 1
            actionList.append([(0,-1) for i in range(b, d-1, -1)])
            a -= 1
            fin_index = finishIndex(actionList)
            if(fin_index < 3 and fin_index != -1):
                # trim up to size_1_loc
                actionList = actionList[:fin_index+2]
                return_list.append(actionList)
                break

            return_list.append(actionList)

            # personally generate next
            if(fin_index == 3):
                # first arm
                return_list.append([[(-1,0) for i in range(a, c-1, -1)]])
                break
    else:
        while(True):
            actionList = []
            # for i in range(d, b+1):
            # (b-1, d)
            actionList.append([(0,1) for i in range(d, b+1)])
            a -= 1
            # (c+1,a)
            actionList.append([(-1,0) for i in range(a, c-1, -1)])
            b -= 1
            # (d+1, b)
            actionList.append([(0,-1) for i in range(b, d-1, -1)])
            c += 1
            # (a-1, c)
            actionList.append([(1,0) for i in range(c, a+1)])
            d += 1
            fin_index = finishIndex(actionList)
            if(fin_index < 3 and fin_index != -1):
                # trim up to size_1_loc
                actionList = actionList[:fin_index+2]
                return_list.append(actionList)
                break

            return_list.append(actionList)

            # personally generate next
            if(fin_index == 3):
                # first arm
                return_list.append([[0,1] for i in range(d, b+1)])
                break
            
    # actionList.reverse()
    return return_list
    # return ((a,b,c,d), actionList)
    # print(actionList)

def encSpiral(board, direction, width, height):
    encoded = []
    action_list = []
    iter_loc = (width, 0)
    a = width-1
    b = height-1
    c = 0
    d = 0
    while(not finished(action_list)):
        action_list = iterSpiral(board, direction, a, b, c, d)
        # a -= 1
        # b -= 1
        # c += 1
        # d += 1
        for entry in action_list:
            a = entry[0]
            b = entry[1]
            iter_loc[0] += a
            iter_loc[1] += b
            encoded.append(board[iter_loc[0]][iter_loc[1]])

def inclusive_range(start, stop, step):
    return range(start, stop-1 if start > stop else stop+1, step)

if __name__ == "__main__":
    board = buildBoard("THISISANEXAMPLE", 6, 3)
    print(board)

    # get operating bounds.. TODO FIXME.
    spiral_bounds = iterSpiral(0, True, 5, 2, 0, 0)
    # spiral_bounds_2 = iterSpiral(0, False, 4, 1, 1, 1)

    print(spiral_bounds)
    # print(spiral_bounds_2)
    pass    



    
import re
import logging

class board:
    def __init__():
        pass

# TODO replace with list comprehension
def buildBoard(unenc, width, height):
    # unenc = unenc.replace(' ', '')
    unenc = re.sub('[\W_]', '', unenc)
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

def iterSpiral(enc_board, reversed, a, b, c, d):

    # prototype applicator to simplify calculations
    # difficult because of arbitrary step values + etc
    # def myApplicator(action, one, two):
        # return lambda action : [action for i in range(d, b+1)]

    return_list = []
    actionList = []
    if(reversed):
        while(True):
            actionList = []
            actionList.append([(-1,0) for i in inclusive_range_one_included(a, c, -1)])
            d += 1
            actionList.append([(0,1) for i in inclusive_range_one_included(d, b)])
            c += 1
            actionList.append([(1,0) for i in inclusive_range_one_included(c, a)])
            b -= 1
            actionList.append([(0,-1) for i in inclusive_range_one_included(b, d, -1)])
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
                return_list.append([[(-1,0) for i in inclusive_range_one_included(a, c, -1)]])
                break
    else:
        while(True):
            actionList = []
            # for i in range(d, b+1):
            # (b-1, d)
            actionList.append([(0,1) for i in inclusive_range_one_included(d, b)])
            a -= 1
            # (c+1,a)
            actionList.append([(-1,0) for i in inclusive_range_one_included(a, c, -1)])
            b -= 1
            # (d+1, b)
            actionList.append([(0,-1) for i in inclusive_range_one_included(b, d, -1)])
            c += 1
            # (a-1, c)
            actionList.append([(1,0) for i in inclusive_range_one_included(c, a)])
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
                return_list.append([[0,1] for i in inclusive_range_one_included(d, b)])
                break
            
    # actionList.reverse()
    return return_list
    # return ((a,b,c,d), actionList)
    # print(actionList)

def encSpiral(board, reversed, width, height):
    encoded = []
    action_list = []
    iter_loc = [width-1, -1] if not reversed else [width, 0]
    # iter_loc = [width-1, 0]
    action_list = iterSpiral(board, reversed, width-1, height-1, 0, 0)
    for spiral in action_list:
        for line in spiral:
            for fst, snd in line:
                # encoded.append(board[iter_loc[0]][iter_loc[1]])
                iter_loc[0] += fst
                iter_loc[1] += snd
                encoded.append(board[iter_loc[1]][iter_loc[0]])
    return encoded

def inclusive_range_one_included(start, stop, step=1):
    return range(start, stop-1 if step < 0 else stop+1, step)

if __name__ == "__main__":
    width = 6
    height = 5
    board = buildBoard("why is this professor so boring omg", width, height)
    reversed = True
    encoded = encSpiral(board, reversed, width, height)

    width = 8 
    height = 6
    reversed = True
    assert list("CGNIVLOSHSYMUCHFUNXXMMLEGNELLAOPERISSOAIADRNROGR") == encSpiral(buildBoard("Solving challenges on r/dailyprogrammer is so much fun!!", width, height), reversed, width, height)
    width=4
    height=12
    reversed = False
    assert list("LHSENURBGAISEHCNNOATUPHLUFORCTVABEDOSWDALNTTEAEN") == encSpiral(buildBoard("For lunch let's have peanut-butter and bologna sandwiches", width, height), reversed, width, height)
    width=9
    height=5
    reversed = False
    assert list("IGAMXXXXXXXLETRTIVEEVENWASACAYFSIONESSEDNAMNW") == encSpiral(buildBoard("I've even witnessed a grown man satisfy a camel", width, height), reversed, width, height)
    width=3
    height=14
    reversed = True
    assert list("YHWDSSPEAHTRSPEAMXJPOIENWJPYTEOIAARMEHENAR") == encSpiral(buildBoard("Why does it say paper jam when there is no paper jam?", width, height), reversed, width, height)



    
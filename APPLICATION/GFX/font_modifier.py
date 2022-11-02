import sys

def parseRow(row, height, spaces = 0):

    row_splitted = row.split(',')

    for e in row_splitted:
        try:
            val = int(e, 16)
        except:
            row_splitted.remove(e)
        pass

    row_size = len(row_splitted)
    char_width = row_size / height
    row_outcome = []

    for i in range(row_size):
        if(i > 0 and i % char_width == 0 ):
            for j in range(spaces):
                row_outcome.append('0x00')
                pass
        int_val = int(row_splitted[i], 16)
        if(i >= char_width):
            int_val =  int_val / 4
        row_outcome.append("0x%0.2X" % int(int_val))

        if(i == (row_size - 1)):
            for j in range(spaces):
                row_outcome.append('0x00')
                pass
        pass
    
    return row_outcome

def constructLine(row):
    line = ''
    
    for e in row:
        line = line + e + ', '
        pass
    return line

def main():

    if(len(sys.argv) < 3):
        print("Usage:", sys.argv[0], "<in_file> <ch_height>")
        return -1
    
    in_filename = sys.argv[1]
    char_height = int(sys.argv[2])
    if(len(sys.argv) < 4):
        spaces = 0
    else:
        spaces = int(sys.argv[3])

    inFile = open(in_filename , 'r')
    if(inFile.mode == 'r'):
        lines = inFile.readlines()    
        for l in lines:
            res = parseRow(l, char_height, spaces)
            res = constructLine(res)
            print('   ', res)
            pass

if __name__ == '__main__':
    main()
    

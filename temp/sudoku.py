import time
import sys
from functools import wraps

def show_process_time(method):
    """(5 pts) Method decorator

    Show the processing time of the decorated method
    """
    @wraps(method)
    def wrapper(self, *args, **kwargs):
        start = time.time()
        method(self)
        stop = time.time()
        print(stop - start)


    return wrapper



class Sudoku:
    """Sudoku solver

    A sudoku is represented by a 9x9 matrix. Each element
    in the matrix is an integer value from 1 to 9.

    For example:

            columns
                                      +-----+    +-----+   +-----+
       9,5,7,6,1,3,2,8,4              |9,5,7|    |6,1,3|   |2,8,4|
       4,8,3,2,5,7,1,9,6              |4,8,3|    |2,5,7|   |1,9,6|
    r  6,1,2,8,4,9,5,3,7              |6,1,2|    |8,4,9|   |5,3,7|
    o  1,7,8,3,6,4,9,5,2   ------->   +-----+    +-----+   +-----+
    w  5,2,4,9,7,1,3,6,8   ------->   block0     block1    block2
    s  3,6,9,5,2,8,7,4,1
       8,4,5,7,9,2,6,1,3              +-----+    +-----+   +-----+
       2,9,1,4,3,6,8,7,5              |1,7,8|    |3,6,4|   |9,5,2|
       7,3,6,1,8,5,4,2,9              |5,2,4|    |9,7,1|   |3,6,8|
                                      |3,6,9|    |5,2,8|   |7,4,1|
                                      +-----+    +-----+   +-----+
                                      block3     block4    block5

                                      +-----+    +-----+   +-----+
                                      |8,4,5|    |7,9,2|   |6,1,3|
                                      |2,9,1|    |4,3,6|   |8,7,5|
                                      |7,3,6|    |1,8,5|   |4,2,9|
                                      +-----+    +-----+   +-----+
                                      block6     block7    block8

    A finished sudoku must satisfy following requirements:
        1. Each row consists of a sequence of numbers from 1 to 9
            ,and each digit can only occur once
        2. Each col consists of a sequence of numbers from 1 to 9
            ,and each digit can only occur once
        3. Each block consists of a sequence of numbers from 1 to 9
            ,and each digit can only occur once

    Argument:
        fname (str): sudoku file name
    """
    def __init__(self, fname):
        """(5 pt) Construct the sudoku 2D matrix from file named as 'fname'"""

        with open(fname) as f:
            sudoku = []
            for i in range(9):
                text = f.readline()
                sudoku.append(text.split(',',9))
            for i in range(9):
                for j in range(9):
                    sudoku[i][j] = int(sudoku[i][j])
        self.sudoku = sudoku
        

    def __str__(self):
        """(5 pt) Return printable string representing current sudoku 2D matrix

        For example:

            9 5 7 6 1 3 2 8 4
            4 8 3 2 5 7 1 9 6
            6 1 2 8 4 9 5 3 7
            1 7 8 3 6 4 9 5 2
            5 2 4 9 7 1 3 6 8
            3 6 9 5 2 8 7 4 1
            8 4 5 7 9 2 6 1 3
            2 9 1 4 3 6 8 7 5
            7 3 6 1 8 5 4 2 9
        """
        k = str()
        for i in range(9):
            for j in range(9):
                if j == 8:
                    k = k+str(self.sudoku[i][j])+'\t\n'
                else:
                    k = k+str(self.sudoku[i][j])+' '
            
        return k
    def check_block(self, block_idx):
        """(10 pt) Return True if the block with index 'block_idx' is valid

        Note:
            Refer the docstring of the Sudoku class. `block_idx` is an integer from 0 to 8.
            valid means no repeated numbers in the block except 0
        """
        columns_index = (block_idx % 3)*3
        rows_index = (block_idx // 3)*3
        temp = set()
        for i in range(columns_index,columns_index+3):
            for j in range(rows_index,rows_index+3):
                temp.add(self.sudoku[i][j])
        for i in range(1,10):
            if i not in temp:
                return False
        
        return True

    def check_row(self, row_idx):
        """(5 pt) Return True if the row with index 'row_idx' is valid

        Note:
            Refer the docstring of the Sudoku class. `row_idx` is an integer from 0 to 8.
            valid means no repeated numbers in the row except 0
        """
        temp = set()
        for i in range(9):
            temp.add(self.sudoku[row_idx][i])
        for i in range(1,10):
            if i not in temp:
                return False
        return True
        

    def check_col(self, col_idx):
        """(5 pt) Return True if the col with index 'col_idx' is valid

        Note:
            Refer the docstring of the Sudoku class. `col_idx` is an integer from 0 to 8.
            valid means no repeated numbers in the col except 0
        """
        temp = set()
        for i in range(9):
            temp.add(self.sudoku[i][col_idx])
        for i in range(1,10):
            if i not in temp:
                return False
        return True

    def is_solved(self):
        """(5 pt) Return True if the sudoku is solved

        Note:
            A solve sudoku must satisfy following requirements:
                1. Each row consists of a sequence of numbers from 1 to 9
                    ,and each digit can only occur once
                2. Each col consists of a sequence of numbers from 1 to 9
                    ,and each digit can only occur once
                3. Each block consists of a sequence of numbers from 1 to 9
                    ,and each digit can only occur once
        """
        for i in range(9):
            if self.check_block(i) is False:
                return False
            if self.check_col(i) is False:
                return False
            if self.check_row(i) is False:
                return False
        return True
        

    # Uncomment the line below when you finish the decorator show_process_time
    
    def solver(self,idx):        
        self.cnt += 1
        if (self.cnt % 10000 == 0): print(self.cnt)
        if idx == 81:
            return self.sudoku
        memory = set()
        x = idx%9
        y = idx//9
        block = y//3*3+x//3*3
        if self.sudoku[y][x] == 0:
            for dx in range(9):
                memory.add(self.sudoku[y][dx])
            for dy in range(9):
                memory.add(self.sudoku[dy][x])
            for dx in range(block%3*3):
                for dy in range(block//3*3):
                    memory.add(self.sudoku[dy][dx])
            for i in range(1,10):
                if i not in memory:
                    self.sudoku[y][x] = i
                    return self.solver(idx+1)
            return self.solver(idx-1)
        else:
            return self.solver(idx+1)
    @show_process_time
    def solve(self):
        """(60 pt) Solve the sudoku puzzle automatically

        Note:
            You can define others functions inside this method to help you solve the puzzle
        """
        sys.setrecursionlimit(10**6)
        self.cnt = 0
        self.solver(0)
              

        time.sleep(1.5)
        return self
sudoku2 = Sudoku('sudoku3.txt')
sudoku2.solve()
print("HI")
print(sudoku2)

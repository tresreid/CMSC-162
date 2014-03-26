
class matrix:
    
    #displays the matrix row by row
    def show(self,matrix):
        for item in matrix:
            print item

    #allows for the user to input a matrix taking the number of element in each row and column
    def makeMatrix(self,rowelm,colelm):
        matrix = [];
        print("Numbers are entered one at a time from left to right across the row then top to bottom through each coloum")
        for i in range(int(colelm)):
            print("starting new row")
            row = []
            for j in range(int(rowelm)):
                n = raw_input("num: ")
                row.append(int(n))
            matrix.append(row)
        print("Entered matrix")
        for item in matrix:
            print item
        return matrix

    #makes the nxn indentity matrix taking n as a parameter
    def makeIdentity(self, size):
        m1=[]
        for i in range(size):
            row=[]
            for j in range(size):
                if (i == j):
                    n=1
                else:
                    n=0
                row.append(n)      
            m1.append(row)
        return m1

    # allows matrix addtion
    def addMatrix(self,m1,m2):
        if (len(m1) != len(m2)):
            print("Cannot add matrices. mismatch")
        elif(len(m1[0]) != len(m2[0])):
            print("Cannot add matrices. mismatch")
        else:
            m3=[]
            for i in range(len(m1)):
                row=[]
                for j in range(len(m1[0])):
                    n= m1[i][j] +m2[i][j]
                    row.append(int(n))
                m3.append(row)
            return m3

    # allows scalar multiplication taking the matrix and then the scalar as parameters
    def scalMult(self,m1,scal):
        m2=[]
        for i in range(len(m1)):
            row=[]
            for j in range(len(m1[0])):
                n= (float(scal)* (m1[i][j])) 
                row.append(n)      
            m2.append(row)
        return m2
    
    # creates a transposed matrix of a matrix   
    def transpose(self,m1):
        m2=[]
        for i in range(len(m1[0])):
            row=[]
            for j in range(len(m1)):
                n= ((m1[j][i])) 
                row.append(int(n))    
            m2.append(row)
        return m2
    
    # allows for matrix multiplication
    def multMatrix(self,m1,m2):
        if (len(m1[0]) != len(m2)):
            print("Cannot add matrices. mismatch")
        else:
            m3=[]
            for i1 in range(len(m1)):
                row=[]
                for i2 in range(len(m2[0])):
                    sum=0
                    for j in range(len(m1[0])):
                        x = m1[i1][j] * m2[j][i2]
                        sum+=x
                    row.append(sum)
                m3.append(row)
            return m3
        
    # allows for matrix exponentiation
    def expMatrix(self,m1,power):
        s = self
        m2 = s.makeIdentity(len(m1))
        for i in range(power):
            m2 = s.multMatrix(m1,m2)
        return m2
    
    #returns the determinant of a square matrix
    def detMatrix(self,m1):
        if(len(m1) != len(m1[0])):
            print("Error, not a square matrix")
        else:
            det=0
            if(len(m1) == 1):
                det = m1[0][0]
            elif (len(m1)==2):
                det = (m1[0][0]*m1[1][1])-(m1[1][0]*m1[0][1])
            else:
                dets=[]
                s = self
                for i in range(len(m1)):
                    n = m1[0][i] * s.detMatrix(s.minor(m1,0,i))
                    dets.append(n*((-1)**i))
                det=sum(dets)
            return det
        
    # returns the minor of a matrix taken from the point r,c in the matrix
    def minor(self,m1,r,c):
        m2=[]
        for i in range(len(m1)):
            if (i==r):
                pass
            else:
                row=[]
                for j in range(len(m1[0])):
                    if (j==c):
                        pass
                    else:
                        n= m1[i][j] 
                        row.append(n)        
                m2.append(row)
        return m2

    #creates a cofactor matrix
    def cofactor(self, m1):
       m2=[]
       s = self
       for i in range(len(m1)):
           row=[]
           for j in range(len(m1[0])):
               cofactor= (s.detMatrix(s.minor(m1,i,j)))*((-1)**(i+j)) 
               row.append(cofactor)        
           m2.append(row)
       return m2
           
    # creates the inverse of a matrix
    def inverse(self,m1):
        s= self
        det = s.detMatrix(m1)
        if (det == 0):
            print("Singular matrix. No inverse")
        else:
            m2= s.cofactor(m1)
            m3 = s.transpose(m2)
            m4 = s.scalMult(m3,det**(-1))
        return m4

    # finds the solutions to a system of equations
    def sofeq(self,m1,m2):
        s = self
        if (len(m1) != len(m2)):
            print("Dimension mismatch")
        else:
            if (s.detMatrix(m1) == 0):
                print("Determinate equals 0. Solution not unique or does not exist")
            else:
                m3= s.multMatrix(s.inverse(m1),m2)
                for i in range(len(m3)):
                    print('x', i,' = ',m3[i][0]) 
    
    #returns the trace of a matrix
    def trace(self,m1):
        if (len(m1) != len(m1[0])):
            print("not a square matrix, cannot trace")
        else:
            tra = 0
            for i in range(len(m1)):
                tra += m1[i][i]
        return tra
    
    # checks if the matrix is linearly independant (improvement: make non-linearly independant matrices linearly independant
    def linIndep(self, m1):
        s = self
        if (s.detMatrix(m1) != 0):
            return True
        else:
            return False
        
    # checks if the matrix is symmetrical
    def sym(self, m1):
        s = self
        m2 = s.transpose(m1)
        sym = True
        for i in range(len(m1)):
            for j in range(len(m1[0])):
                if (m1[i][j] == m2[i][j]):
                    pass
                else:
                    sym = False
        return sym
            
    #checks if the matrix is antisymmetrical
    def antisym(self, m1):
        s = self
        m2 = s.transpose(m1)
        antisym = True
        for i in range(len(m1)):
            for j in range(len(m1[0])):
                if (m1[i][j] == -(m2[i][j])):
                    pass
                else:
                    antisym = False
        return antisym

    #checks if the matrix is orthogonal
    def orthogonal(self, m1):
        s = self
        m2 = s.inverse(m1)
        m3 = s.transpose(m1)
        ortho = True
        for i in range(len(m2)):
            for j in range(len(m2[0])):
                if (m2[i][j] == (m2[i][j])):
                    pass
                else:
                    ortho = False
        return ortho


    #rework later
    def nilpotent(self, m1):
        s = self
        nilpotent = s.makeIdentity(len(m1))
        exp = 1
        done = False
        m2 = m1
        while( done ==False):
            for i in range(len(m2)):
                for j in range(len(m2[0])):
                    if (m2[i][j] != 0):
                        done = False
                    else:
                        pass
            m2= s.scalMult(s.expMatrix(m1,exp),float((s.factorial(exp))**(-1)))
            nilpotent = s.addMatrix(nilpotent, m2)
            exp += 1
        return nilpotent

    def factorial(self,n):
        s = self
        if n == 0:
            return 1
        else:
            return n * s.factorial(n-1)
   

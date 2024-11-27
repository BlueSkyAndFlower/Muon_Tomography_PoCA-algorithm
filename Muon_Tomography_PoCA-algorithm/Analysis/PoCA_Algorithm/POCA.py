
#__________________________________________________________________________
#
#                                Function
#                        Point of Closest Approach 
#__________________________________________________________________________
#
#   This is a function to calculate the PoCA point between two lines
#   Two lines are defined by (p1, p2) and (p3, p4).
#                            ^^^^^^^^     ^^^^^^^^ 
#                             Line #1      Line #2
#
#   INPUT: (p1, p2, p3, p4) which are four 3D points "(x,y,z)".
#
#==========================================================================
import math


#########################  self-defined function for scattering point finding  #########################

def Diff(A,B):   # Get the Difference of list'A' and list'B'
    C=[]
    for i in range(len(A)):
        C.append(A[i]-B[i])
    return C

def Divide(A,c):   # Get the result of A/c, A is list and c is constant
    B=[]
    for i in range(len(A)):
        B.append(A[i]/c)
    return B

def Norm(A):   # Get the ||A||_2
    sum=0
    for i in range(len(A)):
        sum+=A[i]*A[i]
    return math.sqrt(sum)

def LineSpace(X_min,X_max,Nx):   # generator a Nx-length list from X_min to X_max
    List=[]
    Bin = (X_max-X_min)/Nx
    for i in range(Nx):
        x=X_min+(i+0.5)*Bin
        List.append(x)
    return List

def GetVoxelCode(P,X_min,Y_min,Z_min,XBin,YBin,ZBin):
    Code=[]
    I = int((P[0]-X_min)/XBin+1)
    J = int((P[1]-Y_min)/YBin+1)
    K = int((P[2]-Z_min)/ZBin+1)
    Code.append(I)
    Code.append(J)
    Code.append(K)
    
    return Code

def GetPosition(VoxelCode,X_min,Y_min,Z_min,XBin,YBin,ZBin):
    Pos=[]
    x = (VoxelCode[0]-0.5)*XBin+X_min
    y = (VoxelCode[1]-0.5)*YBin+Y_min
    z = (VoxelCode[2]-0.5)*ZBin+Z_min
    Pos.append(x)
    Pos.append(y)
    Pos.append(z)
    
    return Pos



# Above is self-defined function for scattering point finding

# later is the main function of POCA.py

def Point(p1,p2,p3,p4,ObjectGeo):

    A=Diff(p1,p2)   # Get the vector of ingoing muon
    B=Diff(p3,p4)   # ... of outgoing muon

    u1 = Divide(A,Norm(A))      # normalize the ingoing muon direction
    u2 = Divide(B,Norm(B))

    
    #########################  Voxelization of Imaging region

    BIN_Num = ObjectGeo[0]      # Get the bin number

    BIN_X=BIN_Num[0]            # Divide Object into ten equal parts in X direction
    BIN_Y=BIN_Num[1]            # Divide Object into ten equal parts in Y direction
    BIN_Z=BIN_Num[2]            # Divide Object into ten equal parts in Z direction

    Range = ObjectGeo[1]        # Get the range 
    X = Range[0]
    X_min = X[0]         # Region of Interest_X_minimum [cm]
    X_max = X[1]         # Region of Interest_X_minimum [cm]
    
    Y = Range[1]
    Y_min = Y[0]         # Region of Interest_Y_minimum [cm]
    Y_max = Y[1]         # Region of Interest_Y_minimum [cm]
    
    Z = Range[2]
    Z_min = Z[0]         # Region of Interest_Z_minimum [cm]
    Z_max = Z[1]         # Region of Interest_Z_minimum [cm]

    XBin=(X_max-X_min)/BIN_X
    YBin=(Y_max-Y_min)/BIN_Y
    ZBin=(Z_max-Z_min)/BIN_Z



    z = LineSpace(Z_min, Z_max, BIN_Z)    # In between two middle detectors (#2 and #3)
    
    P1 = []         # Generates points in the Line #1
    P2 = []         # Generates points in the Line #2

    for i in range(len(z)):
        new_z = []  # Get the z position around z
        new_z.append(z[i]-ZBin/4)
        new_z.append(z[i])
        new_z.append(z[i]+ZBin/4)
        
        for j in range(len(new_z)):
            xc=u1[0]/u1[2]*(new_z[j]-p2[2])+p2[0]   # Get the x value 
            yc=u1[1]/u1[2]*(new_z[j]-p2[2])+p2[1]   # Get the y value
            
            # Avoid scatter point outside the object
            if (xc<X_min or xc>X_max) or (yc<Y_min or yc>Y_max): continue
            P1.append([xc,yc,new_z[j]])     # Record muon path position according to ingoing muon track
            
            xc=u2[0]/u2[2]*(new_z[j]-p3[2])+p3[0]
            yc=u2[1]/u2[2]*(new_z[j]-p3[2])+p3[1]
            if (xc<X_min or xc>X_max) or (yc<Y_min or yc>Y_max): continue
            P2.append([xc,yc,new_z[j]])     # Record muon path position according to outgoing muon track
    
    minD=1e6    # Record Closest distance   
    FlagContinue = False    # Whether skip this muon event

    if (len(P1)<=0 or len(P2)<=0):
        FlagContinue = True     # If no path in interest region, then skip this event data

    if(FlagContinue): 
        VoxelPosition=[0,0,0]   # If it will skip, scattering point don't need
        PointPosition=[0,0,0]
    # If it don't skip, then get the scttering point
    else:
        for i in range(len(P1)):
            for j in range(len(P2)):
                dist= Norm(Diff(P1[i],P2[j]))   # Get the distance between ingoing and outgoing path position
                if dist<minD:
                    minD=dist
                    MinPosition1 = GetVoxelCode(P1[i],X_min,Y_min,Z_min,XBin,YBin,ZBin) # Find the ingoing muon path position of closest position
                    MinPosition2 = GetVoxelCode(P2[j],X_min,Y_min,Z_min,XBin,YBin,ZBin) # ... outgoing ...
        
        VoxelPosition = [int((MinPosition1[0]+MinPosition2[0])/2),int((MinPosition1[1]+MinPosition2[1])/2),int((MinPosition1[2]+MinPosition2[2])/2)] 
        PointPosition = GetPosition(VoxelPosition,X_min,Y_min,Z_min,XBin,YBin,ZBin)
        # Midpoint of MinPosition1 and MinPosition2

    return VoxelPosition,PointPosition,FlagContinue
#__________________________________________________________________________
#
#                                 Function
#                        In and Out Scattering Angle
#__________________________________________________________________________
#
#   This is a function to compute in and out muon angle
#   And the scattered angle from the in/out angles
#
#==========================================================================

import math

# Input: the position of muon on four track detectors
def InOutAngle(p1,p2,p3,p4):

    AngXZ_in  = math.atan((p2[0]-p1[0])/(p2[2]-p1[2]))  #Ingoing angle in the x direction
    AngXZ_out = math.atan((p4[0]-p3[0])/(p4[2]-p3[2]))

    AngYZ_in  = math.atan((p2[1]-p1[1])/(p2[2]-p1[2]))  #Outgoing angle in the x direction
    AngYZ_out = math.atan((p4[1]-p3[1])/(p4[2]-p3[2]))

    DiffAngXZ = AngXZ_out - AngXZ_in    #Scattering angle in the x direction
    DiffAngYZ = AngYZ_out - AngYZ_in


    return DiffAngXZ,DiffAngYZ

# Output: the scattering angle in the x and y direction

#===============================  END  ====================================

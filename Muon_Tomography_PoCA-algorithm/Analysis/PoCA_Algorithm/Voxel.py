import ROOT as r

# Calculate the Root-Mean-Square value of angle distribution
def GetRMS(Angle):

    hist = r.TH1D("hist","Angle [mrad];Count",300,-1500,1500)
    
    for i in Angle:
        hist.Fill(i)
    
    rms = hist.GetRMS()

    hist.SetDirectory(0)
    return rms

# Calculate the scatterng density
def GetSD(Ax,Ay,Momentum,Path_Length):

    P0 = 3000   #MeV/c; The reference momentum is P0
    sd = 0      #Scattering density

    for i in range(len(Momentum)):
        sd += ((Momentum[i]/P0)**2)*(Ax[i]**2 + Ay[i]**2)/(2*Path_Length)
    sd /= len(Momentum)

    return sd


# Statistic the index at different points in POCAs
def Calculate(POCAs,POINTs,AngleX,AngleY,Momentum,Path_Length):
    
    Ps=[]       #Points
    Pos=[]      #Point position
    pl = Path_Length
    Index=[]    #Repeat index of one point
    n=0         #Number of different points

    for i in range(len(POCAs)):
        if POCAs[i] not in Ps:      # Whether the point have been stored in Ps
            Ps.append(POCAs[i])
            Pos.append(POINTs[i])
            Index.append([])
            Index[n].append(i)
            n+=1
        else:
            index = Ps.index(POCAs[i])
            Index[index].append(i)


    # Get the RMS and Scattering density in each scattering points
    XAngle=[]
    YAngle=[]
    SD=[]       #Scattering density
    
    for i in range(len(Ps)):
        Ax=[]
        Ay=[]
        P=[]
        for j in Index[i]:
            Ax.append(AngleX[j]*1000)   # mrad
            Ay.append(AngleY[j]*1000)
            P.append(Momentum[j])
        XAngle.append(GetRMS(Ax))   # anglex width
        YAngle.append(GetRMS(Ay))
        SD.append(GetSD(Ax,Ay,P,pl))    # Scattering density

    return Ps,Pos,XAngle,YAngle,len(Index),SD

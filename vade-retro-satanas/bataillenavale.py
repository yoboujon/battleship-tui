#l'interface graphique du tableau##########
def graphical():
    print(inutile)
    print(un)
    print(deux)
    print(trois)
    print(quatre)
    print(cinq)
    print(six)
    print(sept)
    print(huit)
    print(neuf)
    print(dix)
############################################

#les valeurs et le tableau#################
plouf=0
touched=0
touched9=0
touched2=0
touched4=0
touched8=0
fin=14
s1=0
s3=0
s6=0
s9=0
d2=0
d3=0
d5=0
d9=0
c2=0
c9=0
n2=0
n4=0
n6=0
n8=0
h8=0
t7=0
q4=0
q5=0
inutile=["/",1,"2","3","4","5","6","7","8","9",10]
un=[1]+["O"]*10
deux=[2]+["O"]*10
trois=[3]+["O"]*10
quatre=[4]+["O"]*10
cinq=[5]+["O"]*10
six=[6]+["O"]*10
sept=[7]+["O"]*10
huit=[8]+["O"]*10
neuf=[9]+["O"]*10
dix=[10]+["O"]*10
############################################

while fin != 0:
    graphical()
    if touched==1:
        print("Coulé !")
        touched=0
        fin=fin-1
#le bateau de 2 de la ligne 9###############
    if touched9 ==2:
        print("Coulé !")
        touched9=0
        fin=fin-1
    if touched9 ==1:
        print("Bateau 9 Touché !")
############################################
#le bateau de 2 de la colonne 2#############
    if touched2 ==2:
        print("Coulé !")
        touched2=0
        fin=fin-1
    if touched2 ==1:
        print("Bateau 2 Touché !")
############################################
#le bateau de 2 de la colonne 4#############
    if touched4 ==2:
        print("Coulé !")
        touched4=0
        fin=fin-1
    elif touched4 ==1:
        print("Bateau 4 Touché !")
############################################
#le bateau de 2 de la ligne 8###############
    if touched8 ==2:
        print("Coulé !")
        touched8=0
        fin=fin-1
    if touched8 ==1:
        print("Bateau 8 Touché !")
############################################
    if plouf ==1 :
        print("*Plouf*")
        plouf=0
    print("Il reste "+str(fin)+" bateaux")
    trouve= int(input("Position Colonne = "))
    trouve2= int(input("Position Ligne = "))
    trouvelign=trouve2

#traduction de la coordonnée en valeur######
    if trouve2==1:
        trouve2=un
    elif trouve2==2:
        trouve2=deux
    elif trouve2==3:
        trouve2=trois
    elif trouve2==4:
        trouve2=quatre
    elif trouve2==5:
        trouve2=cinq
    elif trouve2==6:
        trouve2=six
    elif trouve2==7:
        trouve2=sept
    elif trouve2==8:
        trouve2=huit
    elif trouve2==9:
        trouve2=neuf
    elif trouve2==10:
        trouve2=dix
############################################

#les bateaux ou les ploufs##################
    if trouve == 7 and trouvelign == 1:
        if s1!=1:
            trouve2[trouve] = "X"
            touched=1
            s1=1
        else:
            plouf=1
    elif trouve == 2 and trouvelign ==2:
        if d2!=1:
            trouve2[trouve] = "X"
            touched2=touched2+1
            d2=1
        else:
            plouf=1
    elif trouve == 5 and trouvelign ==2:
        if c2!=1:
            trouve2[trouve] = "X"
            touched=1
            c2=1
        else:
            plouf=1
    elif trouve == 9 and trouvelign ==2:
        if n2!=1:
            trouve2[trouve] = "X"
            touched=1
            n2=1
        else:
            plouf=1
    elif trouve == 2 and trouvelign ==3:
        if d3!=1:
            trouve2[trouve] = "X"
            touched2=touched2+1
            d3=1
        else:
            plouf=1
    elif trouve == 7 and trouvelign ==3:
        if s3!=1:
            trouve2[trouve] = "X"
            touched=1
            s3=1
        else:
            plouf=1
    elif trouve == 9 and trouvelign ==4:
        if n4!=1:    
            trouve2[trouve] = "X"
            touched=1
            n4=1
        else:
            plouf=1
    elif trouve == 2 and trouvelign ==5:
        if d5!=1:
            trouve2[trouve] = "X"
            touched=1
            d5=1
        else:
            plouf=1
    elif trouve == 6 and trouvelign ==6:
        if s6!=1:
            trouve2[trouve] = "X"
            touched=1
            s6=1
        else:
            plouf=1
    elif trouve == 9 and trouvelign ==6:
        if n6!=1:    
            trouve2[trouve] = "X"
            touched=1
            n6=1
        else:
            plouf=1
    elif trouve == 3 and trouvelign ==7:
        if t7!=1:
            trouve2[trouve] = "X"
            touched=1
            t7=1
        else:
            plouf=1
    elif trouve == 2 and trouvelign ==9:
        if d9!=1:
            trouve2[trouve] = "X"
            touched=1
            d9=1
        else:
            plouf=1
    elif trouve == 5 and trouvelign ==9:
        if c9!=1:
            trouve2[trouve] = "X"
            touched9=touched9+1
            c9=1
        else:
            plouf=1
    elif trouve == 6 and trouvelign ==9:
        if s9!=1:
            trouve2[trouve] = "X"   
            touched9=touched9+1
            s9=1
        else:
            plouf=1
    elif trouve == 4 and trouvelign ==4:
        if q4!=1:
            trouve2[trouve] = "X"   
            touched4=touched4+1
            q4=1
        else:
            plouf=1
    elif trouve == 4 and trouvelign ==5:
        if q5!=1:
            trouve2[trouve] = "X"   
            touched4=touched4+1
            q5=1
        else:
            plouf=1
    elif trouve == 8 and trouvelign ==8:
        if h8!=1:
            trouve2[trouve] = "X"   
            touched8=touched8+1
            h8=1
        else:
            plouf=1
    elif trouve == 9 and trouvelign ==8:
        if n8!=1:
            trouve2[trouve] = "X"   
            touched8=touched8+1
            n8=1
        else:
            plouf=1
    else:
        trouve2[trouve] = "*"
        plouf=1
############################################
print("Gagné !")
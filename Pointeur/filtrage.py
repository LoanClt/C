#Q1
import matplotlib.pyplot as plt
import numpy as np

listeFrequences = FFT(signal, Te)[0]

plt.hist(listeFrequences)
plt.show()

#Q2
def FFT_inverse(freq, amp, phase, Te, N):
    listeValeurs = []
    for k in range(N):
        E_k = 0
        for i in range(N//2 + 1):
            E_k += amp[i]*np.cos(2*np.pi*i*freq[i]*k*Te/N + phase[i])
        listeValeurs.append(E_k)
    return listeValeurs

#Q3
def passe_bas(w, params):
    return params[1]/(1+1j*w/params[0])

#Q4
def H(w, params):
    return params[1]/(1+1j*w/params[0])

def filtrage(entree, Te, H, params):
    listeFrequences = FFT(entree, Te)[0]
    listeValeursFiltrees = []
    for elt in listeFrequences:
        listeValeursFiltrees.append(H(2*np.pi*elt, params))
    return listeValeursFiltrees

#Q5
params = [...] 
listeValeursEntree = [...]
Te = ...
N = ...
listeValeursFiltrees = filtrage(listeValeursEntree, Te, H, params)
listeValeursTemps = []

for i in range(N):
    listeValeursTemps.append(i*Te)


plt.plot(listeValeursTemps, listeValeursEntree)
plt.plot(listeValeursTemps, listeValeursFiltrees)
plt.show()

#Q6
listeFrequencesNonFiltrees = FFT(listeValeursEntree, Te)[0].pop(2)
listeFrequencesFiltrees = FFT(listeValeursFiltrees, Te)[0].pop(2)

plt.hist(listeFrequencesNonFiltrees)
plt.hist(listeFrequencesFiltrees)

plt.show() #Si Shannon est vérifié + spectre à support borné => Les deux graphiques se superposent parfaitement.

#Q7
#Il suffit de dégager le troisième élément de listeFrequencesNonFiltrees et listeFrequencesFiltrees.
#Le fondamental est en index 0, la première harmo en 1, la deuxième en 2. On peut utiliser la fonction .pop(2).
#En pratique, on prend un passe-bande avec f_0 ~ 2è harmonique avec Q très grand pour bien selectionner la deuxième harmonique
#et ne pas supprimer d'autres fréquences involontairemeent.

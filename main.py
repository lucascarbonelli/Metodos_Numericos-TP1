import scikit-learn
import time
import eliminacion_gauss
import cholesky

def main():
	n = input('cuantas matrices? ')
	corridas = input('cuantas veces queres correrte? 8===D')
	matrices = []
	tiempoXmatrizG = [n]

	for x in xrange(1,n):
		matriz = sklearn.datasets.make_spd_matrix(x**2)
		matrices.append(matriz)
#GAUSSS
	for x in matrices.size():
		for _ in xrange(1,corridas):
			start_time = time.time()
			corrolacosa
			tiempo = time.time() - start_time
			tiempoXmatrizG[x] += tiempo
	
	for x in tiempoXmatrizG.size():
		tiempoXmatrizG[x] = tiempoXmatrizG[x]/float(corridas)
import os
import csv
import math

# Definir el camino de la FIFO
FIFO_PATH = '/tmp/MI_FIFO'

# Función para calcular la distancia entre dos puntos geográficos utilizando la fórmula de Haversine
def haversine(lat1, lon1, lat2, lon2):
    R = 6371  # Radio de la Tierra en kilómetros
    dlat = math.radians(lat2 - lat1)
    dlon = math.radians(lon2 - lon1)
    a = math.sin(dlat/2)**2 + math.cos(math.radians(lat1)) * math.cos(math.radians(lat2)) * math.sin(dlon/2)**2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
    distance = R * c
    return distance

# Crear la FIFO
try:
    os.mkfifo(FIFO_PATH)
except FileExistsError:
    pass

# Crear el proceso hijo
pid = os.fork()

if pid == 0:
    # Este es el proceso hijo
    with open(FIFO_PATH, 'r') as fifo:
        # Leer la posición inicial del drone
        lat1, lon1, _ = fifo.readline().strip().split(',')
        lat1, lon1 = float(lat1), float(lon1)
        distance_total = 0.0

        # Leer las posiciones siguientes del drone y calcular la distancia recorrida
        for line in fifo:
            lat2, lon2, _ = line.strip().split(',')
            lat2, lon2 = float(lat2), float(lon2)
            distance = haversine(lat1, lon1, lat2, lon2)
            distance_total += distance
            print(f'Distancia recorrida: {distance:.2f} km')
            lat1, lon1 = lat2, lon2

        # Imprimir la distancia total recorrida
        print(f'Distancia total recorrida: {distance_total:.2f} km')
else:
    # Este es el proceso padre
    with open('gps_data.csv', 'r') as f:
        reader = csv.reader(f)
        next(reader)  # Saltar la primera fila (encabezado)
        with open(FIFO_PATH, 'w') as fifo:
            # Leer la primera posición del drone y escribirla en la FIFO
            lat1, lon1, _ = next(reader)
            fifo.write(f'{lat1},{lon1}\n')

            # Leer las posiciones siguientes del drone y escribirlas en la FIFO
            for lat2, lon2, _ in reader:
                fifo.write(f'{lat2},{lon2}\n')
                lat1, lon1 = lat2, lon2

    # Esperar a que el proceso hijo termine y luego eliminar la FIFO
    os.wait()
    os.remove(FIFO_PATH)


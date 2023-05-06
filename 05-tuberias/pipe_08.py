import os
import csv
import math

def haversine(lat1, lon1, lat2, lon2):
    R = 6371  # Radio de la Tierra en km
    dLat = math.radians(lat2 - lat1)
    dLon = math.radians(lon2 - lon1)
    lat1 = math.radians(lat1)
    lat2 = math.radians(lat2)
    a = math.sin(dLat/2)**2 + math.cos(lat1)*math.cos(lat2)*math.sin(dLon/2)**2
    c = 2*math.atan2(math.sqrt(a), math.sqrt(1-a))
    d = R*c
    return d

# Crear una tubería
read_pipe, write_pipe = os.pipe()

# Crear un proceso hijo
child_pid = os.fork()

if child_pid == 0:
    # Esto es el proceso hijo
    os.close(write_pipe)
    reader = os.fdopen(read_pipe)
    total_distance = 0
    prev_lat = None
    prev_lon = None
    for line in reader:
        lat, lon = map(float, line.strip().split(','))
        if prev_lat is not None and prev_lon is not None:
            distance = haversine(prev_lat, prev_lon, lat, lon)
            print(f"Distancia del tramo: {distance:.2f} km")
            total_distance += distance
        prev_lat = lat
        prev_lon = lon
    print(f"Distancia total recorrida: {total_distance:.2f} km")
    os.close(read_pipe)
    exit(0)
else:
    # Esto es el proceso padre
    os.close(read_pipe)
    with open('gps_data.csv', 'r') as f:
        reader = csv.reader(f)
        next(reader)  # saltar la primera fila (encabezados)
        for row in reader:
            lat, lon = map(float, row)
            message = f"{lat},{lon}\n"
            os.write(write_pipe, message.encode())
    os.close(write_pipe)
    pid, status = os.waitpid(child_pid, 0)
    print(f'Proceso hijo {child_pid} finalizó con estado {status}')


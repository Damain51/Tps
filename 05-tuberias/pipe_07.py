import os

# Create a pipe
read_pipe, write_pipe = os.pipe()

# Create a child process
child_pid = os.fork()

if child_pid == 0:
    # This is the child process
    os.close(write_pipe)
    # Cierra la escritura de la tuberia
    message = os.read(read_pipe, 1024)
    # Lee el mensaje
    print(f'Received message in child process: {message.decode()}')
    # Lo escribe en pantalla
    os.close(read_pipe)
    # Cierra la lectura
    exit(0)
else:
    # This is the parent process
    os.close(read_pipe)
    # Cierra la lectura
    message = b'Hello from parent process!'
    #Escribe el mensaje
    os.write(write_pipe, message)
    os.close(write_pipe)
    #Cierra la escritura
    pid, status = os.waitpid(child_pid, 0)
    #Muestra el estado en que termina el proceso
    print(f'Child process {child_pid} finished with status {status}')

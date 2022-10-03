# Informe Lab 02 - Grupo 18
- Ayala Facundo (facundo.ayala@mi.unc.edu.ar)
- Bonfils Gastón Tomás (gastonbonfils@mi.unc.edu.ar)
- Longhi Heredia Fabrizio Mateo (fabrizio.longhi@mi.unc.ecu.ar)
- Lozano Benjamín (benjamin.lozano@mi.unc.edu.ar)

# Contenido

* [Metodología de trabajo](#Metodología-de-trabajo)
* [Introducción](#Introducción)
* [Syscalls que utilizamos](#Syscalls-que-utilizamos)
* [Desarrollo](#Desarrollo)


## Metodología de trabajo

Para la realizacion del laboratorio organizamos encuentros virtuales diarios, usando la plataforma discord en donde cada integrante comentaba en que pudo avanzar y si se encontraba con alguna dificultad. Por otro lado, para consultas más casuales utilizamos la plataforma de mensajeria telegram.

Con respecto a la divisón de tareas, cada integrante se encargó de implementar una system call del semáforo. Luego respecto al programa de usuario ping-pong lo realizamos en conjunto debido a que su implementacion era más larga.

Por último, para el control de versionado utilizamos la plataforma bitbucket



## Introducción
Implementamos un semáforo en el sistema operativo riscv-xv6 añadiendo las syscalls:
* `sem_open`
* `sem_close`
* `sem_up`
* `sem_down`

Además creamos el programa de usuario `pingpong` para poner a prueba el uso de los semáforos.


## Syscalls que utilizamos
Para poder implementar los semáfotos le dimos uso a varias syscalls ya implementadas en xv6, entre las cuales usamos:
* `lock` : Es un objeto que posee dos operaciones: acquire() y release(). Este objeto tiene dos estados: bloqueado (lock) o desbloqueado (not locked)
* `acquire()`: Hacer un llamado a esta funcion con un parámetro espera hasta que este parametro se encuentre desbloqueado, luego lo bloquea y lo devuelve.
* `release()`: Hacer un llamado a esta funcion con un parámetro desbloquea dicho parámetro permitiendo que otros procesos puedan tomarlo
* `sleep()`: Toma un puntero y un `lock`. Se duerme el último proceso que se llamo.
* `wakeup()`: Toma un puntero. Se despiertan los procesos dormidos.
* `argint()`: Es una funcion propia de xv6 que nos permite pasarle argumentos a las funciones desde el espacio de usuario al espacio de kernel (system calls), esto es dado a que en xv6 no es posible hacerlo de forma directa. 


## Desarrollo
En un principio había un problema de concurrencia, ya que usabamos dos forks y un semaforo, de este modo el problema que surgia el problema de `race condition` por lo que aveces teniamos desorden en el programa de pingpong, o recibiamos dos veces seguidas lo mismo. (Solo pondremos la parte de los forks)
El codigo era de esta manera:
```c
int pid_a = fork();
if (pid_a < 0) {
    printf("erroraso del fork \n");
    exit(1);
    }
else if (pid_a == 0){
    for(unsigned int i = 0; i < rally; i++){
        int a = sem_down(0);
        if (a == 0){
            printf("erroraso del sem_down \n");
            exit(1);
            }
        printf("ping \n");
        int b = sem_up(0);
        if(b == 0){
        printf("erroraso del sem_up \n");
        exit(1);
        }
    }
    exit(0);
  }

int pid_b = fork();
if (pid_b < 0) {
    printf("erroraso del fork \n");
  }
  else if (pid_b == 0){
    for(unsigned int i = 0; i < rally; i++){
      int a = sem_down(0);
      if (a == 0){
        printf("erroraso del sem_down \n");
        exit(1);
      }      
      printf("pong \n");
      int b = sem_up(0);
      if(b == 0){
        printf("erroraso del sem_up \n");
        exit(1);
      }     
    }
    exit(0);
  }
  if (pid_a >0 || pid_b>0) {
    wait(0);
  }
  wait(0); 
```

Luego, optamos por usar un solo fork, despues de releer la consigna, pero seguimos utilizando un solo semaforo. El problema persistia, por lo que luego de debuggear y probar soluciones, optamos por la solucion definitiva: Un fork y dos semaforos, como se puede ver en el main(), el codigo luce asi:

```c 
 int pid = fork();
  if (pid < 0) {
    printf("erroraso del fork \n");
    exit(1);
  }
  if (pid > 0) { 
    for (uint i = 0; i < rally; i++) {
      int err_down = sem_down(0);      
      if (err_down == 0) {
        printf("Erroraso del down del padre \n");
        exit(1);
      }
      printf("ping \n"); 

      int err_up = sem_up(9);        
      if (err_up == 0) {
        printf("Erroraso del up al hijo desde el padre \n");
        exit(1);
      }
    } 
  }

  else if (pid == 0) {
    for (uint i = 0; i < rally; i++) {
      int err_down = sem_down(9);    
      if (err_down == 0) {
        printf("Erroraso del down del beibi \n");
        exit(1);
      }
      printf("          pong \n"); 

      int err_up = sem_up(0);   
      if (err_up == 0) {
        printf("Erroraso del up al padre desde el hijitus \n");
        exit(1);
      }
    } 
    exit(0); 
  }

  wait(0);
```


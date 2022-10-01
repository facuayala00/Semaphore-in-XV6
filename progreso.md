Archivos que no hay que tocar mas
`syscall.h`
`syscall.c`
`usys.pl`
`user.h`
`defs.h`  

Los contenidos de `sysproc.c` y `proc.c` se movieron todos a `semaphore.c`   
Para esto se agregó una linea al `Makefile`   
Ahora todo se puede trabajar en `semaphore.c`  c:

nuevos cambios:
* Se agrego manejo de errores en ambos archivos 
* Se agrego un if que hace un wait a los procesos hijos que arregla el problema del close
 
Issues:
* en `sem_open` ver que no se abra uno ya abierto  
* en `sem_close` ver qeu no se cierre uno en uso  (Estos los daria por hechos pero capaz sean autores de fallo)
* en `sem_down` se sufre de starvation si se llama en 0
* en pingpong se resolvio el problema del close pero hay que revisar el funcionamiento.
* Problema de concurrencia respecto al punto anterior

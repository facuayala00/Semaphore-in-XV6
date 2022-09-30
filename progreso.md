Archivos que no hay que tocar mas
`syscall.h`
`syscall.c`
`usys.pl`
`user.h`
`defs.h`  

Los contenidos de `sysproc.c` y `proc.c` se movieron todos a `semaphore.c`   
Para esto se agregó una linea al `Makefile`   
Ahora todo se puede trabajar en `semaphore.c`  c:

nuevos cambios   

Ahora el pingpong anda pero quedan por ver estos casos de error  

* en `sem_open` ver que no se abra uno ya abierto  
* en `sem_close` ver qeu no se cierre uno en uso  
* en `sem_down` se sufre de starvation si se llama en 0
* alguna que otra cosa mas
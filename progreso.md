Archivos que no hay que tocar mas
`syscall.h`
`syscall.c`
`usys.pl`
`user.h`
`defs.h`  

Los contenidos de `sysproc.c` y `proc.c` se movieron todos a `semaphore.c`   
Para esto se agregó una linea al `Makefile`   
Ahora todo se puede trabajar en `semaphore.c`  c:
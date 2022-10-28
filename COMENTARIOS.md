## Informe 
- La explicación de las syscalls es demasiado breve, faltan elementos importantes del funcionamiento, por ejemplo de qué hace sleep con el lock
- Bien que explican algunas dificultades pero esos bloques de código son muy grandes, lo mejor ahí era usar pseudocódigo
- Debería decir como decidieron implementar los semáforos (un arreglo global con un solo lock, etc...)

## Repo 
- Bien distribuidos los commits
- Usen `.gitignore`

## Código
- En general bien
- No hacen chequeo de args
- No hacen chequeo de índice negativo
- Pueden ahorrar wakeups llamandolo sólo cuando el valor del semáforo pasa de 0 a 1
- Se pueden ahorrar el caso `sem_array[sem].value > 0` en `sem_down`
- Semáforos inactivos con valor negativo les ahorraría un campo en la `struct`
- En pingpong deberían inicializar el segundo semáforo en 1, no llamar a `sem_down` 
- Bien registrados los uprogs pero hicieron lío con las syscalls

## Funcionalidad
- `pingpong` bien
- semáforos correctos
